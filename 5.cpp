#include <GL/glut.h>
#include "drawing.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include<iostream>

const float xmin = -0.5f, ymin = -0.5f;
const float xmax = 0.5f, ymax = 0.5f;
void mouse3(int button, int state, int x, int y);
void myDisplay3();
void keyboard3(unsigned char key, int x, int y);

void saveToFile(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "�޷����ļ�����д��: " << filename << std::endl;
        return;
    }

    // д���ͼģʽ
    file << static_cast<int>(currentMode) << "\n";

    // д����Ƶ�
    for (const auto& point : controlPoints) {
        file << point.x << " " << point.y << "\n";
    }

    file.close();
}

void transForm();
// ��ṹ�嶨��
//struct Point {
//    float x, y;
//    Point(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
//};
//
//// ��ͼģʽö��
//enum DrawMode { NONE, LINE, TRIANGLE, SQUARE, BEZIER };
//DrawMode currentMode = NONE;

std::vector<Point> controlPoints5; // �洢���Ƶ�
bool bDraw5 = false;
DrawMode currentMode = NONE;


// ����Bezier����
void calcBezierCurve(std::vector<Point>& curvePoints, const std::vector<Point>& controlPoints5);


// ��ʼ��OpenGL����
void init5() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // ���ñ�����ɫΪ��ɫ
    glColor3f(1.0, 1.0, 1.0);         // ���û�ͼ��ɫΪ��ɫ
    glPointSize(5.0);                 // ���õ��С
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // ��������ϵ��Χ
}

// �˵�������
void menu(int id) {
    switch (id) {
    case 1: currentMode = LINE; break;
    case 2: currentMode = TRIANGLE; break;
    case 3: currentMode = SQUARE; break;
    case 4: currentMode = BEZIER; break;
    default: currentMode = NONE; break;
    }
    glutPostRedisplay();
}

// �����˵�
void createMenu() {
    int menuId = glutCreateMenu(menu);
    glutAddMenuEntry("Line", 1);
    glutAddMenuEntry("Triangle", 2);
    glutAddMenuEntry("Square", 3);
    glutAddMenuEntry("Bezier Curve", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// ����¼�������
void mouse5(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        Point point(20.0f * (static_cast<float>(x) / windowWidth) - 10.0f,
            10.0f - 20.0f * (static_cast<float>(y) / windowHeight));

        switch (currentMode) {
        case LINE:
            if (controlPoints5.size() < 2) {
                controlPoints5.push_back(point);
                if (controlPoints5.size() == 2) bDraw5 = true;
            }
            break;
        case TRIANGLE:
            if (controlPoints5.size() < 3) {
                controlPoints5.push_back(point);
                if (controlPoints5.size() == 3) bDraw5 = true;
            }
            break;
        case SQUARE:
            if (controlPoints5.empty()) {
                controlPoints5.push_back(point);
                bDraw5 = true;
            }
            break;
        case BEZIER:
            if (controlPoints5.size() < 4) {
                controlPoints5.push_back(point);
                if (controlPoints5.size() == 4) bDraw5 = true;
            }
            break;
        default: break;
        }

        glutPostRedisplay();
    }
}

void keyboard5(unsigned char key, int x, int y) {
    switch (key) {
    case 'c': // ��տ��Ƶ�
        controlPoints5.clear();
        bDraw5 = false;
        glutPostRedisplay();
        break;
    case 'r': // ����ģʽ
        currentMode = NONE;
        controlPoints5.clear();
        bDraw5 = false;
        glutPostRedisplay();
        break;
    case 't':
        transForm();
        //bDraw5 = false;
        glutPostRedisplay();
        break;
    case '3': {
        //glClear(GL_COLOR_BUFFER_BIT);

        //glColor3f(1.0f, 0.0f, 0.0f);  // ��ɫ
        //glBegin(GL_LINE_LOOP);
        //glVertex2f(xmin, ymin);
        //glVertex2f(xmax, ymin);
        //glVertex2f(xmax, ymax);
        //glVertex2f(xmin, ymax);
        //glEnd();
        //glFlush();

        //glutPostRedisplay();
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
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
    case 's':
        saveToFile("drawing.txt"); break;
    default:
        break;
    }
}

// ���ƺ���
void myDisplay5() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (!controlPoints5.empty()) {
        glColor3f(1.0, 1.0, 1.0); // ���Ƶ���ɫ
        glBegin(GL_POINTS);
        for (const auto& point : controlPoints5) {
            glVertex2f(point.x, point.y);
        }
        glEnd();

        if (bDraw5) {
            switch (currentMode) {
            case LINE:
                if (controlPoints5.size() == 2) {
                    glColor3f(1.0, 0.0, 0.0); // ������ɫ
                    glBegin(GL_LINES);
                    glVertex2f(controlPoints5[0].x, controlPoints5[0].y);
                    glVertex2f(controlPoints5[1].x, controlPoints5[1].y);
                    glEnd();
                }
                break;
            case TRIANGLE:
                if (controlPoints5.size() == 3) {
                    glColor3f(0.0, 1.0, 0.0); // ��������ɫ
                    glBegin(GL_TRIANGLES);
                    for (const auto& point : controlPoints5) {
                        glVertex2f(point.x, point.y);
                    }
                    glEnd();
                }
                break;
            case SQUARE:
                if (!controlPoints5.empty()) {
                    glColor3f(0.0, 0.0, 1.0); // ��������ɫ
                    Point topLeft = controlPoints5[0];
                    Point bottomRight = controlPoints5[0];
                    glBegin(GL_QUADS);
                    glVertex2f(topLeft.x, topLeft.y);
                    glVertex2f(bottomRight.x + 2, topLeft.y);
                    glVertex2f(bottomRight.x + 2, bottomRight.y - 2);
                    glVertex2f(topLeft.x, bottomRight.y - 2);
                    glEnd();
                }
                break;
            case BEZIER:
                if (controlPoints5.size() == 4) {
                    std::vector<Point> curvePoints;
                    calcBezierCurve(curvePoints, controlPoints5);
                    glColor3f(1.0, 0.0, 0.0); // Bezier������ɫ
                    glBegin(GL_LINE_STRIP);
                    for (const auto& point : curvePoints) {
                        glVertex2f(point.x, point.y);
                    }
                    glEnd();
                }
                break;
            default: break;
            }
        }
    }

    glFlush();
}

//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Interactive Drawing System");
//
//    init5(); // ��ʼ��OpenGL����
//    createMenu(); // �����Ҽ��˵�
//
//    glutDisplayFunc(&myDisplay5); // ע����ʾ�ص�
//    glutMouseFunc(mouse5);       // ע�����ص�
//
//    glutMainLoop();
//    return 0;
//}