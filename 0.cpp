#include <GL/glut.h>  // ����GLUT���ͷ�ļ���GLUT��OpenGLʵ�ù��߿⣬���ڼ򻯴��ں����봦��
#include <cstdlib>



//void Reshape(int w, int h);
//
//
//void Reshape(int w, int h)
//{
//    // �����ӿڣ�viewport��Ϊ�������ڴ�С���ӿڶ�����OpenGL��Ⱦ������
//    // �����ֱ������½�����(x, y)�Ϳ�ȡ��߶�(w, h)��
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//
//    // ָ����ǰ����ΪͶӰ���󣬲����ص�λ������һ����Ϊ��ȷ�����Ǵ�һ���ɾ���״̬��ʼ����ͶӰ��
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    // ����һ������ͶӰ���󡣶���2Dͼ�Σ�ʹ������ͶӰ�Ƿǳ������ģ�
//    // ��Ϊ�����������κ�͸��Ч��������ƽ�����ڱ任����Ȼƽ�С�
//    // �����ֱ�Ϊ����߽硢�ұ߽硢�±߽硢�ϱ߽硣
//    // ��������ǽ���������ϵ�ķ�Χ����Ϊ�봰�ڵ�����������ƥ�䡣
//    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
//}
//
//void drawPixel(float x, float y)
//{
//    glRasterPos2i(x, y);
//    glBegin(GL_POINTS);
//    glVertex2i(x, y);
//    glEnd();
//    glFlush(); // ȷ����������
//}
//
//
//void drawLineDDA(float x0, float y0, float x1, float y1)
//{
//    float dx = x1 - x0;
//    float dy = y1 - y0;
//    float steps;
//    float xIncrement, yIncrement;
//
//    // ������Ҫ�Ĳ�����ȡx��y����仯�����ֵ
//    if (abs(dx) > abs(dy))
//        steps = abs(dx);
//    else
//        steps = abs(dy);
//
//    // ����ÿ�ε���ʱx��y������
//    xIncrement = dx / steps;
//    yIncrement = dy / steps;
//
//    // ��ʼ����ʼ��
//    float x = x0;
//    float y = y0;
//
//    // �����߶�
//    for (float i = 0; i <= steps; i++)
//    {
//        drawPixel(round(x), round(y)); // ʹ��round()�Ը�����������������
//        x += xIncrement;
//        y += yIncrement;
//    }
//}
//// ������һ�����Խ�����������ֵ�ĺ���
//void swap_value(float& a, float& b)
//{
//    float temp = a;
//    a = b;
//    b = temp;
//}
//
//void drawLineBresenham(float x0, float y0, float x1, float y1)
//{
//    bool swap = false;
//    float dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//    float dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
//    float err = dx + dy, e2;  // error value e_xy
//
//    if (abs(dy) > abs(dx)) // swap values if slope is greater than 1 or less than -1
//    {
//        swap = true;
//        swap_value(dx, dy);
//    }
//
//    for (;;)
//    {
//        drawPixel(swap ? y0 : x0, swap ? x0 : y0); // draw pixel with swapped coordinates if needed
//        if (x0 == x1 && y0 == y1) break;
//        e2 = 2 * err;
//        if (e2 >= dy)
//        {
//            if (x0 == x1) break;
//            err += dy; x0 += sx;
//        }
//        if (e2 <= dx)
//        {
//            if (y0 == y1) break;
//            err += dx; y0 += sy;
//        }
//    }
//}
//


void myDisplay0(void)  // �����ͼ�ص�����myDisplay������Ҫ�ػ洰������ʱ����
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // ���������ɫΪ��ɫ��RGBA����������ɫΪ͸���ĺ�ɫ
    glClear(GL_COLOR_BUFFER_BIT);      // �����ɫ��������Ӧ���������õı���ɫ

    glColor3f(1.0f, 1.0f, 1.0f);       // ���õ�ǰ������ɫΪ��ɫ��RGB��
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // ����һ�����Σ�������ԭ�㣬�߳�Ϊ1����λ����

    //drawLineDDA(0.4, 0.25, -0.4, 0.25);

        glBegin(GL_TRIANGLES);             // ��ʼ����һ�������ζ���
        glColor3f(1.0f, 0.0f, 0.0f);   // ������һ���������ɫΪ��ɫ
        glVertex2f(0.0f, 1.0f);        // �����һ���������� (x=0.0, y=1.0)
        glColor3f(0.0f, 1.0f, 0.0f);   // ������һ���������ɫΪ��ɫ
        glVertex2f(0.8f, -0.5f);       // ����ڶ����������� (x=0.8, y=-0.5)
        glColor3f(0.0f, 0.0f, 1.0f);   // ������һ���������ɫΪ��ɫ
        glVertex2f(-0.8f, -0.5f);      // ����������������� (x=-0.8, y=-0.5)
        glEnd();                           // �������������ζ���

        glColor3f(1.0f, 1.0f, 0.0f);       // ����������ɫΪ��ɫ
        glBegin(GL_LINES);                 // ��ʼ�����߶�
        glVertex2f(0.4f, 0.25f);       // �����������
        glVertex2f(-0.4f, 0.25f);       // �����յ�����
            glEnd();                           // ���������߶�

        glBegin(GL_LINES);                 // ��ʼ�����߶�
        glVertex2f(0.4f, 0.25f);       // �����������
        glVertex2f(0.0f, -0.5f);       // �����յ�����
        glEnd();                           // ���������߶�

        glBegin(GL_LINES);                 // ��ʼ�����߶�
        glVertex2f(0.0f, -0.5f);       // �����յ�����
        glVertex2f(-0.4f, 0.25f);       // �����յ�����
        glEnd();                           // ���������߶�

        glPointSize(3);                    // ���õ��СΪ3����
        glBegin(GL_POINTS);               // ��ʼ����һ���
        glColor3f(1.0f, 0.0f, 0.0f);   // ������һ�������ɫΪ��ɫ
        glVertex2f(-0.4f, -0.4f);      // �����һ�������� (x=-0.4, y=-0.4)
        glColor3f(0.0f, 1.0f, 0.0f);   // ������һ�������ɫΪ��ɫ
        glVertex2f(0.0f, 0.0f);        // ����ڶ��������� (x=0.0, y=0.0)
        glColor3f(0.0f, 0.0f, 1.0f);   // ������һ�������ɫΪ��ɫ
        glVertex2f(0.4f, 0.4f);        // ��������������� (x=0.4, y=0.4)
        glEnd();                           // ���������

        //glutSwapBuffers();                 // ����˫����������ʾ���Ƶ����ݣ�����˫����ģʽ��
        glFlush();
}



//int main(int argc, char* argv[])       // ��������������ڵ�
//{
//    glutInit(&argc, argv);             // ��ʼ��GLUT�⣬���������в���
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // ������ʾģʽΪRGB��ɫģ�ͺ�˫������
//    glutInitWindowPosition(100, 100);  // ���ô������ڵ�λ������Ļ�ϵ�λ�� (x=100, y=100)
//    glutInitWindowSize(400, 400);      // ���ô������ڵĳߴ�Ϊ��400���ء���400����
//    glutCreateWindow("Hello OpenGL!"); // ����һ������Ϊ��Hello OpenGL!�����´���
//
//
//
//
//    glutDisplayFunc(myDisplay0);        // ע���ͼ�ص�������ָ����������Ҫ�ػ�ʱ����myDisplay����
//
//    //glutReshapeFunc(Reshape);
//    glutMainLoop();                    // ����GLUT���¼�ѭ������ʼ�����û�����ʹ�����Ϣ
//    return 0;                          // ����0��ʾ������������
//}