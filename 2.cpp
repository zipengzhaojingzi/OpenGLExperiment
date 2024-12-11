#include <GL/glut.h>  // 包含GLUT库的头文件，GLUT是OpenGL实用工具库，用于简化窗口和输入处理


void drawSquare() { // 绘制中心在原点，边长为2的正方形
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f); // 左下角顶点
    glVertex2f(0.5f, -0.5f); // 右下角顶点
    glVertex2f(0.5f, 0.5f);  // 右上角顶点
    glVertex2f(-0.5f, 0.5f); // 左上角顶点
    glEnd();
}


void myDisplay2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);       // 设置当前绘制颜色为白色（RGB）
    glRectf(-1.5f, -1.5f, 1.5f, 1.5f); // 绘制一个矩形，中心在原点，边长为1个单位长度

    //drawLineDDA(0.4, 0.25, -0.4, 0.25);



    // 重置当前矩阵为单位矩阵
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);     // 设置绘制颜色为红色
    drawSquare();                 // 调用绘制正方形的函数
    // 应用平移变换
    glScalef(0.25f, 0.25f, 1.0f);        // 缩放到原来的一半大小
    glTranslatef(1.0, 1.0, 0.0);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // 绕Z轴逆时针旋转45度
    glColor3f(1.0, 1.0, 0.0);     // 设置绘制颜色为yellow
    drawSquare();                 // 调用绘制正方形的函数

    // 应用旋转变换 (角度, x轴分量, y轴分量, z轴分量)
    //glRotatef(theta, vx, vy, vz);

    // 应用缩放变换
    //glScalef(sx, sy, sz);

    // 绘制你的物体...
    glFlush();
}

void transForm() {
    //glLoadIdentity();
    glScalef(0.25f, 0.25f, 1.0f);        // 缩放到原来的1/4大小
    //glTranslatef(1.0, 1.0, 0.0);
    //glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // 绕Z轴逆时针旋转45度
    glColor3f(1.0, 1.0, 0.0);     // 设置绘制颜色为yellow
}