#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <GL/glew.h>

#include "Object.h"
#include "File.h"

using namespace std;


namespace engine
{
    namespace tools
    {
        enum ShaderType{
            vertex = GL_VERTEX_SHADER,
            fragment = GL_FRAGMENT_SHADER
        };

        class Shader : public Object
        {
        public:

            friend class ShaderProgram;
            
            static Shader & create(const enum ShaderType type);
            static Shader & create(const string & fileName, const enum ShaderType type);    
            
            //编译shader
            const bool compile(void) const;
            
            //获取shaderId
            const unsigned int shaderId(void) const;
            
        protected:

            CREATEFUNC(Shader);

            Shader(void){}
            virtual ~Shader(void);
            virtual const bool init(void);
            virtual const bool init(const enum ShaderType type);
            virtual const bool init(const string & fileName, const enum ShaderType type);
            
        private:
            GLuint _shaderId;

            //ShaderTemplateCode
            static string vertexShaderCode(void);
            static string fragmentShaderCode(void);

            static string globalCodeKey, mainCodeKey;
            
            //编译是否成功
            const bool compileIsSuccessful(void) const;
            
        };
    }
}

#endif //__SHADER_H__