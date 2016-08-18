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
            instance = new Appaction();
            if(!instance->init()){
                delete instance;
                instance = nullptr;
            }
        }
        assert(instance);
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

        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(200, 100);

        glutCreateWindow("3DEngine");

        if(glewInit()){
            exit(EXIT_FAILURE);
        }

        initDelegate();


        Zeus::getInstance().setWindowSize(Size2(300)).setWindowTitle("haha").setWindowPosition(Vec2(800, 800));
        Zeus::getInstance().fullScreen();
        
        __displayDelegate = displayDelegate;
        glutDisplayFunc(displayPunc);

        glutIdleFunc(displayPunc);

        glutMainLoop();

    }


    function<void (void)> Appaction::initDelegate = [](void){
            Log.info("..........................");

            Uuid & uuid = Uuid::create();
            Log.info("{0}", uuid);
            Log.info(Uuid::create(uuid).toString());

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

            //准备数据
            const GLfloat vertices[6][2] =
            {
                { -0.50,  -0.50 },
                { 0.50,   -0.50 },
                { 0.50,   0.50 },
                { -0.50,  0.50 }
            };

            const GLfloat colors[] = {
                1.0, 0.0, 0.0, 1.0,
                0.0, 1.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 1.0,
                1.0, 1.0, 0.0, 1.0,
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


            //加载shader 
            Shader & defaultVertexShader = Shader::create(File::readAllText("Engine/Shader/default.vert"), ShaderType::vertex);
            defaultVertexShader.compile();

            Shader & defaultFragmentShader = Shader::create(File::readAllText("Engine/Shader/default.frag"), ShaderType::fragment);
            defaultFragmentShader.compile();

            //链接ShaderProgram
            ShaderProgram & defaultShaderProgram = ShaderProgram::create();
            defaultShaderProgram.attachShader(defaultVertexShader);
            defaultShaderProgram.attachShader(defaultFragmentShader);
            defaultShaderProgram.linkProgram();
            
            //test end
    };

    function<void (void)> Appaction::displayDelegate = [](void){
            static double displayStartTime = 0.0d;
            static double displayEndTime = 0.0d;

            displayStartTime = Zeus::getInstance().getRunningTime();
            // if(displayStartTime > 1000.0){
            //     Log.info("HideWindow");
            //     glutHideWindow();
            // }
            // if(displayStartTime > 1200.0){
            //     Log.info("ShowWindow");
            //     glutShowWindow();
            // }

            // Log.info("parogram running time = {0}", Zeus::getInstance().getRunningTime());

            
            static float hopeFrameCount = 60;
            static float standardTime = 1000.0 / hopeFrameCount;

            // static int farmeCount = hopeFrameCount;
            // static time_t prevSecond = 0;
            
            // //计算当前帧率
            // time_t tempTime = time(NULL);
            // if(!prevSecond || tempTime - prevSecond >= 1){
            //     prevSecond = tempTime;
            //     int fps = farmeCount;
            //     farmeCount = 0;

            //     Log.info("FPS: {0}", fps);
            //     // Size2 screenSize = Zeus::getInstance().getWindowSize();
            //     // Log.info("screen.width: {0}, screen.height: {1}", screenSize.width, screenSize.height);
            // }
            // farmeCount++;
            
            //清空画布
            glClear(GL_COLOR_BUFFER_BIT);
            
            //渲染
            // glFlush();
            glutSwapBuffers();
            
            
            for(int i = 0; i < 1000000; ++i){
                int temp = i >> 5 * 6 << 2 / 3;
                temp ++;
            }
            
            //垃圾回收
            Gc::getInstance().clean();
            
            displayEndTime = Zeus::getInstance().getRunningTime();
            //控制帧率
            if(displayEndTime - displayStartTime < standardTime){
                usleep((standardTime + displayStartTime - displayEndTime) * 1000 - 50);
            }
    };
}

// int main(int argc, char ** argv)
// {
//     glutInit(&argc, argv);

//     glutInitDisplayMode(GLUT_RGBA);
//     glutInitWindowSize(800, 600);
//     glutInitWindowPosition(200, 100);

//     glutCreateWindow(windiwTitle);

//     if(glewInit()){
//         exit(EXIT_FAILURE);
//     }
    
//     init();

//     Zeus::getInstance().setWindowSize(Size2(300)).setWindowTitle("haha").setWindowPosition(Vec2(800, 800));
//     // Zeus::getInstance().fullScreen();
 
//     glutDisplayFunc(display);

//     glutIdleFunc(idle);

//     glutMainLoop();

// }

// void init(void)
// {

//     Log.info("..........................");

//     Uuid & uuid = Uuid::create();
//     Log.info("{0}", uuid);
//     Log.info(Uuid::create(uuid).toString());

//     UdpServer & udpServer = UdpServer::create(5432);
//     udpServer.recvFrom([](const struct sockaddr_in * clientInfo, const string & str){
//         cout << "haha: " << str << endl;
//     });
    
//     // File & file = File::create();
//     // file.autoRelease();

//     string code = File::readAllText("../CMakeLists.txt");
    
//     Log.setFilterLevel(LogManager::level::DEBUG);

//     Log.info("Main -> Code : {0}", code);
    
//     Log.info("------{0, d3}", "1.4");
    
//     Log.info("Vec3(0, 1, 0).modulo() = {0}", Vec3(0, 1, 0).modulo());
//     Log.info("Vec3(1, 0, 0).dot(Vec3(0, 1, 0)) = {0,-5}", Vec3(1, 0, 0).dot(Vec3(0, 1, 0)));
//     Log.info("Vec4(1, 0, 0, 1).modulo() = \\\\{0 , C2 }", Vec4(1, 0, 0, 1).modulo());
    
//     Log.info("{0, -20}", "一");
//     Log.info("{0, -20}", "一二");
//     Log.info("{0, -20}", "一二三");
//     Log.info("{0, -20}", "一二三四");
//     Log.info("{0, -20}", "一二三四五");
//     Log.info("{0, -20}", "1一");
//     Log.info("{0, -20}", "12一二");
//     Log.info("{0, -20}", "123一二三");
//     Log.info("{0, -20}", "1234一二三四");
//     Log.info("{0, -20}", "12345一二三四五");
    

//     Log.debug("Vec3(1, 2, 3).modulo() = {0}; Vec4(1, 2, 3, 1).modulo() = {1}", Vec3(1, 2, 3).modulo(), Vec4(1, 2, 3, 1).modulo());
    
//     // a->autoRelease();
//     // b->autoRelease();

//     // b->retain();
    
//     // Node & item = Node::create();   
    
//     glClearColor(0.0, 0.0, 0.0, 1.0);
    
    
    
//     //test start
//     // const float vertices[3][2] = {
//     //     {-0.5, -0.5},
//     //     {0.5, -0.5},
//     //     {0.5, 0.0}
//     // };
    
//     // const float colors[] = {
//     //     1.0, 0.0, 0.0, 1.0,
//     //     0.0, 1.0, 0.0, 1.0,
//     //     0.0, 0.0, 1.0, 1.0,  
//     // };
    
//     // const GLushort vertex_indies[] = {
//     //     0, 1, 2
//     // };
    
//     // glGenBuffers
    
//     //test end
    
// }

// void display(void)
// {

    
// }

// void idle(void)
// {
//     display();
// }

