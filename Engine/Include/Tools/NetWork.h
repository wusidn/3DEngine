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

namespace engine
{
    namespace tools
    {
        class NetWork: public Object
        {
        public:

            //绑定本机ip　
            const bool bind(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT) const;

            //链接目标ip
            const bool connect(const string & address = DEFAULT_ADDR, const unsigned port = DEFAULT_PORT, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
            
            //监听绑定的本机ip
            const bool listen(const unsigned poolSize = DEFAULT_POOL_SIZE, const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);
            //取消监听
            void unlisten();

            //循环调用recvfrom
            const bool loopRecvFrom(const unsigned loopInterval = DEFAULT_LOOP_INTERVAL);

            //设置客户端链接回调
            void accept(const function<void (const int client, const struct sockaddr_in & clientInfo)> & callBack);
            
            //设置客户端关闭回调
            void close(const function<void (const int client)> & callBack);

            //接收到消息回调
            void recv(const function<void (const int client, const string & str)> & callBack);

            //设置接受无连接消息回调
            void recvFrom(const function<void (const struct sockaddr_in * clientInfo, const string & str)> & callBack);

            //发送消息
            const bool send(const string & str) const;
            const bool send(const int client, const string & str) const;

        protected:
            NetWork(){}
            virtual const bool init(const int type = SOCK_STREAM);

            int socket_id;
            map<const int, struct sockaddr_in *> clientList;
        private:
                    
            bool running = false;
            
            function<void (const int client, const struct sockaddr_in & clientInfo)> acceptCallBack = nullptr;
            function<void (const int client)> closeCallBack = nullptr;
            function<void (const int client, const string & str)> recvCallBack = nullptr;
            function<void (const struct sockaddr_in * clientInfo, const string & str)> recvFromCallBack = nullptr;

        };
    }
}

#endif //__NET_WORK__