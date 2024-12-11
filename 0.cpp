#include <GL/glut.h>  // 包含GLUT库的头文件，GLUT是OpenGL实用工具库，用于简化窗口和输入处理
#include <cstdlib>



//void Reshape(int w, int h);
//
//
//void Reshape(int w, int h)
//{
//    // 设置视口（viewport）为整个窗口大小。视口定义了OpenGL渲染的区域。
//    // 参数分别是左下角坐标(x, y)和宽度、高度(w, h)。
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//
//    // 指定当前矩阵为投影矩阵，并加载单位矩阵。这一步是为了确保我们从一个干净的状态开始设置投影。
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    // 定义一个正交投影矩阵。对于2D图形，使用正交投影是非常常见的，
//    // 因为它不会引入任何透视效果，保持平行线在变换后仍然平行。
//    // 参数分别为：左边界、右边界、下边界、上边界。
//    // 在这里，我们将世界坐标系的范围设置为与窗口的像素坐标相匹配。
//    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
//}
//
//void drawPixel(float x, float y)
//{
//    glRasterPos2i(x, y);
//    glBegin(GL_POINTS);
//    glVertex2i(x, y);
//    glEnd();
//    glFlush(); // 确保立即绘制
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
//    // 计算需要的步数，取x和y方向变化的最大值
//    if (abs(dx) > abs(dy))
//        steps = abs(dx);
//    else
//        steps = abs(dy);
//
//    // 计算每次迭代时x和y的增量
//    xIncrement = dx / steps;
//    yIncrement = dy / steps;
//
//    // 初始化起始点
//    float x = x0;
//    float y = y0;
//
//    // 绘制线段
//    for (float i = 0; i <= steps; i++)
//    {
//        drawPixel(round(x), round(y)); // 使用round()对浮点数进行四舍五入
//        x += xIncrement;
//        y += yIncrement;
//    }
//}
//// 假设有一个可以交换两个整数值的函数
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


void myDisplay0(void)  // 定义绘图回调函数myDisplay，当需要重绘窗口内容时调用
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 设置清除颜色为黑色（RGBA），即背景色为透明的黑色
    glClear(GL_COLOR_BUFFER_BIT);      // 清除颜色缓冲区，应用上面设置的背景色

    glColor3f(1.0f, 1.0f, 1.0f);       // 设置当前绘制颜色为白色（RGB）
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // 绘制一个矩形，中心在原点，边长为1个单位长度

    //drawLineDDA(0.4, 0.25, -0.4, 0.25);

        glBegin(GL_TRIANGLES);             // 开始定义一组三角形顶点
        glColor3f(1.0f, 0.0f, 0.0f);   // 设置下一个顶点的颜色为红色
        glVertex2f(0.0f, 1.0f);        // 定义第一个顶点坐标 (x=0.0, y=1.0)
        glColor3f(0.0f, 1.0f, 0.0f);   // 设置下一个顶点的颜色为绿色
        glVertex2f(0.8f, -0.5f);       // 定义第二个顶点坐标 (x=0.8, y=-0.5)
        glColor3f(0.0f, 0.0f, 1.0f);   // 设置下一个顶点的颜色为蓝色
        glVertex2f(-0.8f, -0.5f);      // 定义第三个顶点坐标 (x=-0.8, y=-0.5)
        glEnd();                           // 结束定义三角形顶点

        glColor3f(1.0f, 1.0f, 0.0f);       // 设置线条颜色为黄色
        glBegin(GL_LINES);                 // 开始定义线段
        glVertex2f(0.4f, 0.25f);       // 线条起点坐标
        glVertex2f(-0.4f, 0.25f);       // 线条终点坐标
            glEnd();                           // 结束定义线段

        glBegin(GL_LINES);                 // 开始定义线段
        glVertex2f(0.4f, 0.25f);       // 线条起点坐标
        glVertex2f(0.0f, -0.5f);       // 线条终点坐标
        glEnd();                           // 结束定义线段

        glBegin(GL_LINES);                 // 开始定义线段
        glVertex2f(0.0f, -0.5f);       // 线条终点坐标
        glVertex2f(-0.4f, 0.25f);       // 线条终点坐标
        glEnd();                           // 结束定义线段

        glPointSize(3);                    // 设置点大小为3像素
        glBegin(GL_POINTS);               // 开始定义一组点
        glColor3f(1.0f, 0.0f, 0.0f);   // 设置下一个点的颜色为红色
        glVertex2f(-0.4f, -0.4f);      // 定义第一个点坐标 (x=-0.4, y=-0.4)
        glColor3f(0.0f, 1.0f, 0.0f);   // 设置下一个点的颜色为绿色
        glVertex2f(0.0f, 0.0f);        // 定义第二个点坐标 (x=0.0, y=0.0)
        glColor3f(0.0f, 0.0f, 1.0f);   // 设置下一个点的颜色为蓝色
        glVertex2f(0.4f, 0.4f);        // 定义第三个点坐标 (x=0.4, y=0.4)
        glEnd();                           // 结束定义点

        //glutSwapBuffers();                 // 交换双缓冲区，显示绘制的内容（对于双缓冲模式）
        glFlush();
}



//int main(int argc, char* argv[])       // 主函数，程序入口点
//{
//    glutInit(&argc, argv);             // 初始化GLUT库，解析命令行参数
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 设置显示模式为RGB颜色模型和双缓冲区
//    glutInitWindowPosition(100, 100);  // 设置创建窗口的位置在屏幕上的位置 (x=100, y=100)
//    glutInitWindowSize(400, 400);      // 设置创建窗口的尺寸为宽400像素、高400像素
//    glutCreateWindow("Hello OpenGL!"); // 创建一个标题为“Hello OpenGL!”的新窗口
//
//
//
//
//    glutDisplayFunc(myDisplay0);        // 注册绘图回调函数，指定当窗口需要重绘时调用myDisplay函数
//
//    //glutReshapeFunc(Reshape);
//    glutMainLoop();                    // 进入GLUT主事件循环，开始处理用户输入和窗口消息
//    return 0;                          // 返回0表示程序正常结束
//}