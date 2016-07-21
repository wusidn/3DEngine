#pragma once
#ifndef __UDP_CLIENT_H__
#define __UDP_CLIENT_H__

#include "NetWork.h"

namespace engine::tools
{
    class UdpClient : private NetWork
    {
    public:
        UdpClient * create(const string & address, const unsigned port);

    protected:
        const bool send(const string & str);
    };
}

#endif //__UDP_CLIENT_H__