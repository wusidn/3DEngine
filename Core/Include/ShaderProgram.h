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
    
    virtual const bool init(void);
    const bool init(const list<const Shader *> & shaderList);
    
    const bool attachShader(const Shader & shader) const;
    const bool detachShader(const Shader & shader) const;
    
    const bool linkProgram(void) const;
    const string getErrorInfo(void) const;
    
    const unsigned int programId(void) const;
    
private:
    unsigned int _programId;
    const bool linkIsSuccessful(void) const;

};

#endif //__SHADER_PROGRAM_H__