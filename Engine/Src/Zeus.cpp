#include "Zeus.h"
#include "LogManager.h"

#include <GL/freeglut.h>
#include <cmath>

namespace engine
{
    using namespace std;
    using namespace tools;

    
    Zeus * Zeus::_instance = nullptr;

    Zeus & Zeus::instance()
    {

        if(!_instance){
            _instance = &Zeus::create();
            _instance->retain();
        }

        return *_instance;
    }

    const bool Zeus::init()
    {
        if(!Object::init())
        {
            return false;
        }

        //当窗口大小发生改变
        glutReshapeFunc([](const int _width, const int _height){
            Zeus::instance()._windowSize.width = _width;
            Zeus::instance()._windowSize.height = _height;

            glViewport(0,0,_width,_height);
        });

        return true;
    }

    //获取桌面大小
    const Size2 Zeus::screenSize(void) const
    {
        return Size2(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    }

    //获取程序运行时间
    const int Zeus::runningTime(void) const
    {
        // return (double)clock() / CLOCKS_PER_SEC * 1000;
        return glutGet(GLUT_ELAPSED_TIME);
    }

    //改变窗口大小
    const Zeus & Zeus::windowSize(const Size2 & _size) const
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
    const Size2 Zeus::windowSize(void) const
    {
        return _windowSize;
    }

    //全屏
    const Zeus & Zeus::fullScreen(void) const
    {
        glutFullScreen();
        glutPostRedisplay();
        return *this;
    }

    //设置窗口标题
    const Zeus & Zeus::windowTitle(const string & _title) const
    {
        glutSetWindowTitle(_title.c_str());
        return *this;
    }

    //设置窗口位置
    const Zeus & Zeus::windowPosition(const Vec2 & _position) const
    {
        int x = round(_position.x);
        int y = round(_position.y);
        if(x < 0 || y < 0){
            Log.error("Zeus::setWindowPosition: x and y can not be less than zero");
        }
        glutPositionWindow(x, y);
        return *this;
    }

    ShaderProgram & Zeus::defaultShaderProgram(void)
    {
        static ShaderProgram & result = ShaderProgram::create("Test.vert", "Test.frag");
        return result;
    }
}