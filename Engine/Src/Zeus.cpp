#include "Zeus.h"
#include "LogManager.h"

#include <GL/freeglut.h>
#include <cmath>

namespace engine
{
    using namespace std;
    using namespace tools;

    
    Zeus * Zeus::instance = nullptr;

    Zeus & Zeus::getInstance()
    {

        if(!instance){
            instance = &Zeus::create();
            instance->retain();
        }

        return *instance;
    }

    const bool Zeus::init()
    {
        if(!Object::init())
        {
            return false;
        }

        //当窗口大小发生改变
        glutReshapeFunc([](const int _width, const int _height){
            Zeus::getInstance().windowSize.width = _width;
            Zeus::getInstance().windowSize.height = _height;
        });

        return true;
    }

    //获取桌面大小
    const Size2 Zeus::getScreenSize(void) const
    {
        return Size2(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    }

    //改变窗口大小
    const Zeus & Zeus::setWindowSize(const Size2 & _size) const
    {

        int width = round(_size.width);
        int height = round(_size.height);
        if(!(width * height))
        {
            Log.error("Zeus::setWindowSize: width and height Can not be zero");
        }else{
            glutReshapeWindow(width, height);
        }
        
        return *this;
    }

    //获取当前窗口大小
    const Size2 Zeus::getWindowSize(void) const
    {
        return windowSize;
    }

    //全屏
    const Zeus & Zeus::fullScreen(void) const
    {
        glutFullScreen();
        return *this;
    }

    //设置窗口标题
    const Zeus & Zeus::setWindowTitle(const string & _title) const
    {
        glutSetWindowTitle(_title.c_str());
        return *this;
    }

    //设置窗口位置
    const Zeus & Zeus:: setWindowPosition(const Vec2 & _position) const
    {
        int x = round(_position.x);
        int y = round(_position.y);
        if(x < 0 || y < 0){
            Log.error("Zeus::setWindowPosition: x and y can not be less than zero");
        }
        glutPositionWindow(x, y);
        return *this;
    }
}