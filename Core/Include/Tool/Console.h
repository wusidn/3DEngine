#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <iostream>
#include <string>
#include <cstdarg>
#include <regex>

#include "Object.h"

using namespace std;

class Console : Object
{
public:

    template<typename... Arguments>
    void log(string str, const Arguments & ... args) const
    {
        cout << "haha" << str << sizeof...(Arguments) << endl;
        cout << "haha" << str;

        //regex reg("([^\\{]*((\\{)|\\)?)*({(\\d)(:(([^\\}]*((\\})|\\)?)*?))?}");
        // regex reg("([^\\\\\\{]*((\\\\\\{)|\\\\)?)*(\\{(\\d)(:(([^\\\\\\}]*((\\\\\\})|\\\\)?)*?))?\\}");
        string temp = "([^\\\\\\{]*((\\\\\\{)|\\\\)?)*(\\{(\\d)(:(([^\\\\\\}]*((\\\\\\})|\\\\)?)*?))?\\})";
        cout << "temp: " << temp << endl;
         regex reg("([^\\\\\\{]*((\\\\\\{)|\\\\)?)*(\\{(\\d)(:(([^\\\\\\}]*((\\\\\\})|\\\\)?)*?))?\\})[\\w\\W]*");
        smatch result;
        regex_match(str.cbegin(), str.cend(), result, reg);

        cout << "result.length = " << result.size() << endl;

        for(unsigned i = 0; i < result.size(); ++i){
            cout << "[" << i << "]: " << result[i] << endl;
        }

        _log(str, args...);
        // log(str, args...);
    }

protected:
    virtual const bool init(void);


private:
    template<typename Argument, typename... Arguments>
    void _log(string & str, const Argument & arg, const Arguments & ... args) const
    {
        cout << arg;
        _log(str, args...);
    }

    template<typename Argument>
    void _log(string & str, const Argument & arg) const
    {
        cout << arg << endl;
    }

};

extern Console console;

#endif //__CONSOLE_H__