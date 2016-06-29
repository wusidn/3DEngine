#include "Tool/Uuid.h"
#include <cstring>

Uuid * Uuid::create(const Uuid & _uuid)
{
    Uuid * result = new Uuid();
    if(!result->init(_uuid)){
        delete result;
        result = nullptr;
    }
    return result;
}

const bool Uuid::init(void)
{
    if(!Object::init()){
        return false;
    }
    uuid_generate(data);
    return true;
}

const bool Uuid::init(const Uuid & _uuid)
{
    if(!Object::init()){
        return false;
    }

    memcpy(data, _uuid.data, sizeof(_uuid.data));

    return true;
}

const string Uuid::toString(void) const
{
    char temp[33] = {0};
    for(unsigned i = 0; i < 16; ++i){
        sprintf(temp + 2 * i, "%02X", data[i]);
    }
    return temp;
}

ostream & operator<< (ostream & _out, const Uuid & _uuid)
{
    return _out << _uuid.toString();
}