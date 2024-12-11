//#include <GL/glut.h>
//#include <vector>
//
//struct Point {
//    float x, y;
//   
//};
//
//std::vector<Point> controlPoints; // 存储控制点
//bool bDraw = false;
//
//// 计算Bezier曲线上的点
//void calcBezierCurve(std::vector<Point>& curvePoints, const std::vector<Point>& controlPoints) {
//    int numPoints = 100; // 曲线上点的数量
//    curvePoints.clear();
//    for (int i = 0; i <= numPoints; ++i) {
//        float t = static_cast<float>(i) / numPoints;
//        Point p;
//        p.x = pow(1 - t, 3) * controlPoints[0].x +
//            3 * pow(1 - t, 2) * t * controlPoints[1].x +
//            3 * (1 - t) * pow(t, 2) * controlPoints[2].x +
//            pow(t, 3) * controlPoints[3].x;
//        p.y = pow(1 - t, 3) * controlPoints[0].y +
//            3 * pow(1 - t, 2) * t * controlPoints[1].y +
//            3 * (1 - t) * pow(t, 2) * controlPoints[2].y +
//            pow(t, 3) * controlPoints[3].y;
//        curvePoints.push_back(p);
//    }
//}
//
//// 初始化OpenGL环境
////void init() {
////    glClearColor(0.0, 0.0, 0.0, 0.0); // 设置背景颜色为黑色
////    glColor3f(1.0, 1.0, 1.0);         // 设置绘图颜色为白色
////    glPointSize(5.0);                 // 设置点大小
////    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // 设置坐标系范围
////}
//
//// 绘制函数
//void myDisplay4() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    if (!controlPoints.empty()) {
//        glBegin(GL_POINTS);
//        for (const auto& point : controlPoints) {
//            glVertex2f(point.x, point.y);
//        }
//        glEnd();
//
//        if (controlPoints.size() == 4 && bDraw) {
//            std::vector<Point> curvePoints;
//            calcBezierCurve(curvePoints, controlPoints);
//
//            glColor3f(1.0, 0.0, 0.0); // 设置Bezier曲线颜色为红色
//            glBegin(GL_LINE_STRIP);
//            for (const auto& point : curvePoints) {
//                glVertex2f(point.x, point.y);
//            }
//            glEnd();
//        }
//    }
//
//    glutSwapBuffers();
//}
//
//// 鼠标事件处理函数
//void mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        if (controlPoints.size() < 4) {
//            controlPoints.emplace_back(static_cast<float>(x) / 50.0 - 10.0, 10.0 - static_cast<float>(y) / 50.0);
//            if (controlPoints.size() == 4) {
//                bDraw = true;
//            }
//            glutPostRedisplay();
//        }
//    }
//}
//
////int main(int argc, char** argv) {
////    glutInit(&argc, argv);
////    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
////    glutInitWindowSize(800, 600);
////    glutCreateWindow("Bezier Curve Experiment");
////
////    glClearColor(0.0, 0.0, 0.0, 0.0); // 设置背景颜色为黑色
////    glColor3f(1.0, 1.0, 1.0);         // 设置绘图颜色为白色
////    glPointSize(5.0);                 // 设置点大小
////    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // 设置坐标系范围
////    glutDisplayFunc(display);
////    glutMouseFunc(mouse);
////
////    glutMainLoop();
////    return 0;
////}

//#include <GL/glut.h>
//#include <vector>
//#include <cmath> // for pow function
//
//struct Point {
//    float x, y;
//
//    // 构造函数
//    Point(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
//};
//
//std::vector<Point> controlPoints; // 存储控制点
//bool bDraw = false;
//
//// 计算Bezier曲线上的点
//void calcBezierCurve(std::vector<Point>& curvePoints, const std::vector<Point>& controlPoints) {
//    int numPoints = 100; // 曲线上点的数量
//    curvePoints.clear();
//    for (int i = 0; i <= numPoints; ++i) {
//        float t = static_cast<float>(i) / numPoints;
//        Point p(
//            pow(1 - t, 3) * controlPoints[0].x +
//            3 * pow(1 - t, 2) * t * controlPoints[1].x +
//            3 * (1 - t) * pow(t, 2) * controlPoints[2].x +
//            pow(t, 3) * controlPoints[3].x,
//
//            pow(1 - t, 3) * controlPoints[0].y +
//            3 * pow(1 - t, 2) * t * controlPoints[1].y +
//            3 * (1 - t) * pow(t, 2) * controlPoints[2].y +
//            pow(t, 3) * controlPoints[3].y
//        );
//        curvePoints.push_back(p);
//    }
//}
//
//// 绘制函数
//void myDisplay4() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    if (!controlPoints.empty()) {
//        glColor3f(1.0, 1.0, 1.0); // 设置控制点颜色为白色
//        glBegin(GL_POINTS);
//        for (const auto& point : controlPoints) {
//            glVertex2f(point.x, point.y);
//        }
//        glEnd();
//
//        if (controlPoints.size() == 4 && bDraw) {
//            std::vector<Point> curvePoints;
//            calcBezierCurve(curvePoints, controlPoints);
//
//            glColor3f(1.0, 0.0, 0.0); // 设置Bezier曲线颜色为红色
//            glBegin(GL_LINE_STRIP);
//            for (const auto& point : curvePoints) {
//                glVertex2f(point.x, point.y);
//            }
//            glEnd();
//        }
//    }
//
//    glFlush();
//}
//
//// 鼠标事件处理函数
//void mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        if (controlPoints.size() < 4) {
//            // 将屏幕坐标转换为世界坐标
//            int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
//            int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
//            controlPoints.emplace_back(
//                20.0f * (static_cast<float>(x) / windowWidth) - 10.0f,
//                10.0f - 20.0f * (static_cast<float>(y) / windowHeight)
//            );
//            if (controlPoints.size() == 4) {
//                bDraw = true;
//            }
//            glutPostRedisplay();
//        }
//    }
//}

#include <GL/glut.h>
#include "drawing.h"
#include <cmath> // for pow function



std::vector<Point> controlPoints; // Store control points
bool bDraw = false;

// Calculate the points on the Bezier curve
void calcBezierCurve(std::vector<Point>& curvePoints, const std::vector<Point>& controlPoints) {
    int numPoints = 100; // Number of points on the curve
    curvePoints.clear();
    for (int i = 0; i <= numPoints; ++i) {
        float t = static_cast<float>(i) / numPoints;
        Point p(
            pow(1 - t, 3) * controlPoints[0].x +
            3 * pow(1 - t, 2) * t * controlPoints[1].x +
            3 * (1 - t) * pow(t, 2) * controlPoints[2].x +
            pow(t, 3) * controlPoints[3].x,

            pow(1 - t, 3) * controlPoints[0].y +
            3 * pow(1 - t, 2) * t * controlPoints[1].y +
            3 * (1 - t) * pow(t, 2) * controlPoints[2].y +
            pow(t, 3) * controlPoints[3].y
        );
        curvePoints.push_back(p);
    }
}

//// Initialize the OpenGL environment (viewport and projection matrix)
//void myInit() {
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0); // Set orthographic projection
//    glMatrixMode(GL_MODELVIEW);
//}

// Display function to render the control points and Bezier curve
void myDisplay4() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (!controlPoints.empty()) {
        glColor3f(1.0, 1.0, 1.0); // Set control points color to white
        glBegin(GL_POINTS);
        for (const auto& point : controlPoints) {
            glVertex2f(point.x, point.y);
        }
        glEnd();

        if (controlPoints.size() == 4 && bDraw) {
            std::vector<Point> curvePoints;
            calcBezierCurve(curvePoints, controlPoints);

            glColor3f(1.0, 0.0, 0.0); // Set Bézier curve color to red
            glBegin(GL_LINE_STRIP);
            for (const auto& point : curvePoints) {
                glVertex2f(point.x, point.y);
            }
            glEnd();
        }
    }
    glFlush();
    //glutSwapBuffers();
}

// Mouse event handling function
void mouse4(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (controlPoints.size() < 4) {
            // Convert screen coordinates to world coordinates
            int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
            int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
            float worldX = (static_cast<float>(x) / windowWidth) * 20.0f - 10.0f;
            float worldY = 10.0f - (static_cast<float>(y) / windowHeight) * 20.0f;
            controlPoints.emplace_back(worldX, worldY);

            if (controlPoints.size() == 4) {
                bDraw = true;
            }
            glutPostRedisplay();
        }
    }
}
