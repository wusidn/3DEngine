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

void Log::setFilterLevel(const level para)
{
    _filter = para;
}

Log & log = *Log::create();
