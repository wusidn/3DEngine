#include "Shader.h"

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
    if(glIsShader(_shaderId = glCreateShader(type)) != GL_TRUE){
        return false;
    }
    const GLchar * source = code.c_str();
    glShaderSource(_shaderId, 1, &source, nullptr);
    return true;
}

const bool Shader::compile(void) const
{
    glCompileShader(_shaderId);
    return compileIsSuccessful();
}

const string Shader::getErrorInfo(void) const
{
    
    if(compileIsSuccessful()){
        return "";
    }
    
    if(glIsShader(_shaderId) != GL_TRUE){
        return "ShaderElement Create failed Or Delegated";
    }
    
    GLint infoLen = 0;
    glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infoLen);
    if(infoLen == 0){
        return "Not Fined Error Info";
    }
    GLchar * buff = new GLchar[infoLen];
    glGetShaderInfoLog(_shaderId, infoLen, nullptr, buff);
    
    string result(buff);
    delete [] buff;
    return result;
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