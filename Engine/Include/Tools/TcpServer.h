#pragma once
#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "NetWork.h"

namespace engine::tools
{
    class TcpServer : private NetWork
    {
    public:

        static TcpServer * create(const unsigned port);
        static TcpServer * create(const string & address, const unsigned port, const unsigned poolSize = DEFAULT_POOL_SIZE, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
        
        void accept(const function<void (const int client, const struct sockaddr_in & clientInfo)> & callBack);
        void close(const function<void (const int client)> & callBack);
        void recv(const function<void (const int client, const string & str)> & callBack);
        const bool send(const string & str, const int client = -1) const;
        
    protected:
        virtual const bool init(const string & address, const unsigned port, const unsigned poolSize, const unsigned loopInterval);

    private:

    };
}

#endif //__TCP_SERVER_H__