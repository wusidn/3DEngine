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

        Textrue2D::create("asds.jpg");
 }

 void TestAppaction::update(const int dt)
 {
        int currDisplayTime = Zeus::instance().runningTime();

		Node & tr = *ScreenWorld::instance().root().chidren().at(1);
		tr.position(Vec2((Zeus::instance().windowSize().width - 100) * 0.5f + cos(currDisplayTime / 1000.0f) * (Zeus::instance().windowSize().width - 100) * 0.5f, (Zeus::instance().windowSize().height - 100) * 0.5f + sin(currDisplayTime / 1000.0f) * (Zeus::instance().windowSize().height - 100) * 0.5f));
 }