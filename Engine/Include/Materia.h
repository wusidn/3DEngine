#pragma once 
#ifndef __MATERIA_H__
#define __MATERIA_H__

#include "Object.h"

namespace engine
{
    enum MateriaType {
        //纯色
        Purity,
        //彩色
        Multicolor,
        //贴图
        Chartlet
    };

    class Materia : public Object
    {
    public:
        const MateriaType &  materiaType(void) const;
    };
}

#endif //__MATERIA_H__