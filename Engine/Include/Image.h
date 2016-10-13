#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Object.h"
#include <string>

using namespace std;

namespace engine
{
    class Image : public Object
    {
    public:
        static Image & create(const string & path);

        const int width(void) const;
        const int height(void) const;
        unsigned char * data(void) const;
        
    protected:
        virtual const bool init(void);
        virtual const bool init(const string & path);
        Image(){}
        virtual ~Image(void);
    private:
        CREATEFUNC(Image);
        int _width, _height, _n;
        unsigned char * _data;
    };
}

#endif //__IMAGE_H__