#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Object.h"
#include <SOIL.h>

namespace engine
{
    class Image : public Object
    {
    public:
        static Image & create(const string & path);
    protected:
        virtual const bool init(void);
        virtual const bool init(const string & path);
    private:
        CREATEFUNC(Image);
    };
}

#endif //__IMAGE_H__