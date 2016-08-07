#pragma once
#ifndef __ZEUS_H__
#define __ZEUS_H__

#include "Object.h"
#include "Size2.h"
#include "Vec2.h"
#include <string>

using namespace std;

namespace engine
{
    class Zeus : public Object
    {
    public:
        static Zeus & getInstance(void);


        //获取桌面大小
        const Size2 getScreenSize(void) const; 
        
        //改变窗口大小 (只取整数部分)
        void setWindowSize(const Size2 & _size) const;
        //获取当前窗口大小
        const Size2 getWindowSize(void) const;

        //全屏
        void fullScreen(void) const;

        //设置窗口标题
        const void setWindowTitle(const string & _title) const;

        //设置窗口位置 (只取整数部分)
        const void setWindowPosition(const Vec2 & _position) const;

    protected:
        CREATEFUNC(Zeus);
        virtual const bool init(void);
    private:
        Size2 windowSize;
        static Zeus * instance;
    };
}

#endif //__ZEUS_H__