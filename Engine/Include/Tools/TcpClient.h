#pragma once
#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include "NetWork.h"

namespace engine
{
    namespace tools
    {
        class TcpClient : public NetWork
        {
        public:
            static TcpClient & create(const string & address, const unsigned port = DEFAULT_PORT, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
            
            //设置客户端关闭回调
            void close(const function<void (const int client)> & callBack);
            //接收到消息回调
            void recv(const function<void (const int client, const string & str)> & callBack);
            //发送消息
            const bool send(const string & str) const;

        protected:
            
            virtual const bool init(void);
            virtual const bool init(const string & address, const unsigned port, const unsigned loopInterval);
        private:
            CREATEFUNC(TcpClient);
        };
    }
}

#endif //__TCP_CLIENT_H__
