#include "../Include/File.h"

File * File::createWithFilePath(const string & filePath)
{
    File * result = new File();
    if(!result->init(filePath))
    {
        delete result;
        result = nullptr;
    }
    return result;
}

const bool File::init()
{
    if(!Object::init())
    {
        return false;
    }

    this->filePath = new string("");
    return true;
}

const bool File::init(const string & filePath)
{
    if(!init()){
        return false;
    }
    if(this->filePath){
        delete this->filePath;
        this->filePath = nullptr;
    }
    this->filePath = new string(filePath);
    return true;
}

File::~File(void)
{

}
