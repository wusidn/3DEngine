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
#include "ScreenWorld.h"

#include <iostream>

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

    Appaction * Appaction::instance = nullptr; 

    Appaction & Appaction::getInstance(void)
    {
        if(!instance){
            instance = &create();
        }
        return *instance;
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

    World & Appaction::screen(void)
    {
        if(!_screen){
            _screen = &World::create();
        }
        return * _screen;
    }


    Appaction::~Appaction(void)
    {
        _screen->release();
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


            Appaction::getInstance().screen().append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));
            
            glClearColor(0.0, 0.0, 0.0, 1.0);

            Log.info("Vec3(1.0f, 1.0f) = {0}", Vec3(1.0f, 1.0f));


// {

//             //             //test start

//             // // 准备数据
//             // const GLfloat vertices[4][2] =
//             // {
//             //     { -0.50,  -0.50 },
//             //     { 0.50,   -0.50 },
//             //     { 0.50,   0.50 },
//             //     { -0.50,  0.50 }
//             // };

//             // const GLfloat colors[] = {
//             //     1.0, 0.0, 0.0, 1.0,
//             //     0.0, 1.0, 0.0, 1.0,
//             //     0.0, 0.0, 1.0, 1.0,
//             //     1.0, 1.0, 0.0, 1.0,
//             // };

//             // const GLfloat colors[] = {
//             //     1.0, 0.0, 0.0, 1.0,
//             //     0.0, 1.0, 0.0, 1.0,
//             //     0.0, 1.0, 0.0, 1.0,
//             //     1.0, 0.0, 0.0, 1.0
//             // };



//             // const GLushort vertex_indies[] = {
//             //     0, 1, 2, 0, 2, 3
//             // };


//             // //处理数据
//             // glGenBuffers(1, &indiesBufferObject);
//             // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject);
//             // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indies), vertex_indies, GL_STATIC_DRAW);

//             // glGenVertexArrays(1, &vertexArrayObject);
//             // glBindVertexArray(vertexArrayObject);

//             // glGenBuffers(1, &vertexBufferObject);
//             // glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//             // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), nullptr, GL_STATIC_DRAW);


//             // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//             // glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);


//             // //加载Shader
//             // ShaderProgram & defaultShaderProgram = ShaderProgram::create("Engine/Shader/default.vert", "Engine/Shader/default.frag");
//             // if(defaultShaderProgram.fault()){
//             //     Log.error("defaultShaderProgram create fault");
//             // }

//             // //启用着色器程序
//             // defaultShaderProgram.use();

//             // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
//             // glEnableVertexAttribArray(0);

//             // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void *)sizeof(vertices));
//             // glEnableVertexAttribArray(1);

//             //test end
// }
            
    };

    function<void (void)> Appaction::_displayDelegate = [](void){

            static int prevDisplayTime = 0;
            int currDisplayTime = Zeus::instance().runningTime();

            //先执行代码（包括注册的动画、用户注册的代码）


            //确定所有元素的位置后计算所有元素的位置
            ScreenWorld::instance().render(currDisplayTime - prevDisplayTime);

            //以每个视口绘制
            // ScreenWorld::instance().draw();

            prevDisplayTime = currDisplayTime;

            //清空画布
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // glBindVertexArray(vertexArrayObject);
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject);

            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
            
            
            for(int i = 0; i < 1000000; ++i){
                int temp = i >> 5 * 6 << 2 / 3;
                temp ++;
            }
            
            //垃圾回收
            Gc::getInstance().clean();

            //渲染
            glutSwapBuffers();
    };
    
}
