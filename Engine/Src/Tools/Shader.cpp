#include "Shader.h"
#include "LogManager.h"
#include "File.h"
#include "Appaction.h"
#include <cassert>

using namespace std;

namespace engine
{
    namespace tools
    {
        Shader & Shader::create(const enum ShaderType type)
        {
            Shader & result = create();
            bool shaderInit = result.init(type);

            assert(shaderInit);

            if(shaderInit){
                result.initializeError(1);
            }
            return result;
        }

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

        const bool Shader::init(const enum ShaderType type)
        {

            string source;
            _shaderId = glCreateShader(type);
            if(glIsShader(_shaderId) != GL_TRUE){
                return false;
            }

            switch(type)
            {
            case ShaderType::vertex:
                source = vertexShaderCode();
                break;
            case ShaderType::fragment:
                source = fragmentShaderCode();
                break;
            default:
                Log.error("Unknown Shader Type");
                return false;
            }

            const GLchar * p_source = source.c_str();
            glShaderSource(_shaderId, 1, &p_source, nullptr);

            return true;
        }

        const bool Shader::init(const string & code, const enum ShaderType type)
        {

            string source;
            _shaderId = glCreateShader(type);
            if(glIsShader(_shaderId) != GL_TRUE){
                return false;
            }

            switch(type)
            {
            case ShaderType::vertex:
                source = vertexShaderCode();
                break;
            case ShaderType::fragment:
                source = fragmentShaderCode();
                break;
            default:
                Log.error("Unknown Shader Type");
                return false;
            }

            //
            string removeAfterCode = code;

            //模板与shader组合
            static regex searchAnnotationRegex("#[^\n]*\n|//[^\n]*\n|/\\*[\\s\\S]*?\\*/");
            smatch searchResult;

            auto matchBegin = sregex_iterator(code.begin(), code.end(), searchAnnotationRegex);
            auto matchEnd = sregex_iterator();
            for(auto item  = matchBegin; item != matchEnd; ++item){
                removeAfterCode.erase(removeAfterCode.find(item->str()), item->str().size());
            }

            // regex_search(code, searchResult, searchAnnotationRegex);
            // for(auto item : searchResult)
            // {
            //     Log.info("erase: {0}", item.str());
            //     removeAfterCode.erase(removeAfterCode.find(item), item.str().size());
            // }

            Log.info("-----------{0}", removeAfterCode);

             
            const GLchar * p_source = source.c_str();
            glShaderSource(_shaderId, 1, &p_source, nullptr);

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

        string Shader::vertexShaderCode(void)
        {
            static string result = File::readAllText(Appaction::instance().appactionPath() + "Shader/template.vert");
            return result;
        }

        string Shader::fragmentShaderCode(void)
        {
            static string result = File::readAllText(Appaction::instance().appactionPath() + "Shader/template.frag");
            return result;
        }
    }
}