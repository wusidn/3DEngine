#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__
#include "Object.h"
#include <functional>

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


        static function<void (void)> displayDelegate;
        static function<void (void)> initDelegate;

    private:
        static Appaction * instance;

        enum runningState state;
    };
}


#endif //__MAIN_H__