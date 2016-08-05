#include "File.h"

#include <iostream>
#include <cassert>

using namespace std;


namespace engine::tools{

    string File::readAllText(const string & filePath)
    {
        string result;
        ifstream is(filePath);

        if(is){
            
            is.seekg (0, is.end);
            int length = is.tellg();
            is.seekg (0, is.beg);
            
            char * temp = new char[length];
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
        assert(!result.init(filePath));
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
