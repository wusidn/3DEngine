#pragma once
#ifndef __APPACTION_H__
#define __APPACTION_H__
#include "Object.h"
#include "World.h"
#include <functional>

using namespace std;

namespace engine
{

    enum runningState{
        stop, running 
    };

    class Appaction : public Object
    {
    public: 
        static Appaction & getInstance(void);

        virtual const bool init(void);

        void run(int argc, char ** argv);
        World & screen(void);

    protected:
        virtual ~Appaction(void);
    private:
        CREATEFUNC(Appaction);
        static Appaction * instance;
        static function<void (void)> displayDelegate;
        static function<void (void)> initDelegate;
        
        World * _screen;
    };
}


#endif //__APPACTION_H__