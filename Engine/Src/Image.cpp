#include "Image.h"
#include "std_image.h"

namespace engine
{
    Image & Image::create(const string & path)
    {
        Image & result = create();

        if(!result.init(path)){
            result.initializeError(1);
        }

        return result;
    }

    const bool Image::init(void)
    {
        if(!Object::init()){
            return false;
        }

        return true;
    }

    const bool Image::init(const string & path)
    {
        int width, height, n;
        unsigned char * data = stbi_load(path.c_str(), &width, & height, &n, 0);
        return true;
    }
}