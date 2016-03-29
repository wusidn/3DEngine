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
    glClear(GL_COLOR_BUFFER_BIT);

    //渲染
    glFlush();
    
    //垃圾回收
    Gc::getInstance().clean();
}

void idle(void)
{
    display();
}
