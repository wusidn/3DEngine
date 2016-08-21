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
        static Zeus & getInstance(void);


        //获取桌面大小
        const Size2 getScreenSize(void) const; 

        //获取程序运行时间
        const double getRunningTime(void) const;
        
        //改变窗口大小 (只取整数部分)
        const Zeus & setWindowSize(const Size2 & _size) const;
        //获取当前窗口大小
        const Size2 getWindowSize(void) const;

        //全屏
        const Zeus & fullScreen(void) const;

        //设置窗口标题
        const Zeus & setWindowTitle(const string & _title) const;

        //设置窗口位置 (只取整数部分)
        const Zeus & setWindowPosition(const Vec2 & _position) const;

    protected:
        CREATEFUNC(Zeus);
        virtual const bool init(void);
    private:
        Size2 windowSize;
        static Zeus * instance;
    };
}

#endif //__ZEUS_H__