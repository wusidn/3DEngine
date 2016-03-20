#pragma once
#ifndef __GC_H__
#define __GC_H__

#include <list>
#include <iostream>
#include "Object.h"
using namespace std;

class Gc
{
private:
    list<const Object *> * objectPool;
    static Gc * instance;
public:
    static Gc & getInstance(void);

    Gc(void);
    void clean(void);
    void watch(const Object *);
};
#endif //__GC_H__
