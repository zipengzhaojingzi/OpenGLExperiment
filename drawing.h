#pragma once
#ifndef DRAWING_H
#define DRAWING_H

#include <vector>

// 点结构体定义
struct Point {
    float x, y;
    Point(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

// 绘图模式枚举
enum DrawMode { NONE, LINE, TRIANGLE, SQUARE, BEZIER };
extern DrawMode currentMode;

extern std::vector<Point> controlPoints; // 声明外部变量
extern bool bDraw;

//void calcBezierCurve(std::vector<Point>& curvePoints, const std::vector<Point>& controlPoints);


#endif // DRAWING_H