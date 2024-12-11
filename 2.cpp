#include <GL/glut.h>  // ����GLUT���ͷ�ļ���GLUT��OpenGLʵ�ù��߿⣬���ڼ򻯴��ں����봦��


void drawSquare() { // ����������ԭ�㣬�߳�Ϊ2��������
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f); // ���½Ƕ���
    glVertex2f(0.5f, -0.5f); // ���½Ƕ���
    glVertex2f(0.5f, 0.5f);  // ���ϽǶ���
    glVertex2f(-0.5f, 0.5f); // ���ϽǶ���
    glEnd();
}


void myDisplay2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);       // ���õ�ǰ������ɫΪ��ɫ��RGB��
    glRectf(-1.5f, -1.5f, 1.5f, 1.5f); // ����һ�����Σ�������ԭ�㣬�߳�Ϊ1����λ����

    //drawLineDDA(0.4, 0.25, -0.4, 0.25);



    // ���õ�ǰ����Ϊ��λ����
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);     // ���û�����ɫΪ��ɫ
    drawSquare();                 // ���û��������εĺ���
    // Ӧ��ƽ�Ʊ任
    glScalef(0.25f, 0.25f, 1.0f);        // ���ŵ�ԭ����һ���С
    glTranslatef(1.0, 1.0, 0.0);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // ��Z����ʱ����ת45��
    glColor3f(1.0, 1.0, 0.0);     // ���û�����ɫΪyellow
    drawSquare();                 // ���û��������εĺ���

    // Ӧ����ת�任 (�Ƕ�, x�����, y�����, z�����)
    //glRotatef(theta, vx, vy, vz);

    // Ӧ�����ű任
    //glScalef(sx, sy, sz);

    // �����������...
    glFlush();
}

void transForm() {
    //glLoadIdentity();
    glScalef(0.25f, 0.25f, 1.0f);        // ���ŵ�ԭ����1/4��С
    //glTranslatef(1.0, 1.0, 0.0);
    //glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // ��Z����ʱ����ת45��
    glColor3f(1.0, 1.0, 0.0);     // ���û�����ɫΪyellow
}