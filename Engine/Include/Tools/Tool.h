#pragma once
#ifndef __TOOL_H__
#define __TOOL_H__

#include "Object.h"
#include <string>

using namespace std;

namespace engine::tools{
    unsigned getStringLength(const string & str);
    string wsToS(const wstring & ws);
    wstring sTOWs(const string & s);
}

#endif //__TOOL_H__