#ifndef __LOG_H__
#define __LOG_H__

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

class Log : public Object
{
public:

    CREATEFUNC(Log);

    enum level{
        DEBUG = 0,
        INFO,
        NOTICE,
        WARN,
        ERR,
        CRIT,
        ALERT,
        EMERG
    };

    // 调试: 调试信息
    template<typename... Arguments>
    void debug(string str, const Arguments & ... args) const
    {
        _log(level::DEBUG, str, args...);
    }

    // 信息: 程序输出信息
    template<typename... Arguments>
    void info(string str, const Arguments & ... args) const
    {
        _log(level::INFO, str, args...);
    }

    // 通知: 程序可以运行但是还不够完美的错误
    template<typename... Arguments>
    void notice(string str, const Arguments & ... args) const
    {
        _log(level::NOTICE, str, args...);
    }

    // 警告性错误: 需要发出警告的错误
    template<typename... Arguments>
    void warning(string str, const Arguments & ... args) const
    {
        _log(level::WARN, str, args...);
    }

    // 一般错误: 一般性错误
    template<typename... Arguments>
    void error(string str, const Arguments & ... args) const
    {
        _log(level::ERR, str, args...);
    }

    // 临界值错误: 超过临界值的错误，例如一天24小时，而输入的是25小时这样
    template<typename... Arguments>
    void critical(string str, const Arguments & ... args) const
    {
        _log(level::CRIT, str, args...);
    }

    // 警戒性错误: 必须被立即修改的错误
    template<typename... Arguments>
    void alert(string str, const Arguments & ... args) const
    {
        _log(level::ALERT, str, args...);
    }

    // 严重错误: 导致系统崩溃无法使用
    template<typename... Arguments>
    void emerg(string str, const Arguments & ... args) const
    {
        _log(level::EMERG, str, args...);
    }

    //设置过滤级别　　低于过滤级别的信息不被输出
    void setFilterLevel(const level _level);

protected:
    Log(){}
    virtual const bool init(void);
        
    struct placeholder
    {
        unsigned paraIndex;
        string str;
        string format;
    };
private:

    //级别名称
    static string _levelName[];
    //过滤级别
    level _filter = level::DEBUG;

    //解析参数
    template<typename... Arguments>
    void _log(const level _level, string str, const Arguments & ... args) const
    {
        if(_level < _filter) return;

        //存储解析后的占位符
        vector<placeholder> placeholders;
        unsigned parameterCount = sizeof...(Arguments);

        if(parameterCount){

            //匹配占位符:{index[:format]}
            //js 可用: /([^\\{]*(\\.)?)*({(\d)([\s]*,[\s]*(([^\\}]*(\\.)?)*))?})/ig;
            regex reg("([^\\\\\\{]*(\\\\.)?)*(\\{(\\d)([\\s]*,[\\s]*(([^\\\\\\}]*(\\\\.)?)*))?\\})");

            auto matchBegin = sregex_iterator(str.begin(), str.end(), reg);
            auto matchEnd = sregex_iterator();

            for(sregex_iterator item = matchBegin; item != matchEnd; ++item){

                placeholder temp = {
                    .paraIndex = (unsigned)atoi(string(item->str(4)).c_str()),
                    .str = item->str(3),
                    .format = item->str(6)
                };

                bool exist = false;
                for(auto item : placeholders){
                    if(item.str != temp.str) continue; 
                    exist = true;
                    break;
                }
                if(exist) continue;

                //检查参数是否合法
                if(temp.paraIndex >= parameterCount)
                {
                    error("Error: Can not find the parameters with the [{0}] matching.", temp.str);
                    assert(temp.paraIndex < parameterCount);
                }
                
                placeholders.push_back(temp);
            }

            //处理打印信息
            _log(str, placeholders, parameterCount, args...);
        }

        //输出打印信息
        _log(_level, str);
    }

    //没有额外参数
    void _log(const level _level, const string & str) const
    {
        //输出打印信息
        stringstream sstr;
        sstr << "[" << _levelName[_level] << "] " << str;
        printLog(sstr.str());
    }

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

        for(auto item : placeholders){
            if(item.paraIndex != parameterIndex) continue;

            auto index = string::npos;
            
            while((index = str.find(item.str)) != string::npos){
                
                string temp_left = str.substr(0, index);
                string temp_right = str.substr(index + item.str.length(), str.length());
                str = temp_left + _format(item.format, arg) + temp_right;
            }
        }
    }

    //格式化参数
    template<typename Argument>
    string _format(const string & format, const Argument & source) const
    {
          stringstream strs;
          strs << source;
          return strs.str();
    }

    //输出日志
    void printLog(const string & log) const;
};

extern Log & log;

#endif //__LOG_H__