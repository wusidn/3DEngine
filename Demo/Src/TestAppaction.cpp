#include "TestAppaction.h"

#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "ScreenWorld.h"
#include "Zeus.h"
#include "Node.h"
#include "LogManager.h"
#include "Image.h"
#include "Textrue2D.h"
#include "Matrix2.h"
#include "Matrix3.h"

#include <iostream>
#include <cmath>

using namespace std;
using namespace engine;
using namespace tools;

TestAppaction & TestAppaction::instance(void)
{
    static TestAppaction & result = create();
    assert(result.ready());
    return result;
}


 void TestAppaction::start(void)
 {
        ScreenWorld::instance().append(Triangle::create(Vec2(.0f, .0f), Vec2(.0f, 100.0f), Vec2(100.0f, .0f)));
        ScreenWorld::instance().append(Rectangle::create(50.0f));

		Circle & fristCircle = Circle::create(1000.0f);
		fristCircle.position(Vec2(Zeus::instance().screenSize().width * 0.5f, Zeus::instance().screenSize().height * 0.5f));
		ScreenWorld::instance().append(fristCircle);

        // Vec3 location(1.0f, 2.0f, 3.0f);
        // Log.info("location[0] = {0}", location[0]);
        // Log.info("location[1] = {0}", location[1]);
        // Log.info("location[2] = {0}", location[2]);

        // location[1] += 5;

        // Log.info("location = {0}", location);

        Matrix2 matrix(Vec2(1.6666, 3.152454), Vec2(2.154, 4.556));

        Matrix2 matrix2(matrix);

        matrix[0][0] += 2.356645f;

        Log.info("matrix[0][0] = {0}", matrix[0][0]);
        Log.info("matrix[1][1] = {0}", matrix[1][0]);

        

        Log.info("matrix2[0][0] = {0}", matrix2[0][0]);
        Log.info("matrix2[1][1] = {0}", matrix2[1][0]);

        Log.info("matrix2 = {0}", matrix2);

        Matrix3 matrix3(5.123456789f);
        Log.info("matrix3 = {0}", matrix3);



        Textrue2D::create("asds.jpg");
 }

 void TestAppaction::update(const int dt)
 {
        int currDisplayTime = Zeus::instance().runningTime();

		Node & tr = *ScreenWorld::instance().root().chidren().at(1);
		tr.position(Vec2((Zeus::instance().windowSize().width - 100) * 0.5f + cos(currDisplayTime / 1000.0f) * (Zeus::instance().windowSize().width - 100) * 0.5f, (Zeus::instance().windowSize().height - 100) * 0.5f + sin(currDisplayTime / 1000.0f) * (Zeus::instance().windowSize().height - 100) * 0.5f));
 }