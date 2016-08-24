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
        state = runningState::stop;
        return true;
    }

    void Appaction::run(int argc, char ** argv)
    {
        if(state == runningState::running){
            return;
        }

        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(200, 100);

        glutCreateWindow("3DEngine");

        if(glewInit()){
            exit(EXIT_FAILURE);
        }

        initDelegate();

        Zeus::getInstance().setWindowTitle("haha");
        Zeus::getInstance().fullScreen();


        __displayDelegate = displayDelegate;
        glutDisplayFunc(displayPunc);

        glutIdleFunc(displayPunc);

        glutMainLoop();

    }


    function<void (void)> Appaction::initDelegate = [](void){
            Log.info("..........................");

            Vec4 p(100);
            Vec4 pp = p;
            
            pp.x = 12;
            Log.info("pp.x: {0}, p.x: {1}", pp.x, p.x);
            Log.info("pp.y: {0}, p.y: {1}", pp.y, p.y);
            Log.info("pp.z: {0}, p.z: {1}", pp.z, p.z);
            Log.info("pp.w: {0}, p.w: {1}", pp.w, p.w);

            Uuid & uuid = Uuid::create();
            if(uuid.ready()){
                Log.info("{0}", uuid);
                Log.info(Uuid::create(uuid).toString());
            }

            // UdpServer & udpServer = UdpServer::create(5432);
            // udpServer.recvFrom([](const struct sockaddr_in * clientInfo, const string & str){
            //     cout << "haha: " << str << endl;
            // });
            
            // File & file = File::create();
            // file.autoRelease();

            string code = File::readAllText("../CMakeLists.txt");
            
            Log.setFilterLevel(LogManager::level::DEBUG);

            Log.info("Main -> Code : {0}", code);
            
            Log.info("------{0, d3}", "1.4");
            
            Log.info("Vec3(0, 1, 0).modulo() = {0}", Vec3(0, 1, 0).modulo());
            Log.info("Vec3(1, 0, 0).dot(Vec3(0, 1, 0)) = {0,-5}", Vec3(1, 0, 0).dot(Vec3(0, 1, 0)));
            Log.info("Vec4(1, 0, 0, 1).modulo() = \\\\{0 , C2 }", Vec4(1, 0, 0, 1).modulo());
            

            Log.debug("Vec3(1, 2, 3).modulo() = {0}; Vec4(1, 2, 3, 1).modulo() = {1}", Vec3(1, 2, 3).modulo(), Vec4(1, 2, 3, 1).modulo());
            
            // a->autoRelease();
            // b->autoRelease();

            // b->retain();
            
            // Node & item = Node::create();   
            
            glClearColor(0.0, 0.0, 0.0, 1.0);

                        //test start

            // 准备数据
            const GLfloat vertices[4][2] =
            {
                { -0.50,  -0.50 },
                { 0.50,   -0.50 },
                { 0.50,   0.50 },
                { -0.50,  0.50 }
            };

            // const GLfloat colors[] = {
            //     1.0, 0.0, 0.0, 1.0,
            //     0.0, 1.0, 0.0, 1.0,
            //     0.0, 0.0, 1.0, 1.0,
            //     1.0, 1.0, 0.0, 1.0,
            // };

            const GLfloat colors[] = {
                1.0, 0.0, 0.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                1.0, 0.0, 0.0, 1.0
            };



            const GLushort vertex_indies[] = {
                0, 1, 2, 0, 2, 3
            };


            //处理数据
            glGenBuffers(1, &indiesBufferObject);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indies), vertex_indies, GL_STATIC_DRAW);

            glGenVertexArrays(1, &vertexArrayObject);
            glBindVertexArray(vertexArrayObject);

            glGenBuffers(1, &vertexBufferObject);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), nullptr, GL_STATIC_DRAW);


            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);



            // //加载shader 
            // Shader & defaultVertexShader = Shader::create(File::readAllText("Engine/Shader/default.vert"), ShaderType::vertex);
            // defaultVertexShader.compile();

            // Shader & defaultFragmentShader = Shader::create(File::readAllText("Engine/Shader/default.frag"), ShaderType::fragment);
            // defaultFragmentShader.compile();

            // //链接ShaderProgram
            // ShaderProgram & defaultShaderProgram = ShaderProgram::create();
            // defaultShaderProgram.attachShader(defaultVertexShader);
            // defaultShaderProgram.attachShader(defaultFragmentShader);
            // defaultShaderProgram.linkProgram();

            // //删除Shader
            // defaultVertexShader.release();
            // defaultFragmentShader.release();

            //高度封装版本
            ShaderProgram & defaultShaderProgram = ShaderProgram::create("Engine/Shader/default.vert", "Engine/Shader/default.frag");
            if(defaultShaderProgram.fault()){
                Log.error("defaultShaderProgram create fault");
            }

            //启用着色器程序
            defaultShaderProgram.use();

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void *)sizeof(vertices));
            glEnableVertexAttribArray(1);

            
            //test end
            
    };

    function<void (void)> Appaction::displayDelegate = [](void){

            //清空画布
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindVertexArray(vertexArrayObject);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiesBufferObject);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
            
           
            
            for(int i = 0; i < 1000000; ++i){
                int temp = i >> 5 * 6 << 2 / 3;
                temp ++;
            }
            
            //垃圾回收
            Gc::getInstance().clean();

            //计算fps
            // static int prevCallTime = 0;
            // int curTime Zeus::getRunningTime(); 
            
            //渲染
            glutSwapBuffers();
    };
}
