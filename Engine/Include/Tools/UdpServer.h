#pragma once
#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__

#include "NetWork.h"

namespace engine::tools
{
    class UdpServer : private NetWork
    {
    public:
        static UdpServer * create(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT);

    protected:
        virtual const bool init(const string & address, const unsigned port);
        
        //接收到消息回调
        void recv(const function<void (const int client, const string & str)> & callBack);
    };
}

#endif //__UDP_SERVER_H__