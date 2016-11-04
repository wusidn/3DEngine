#include "Uuid.h"
#include <cstring>


namespace engine
{
    namespace tools
    {
        Uuid & Uuid::create(const Uuid & _uuid)
        {
            Uuid & result = create();
            bool uuidInit = result.init(_uuid);

            assert(uuidInit);

            if(!uuidInit){ result.initializeError(1); }
            return result;
        }

        const bool Uuid::init(void)
        {
            if(!Object::init()){ return false; }
            uuid_generate(data);
            return true;
        }

        const bool Uuid::init(const Uuid & _uuid)
        {
            memcpy(data, _uuid.data, sizeof(_uuid.data));

            return true;
        }

        const string Uuid::toString(void) const
        {
            char temp[33] = {0};
            for(unsigned i = 0; i < 16; ++i)
            {
                sprintf(temp + 2 * i, "%02X", data[i]);
            }
            return temp;
        }

        ostream & operator<< (ostream & _out, const Uuid & _uuid)
        {
            return _out << _uuid.toString();
        }
    }
}