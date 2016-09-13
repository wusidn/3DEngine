#pragma once
#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "Geometry.h"
#include "Vec3.h"
#include "Vec4.h"

namespace engine
{
    class Triangle: public Geometry
    {
    public:
        CREATEFUNC(Triangle);
        static Triangle & create(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3);
    protected:

        virtual const bool init(void);
        virtual const bool init(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3);

        virtual const bool render(const int dp);
        virtual const bool draw(Camera & viewPort);
        
        ~Triangle(void){}
    private:

    };
}

#endif //__TRIANGLE_H__