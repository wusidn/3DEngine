#include "Tool/Console.h"
#include <vector>

string Console::_levelName[]  = {
        "DEBUG",
        "INFO",
        "NOTICE",
        "WARN",
        "ERR",
        "CRIT",
        "ALERT",
        "EMERG"
    };

const bool Console::init(void)
{
    if(!Object::init()){
        return false;
    }

    return true;
}

void Console::setLevel(const level para)
{
    _level = para;
}

void Console::setFilterLevel(const level para)
{
    _filter = para;
}

Console & console = *Console::create();
