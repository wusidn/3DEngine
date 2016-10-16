#include "ShaderProgram.h"
#include "LogManager.h"
#include "File.h"

namespace engine
{
    namespace tools
    {
        ShaderProgram & ShaderProgram::create(const list<const Shader *> & shaderList)
        {
            ShaderProgram & result = create();
            bool shaderProgramInit = result.init(shaderList);

            assert(shaderProgramInit);

            if(!shaderProgramInit){
                result.initializeError(1);
            }
            return result;
        }

        ShaderProgram & ShaderProgram::create(const string & vShaderPath, const string & fShaderPath)
        {
            ShaderProgram & result = create();
            bool shaderProgramInit = result.init(vShaderPath, fShaderPath);

            assert(shaderProgramInit);

            if(!shaderProgramInit){
                result.initializeError(1);
            }
            return result; 
        }

        ShaderProgram & ShaderProgram::createTemplat(void)
        {
            ShaderProgram & result = create();
            
            bool shaderProgramInit = result.init("", "");

            if(!shaderProgramInit){
                result.initializeError(1);
            }
            return result; 
        }

        const bool ShaderProgram::init(void)
        {
            if(!Object::init()){
                return false;
            }
            _programId = glCreateProgram();
            if(glIsProgram(_programId) != GL_TRUE){
                return false;
            }

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

        const bool ShaderProgram::init(const string & vShaderPath, const string & fShaderPath)
        {
        
            Shader & vertexShader = vShaderPath.size() <= 0 ? Shader::create(ShaderType::vertex) : Shader::create(vShaderPath, ShaderType::vertex);
            if(!vertexShader.compile()){
                return false;
            }

            Shader & fragmentShader = fShaderPath.size() <= 0 ? Shader::create(ShaderType::fragment) : Shader::create(fShaderPath, ShaderType::fragment);
            if(!fragmentShader.compile()){
                return false;
            }

            attachShader(vertexShader);
            attachShader(fragmentShader);
            linkProgram();

            if(!linkIsSuccessful()){
                return false;
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

        const bool ShaderProgram::use(void) const
        {
            if(!linkIsSuccessful()){
                return false;
            }
            glUseProgram(_programId);
            return true;
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
}