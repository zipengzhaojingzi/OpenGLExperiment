#include <GL/glut.h>
#include <iostream>

// ���ڱ߽�
const float xmin = -0.5f, ymin = -0.5f;
const float xmax = 0.5f, ymax = 0.5f;

// ��ǰ���Ƶ�ֱ�ߵ������յ�
float X1 = 0.0f, Y1 = 0.0f;
float X2 = 0.0f, Y2 = 0.0f;

// ��־λ���Ƿ�ִ�вü�
bool isClipped = false;

// ��ǰ�ü��㷨��1 = Cohen-Sutherland��2 = Liang-Barsky
int currentAlgorithm = 1;

// �����λ�ô洢
float mouseX1, mouseY1, mouseX2, mouseY2;
bool isFirstPointSet = false;

// ���������루����Cohen-Sutherland��
int computeOutCode(float x, float y) {
    int code = 0;  // INSIDE
    if (x < xmin) code |= 1;  // LEFT   0001
    if (x > xmax) code |= 2;  // RIGHT  0010
    if (y < ymin) code |= 4;  // BOTTOM  0100
    if (y > ymax) code |= 8;  // TOP  1000
    return code;
}

// Cohen-Sutherland�ü��㷨
bool cohenSutherlandClip(float& x1, float& y1, float& x2, float& y2) {
    int outcode1 = computeOutCode(x1, y1);
    int outcode2 = computeOutCode(x2, y2);
    bool accept = false;

    while (true) {
        if (!(outcode1 | outcode2)) {
            // ���˵���ڴ�����,��ȡ
            accept = true;
            break;
        }
        else if (outcode1 & outcode2) {
            // ���˵���ڴ����⣬����
            break;
        }
        else {
            // ������һ���˵��ڴ�����
            float x, y;
            int outcodeOut = outcode1 ? outcode1 : outcode2;  //ȡ�ڴ������

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

// ���Ѷ��ü��㷨
bool liangBarskyClip(float& x1, float& y1, float& x2, float& y2) {
    float dx = x2 - x1, dy = y2 - y1;
    float t0 = 0.0f, t1 = 1.0f;
    float p[4] = { -dx, dx, -dy, dy };
    float q[4] = { x1 - xmin, xmax - x1, y1 - ymin, ymax - y1 };

    for (int i = 0; i < 4; ++i) {
        if (p[i] == 0) {
            if (q[i] < 0) return false;  // ƽ�в��ڱ߽���
        }
        else {
            float t = q[i] / p[i];
            if (p[i] < 0) {
                t0 = std::max(t0, t);  // �����
            }
            else {
                t1 = std::min(t1, t);  // �뿪��
            }
        }
    }

    if (t0 > t1) return false;  // ֱ���ڴ����⣬���ɼ�

    x2 = x1 + t1 * dx;
    y2 = y1 + t1 * dy;
    x1 = x1 + t0 * dx;
    y1 = y1 + t0 * dy;
    return true;
}

// ��Ⱦ����
void myDisplay3() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ���Ʋü�����
    glColor3f(1.0f, 0.0f, 0.0f);  // ��ɫ
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // ���Ƶ�ǰֱ��
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
            glColor3f(0.0f, 1.0f, 0.0f);  // ��ɫ��ʾ�ü����ֱ��
            glBegin(GL_LINES);
            glVertex2f(x1_clipped, y1_clipped);
            glVertex2f(x2_clipped, y2_clipped);
            glEnd();
        }
    }
    else {
        glColor3f(0.0f, 0.0f, 1.0f);  // ��ɫ��ʾԭʼֱ��
        glBegin(GL_LINES);
        glVertex2f(X1, Y1);
        glVertex2f(X2, Y2);
        glEnd();
    }

    glFlush();
}

// ���̻ص�����
void keyboard3(unsigned char key, int x, int y) {
    switch (key) {
    case '1':  // ѡ��Cohen-Sutherland�㷨
        currentAlgorithm = 1;
        std::cout << "Selected: Cohen-Sutherland Algorithm\n";
        printf("Press key 'c' to Clip!\nPress key 'r' to Restore!\n");
        break;
    case '2':  // ѡ�����Ѷ��㷨
        currentAlgorithm = 2;
        std::cout << "Selected: Liang-Barsky Algorithm\n";
        printf("Press key 'c' to Clip!\nPress key 'r' to Restore!\n");
        break;
    case 'c':  // ִ�вü�
        isClipped = true;
        break;
    case 'r':  // ��ԭԭʼֱ��
        isClipped = false;
        break;
    case 27:  // ��ESC�˳�
        exit(0);
    default:
        break;
    }
    glutPostRedisplay();  // ����������Ⱦ
}

// ���ص�����
void mouse3(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // ����������ת��ΪOpenGL����
        float wx = (x - 250.0f) / 250.0f; // ���贰�ڴ�СΪ500x500
        float wy = (250.0f - y) / 250.0f; // ��תY��

        if (!isFirstPointSet) {
            // ��һ�ε���������
            mouseX1 = wx;
            mouseY1 = wy;
            isFirstPointSet = true;
        }
        else {
            // �ڶ��ε�������յ㲢���ñ�־λ
            mouseX2 = wx;
            mouseY2 = wy;
            isFirstPointSet = false;

            // ���µ�ǰ���Ƶ�ֱ�ߵ������յ�
            X1 = mouseX1;
            Y1 = mouseY1;
            X2 = mouseX2;
            Y2 = mouseY2;
            printf("Press key '1' to select: Cohen-Sutherland Algorithm\nPress key '2' to select: Liang-Barsky Algorithm\n");
            // ����������Ⱦ
            glutPostRedisplay();
        }
    }
}

//// ������
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("�ü��㷨");
//
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboard);
//    glutMouseFunc(mouse);  // ע�����ص�
//
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//
//    glutMainLoop();
//    return 0;
//}