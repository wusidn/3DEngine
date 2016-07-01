#pragma once
#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__


#include <GL/glew.h>
#include <string>
#include <list>

#include "Object.h"
#include "Shader.h"


using namespace std;

class ShaderProgram : public Object
{
public:
    CREATEFUNC(ShaderProgram);
    static ShaderProgram * create(const list<const Shader *> & shaderList);
    
    //添加shader
    const bool attachShader(const Shader & shader) const;
    //删除shader
    const bool detachShader(const Shader & shader) const;
    
    //链接shader程序
    const bool linkProgram(void) const;
    
    //获取错误信息
    const string getErrorInfo(void) const;
    
    //获取shader程序id
    const unsigned int programId(void) const;
    
protected:

    ShaderProgram(void){}
    
    virtual const bool init(void);
    const bool init(const list<const Shader *> & shaderList);
    
private:
    unsigned int _programId;
    
    //链接是否成功
    const bool linkIsSuccessful(void) const;

};

#endif //__SHADER_PROGRAM_H__