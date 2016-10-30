#pragma once
#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__


#include <GL/glew.h>
#include <string>
#include <list>
#include <vector>

#include "Object.h"
#include "Shader.h"

using namespace std;

namespace engine
{
    namespace tools
    {
        class ShaderProgram : public Object
        {
        public:
            
            static ShaderProgram & create(const list<const Shader *> & shaderList);
            static ShaderProgram & create(const string & vShaderPath, const string & fShaderPath);
            static ShaderProgram & create(const vector<string> & vShaderFiles, const vector<string> & fShaderFiles);

            static ShaderProgram & createTemplat(void);
            
            //添加shader
            const bool attachShader(const Shader & shader) const;
            //删除shader
            const bool detachShader(const Shader & shader) const;
            
            //链接shader程序
            const bool linkProgram(void) const;

            //启用着色器
            const bool use(void) const;
            
        protected:

            CREATEFUNC(ShaderProgram);

            ShaderProgram(void){}
            
            virtual const bool init(void);
            virtual const bool init(const list<const Shader *> & shaderList);
            virtual const bool init(const string & vShaderPath, const string & fShaderPath);
            
        private:
            unsigned int _programId;
            
            //链接是否成功
            const bool linkIsSuccessful(void) const;

        };
    }
}

#endif //__SHADER_PROGRAM_H__