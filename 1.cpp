#include <GL/glut.h>
#include <math.h>
#include<iostream>


void myDisplay0(void);
void myDisplay2();
void myDisplay3();
void myDisplay4();
void myDisplay5();
void keyboard3(unsigned char key, int x, int y);
void keyboard5(unsigned char key, int x, int y);
void mouse3(int button, int state, int x, int y);
void mouse4(int button, int state, int x, int y);
void mouse5(int button, int state, int x, int y);
void createMenu();
void init5();






// DDA�㷨����
void DDALine(int x0, int y0, int x1, int y1) {
    int ddx = x1 - x0, ddy = y1 - y0;
    int dm = (fabs(ddx) > fabs(ddy)) ? fabs(ddx) : fabs(ddy);
    float dx = (float)ddx / (float)dm, dy = (float)ddy / (float)dm;
    float x = x0, y = y0;
    glBegin(GL_POINTS);
    for (int i = 0; i <= dm; i++) {
        glVertex2f(int(x + 0.5), (int)(y + 0.5));
        x += dx;
        y += dy;
    }
    glEnd();
}

void swap_value(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// �Ľ���Bresenham�㷨����
void improvedBresenhamLine(int x0, int y0, int x1, int y1) {
    int dx, dy, d, UpIncre, DownIncre, x, y;
    if (x0 > x1) {
        swap_value(x0, x1); swap_value(y0, y1);
    }
    x = x0, y = y0;
    int xx = x1, yy = y1;
    dx = x1 - x0, dy = y1 - y0;
    bool flag = true;
    if (dx < dy) {
        flag = false;
        swap_value(x, y);
        swap_value(dx, dy);
        swap_value(xx, yy);
    }
    d = dx - 2 * dy;
    UpIncre = 2 * dx - 2 * dy;
    DownIncre = -2 * dy;
    glBegin(GL_POINTS);
    while (x <= xx) {
        if (flag)
            glVertex2d(x, y);
        else glVertex2d(y, x);
        x++;
        if (d < 0) {
            y++;
            d += UpIncre;
        }
        else
            d += DownIncre;
    }
    glEnd();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void myDisplay1() {
    glClear(GL_COLOR_BUFFER_BIT);
    Reshape(500, 500);
    DDALine(10, 10, 200, 200); //��ɫ��DDA����
    glColor3f(1.0f, 0.0f, 0.0f);
    improvedBresenhamLine(50, 10, 200, 400); //��ɫ��Bresenham����
    glFlush();
}

int main(int argc, char** argv) {
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
        int n;
        std::cin >> n;
        switch (n)
        {
        case 0:
        {
            glutCreateWindow("Hello OpenGL!"); // ����һ������Ϊ��Hello OpenGL!�����´���
            glutDisplayFunc(&myDisplay0);        // ע���ͼ�ص�������ָ����������Ҫ�ػ�ʱ����myDisplay����
            //glutReshapeFunc(Reshape);

            break;
        }
        case 1:
        {
            glutCreateWindow("Lines!");
            glutDisplayFunc(&myDisplay1);
            // Register reshape callback
            //glutReshapeFunc(Reshape);
            break;
        }
        case 2:
        {
            glutCreateWindow("Transform!");
            glutDisplayFunc(&myDisplay2);
            // Register reshape callback
            //glutReshapeFunc(Reshape);
            break;
        }
        case 3:
        {
            glutCreateWindow("Cut");

            glutDisplayFunc(&myDisplay3);
            glutKeyboardFunc(keyboard3);
            glutMouseFunc(mouse3);  // ע�����ص�

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
            break;
        }
        case 4:
        {
            glutCreateWindow("Bezier Curve Experiment");

            glClearColor(0.0, 0.0, 0.0, 0.0); // ���ñ�����ɫΪ��ɫ
            glColor3f(1.0, 1.0, 1.0);         // ���û�ͼ��ɫΪ��ɫ
            glPointSize(5.0);                 // ���õ��С
            gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // ��������ϵ��Χ
            glutDisplayFunc(&myDisplay4);
            glutMouseFunc(mouse4);
            break;
        }
        case 5: {
            glutCreateWindow("Experiment Finish! Interactive Drawing System");

            init5(); // ��ʼ��OpenGL����
            createMenu(); // �����Ҽ��˵�

            glutDisplayFunc(&myDisplay5); // ע����ʾ�ص�
            glutMouseFunc(mouse5);       // ע�����ص�
            glutKeyboardFunc(keyboard5);

            break;
        }
        default:
            break;
        }
        glutMainLoop();
    
   

    return 0;
}