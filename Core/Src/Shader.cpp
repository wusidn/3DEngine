#include "../Include/Shader.h"

Shader * Shader::create(const string & code, const enum ShaderType type)
{
    Shader * result = new Shader();
    if(!result->init() || !result->init(type, code))
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
    shaderId = 0;
    return true;
}

const bool Shader::init(const string & code, const enum ShaderType type)
{
    if(glIsShader(shaderId = glCreateShader(type) != GL_TRUE){
        return false;
    }
    const GLchar * source = code.c_str();
    glShaderSource(shaderId, 1, &source, nullptr);
    return true;
}

const bool Shader::compile(void) const
{
    glCompileShader(shaderId);
    return compileIsSuccessful();
}

const string Shader::getErrorInfo(void) const
{
    if(glIsShader(shaderId) != GL_TRUE){
        return "ShaderElement Create failed Or Delegated";
    }
    
    GLint compiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
    if(compiled == GL_TRUE){
        return "Shader Compile Successful";
    }
    
    GLint infolen = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);
    if(infoLen == 0){
        return "Not Fined Error Info";
    }
    GLchar * buff = new GLchar[infolen];
    if(!buff){
        return "Get Error Info Fail";
    }
    glGetShaderInfoLog(shaderId, infoLen, nullptr, buff);
    string result(buff);
    delete buff;
    return result;
}

const unsigned int Shader::shaderId(void) const
{
    if(!compileIsSuccessful()){
        return 0;
    }
    return shaderId;
}

const bool Shader::compileIsSuccessful(void) const
{
    if(glIsShader(shaderId) != GL_TRUE){
        return false;
    }
    GLint compiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
    return compiled == GL_TRUE;
}