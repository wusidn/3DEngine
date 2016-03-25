#include <GL/glew.h>
#include <GL/freeglut.h>
#include "main.h"
#include "../Include/Gc.h"
#include "../Include/File.h"
#include <ctime>
#include <unistd.h>

#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow(windiwTitle);

    if(glewInit())
    {
        exit(EXIT_FAILURE);
    }

    init();

    glutDisplayFunc(display);

    glutIdleFunc(idle);

    glutMainLoop();

}

void init(void)
{

    
    Object * a = new Object();
    Object * b = new Object();
   
    string & code = * new string(File::readAllText("../../CMakeLists.txt"));
    
    cout << "Main -> Code : " << code << endl;
    
    a->autoRelease();
    b->autoRelease();

    b->retain();
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
    static const float expect = 1.0 * 1000 / 60;
    
    static int frame = 0;
    static clock_t _prevScecond = clock(); 
    static clock_t _last = _prevScecond;
    
    frame++;
    
    glClear(GL_COLOR_BUFFER_BIT);

    //渲染
    glFlush();
    
    //垃圾回收
    Gc::getInstance().clean();
    
    //当前帧渲染所用时间
    clock_t _now = clock();
    float spendTime = float(_now - _last) / CLOCKS_PER_SEC;
    //当前秒已渲染帧数共用时间
    float sumSpendTime = float(_now - _prevScecond) / CLOCKS_PER_SEC;
    // cout << "执行时间:" << spendTime << ", 等待时间:" << expect - spendTime << endl;
    cout << "sumSpendTime * 1000 : " << sumSpendTime * 1000  << ", frame * expect: " << frame * expect << endl;
    usleep(expect - spendTime * 1000 - (sumSpendTime * 1000 - frame * expect));
    
    //  if(sumSpendTime >= 0.1){
    //     fps = frame;
    //     frame = 0;
    //     _prevScecond = _now;
    //     cout << "FPS: " << fps << endl;
    //  }
    
    _last = clock();
}

void idle(void)
{
    display();
}
