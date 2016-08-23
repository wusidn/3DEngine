#pragma once
#ifndef __APPACTION_H__
#define __APPACTION_H__
#include "Object.h"
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


    private:
        CREATEFUNC(Appaction);
        static Appaction * instance;
        static function<void (void)> displayDelegate;
        static function<void (void)> initDelegate;

        enum runningState state;
    };
}


#endif //__APPACTION_H__