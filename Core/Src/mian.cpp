#include <GL/glew.h>
#include <GL/freeglut.h>

const char * windiwTitle = "Hello World";

void init(void);
void display(void);
void idle(void);

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
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);


    glFlush();
}

void idle(void)
{
    display();
}
