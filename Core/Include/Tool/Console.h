#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <iostream>
#include <string>
#include <cstdarg>
#include <regex>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <sstream>

#include "Object.h"

using namespace std;

class Console : Object
{
public:

    template<typename... Arguments>
    void log(string str, const Arguments & ... args) const
    {
        vector<placeholder> placeholders;
        unsigned parameterCount = sizeof...(Arguments);
        cout << "parameterCount: " << parameterCount << endl;
        if(parameterCount){

            //匹配占位符:{index[:format]}
            regex reg("([^\\\\\\{]*((\\\\\\{)|\\\\)?)*(\\{(\\d)(:(([^\\\\\\}]*((\\\\\\})|\\\\)?)*?))?\\})");

            auto matchBegin = sregex_iterator(str.cbegin(), str.cend(), reg);
            auto matchEnd = sregex_iterator();

            for(sregex_iterator item = matchBegin; item != matchEnd; ++item){
                placeholder temp = {
                    .paraIndex = (unsigned)atoi(string(item->str(5)).c_str()),
                    .str = item->str(4),
                    .format = item->str(7)
                };

                bool exist = false;
                for(auto item : placeholders){
                    if(item.str != temp.str) continue; 
                    exist = true;
                    break;
                }
                if(exist) continue;

                //检查参数是否合法
                if(temp.paraIndex >= parameterCount){
                    cout << "Error: Can not find the parameters with the [" << temp.str << "] matching." << endl;
                    assert(temp.paraIndex < parameterCount);
                }
                
                placeholders.push_back(temp);
            }
        }

        _log(str, placeholders, parameterCount, args...);

        cout << "Log: " << str << endl;
    }

protected:
    virtual const bool init(void);

    struct placeholder
    {
        unsigned paraIndex;
        string str;
        string format;
    };
private:

    //处理动态参数
    template<typename Argument, typename... Arguments>
    void _log(string & str, const vector<placeholder> & placeholders, const unsigned parameterCount, const Argument & arg, const Arguments & ... args) const
    {
        _replace(str, placeholders, parameterCount - 1 - sizeof...(Arguments), arg);
        _log(str, placeholders, parameterCount, args...);
    }

    //处理动态参数
    template<typename Argument>
    void _log(string & str, const vector<placeholder> & placeholders, const unsigned parameterCount, const Argument & arg) const
    {
        _replace(str, placeholders, parameterCount - 1, arg);
    }

    //替换占位符
    template<typename Argument>
    void _replace(string & str, const vector<placeholder> & placeholders, const unsigned parameterIndex, const Argument & arg) const
    {
        cout << "parameterIndex: " << parameterIndex << "->" << arg << endl;

        for(auto item : placeholders){
            if(item.paraIndex != parameterIndex) continue;

            auto index = string::npos;
            while((index = str.find(item.str)) != string::npos){
                
                string temp_left = str.substr(0, index);
                string temp_right = str.substr(index + item.str.length(), str.length());

                stringstream strs;
                strs << temp_left << arg << temp_right;
                str = string(strs.str());
            }
        }
    }

};

extern Console console;

#endif //__CONSOLE_H__