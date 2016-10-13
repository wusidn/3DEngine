#pragma once
#ifndef __FILE_H__
#define __FILE_H__

#include "Object.h"
#include <string>
#include <fstream>

using namespace std;

namespace engine
{
    namespace tools
    {
        class File: public Object
        {
        public:

            //以文本格式读取所有字符
            static string readAllText(const string & filePath);

            //判断文件夹或文件是否存在
            static const bool pathIsExists(const string & path);

            CREATEFUNC(File);
            static File & createWithFilePath(const string & filePath);
        
            const bool open(const int mode = ios::in | ios::out);
            const bool open(const string & filePath, const int mode = ios::in | ios::out);
            
        protected:
            virtual const bool init(void);
            virtual const bool init(const string & filePath);
            
            virtual ~File(void);
            
        private:
            string * _filePath;
        };
    }
}

#endif //__FILE_H__



