#include "LogManager.h"
#include "Tool/Uuid.h"
#include <vector>

string LogManager::_levelName[]  = {
        "DEBUG",
        "INFO",
        "NOTICE",
        "WARN",
        "ERR",
        "CRIT",
        "ALERT",
        "EMERG"
    };

map<string, string> LogManager::escapes;

const bool LogManager::init(void)
{
    if(!Object::init()){
        return false;
    }

    return true;
}

void LogManager::setFilterLevel(const level _level)
{
    _filter = _level;
}

void LogManager::printLog(const level _level, const string & log) const
{
    //暂时只有输出到终端功能
    cout << "[" << _levelName[_level] << "] " << log << endl;
}

LogManager & Log = *LogManager::create();
