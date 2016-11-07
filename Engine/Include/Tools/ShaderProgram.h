#pragma once
#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__


#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>

#include "Object.h"
#include "Shader.h"
#include "Vec4.h"
#include "Matrix4.h"

using namespace std;

namespace engine
{
    namespace tools
    {
        class ShaderProgram : public Object
        {
        public:
            
            static ShaderProgram & create(const vector<const Shader *> & shaderList);
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

            //uniform变量
            // const unsigned short uniformSizeOf(const char * unformName) const;
            const bool uniformSet(const char * uniformName, const float & s) const;
            const bool uniformSet(const char * uniformName, const Vec4 & v) const;
            const bool uniformSet(const char * uniformName, const Matrix4 & m) const;

            
        protected:

            CREATEFUNC(ShaderProgram);

            ShaderProgram(void);
            
            virtual const bool init(void);
            virtual const bool init(const vector<const Shader *> & shaderList);
            virtual const bool init(const string & vShaderPath, const string & fShaderPath);
            virtual const bool init(const vector<string> & vShaderFiles, const vector<string> & fShaderFiles);

            GLuint getUniformLocation(const char * name) const;
            
        private:
            unsigned int _programId;
            
            //链接是否成功
            const bool linkIsSuccessful(void) const;
            static map<string, ShaderProgram *> shaderProgramsPool;

            //tools
            static const unsigned short typeSize(const GLenum type);

        };
    }
}

#endif //__SHADER_PROGRAM_H__