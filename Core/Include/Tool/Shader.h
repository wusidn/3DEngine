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

    friend class ShaderProgram;
    
    CREATEFUNC(Shader);
    static Shader * create(const string & code, const enum ShaderType type);    
    
    //编译shader
    const bool compile(void) const;
    
    //获取shaderId
    const unsigned int shaderId(void) const;
    
protected:

    Shader(void){}
    virtual const bool init(void);
    virtual const bool init(const string & code, const enum ShaderType type);
     
private:
    GLuint _shaderId;
    
    
    //编译是否成功
    const bool compileIsSuccessful(void) const;
    
};

#endif //__SHADER_H__