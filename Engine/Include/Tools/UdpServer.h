#pragma once
#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__

#include "NetWork.h"

namespace engine::tools
{
    class UdpServer : private NetWork
    {
    public:
        static UdpServer * create(const unsigned port, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
        static UdpServer * create(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);

    protected:
        virtual const bool init(const string & address, const unsigned port, const unsigned loopInterval);
        
        //接收到消息回调
        // void recv(const function<void (const static , const string & str)> & callBack);
    private:

    };
}

#endif //__UDP_SERVER_H__