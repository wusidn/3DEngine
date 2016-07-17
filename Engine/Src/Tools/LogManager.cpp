#include "LogManager.h"
#include "Uuid.h"

namespace engine::tools{

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

    mutex LogManager::mtx;

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
        //加线程锁锁
        unique_lock<mutex> lck(mtx, defer_lock);
        lck.lock();
        //暂时只有输出到终端功能
        cout << "[" << _levelName[_level] << "] " << log << endl;
        lck.unlock();
    }

    LogManager & Log = *LogManager::create();
}
