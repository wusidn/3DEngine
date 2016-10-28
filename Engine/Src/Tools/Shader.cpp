#include "Shader.h"
#include "LogManager.h"
#include "File.h"
#include "Appaction.h"
#include <cassert>

using namespace std;

namespace engine
{
    namespace tools
    {

        string Shader::globalCodeKey = "#globalCode";
        string Shader::mainCodeKey = "#mainCode";

        Shader & Shader::create(const enum ShaderType type)
        {
            Shader & result = create();
            bool shaderInit = result.init(type);

            assert(shaderInit);

            if(shaderInit){
                result.initializeError(1);
            }
            return result;
        }

        Shader & Shader::create(const string & fileName, const enum ShaderType type)
        {
            vector<string> fileList(1, fileName);
            return create(fileList, type);
        }

        static Shader & Shader::create(const vector<string> & shaderFiles, const enum ShaderType type)
        {
            Shader & result = create();
            bool shaderInit = result.init(shaderFiles, type);

            assert(shaderInit);

            if(shaderInit){
                result.initializeError(1);
            }
            return result;
        }

        const bool Shader::init(void)
        {
            if(!Object::init()){
                return false;
            }
            _shaderId = 0;
            return true;
        }

        const bool Shader::init(const enum ShaderType type)
        {

            string source;
            _shaderId = glCreateShader(type);
            if(glIsShader(_shaderId) != GL_TRUE){
                return false;
            }

            switch(type)
            {
            case ShaderType::vertex:
                source = vertexShaderCode();
                break;
            case ShaderType::fragment:
                source = fragmentShaderCode();
                break;
            default:
                Log.error("Unknown Shader Type");
                return false;
            }

            source.replace(source.find(globalCodeKey), globalCodeKey.size(), "");
            source.replace(source.find(mainCodeKey), mainCodeKey.size(), "");

            const GLchar * p_source = source.c_str();
            glShaderSource(_shaderId, 1, &p_source, nullptr);

            return true;
        }

        const bool Shader::init(const vector<string> & shaderFiles, const enum ShaderType type)
        {

            //获取每个文件的路径
            vector<string> filePathList;
            for(auto fileName : shaderFiles)
            {
                string shaderFilePath = "";

                if(shaderFilePath.size() <= 0){
                    shaderFilePath = File::pathIsExists(fileName) ? fileName : "";
                }

                if(shaderFilePath.size() <= 0){
                    string tempPath = Appaction::appactionPath() + "Shader/" + fileName;
                    shaderFilePath = File::pathIsExists(tempPath) ? tempPath : "";
                }

                if(shaderFilePath.size() <= 0){
                    Log.error("Shader: [{0}] Is Not Exists!", fileName);
                    return false;
                }  
                filePathList.push_back(shaderFilePath);
            }

            //获取代码模板
            string source;
            _shaderId = glCreateShader(type);
            if(glIsShader(_shaderId) != GL_TRUE){
                return false;
            }

            switch(type)
            {
            case ShaderType::vertex:
                source = vertexShaderCode();
                break;
            case ShaderType::fragment:
                source = fragmentShaderCode();
                break;
            default:
                Log.error("Unknown Shader Type");
                return false;
            }


            //代码融合
            string mainCode = "";
            string globalCode = "";


            for(auto shaderFilePath : filePathList)
            {                
                string code = File::readAllText(shaderFilePath);
                string removeAfterCode = code;

                //  删除注释
                static regex searchAnnotationRegex("#[^\n]*\n|//[^\n]*\n|/\\*[\\s\\S]*?\\*/");

                auto matchBegin = sregex_iterator(code.begin(), code.end(), searchAnnotationRegex);
                auto matchEnd = sregex_iterator();
                for(auto item  = matchBegin; item != matchEnd; ++item){
                    removeAfterCode.erase(removeAfterCode.find(item->str()), item->str().size());
                }
                
                //拆分代码块
                static regex mainRegex("void\\s+main\\s*\\(\\s*\\)\\s*\\{");
                smatch searchResult;
                if(regex_search(removeAfterCode, searchResult, mainRegex))
                {
                    int openLeftBraceCount = 1;
                    auto bodyIndex = removeAfterCode.find(searchResult[0].str());
                    auto contentIndex = bodyIndex + searchResult[0].str().size();
                    auto begin = removeAfterCode.begin();
                    auto i = begin + contentIndex;
                    for(; i != removeAfterCode.end() && openLeftBraceCount; ++i){
                        if(*i == '{'){
                            ++openLeftBraceCount;
                        }
                        if(*i == '}'){
                            --openLeftBraceCount;
                        }
                    }
                    mainCode += removeAfterCode.substr(contentIndex, i - begin - contentIndex - 1);
                    globalCode += removeAfterCode.erase(bodyIndex, i - begin - bodyIndex);
                }
                
            }

            //替换占位符
            source.replace(source.find(globalCodeKey), globalCodeKey.size(), globalCode);
            source.replace(source.find(mainCodeKey), mainCodeKey.size(), mainCode);
             
            const GLchar * p_source = source.c_str();
            glShaderSource(_shaderId, 1, &p_source, nullptr);

            return true;
        }

        const bool Shader::compile(void) const
        {
            glCompileShader(_shaderId);

            GLint compiled = 0;
            glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compiled);
            if(compiled == GL_TRUE){
                return true;
            }

            GLint infoLen = 0;
            glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infoLen);

            if(infoLen == 0){
                Log.error("# Shader::compile #  Not Fined Error Info");
                return false;
            }

            GLchar * buff = new GLchar[infoLen];
            glGetShaderInfoLog(_shaderId, infoLen, nullptr, buff);

            Log.error("# Shader::compile #  {0}", buff);
            delete [] buff;

            return false;
        }

        const unsigned int Shader::shaderId(void) const
        {
            if(!compileIsSuccessful()){
                return 0;
            }
            return _shaderId;
        }

        const bool Shader::compileIsSuccessful(void) const
        {
            if(glIsShader(_shaderId) != GL_TRUE){
                return false;
            }
            GLint compiled = 0;
            glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compiled);
            return compiled == GL_TRUE;
        }

        Shader::~Shader(void)
        {
            if(glIsShader(_shaderId) == GL_TRUE){
                glDeleteShader(_shaderId);
            }
        }

        string Shader::vertexShaderCode(void)
        {
            static string result = File::readAllText(Appaction::appactionPath() + "Shader/template.vert");
            return result;
        }

        string Shader::fragmentShaderCode(void)
        {
            static string result = File::readAllText(Appaction::appactionPath() + "Shader/template.frag");
            return result;
        }
    }
}