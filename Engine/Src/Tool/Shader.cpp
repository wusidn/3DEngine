#include "Shader.h"
#include "LogManager.h"


namespace engine::tool{

    Shader * Shader::create(const string & code, const enum ShaderType type)
    {
        Shader * result = new Shader();
        if(!result->init() || !result->init(code, type))
        {
            delete result;
            result = nullptr;
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
        assert(_shaderId == GL_TRUE);

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
}