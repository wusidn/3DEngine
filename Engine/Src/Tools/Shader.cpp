#include "Shader.h"
#include "LogManager.h"
#include <cassert>

using namespace std;

namespace engine
{
    namespace tools
    {
        Shader & Shader::create(const string & code, const enum ShaderType type)
        {
            Shader & result = create();
            bool shaderInit = result.init(code, type);

            assert(shaderInit);

            if(shaderInit){
                result.initializeError(1);
            }
            return result;
        }

        const bool Shader::init(void)
        {
            if(!Object::init()){
                return false;
            }
            _shaderId = 0;
            return true;
        }

        const bool Shader::init(const string & code, const enum ShaderType type)
        {

            _shaderId = glCreateShader(type);
            if(glIsShader(_shaderId) != GL_TRUE){
                return false;
            }

            const GLchar * source = code.c_str();
            glShaderSource(_shaderId, 1, &source, nullptr);

            return true;
        }

        const bool Shader::compile(void) const
        {
            glCompileShader(_shaderId);

            GLint compiled = 0;
            glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compiled);
            if(compiled == GL_TRUE){
                return true;
            }

            GLint infoLen = 0;
            glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infoLen);

            if(infoLen == 0){
                Log.error("# Shader::compile #  Not Fined Error Info");
                return false;
            }

            GLchar * buff = new GLchar[infoLen];
            glGetShaderInfoLog(_shaderId, infoLen, nullptr, buff);

            Log.error("# Shader::compile #  {0}", buff);
            delete [] buff;

            return false;
        }

        const unsigned int Shader::shaderId(void) const
        {
            if(!compileIsSuccessful()){
                return 0;
            }
            return _shaderId;
        }

        const bool Shader::compileIsSuccessful(void) const
        {
            if(glIsShader(_shaderId) != GL_TRUE){
                return false;
            }
            GLint compiled = 0;
            glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compiled);
            return compiled == GL_TRUE;
        }

        Shader::~Shader(void)
        {
            if(glIsShader(_shaderId) == GL_TRUE){
                glDeleteShader(_shaderId);
            }
        }
    }
}