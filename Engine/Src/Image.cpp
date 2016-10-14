#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"
#include "File.h"
#include "LogManager.h"
#include "Appaction.h"

namespace engine
{
    using namespace tools;
    Image & Image::create(const string & path)
    {
        Image & result = create();

        bool imageInit = result.init(path);

        assert(imageInit);

        if(!imageInit){
            result.initializeError(1);
        }

        return result;
    }

    const bool Image::init(void)
    {
        if(!Object::init()){
            return false;
        }
        _width = _height = _n = 0;
        _data = nullptr;

        return true;
    }

    const bool Image::init(const string & path)
    {
        
        string checkPath = "";

        if(checkPath.size() <= 0){
            checkPath = File::pathIsExists(path) ? path : "";
        }

        if(checkPath.size() <= 0){
            string temp = Appaction::appactionPath() + "Source/" + path;
            checkPath = File::pathIsExists(temp) ? temp : "";
        }
        
        if(checkPath.size() <= 0){
            Log.error("Path: [{0}] Is Not Exists!", path);
            return false;
        }

         _data = stbi_load(checkPath.c_str(), &_width, &_height, &_n, 0);

        return true;
    }

    const int Image::width(void) const
    {
        if(!ready()) return 0;

        return _width;
    }
    const int Image::height(void) const 
    {
        if(!ready()) return 0;

        return _height;
    }
    unsigned char * Image::data(void) const 
    {
        if(!ready()) return nullptr;

        return _data;
    }

    Image::~Image(void)
    {
        if(_data) stbi_image_free(_data);
    }
}