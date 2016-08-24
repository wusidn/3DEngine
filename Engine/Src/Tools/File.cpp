#include "File.h"
#include "LogManager.h"

#include <iostream>
#include <cstring>

using namespace std;


namespace engine::tools{

    string File::readAllText(const string & filePath)
    {
        string result;
        ifstream is(filePath);

        if(!is){
            Log.error("# File::readAllText # filePath is not legal");
        }

        if(is){
            
            is.seekg (0, is.end);
            int length = is.tellg();
            is.seekg (0, is.beg);
            
            char * temp = new char[length + 1];
            temp[length] = 0;
            is.read (temp,length);
            is.close();
            
            result = string(temp);
            delete temp;
        }

        return result;
    }


    File & File::createWithFilePath(const string & filePath)
    {
        File & result = create();
        bool fileInit = result.init(filePath);

        assert(fileInit);

        //出错了
        if(!fileInit){
            result._state = 1;
        }

        return result;
    }

    const bool File::init()
    {
        if(!Object::init())
        {
            return false;
        }
        this->_filePath = nullptr;
        return true;
    }

    const bool File::init(const string & filePath)
    {
        this->_filePath = new string(filePath);
        return true;
    }

    const bool File::open(const int mode)
    {
        if(!this->_filePath){
            //error
            return false;
        }
        
        return true;
    }

    const bool File::open(const string & filePath, const int mode)
    {
    return true; 
    }


    File::~File(void)
    {
        if(this->_filePath){
            delete this->_filePath;
            this->_filePath = nullptr;
        }
    }
}
