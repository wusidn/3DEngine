#pragma once
#ifndef __NET_WORK__
#define __NET_WORK__

#include "Object.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>


#define DEFAULT_ADDR ""
#define DEFAULT_PORT 5432
#define DEFAULT_POOL_SIZE 200
#define DEFAULT_ACCEPT_INTERVAL 1000

using namespace std;

namespace engine::tools
{
    class NetWork: public Object
    {
    public:
        CREATEFUNC(NetWork);
        const bool bind(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT) const;
        const bool listen(const unsigned poolSize = DEFAULT_POOL_SIZE) const;
        const bool accept(const function<void (const struct sockaddr_in clientAddr)> & callBack, const unsigned acceptInterval = DEFAULT_ACCEPT_INTERVAL);
    protected:
        NetWork(){}
        virtual const bool init();
    private:
        int socket_id;
        // function<void (struct sockaddr_in clientAddr)> acceptCallBack = nullptr;
    };

    class TcpServer: public NetWork
    {
    public:
        static TcpServer * create(const string & address, const unsigned port);
    protected:
        TcpServer();
        virtual const bool init(const string & address, const unsigned port);
    private:
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