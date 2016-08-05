#pragma once
#ifndef __ZEUS_H__
#define __ZEUS_H__

#include "Object.h"

namespace engine
{
    class Zeus : public Object
    {
    public:
        static Zeus & getInstance(void);
        
        void reshapeWindow(const int width, const int height) const;

        // loadScene();
    protected:
        CREATEFUNC(Zeus);
        virtual const bool init(void);
    private:
        
    };
}

#endif //__ZEUS_H__