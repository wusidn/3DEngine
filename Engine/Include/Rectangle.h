#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Geometry.h"


namespace engine
{
    class Rectangle : public Geometry
    {
    public:
        static Rectangle & create(const Size2 & _size);

    protected:
        CREATEFUNC(Rectangle);

        virtual const bool init(void);
        virtual const bool init(const Size2 & _size);

        virtual const bool render(const int dp);
        virtual const bool draw(Camera & viewPort);

    private:
        Size2 _size;
    };
}


#endif  //__RECTANGLE_H__