#include "Tool/Log.h"
#include <vector>

string Log::_levelName[]  = {
        "DEBUG",
        "INFO",
        "NOTICE",
        "WARN",
        "ERR",
        "CRIT",
        "ALERT",
        "EMERG"
    };

const bool Log::init(void)
{
    if(!Object::init()){
        return false;
    }

    return true;
}

void Log::setFilterLevel(const level _level)
{
    _filter = _level;
}

void Log::printLog(const string & log) const
{
    //暂时只有输出到终端功能
    cout << log << endl;
}

Log & log = *Log::create();
