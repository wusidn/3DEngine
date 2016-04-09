#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include "Object.h"
#include <GL/glew.h>

using namespace std;

enum ShaderType{
    vertex = GL_VERTEX_SHADER,
    fragment = GL_FRAGMENT_SHADER
};

class Shader : public Object
{
public:
    
    CREATEFUNC(Shader);
    static Shader * create(const string & code, const enum ShaderType type);    
    virtual const bool init(void);
    virtual const bool init(const string & code, const enum ShaderType type);
    
    const bool compile(void) const;
    const string getErrorInfo(void) const;
    
    const unsigned int shaderId(void) const;
     
private:
    GLuint _shaderId;
    const bool compileIsSuccessful(void) const;
};

#endif //__SHADER_H__