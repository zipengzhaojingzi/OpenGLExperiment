#include <GL/glut.h>
#include <iostream>

// 窗口边界
const float xmin = -0.5f, ymin = -0.5f;
const float xmax = 0.5f, ymax = 0.5f;

// 当前绘制的直线的起点和终点
float X1 = 0.0f, Y1 = 0.0f;
float X2 = 0.0f, Y2 = 0.0f;

// 标志位：是否执行裁剪
bool isClipped = false;

// 当前裁剪算法：1 = Cohen-Sutherland，2 = Liang-Barsky
int currentAlgorithm = 1;

// 鼠标点击位置存储
float mouseX1, mouseY1, mouseX2, mouseY2;
bool isFirstPointSet = false;

// 计算区域码（用于Cohen-Sutherland）
int computeOutCode(float x, float y) {
    int code = 0;  // INSIDE
    if (x < xmin) code |= 1;  // LEFT   0001
    if (x > xmax) code |= 2;  // RIGHT  0010
    if (y < ymin) code |= 4;  // BOTTOM  0100
    if (y > ymax) code |= 8;  // TOP  1000
    return code;
}

// Cohen-Sutherland裁剪算法
bool cohenSutherlandClip(float& x1, float& y1, float& x2, float& y2) {
    int outcode1 = computeOutCode(x1, y1);
    int outcode2 = computeOutCode(x2, y2);
    bool accept = false;

    while (true) {
        if (!(outcode1 | outcode2)) {
            // 两端点均在窗口内,简取
            accept = true;
            break;
        }
        else if (outcode1 & outcode2) {
            // 两端点均在窗口外，简弃
            break;
        }
        else {
            // 至少有一个端点在窗口外
            float x, y;
            int outcodeOut = outcode1 ? outcode1 : outcode2;  //取在窗口外的

            if (outcodeOut & 8) {  // TOP
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (outcodeOut & 4) {  // BOTTOM
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (outcodeOut & 2) {  // RIGHT
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (outcodeOut & 1) {  // LEFT
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (outcodeOut == outcode1) {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                outcode2 = computeOutCode(x2, y2);
            }
        }
    }
    return accept;
}

// 梁友栋裁剪算法
bool liangBarskyClip(float& x1, float& y1, float& x2, float& y2) {
    float dx = x2 - x1, dy = y2 - y1;
    float t0 = 0.0f, t1 = 1.0f;
    float p[4] = { -dx, dx, -dy, dy };
    float q[4] = { x1 - xmin, xmax - x1, y1 - ymin, ymax - y1 };

    for (int i = 0; i < 4; ++i) {
        if (p[i] == 0) {
            if (q[i] < 0) return false;  // 平行并在边界外
        }
        else {
            float t = q[i] / p[i];
            if (p[i] < 0) {
                t0 = std::max(t0, t);  // 进入点
            }
            else {
                t1 = std::min(t1, t);  // 离开点
            }
        }
    }

    if (t0 > t1) return false;  // 直线在窗口外，不可见

    x2 = x1 + t1 * dx;
    y2 = y1 + t1 * dy;
    x1 = x1 + t0 * dx;
    y1 = y1 + t0 * dy;
    return true;
}

// 渲染函数
void myDisplay3() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制裁剪窗口
    glColor3f(1.0f, 0.0f, 0.0f);  // 红色
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // 绘制当前直线
    if (isClipped) {
        float x1_clipped = X1, y1_clipped = Y1;
        float x2_clipped = X2, y2_clipped = Y2;
        bool visible = false;

        if (currentAlgorithm == 1) {
            visible = cohenSutherlandClip(x1_clipped, y1_clipped, x2_clipped, y2_clipped);
        }
        else if (currentAlgorithm == 2) {
            visible = liangBarskyClip(x1_clipped, y1_clipped, x2_clipped, y2_clipped);
        }

        if (visible) {
            glColor3f(0.0f, 1.0f, 0.0f);  // 绿色表示裁剪后的直线
            glBegin(GL_LINES);
            glVertex2f(x1_clipped, y1_clipped);
            glVertex2f(x2_clipped, y2_clipped);
            glEnd();
        }
    }
    else {
        glColor3f(0.0f, 0.0f, 1.0f);  // 蓝色表示原始直线
        glBegin(GL_LINES);
        glVertex2f(X1, Y1);
        glVertex2f(X2, Y2);
        glEnd();
    }

    glFlush();
}

// 键盘回调函数
void keyboard3(unsigned char key, int x, int y) {
    switch (key) {
    case '1':  // 选择Cohen-Sutherland算法
        currentAlgorithm = 1;
        std::cout << "Selected: Cohen-Sutherland Algorithm\n";
        printf("Press key 'c' to Clip!\nPress key 'r' to Restore!\n");
        break;
    case '2':  // 选择梁友栋算法
        currentAlgorithm = 2;
        std::cout << "Selected: Liang-Barsky Algorithm\n";
        printf("Press key 'c' to Clip!\nPress key 'r' to Restore!\n");
        break;
    case 'c':  // 执行裁剪
        isClipped = true;
        break;
    case 'r':  // 复原原始直线
        isClipped = false;
        break;
    case 27:  // 按ESC退出
        exit(0);
    default:
        break;
    }
    glutPostRedisplay();  // 请求重新渲染
}

// 鼠标回调函数
void mouse3(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // 将窗口坐标转换为OpenGL坐标
        float wx = (x - 250.0f) / 250.0f; // 假设窗口大小为500x500
        float wy = (250.0f - y) / 250.0f; // 翻转Y轴

        if (!isFirstPointSet) {
            // 第一次点击设置起点
            mouseX1 = wx;
            mouseY1 = wy;
            isFirstPointSet = true;
        }
        else {
            // 第二次点击设置终点并重置标志位
            mouseX2 = wx;
            mouseY2 = wy;
            isFirstPointSet = false;

            // 更新当前绘制的直线的起点和终点
            X1 = mouseX1;
            Y1 = mouseY1;
            X2 = mouseX2;
            Y2 = mouseY2;
            printf("Press key '1' to select: Cohen-Sutherland Algorithm\nPress key '2' to select: Liang-Barsky Algorithm\n");
            // 请求重新渲染
            glutPostRedisplay();
        }
    }
}

//// 主函数
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("裁剪算法");
//
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboard);
//    glutMouseFunc(mouse);  // 注册鼠标回调
//
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//
//    glutMainLoop();
//    return 0;
//}