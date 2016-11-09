#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Appaction.h"
#include "Gc.h"
#include "File.h"
#include "Node.h"
#include "Vec4.h"
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

using namespace std;

//渲染函入口
function<void (void)> __displayDelegate;
void displayPunc()
{
    if(!__displayDelegate) return;

    __displayDelegate();
}


GLuint vertexArrayObject;
GLuint vertexBufferObject;
GLuint indiesBufferObject;

namespace engine
{
    using namespace tools;

    const bool Appaction::init(void)
    {
        retain();
        return true;
    }

    string Appaction::_appactionPath = "";

    void Appaction::run(int argc, char ** argv)
    {
        static bool running = false;
        if(running) return;
        running = true;

        
        static regex pathRegex("^([^/\\\\]*[/\\\\])+");
        smatch searchResult;
        string sourceAppactionPath = string(argv[0]);
        if(!regex_search(sourceAppactionPath, searchResult, pathRegex))
        {
            Log.info("Matching appactionPath Error");
        }

        _appactionPath = string(searchResult[0]);
        
        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitContextVersion (3, 3);
        glutInitContextProfile(GLUT_CORE_PROFILE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(200, 100);

        glutCreateWindow("3DEngine");

        if(glewInit()) exit(EXIT_FAILURE);

        Zeus::instance().windowTitle("haha");
        Zeus::instance().fullScreen();

        // Uuid & uuid = Uuid::create();
        // if(uuid.ready())
        // {
        //     Log.info("{0}", uuid);
        //     Log.info(Uuid::create(uuid).toString());
        // }
        
        // Log.info("1.0d / 3 = {0, F10}", 0.0000023456789d);
        // Log.debug("equal(1.0, {1, F}) = {0}", equal(1.0, (1.0f / 3.0f - 1.0f / 6.0f) * 6.0f), (1.0 / 3.0f - 1.0 / 6.0f));
        
        // Log.setFilterLevel(LogManager::level::DEBUG);

        
        // Log.info("------{0, d3}", "1.4");
        
        // Log.info("Vec3(0, 1, 0).modulo() = {0}", Vec3(0, 1, 0).modulo());
        // Log.info("Vec3(1, 0, 0).dot(Vec3(0, 1, 0)) = {0,-5}", Vec3(1, 0, 0).dot(Vec3(0, 1, 0)));
        // Log.info("Vec4(1, 0, 0, 1).modulo() = \\\\{0 , C2 }", Vec4(1, 0, 0, 1).modulo());

        // Log.debug("Vec3(1, 2, 3).modulo() = {0}; Vec4(1, 2, 3, 1).modulo() = {1}", Vec3(1, 2, 3).modulo(), Vec4(1, 2, 3, 1).modulo());

        
        // for(int i = 0; i < 10; ++i)
        // {
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

        // Log.info("Vec3(1.0f, 1.0f) = {0}", Vec3(1.0f, 1.0f));

        start();

        __displayDelegate = [this](void)
        {

            static int prevDisplayTime = 0;
            int currDisplayTime = Zeus::instance().runningTime();

            //动画系统、计时器执行

            //执行用户代码逻辑
            update(currDisplayTime - prevDisplayTime);

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

        glutDisplayFunc(displayPunc);

        glutIdleFunc(displayPunc);

        glutMainLoop();

    }

    string Appaction::appactionPath(void)
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

}
