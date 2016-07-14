#pragma once
#ifndef __NET_WORK__
#define __NET_WORK__

#include "Object.h"
#include <string>
#include <sys/socket.h>

using namespace std;

namespace engine::tools
{
    class NetWork: public Object
    {
    public:
        static NetWork * create(const string & address, const unsigned port);
    protected:
        NetWork(){}
        virtual const bool init(const string & address, const unsigned port);
    private:
        int socket_id;
    };

    class TcpServer: public NetWork
    {
    public:
        static TcpServer * create(const string & address, const unsigned port);
    protected:
        TcpServer();
        virtual const bool init(const string & address, const unsigned port);
    };

    // class TcpClient: public Object
    // {
    // public:
    //     TcpClient * create(const string & address, const unsigned port);

    // };

    // class UdpClient: public Object
    // {
    // public:
    //     UdpClient * create(const string & address, const unsigned port);

    // };
}

#endif //__NET_WORK__