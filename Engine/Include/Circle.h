#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Geometry.h"

namespace engine
{
    class Circle : public Geometry
    {
    public:
        static Circle & create(const float r);

        const bool radius(const float r);
        const float radius(void);

    protected:

        Circle(void);
        ~Circle(void){}

        CREATEFUNC(Circle);

        virtual const bool init(void);
        virtual const bool init(const float r);

        virtual const bool render(const int dp);
        virtual const bool draw(Camera & viewPort);

    private:
        float _radius;
        float _density;
    };
}

#endif //__CIRCLE_H__