#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Appaction.h"
#include "Gc.h"
#include "File.h"
#include "Node.h"
#include "Vec4.h"

#include <ctime>
#include <unistd.h>
#include <string.h>
// #include <uuid/uuid.h>

#include "LogManager.h"
#include "Zeus.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Size2.h"
#include "World.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "ScreenWorld.h"
#include "CameraOutput.h"

#include <iostream>
#include <cmath>
#include <regex>

using namespace std;

//渲染函入口
function<void (void)> __displayDelegate;
void displayPunc()
{
    if(!__displayDelegate){
        return;
    }
    __displayDelegate();
}


GLuint vertexArrayObject;
GLuint vertexBufferObject;
GLuint indiesBufferObject;

namespace engine
{
    using namespace tools;

    Appaction * Appaction::_instance = nullptr; 

    Appaction & Appaction::instance(void)
    {
        if(!_instance){
            _instance = &create();
        }
        return *_instance;
    }

    const bool Appaction::init(void)
    {
        retain();
        return true;
    }

    void Appaction::run(int argc, char ** argv)
    {
        static bool running = false;
        if(running) return;
        running = true;

        
        static regex pathRegex("^([^/\\\\]*[/\\\\])+");
        smatch searchResult;
        string sourceAppactionPath = string(argv[0]);
        if(regex_search(sourceAppactionPath, searchResult, pathRegex))
        {
            _appactionPath = string(searchResult[0]);
        }else{
            Log.info("Matching appactionPath Error");
        }
        
        
        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(200, 100);

        glutCreateWindow("3DEngine");

        if(glewInit()){
            exit(EXIT_FAILURE);
        }

        _initDelegate();

        Zeus::instance().windowTitle("haha");
        Zeus::instance().fullScreen();


        __displayDelegate = _displayDelegate;
        glutDisplayFunc(displayPunc);

        glutIdleFunc(displayPunc);

        glutMainLoop();

    }

    string Appaction::appactionPath(void) const
    {
        return _appactionPath;
    }

    World & Appaction::screen(void)
    {
        return ScreenWorld::instance();
    }


    Appaction::~Appaction(void)
    {

    }

    function<void (void)> Appaction::_initDelegate = [](void){

            Log.info("..........................");

            Uuid & uuid = Uuid::create();
            if(uuid.ready()){
                Log.info("{0}", uuid);
                Log.info(Uuid::create(uuid).toString());
            }
            
            Log.info("1.0d / 3 = {0, F10}", 0.0000023456789d);
            Log.debug("equal(1.0, {1, F}) = {0}", equal(1.0, (1.0f / 3.0f - 1.0f / 6.0f) * 6.0f), (1.0 / 3.0f - 1.0 / 6.0f));
            
            Log.setFilterLevel(LogManager::level::DEBUG);

            
            Log.info("------{0, d3}", "1.4");
            
            Log.info("Vec3(0, 1, 0).modulo() = {0}", Vec3(0, 1, 0).modulo());
            Log.info("Vec3(1, 0, 0).dot(Vec3(0, 1, 0)) = {0,-5}", Vec3(1, 0, 0).dot(Vec3(0, 1, 0)));
            Log.info("Vec4(1, 0, 0, 1).modulo() = \\\\{0 , C2 }", Vec4(1, 0, 0, 1).modulo());

            Log.debug("Vec3(1, 2, 3).modulo() = {0}; Vec4(1, 2, 3, 1).modulo() = {1}", Vec3(1, 2, 3).modulo(), Vec4(1, 2, 3, 1).modulo());

            ScreenWorld::instance().append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));


            // ScreenWorld::instance().append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));
            // ScreenWorld::instance().append(Triangle::create(Vec2(100.0f, 100.0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));

            ScreenWorld::instance().append(Rectangle::create(100.0f));

            Circle & fristCircle = Circle::create(1000.0f);
            fristCircle.position(Vec2(Zeus::instance().screenSize().width * 0.5f, Zeus::instance().screenSize().height * 0.5f));
            ScreenWorld::instance().append(fristCircle);
            
            // for(int i = 0; i < 10; ++i){
            //     ScreenWorld::instance().append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));
            // }

            // World & fristWorld = World::create();
            // Camera & fristWorldCamera = Camera::create();

            // // fristWorld.append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));
            // // fristWorld.append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));

            // Node & newNode = Node::create();
            // newNode.append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 1000.0f), Vec2(1000.0f, .0f)));
            // // newNode.position(Vec2(50.0f, 20.0f));
            // fristWorld.append(newNode);
            // fristWorld.append(fristWorldCamera);

            // CameraOutput & fristWorldCameraOutput = CameraOutput::create();
            // fristWorldCameraOutput.camera(fristWorldCamera);

            // ScreenWorld::instance().append(fristWorldCameraOutput);
            
            glClearColor(0.0, 0.0, 0.0, 1.0);

            Log.info("Vec3(1.0f, 1.0f) = {0}", Vec3(1.0f, 1.0f));
            
    };

    function<void (void)> Appaction::_displayDelegate = [](void){

            static int prevDisplayTime = 0;
            int currDisplayTime = Zeus::instance().runningTime();

            //先执行代码（包括注册的动画、用户注册的代码）

            Node & tr = *ScreenWorld::instance().root().chidren().at(1);

            tr.position(Vec2((Zeus::instance().windowSize().width - 100) * 0.5f + cos(currDisplayTime / 1000.0f) * (Zeus::instance().windowSize().width - 100) * 0.5f, (Zeus::instance().windowSize().height - 100) * 0.5f + sin(currDisplayTime / 1000.0f) * (Zeus::instance().windowSize().height - 100) * 0.5f));


            //确定所有元素的位置后计算所有元素的位置
            ScreenWorld::instance().render(currDisplayTime - prevDisplayTime);

            //清空画布
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //以每个视口绘制
            ScreenWorld::instance().draw();

            prevDisplayTime = currDisplayTime;

            //垃圾回收
            Gc::getInstance().clean();

            //渲染
            glutSwapBuffers();
    };
    
}
