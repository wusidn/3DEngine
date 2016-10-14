#pragma once
#ifndef __TEXTRUE_2D_H__
#define __TEXTRUE_2D_H__

#include "Object.h"
#include "Image.h"

#include <string>
#include <GL/glew.h>

using namespace std;

namespace engine
{
    class Textrue2D : public Object
    {
    public:
        static Textrue2D & create(const string & fileName);
        static Textrue2D & create(const Image & img);
    protected:
        CREATEFUNC(Textrue2D);

        virtual const bool init(void);
        virtual const bool init(const string & fileName);
        virtual const bool init(const Image & img);
    private:
        GLuint _textrueId;
    };
}

#endif //__TEXTRUE_2D_H__