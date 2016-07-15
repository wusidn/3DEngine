#pragma once
#ifndef __NET_WORK__
#define __NET_WORK__

#include "Object.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>
#include <map>


#define DEFAULT_ADDR ""
#define DEFAULT_PORT 5432
#define DEFAULT_POOL_SIZE 200
#define DEFAULT_LOOP_INTERVAL 10
#define DEFAULT_RECV_BUFFER_SIZE 1024

using namespace std;

namespace engine::tools
{
    class NetWork: public Object
    {
    public:
        CREATEFUNC(NetWork);

        const bool bind(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT) const;

        const bool connect(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
        
        const bool listen(const unsigned poolSize = DEFAULT_POOL_SIZE, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
        void unlisten();

        void accept(const function<void (const int client)> & callBack);
        void close(const function<void (const int client)> & callBack);

        void recv(const function<void (const int client, const string & str)> & callBack);
        
        const bool send(const string & str, const int client = -1) const;

    protected:
        NetWork(){}
        virtual const bool init();
    private:
        int socket_id;
        map<const int, struct sockaddr_in *> clientList;

        bool listenRunning = false;
        
        function<void (const int client)> acceptCallBack = nullptr;
        function<void (const int client)> closeCallBack = nullptr;
        
        function<void (const int client, const string & str)> recvCallBack = nullptr;
        
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