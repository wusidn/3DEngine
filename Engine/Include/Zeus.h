#pragma once
#ifndef __ZEUS_H__
#define __ZEUS_H__

#include "Object.h"
#include "Size2.h"
#include "Vec2.h"
#include <string>
#include <functional>

using namespace std;

namespace engine
{

    enum ZeusFunctionType{
        fullScreen, reshapeWindow
    };

    class Zeus : public Object
    {
    public:
        static Zeus & instance(void);


        //获取桌面大小
        const Size2 screenSize(void) const; 

        //获取程序运行时间
        const int runningTime(void) const;
        
        //改变窗口大小 (只取整数部分)
        const Zeus & windowSize(const Size2 & _size) const;
        //获取当前窗口大小
        const Size2 windowSize(void) const;

        //全屏
        const Zeus & fullScreen(void) const;

        //设置窗口标题
        const Zeus & windowTitle(const string & _title) const;

        //设置窗口位置 (只取整数部分)
        const Zeus & windowPosition(const Vec2 & _position) const;

    protected:
        CREATEFUNC(Zeus);
        virtual const bool init(void);
    private:
        Size2 _windowSize;
        static Zeus * _instance;
    };
}

#endif //__ZEUS_H__