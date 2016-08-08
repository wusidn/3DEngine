#include <GL/glew.h>
#include <GL/freeglut.h>
#include "main.h"
#include "Gc.h"
#include "File.h"
#include "Node.h"
#include "Vec4.h"

#include <ctime>
#include <unistd.h>
#include <string.h>
// #include <uuid/uuid.h>

#include "LogManager.h"
#include "Uuid.h"

#include "UdpServer.h"
#include "UdpClient.h"
#include "Zeus.h"
#include "Size2.h"

#include <iostream>

using namespace std;
using namespace engine;
using namespace engine::tools;

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);

    glutCreateWindow(windiwTitle);

    if(glewInit()){
        exit(EXIT_FAILURE);
    }
    
    init();

    Zeus::getInstance().setWindowSize(Size2(300)).setWindowTitle("haha").setWindowPosition(Vec2(800, 800));
    Zeus::getInstance().fullScreen();

    Size2 screenSize = Zeus::getInstance().getWindowSize();
    Log.info("screen.width: {0}, screen.height: {1}", screenSize.width, screenSize.height);

    glutDisplayFunc(display);

    glutIdleFunc(idle);

    glutMainLoop();

}

void init(void)
{

    Log.info("..........................");

    Uuid & uuid = Uuid::create();
    Log.info("{0}", uuid);
    Log.info(Uuid::create(uuid).toString());

    UdpServer & udpServer = UdpServer::create(5432);
    udpServer.recvFrom([](const struct sockaddr_in * clientInfo, const string & str){
        cout << "haha: " << str << endl;
    });
    
    // File & file = File::create();
    // file.autoRelease();

    string code = File::readAllText("../CMakeLists.txt");
    
    Log.setFilterLevel(LogManager::level::DEBUG);

    Log.info("Main -> Code : {0}", code);
    
    Log.info("------{0, d3}", "1.4");
    
    Log.info("Vec3(0, 1, 0).modulo() = {0}", Vec3(0, 1, 0).modulo());
    Log.info("Vec3(1, 0, 0).dot(Vec3(0, 1, 0)) = {0,-5}", Vec3(1, 0, 0).dot(Vec3(0, 1, 0)));
    Log.info("Vec4(1, 0, 0, 1).modulo() = \\\\{0 , C2 }", Vec4(1, 0, 0, 1).modulo());
    
    Log.info("{0, -20}", "一");
    Log.info("{0, -20}", "一二");
    Log.info("{0, -20}", "一二三");
    Log.info("{0, -20}", "一二三四");
    Log.info("{0, -20}", "一二三四五");
    Log.info("{0, -20}", "1一");
    Log.info("{0, -20}", "12一二");
    Log.info("{0, -20}", "123一二三");
    Log.info("{0, -20}", "1234一二三四");
    Log.info("{0, -20}", "12345一二三四五");
    

    Log.debug("Vec3(1, 2, 3).modulo() = {0}; Vec4(1, 2, 3, 1).modulo() = {1}", Vec3(1, 2, 3).modulo(), Vec4(1, 2, 3, 1).modulo());
    
    // a->autoRelease();
    // b->autoRelease();

    // b->retain();
    
    // Node & item = Node::create();   
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    
    
    //test start
    // const float vertices[3][2] = {
    //     {-0.5, -0.5},
    //     {0.5, -0.5},
    //     {0.5, 0.0}
    // };
    
    // const float colors[] = {
    //     1.0, 0.0, 0.0, 1.0,
    //     0.0, 1.0, 0.0, 1.0,
    //     0.0, 0.0, 1.0, 1.0,  
    // };
    
    // const GLushort vertex_indies[] = {
    //     0, 1, 2
    // };
    
    // glGenBuffers
    
    //test end
    
}

void display(void)
{

    // for(unsigned i = 0; i < 10000; ++i)
    // {
    //     Uuid * uuid = Uuid::create();
    //     uuid->toString();
    // }
    
    // log.info(uuid->toString());
    
    static float hopeFrameCount = 120;
    static int farmeCount = hopeFrameCount;
    static time_t prevSecond = 0;
    static float standardTime = 1000.0 / hopeFrameCount;
    static float prevFrameTime = 0.0;
    if(!prevFrameTime){
        prevFrameTime = clock();
    }
    
    //计算当前帧率
    time_t tempTime = time(NULL);
    if(!prevSecond || tempTime - prevSecond >= 1){
        prevSecond = tempTime;
        fps = farmeCount;
        farmeCount = 0;

        Log.info("FPS: {0}", fps);
        
    }
    farmeCount++;
    
    //清空画布
    glClear(GL_COLOR_BUFFER_BIT);
    
    //渲染
    glFlush();
    
    
    // for(int i = 0; i < 1000000; ++i){
    //     int temp = i >> 5 * 6 << 2 / 3;
    //     temp ++;
    // }
    
    //垃圾回收
    Gc::getInstance().clean();
    
    //控制帧率
    float useTime = 0.0;
    float currFrameTime = clock();
    useTime = (currFrameTime - prevFrameTime) / CLOCKS_PER_SEC * 1000;
    if(useTime < standardTime){
        // usleep((standardTime - useTime) * 1000);
    }
    prevFrameTime = currFrameTime;
}

void idle(void)
{
    display();
}

