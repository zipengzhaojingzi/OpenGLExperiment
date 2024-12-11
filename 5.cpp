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
        std::cout << "无法打开文件进行写入: " << filename << std::endl;
        return;
    }

    // 写入绘图模式
    file << static_cast<int>(currentMode) << "\n";

    // 写入控制点
    for (const auto& point : controlPoints) {
        file << point.x << " " << point.y << "\n";
    }

    file.close();
}

void transForm();
// 点结构体定义
//struct Point {
//    float x, y;
//    Point(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
//};
//
//// 绘图模式枚举
//enum DrawMode { NONE, LINE, TRIANGLE, SQUARE, BEZIER };
//DrawMode currentMode = NONE;

std::vector<Point> controlPoints5; // 存储控制点
bool bDraw5 = false;
DrawMode currentMode = NONE;


// 计算Bezier曲线
void calcBezierCurve(std::vector<Point>& curvePoints, const std::vector<Point>& controlPoints5);


// 初始化OpenGL环境
void init5() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // 设置背景颜色为黑色
    glColor3f(1.0, 1.0, 1.0);         // 设置绘图颜色为白色
    glPointSize(5.0);                 // 设置点大小
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // 设置坐标系范围
}

// 菜单处理函数
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

// 创建菜单
void createMenu() {
    int menuId = glutCreateMenu(menu);
    glutAddMenuEntry("Line", 1);
    glutAddMenuEntry("Triangle", 2);
    glutAddMenuEntry("Square", 3);
    glutAddMenuEntry("Bezier Curve", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// 鼠标事件处理函数
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
    case 'c': // 清空控制点
        controlPoints5.clear();
        bDraw5 = false;
        glutPostRedisplay();
        break;
    case 'r': // 重置模式
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

        //glColor3f(1.0f, 0.0f, 0.0f);  // 红色
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
        glutMouseFunc(mouse3);  // 注册鼠标回调

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

// 绘制函数
void myDisplay5() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (!controlPoints5.empty()) {
        glColor3f(1.0, 1.0, 1.0); // 控制点颜色
        glBegin(GL_POINTS);
        for (const auto& point : controlPoints5) {
            glVertex2f(point.x, point.y);
        }
        glEnd();

        if (bDraw5) {
            switch (currentMode) {
            case LINE:
                if (controlPoints5.size() == 2) {
                    glColor3f(1.0, 0.0, 0.0); // 线条颜色
                    glBegin(GL_LINES);
                    glVertex2f(controlPoints5[0].x, controlPoints5[0].y);
                    glVertex2f(controlPoints5[1].x, controlPoints5[1].y);
                    glEnd();
                }
                break;
            case TRIANGLE:
                if (controlPoints5.size() == 3) {
                    glColor3f(0.0, 1.0, 0.0); // 三角形颜色
                    glBegin(GL_TRIANGLES);
                    for (const auto& point : controlPoints5) {
                        glVertex2f(point.x, point.y);
                    }
                    glEnd();
                }
                break;
            case SQUARE:
                if (!controlPoints5.empty()) {
                    glColor3f(0.0, 0.0, 1.0); // 正方形颜色
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
                    glColor3f(1.0, 0.0, 0.0); // Bezier曲线颜色
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
//    init5(); // 初始化OpenGL设置
//    createMenu(); // 创建右键菜单
//
//    glutDisplayFunc(&myDisplay5); // 注册显示回调
//    glutMouseFunc(mouse5);       // 注册鼠标回调
//
//    glutMainLoop();
//    return 0;
//}