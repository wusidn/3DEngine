#include "ShaderProgram.h"
#include "LogManager.h"

#include <cassert>

using namespace std;

namespace engine::tools{

    ShaderProgram & ShaderProgram::create(const list<const Shader *> & shaderList)
    {
        ShaderProgram & result = create();
        assert(!result.init(shaderList));
        return result; 
    }

    const bool ShaderProgram::init(void)
    {
        if(!Object::init()){
            return false;
        }
        _programId = glCreateProgram();
        assert(glIsProgram(_programId) == GL_TRUE);

        return true;
    }

    const bool ShaderProgram::init(const list<const Shader *> & shaderList)
    {
        for(auto item = shaderList.begin(); item != shaderList.end(); ++item){
            if(!(*item)->compileIsSuccessful()){
                Log.error("ShaderProgram::init Shader Is Not Compiled!");
                return false;
            }
            if(!attachShader(**item)){
                return false;
            }
        }
        
        return true;   
    }

    const bool ShaderProgram::attachShader(const Shader & shader) const
    {
        const unsigned int shaderId = shader.shaderId();
        if(!shaderId){
            Log.error("# ShaderProgram::attachShader #  Shader Is Not legitimate!");
            return false;
        }
        glAttachShader(_programId, shaderId);
        return true;
    }

    const bool ShaderProgram::detachShader(const Shader & shader) const
    {
        const unsigned int shaderId = shader.shaderId();
        if(!shaderId){
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
        if(linked == GL_TRUE){
            return true;
        }

        GLint info_len = 0;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &info_len);
        if(!info_len){
            Log.error("# ShaderProgram::linkProgram #  Not Fined Error Info");
        }

        GLchar * buff = new GLchar[info_len];
        glGetProgramInfoLog(_programId, info_len, nullptr, buff);
        Log.error("# ShaderProgram::linkProgram #  {0}", buff);
        delete [] buff;

        return false;
    }

    const bool ShaderProgram::linkIsSuccessful(void) const
    {
        if(glIsProgram(_programId) != GL_TRUE){
            return false;
        }
        GLint linked;
        glGetProgramiv(_programId, GL_LINK_STATUS, &linked);
        if(linked != GL_TRUE){
            return false;
        }
        return true;
    }
}