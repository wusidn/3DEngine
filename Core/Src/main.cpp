#include <GL/glew.h>
#include <GL/freeglut.h>
#include "main.h"
#include "../Include/Gc.h"
#include "../Include/File.h"
#include "../Include/Node.h"
#include "../Include/Vec4.h"

#include <ctime>
#include <unistd.h>
#include <string.h>

#include <iostream>

using namespace std;

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

    glutDisplayFunc(display);

    glutIdleFunc(idle);

    glutMainLoop();

}

void init(void)
{

    
    // Object * a = new Object();
    // Object * b = new Object();
    
    File * file = File::create();
    file->autoRelease();
   
    string code = File::readAllText("../CMakeLists.txt");
    
    cout << "Main -> Code : " << code << endl;
    
    
    cout << "Vec3(0, 1, 0).modulo() = " << Vec3(0, 1, 0).modulo() << endl;
    cout << "Vec3(1, 0, 0).dot(Vec3(0, 1, 0)) = " << Vec3(1, 0, 0).dot(Vec3(0, 1, 0)) << endl;
    
    cout << "Vec4(1, 0, 0, 1).modulo() = " << Vec4(1, 0, 0, 1).modulo() << endl;
    
    
    cout << "Vec3(1, 2, 3).modulo() = " << Vec3(1, 2, 3).modulo() << endl;
    cout << "Vec4(1, 2, 3, 1).modulo() = " << Vec4(1, 2, 3, 1).modulo() << endl;
    
    // a->autoRelease();
    // b->autoRelease();

    // b->retain();
    
    Node * item = Node::create();
    item->autoRelease();
    
    
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
        cout << "FPS: " << fps << endl;
    }
    farmeCount++;
    
    //清空画布
    glClear(GL_COLOR_BUFFER_BIT);
    
    //渲染
    glFlush();
    
    
    for(int i = 0; i < 1000000; ++i){
        int temp = i >> 5 * 6 << 2 / 3;
        temp ++;
    }
    
    //垃圾回收
    Gc::getInstance().clean();
    
    //控制帧率
    float useTime = 0.0;
    float currFrameTime = clock();
    useTime = (currFrameTime - prevFrameTime) / CLOCKS_PER_SEC * 1000;
    if(useTime < standardTime){
        usleep((standardTime - useTime) * 1000);
    }
    prevFrameTime = currFrameTime;
}

void idle(void)
{
    display();
}
