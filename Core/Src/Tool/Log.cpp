#include "Tool/Log.h"
#include "Tool/Uuid.h"
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

map<string, string> Log::escapes;

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

void Log::printLog(const level _level, const string & log) const
{
    //暂时只有输出到终端功能
    cout << "[" << _levelName[_level] << "] " << log << endl;
}

Log & log = *Log::create();
