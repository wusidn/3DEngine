#pragma once
#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__

#include "NetWork.h"

namespace engine::tools
{
    class UdpServer : private NetWork
    {
    public:
        static UdpServer & create(const unsigned port, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
        static UdpServer & create(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);

        //设置接受无连接消息回调
        void recvFrom(const function<void (const struct sockaddr_in * clientInfo, const string & str)> & callBack);

    protected:
        virtual const bool init(const string & address, const unsigned port, const unsigned loopInterval);
        
    private:

    };
}

#endif //__UDP_SERVER_H__