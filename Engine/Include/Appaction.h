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
        static Appaction & instance(void);

        virtual const bool init(void);

        //运行程序
        void run(int argc, char ** argv);

        //获取程序路径
        string appactionPath(void) const;

        //获取屏幕
        World & screen(void);

    protected:
        virtual ~Appaction(void);
    private:
        CREATEFUNC(Appaction);

        string _appactionPath;
        static Appaction * _instance;
        static function<void (void)> _displayDelegate;
        static function<void (void)> _initDelegate;
        
    };
}


#endif //__APPACTION_H__