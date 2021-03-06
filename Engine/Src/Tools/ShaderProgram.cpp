#include "ShaderProgram.h"
#include "LogManager.h"
#include "File.h"

namespace engine
{
    namespace tools
    {

        //着色器缓存池
        map<string, ShaderProgram *> ShaderProgram::shaderProgramsPool;

        ShaderProgram & ShaderProgram::create(const vector<const Shader *> & shaderList)
        {

            //* 待实现 __着色器缓存池__

            ShaderProgram & result = create();
            bool shaderProgramInit = result.init(shaderList);

            assert(shaderProgramInit);

            if(!shaderProgramInit){ result.initializeError(1); }
            return result;
        }

        ShaderProgram & ShaderProgram::create(const string & vShaderPath, const string & fShaderPath)
        {

            //* 待实现 __着色器缓存池__

            ShaderProgram & result = create();
            bool shaderProgramInit = result.init(vShaderPath, fShaderPath);

            assert(shaderProgramInit);

            if(!shaderProgramInit){ result.initializeError(1); }
            return result; 
        }

        ShaderProgram & ShaderProgram::create(const vector<string> & vShaderFiles, const vector<string> & fShaderFiles)
        {

            //* 待实现 __着色器缓存池__

            ShaderProgram & result = create();
            bool shaderProgramInit = result.init(vShaderFiles, fShaderFiles);

            assert(shaderProgramInit);

            if(!shaderProgramInit){ result.initializeError(1); }
            return result; 
        }

        ShaderProgram & ShaderProgram::createTemplat(void)
        {
            ShaderProgram & result = create();
            
            bool shaderProgramInit = result.init("", "");

            if(!shaderProgramInit){ result.initializeError(1); }
            return result; 
        }

        const bool ShaderProgram::init(void)
        {
            if(!Object::init()){ return false; }

            _programId = glCreateProgram();
            if(glIsProgram(_programId) != GL_TRUE){ return false; }

            return true;
        }

        const bool ShaderProgram::init(const vector<const Shader *> & shaderList)
        {
            for(auto item : shaderList)
            {
                if(!item->compileIsSuccessful())
                {
                    Log.error("ShaderProgram::init Shader Is Not Compiled!");
                    return false;
                }

                if(!attachShader(*item)){ return false; }
            }
            
            return true;
        }

        const bool ShaderProgram::init(const string & vShaderPath, const string & fShaderPath)
        {
        
            Shader & vertexShader = vShaderPath.size() <= 0 ? Shader::create(ShaderType::vertex) : Shader::create(vShaderPath, ShaderType::vertex);
            if(!vertexShader.compile()){ return false; }

            Shader & fragmentShader = fShaderPath.size() <= 0 ? Shader::create(ShaderType::fragment) : Shader::create(fShaderPath, ShaderType::fragment);
            if(!fragmentShader.compile()){ return false; }

            attachShader(vertexShader);
            attachShader(fragmentShader);
            linkProgram();

            if(!linkIsSuccessful()){ return false; }
            
            return true;
        }

        const bool ShaderProgram::init(const vector<string> & vShaderFiles, const vector<string> & fShaderFiles)
        {
            Shader & vertexShader = vShaderFiles.size() <= 0 ? Shader::create(ShaderType::vertex) : Shader::create(vShaderFiles, ShaderType::vertex);
            if(!vertexShader.compile()){ return false; }

            Shader & fragmentShader = fShaderFiles.size() <= 0 ? Shader::create(ShaderType::fragment) : Shader::create(fShaderFiles, ShaderType::fragment);
            if(!fragmentShader.compile()){ return false; }

            attachShader(vertexShader);
            attachShader(fragmentShader);
            linkProgram();

            if(!linkIsSuccessful()){ return false; }
            return true;
        }

        ShaderProgram::ShaderProgram(void)
        {
            _programId = 0;
        }


        const bool ShaderProgram::attachShader(const Shader & shader) const
        {
            const unsigned int shaderId = shader.shaderId();
            if(!shaderId)
            {
                Log.error("# ShaderProgram::attachShader #  Shader Is Not legitimate!");
                return false;
            }
            glAttachShader(_programId, shaderId);
            return true;
        }

        const bool ShaderProgram::detachShader(const Shader & shader) const
        {
            const unsigned int shaderId = shader.shaderId();
            if(!shaderId)
            {
                Log.error("# ShaderProgram::detachShader #  Shader Is Not legitimate!");
                return false;
            }
            glDetachShader(_programId, shaderId);
            return true;
        }

        const bool ShaderProgram::linkProgram(void) const
        {
            glLinkProgram(_programId);

            GLint linked;
            glGetProgramiv(_programId, GL_LINK_STATUS, &linked);
            if(linked == GL_TRUE){ return true; }

            GLint info_len = 0;
            glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &info_len);
            if(!info_len){ Log.error("# ShaderProgram::linkProgram #  Not Fined Error Info"); }

            GLchar * buff = new GLchar[info_len];
            glGetProgramInfoLog(_programId, info_len, nullptr, buff);
            Log.error("# ShaderProgram::linkProgram #  {0}", buff);
            delete [] buff;

            return false;
        }

        const bool ShaderProgram::use(void) const
        {
            if(!linkIsSuccessful()){ return false; }
            glUseProgram(_programId);
            return true;
        }


        // const unsigned short ShaderProgram::uniformSizeOf(const char * unformName) const
        // {
        //     if(!linkIsSuccessful()){ return false; }
            
        //     GLuint uboIndex = glGetUniformLocation(_programId, unformName);
        //     if(uboIndex == GL_INVALID_INDEX){
        //         Log.error("unifrom name is invalid");
        //         return 0;
        //     }

        //     GLint uboSize;
        //     GLuint uniformIndices;
        //     glGetActiveUniformsiv((const GLuint )_programId, uboIndex, &uniformIndices, nullptr, &uboSize);

        //     return (unsigned short)uboSize;
        // }

        const bool ShaderProgram::uniformSet(const char * uniformName, const float & s) const 
        {
            GLuint uboIndex = getUniformLocation(uniformName);
            if(!uboIndex) return false;

            glUniform1f(uboIndex, s);
            return true;
        }
        const bool ShaderProgram::uniformSet(const char * uniformName, const Vec4 & v) const 
        {
            GLuint uboIndex = getUniformLocation(uniformName);
            if(!uboIndex) return false;

            glUniform4fv(uboIndex, 4, &v[0]);
            return true;
        }
        const bool ShaderProgram::uniformSet(const char * uniformName, const Matrix4 & m) const 
        {
            GLuint uboIndex = getUniformLocation(uniformName);
            if(!uboIndex) return false;

            glUniformMatrix4fv(uboIndex, 16, false, &m[0][0]);
            return true;
        }

        GLuint ShaderProgram::getUniformLocation(const char * name) const 
        {
            GLuint uboIndex = 0;

            if(!linkIsSuccessful()){ return uboIndex; }
            
            uboIndex = glGetUniformLocation(_programId, name);
            if(uboIndex == GL_INVALID_INDEX)
            {
                Log.error("unifrom name is invalid");
                return uboIndex;
            }

            return uboIndex;
        }

        const bool ShaderProgram::linkIsSuccessful(void) const
        {
            if(glIsProgram(_programId) != GL_TRUE){ return false; }

            GLint linked;
            glGetProgramiv(_programId, GL_LINK_STATUS, &linked);
            if(linked != GL_TRUE){ return false; }
            
            return true;
        }

        const unsigned short ShaderProgram::typeSize(const GLenum type)
        {
            unsigned short result;
            #define CASE(Enum, Count, Type) case Enum : result = Count * sizeof(Type); break;

            switch (type) {
                CASE(GL_FLOAT, 1, GLfloat);
                CASE(GL_FLOAT_VEC2, 2, GLfloat);
                CASE(GL_FLOAT_VEC3, 3, GLfloat);
                CASE(GL_FLOAT_VEC4, 4, GLfloat);

                CASE(GL_INT, 1, GLint);
                CASE(GL_INT_VEC2, 2, GLint);
                CASE(GL_INT_VEC3, 3, GLint);
                CASE(GL_INT_VEC4, 4, GLint);

                CASE(GL_UNSIGNED_INT, 1, GLuint);
                CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
                CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
                CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);

                CASE(GL_BOOL, 1, GLboolean);
                CASE(GL_BOOL_VEC2, 1, GLboolean);
                CASE(GL_BOOL_VEC3, 1, GLboolean);
                CASE(GL_BOOL_VEC4, 1, GLboolean);

                CASE(GL_FLOAT_MAT2, 4, GLfloat);
                CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
                CASE(GL_FLOAT_MAT2x4, 8, GLfloat);

                CASE(GL_FLOAT_MAT3, 9, GLfloat);
                CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
                CASE(GL_FLOAT_MAT3x4, 12, GLfloat);

                CASE(GL_FLOAT_MAT4, 16, GLfloat);
                CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
                CASE(GL_FLOAT_MAT4x3, 12, GLfloat);

             #undef CASE

            default:
                result = -1;
                break;

            }

            return result;
        }
    }
}