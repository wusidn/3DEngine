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
        static Triangle & create(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3);
        virtual const bool init(const Vec3 & vertex_1, const Vec3 & vertex_2, const Vec3 & vertex_3);
    protected:
        ~Triangle(void);

    private:
        Triangle(void){}
    };
}

#endif //__TRIANGLE_H__