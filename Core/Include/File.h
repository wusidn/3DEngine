#pragma once
#ifndef __FILE_H__
#define __FILE_H__

#include "Object.h"
#include <string>

using namespace std;

class File: public Object
{
public:

    enum openType{

    };

    CREATEFUNC(File);
    static File * createWithFilePath(const string & filePath);
    static string & readAllText(const string & filePath);

    virtual const bool init(void);
    virtual const bool init(const string & filePath);

    const bool open

private:
    string * filePath;

protected:
    virtual ~File(void);
};

#endif //__FILE_H__



