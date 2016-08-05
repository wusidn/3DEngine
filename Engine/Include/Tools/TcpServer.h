#pragma once
#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "NetWork.h"

namespace engine::tools
{
    class TcpServer : private NetWork
    {
    public:

        static TcpServer & create(const unsigned port);
        static TcpServer & create(const string & address, const unsigned port, const unsigned poolSize = DEFAULT_POOL_SIZE, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
        
        //设置客户端链接回调
        void accept(const function<void (const int client, const struct sockaddr_in & clientInfo)> & callBack);
        //设置客户端关闭回调
        void close(const function<void (const int client)> & callBack);
        //接收到消息回调
        void recv(const function<void (const int client, const string & str)> & callBack);
        //发送消息
        const bool send(const string & str) const;
        const bool send(const int client, const string & str) const;
        
    protected:
        virtual const bool init(const string & address, const unsigned port, const unsigned poolSize, const unsigned loopInterval);

    private:

    };
}

#endif //__TCP_SERVER_H__