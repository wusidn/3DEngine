#include "NetWork.h"
#include "LogManager.h"

#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#include <thread>
#include <unistd.h>

#include <iostream>

using namespace std;

namespace engine
{
    namespace tools
    {
        const bool NetWork::init(const int type)
        {
            if(!Object::init()){ return false; }

            socket_id = socket(AF_INET, type, 0);
            if(socket_id < 0){ return false; }

            int flag = fcntl(socket_id, F_GETFL, 0);
            fcntl(socket_id, F_SETFL, flag | O_NONBLOCK);

            return true;
        }

        const bool NetWork::bind(const string & address, const unsigned port) const
        {
            struct sockaddr_in net_sockaddr;
            memset(&net_sockaddr, 0, sizeof(net_sockaddr));
            net_sockaddr.sin_family = AF_INET;
            net_sockaddr.sin_port = htons(port);

            if(address.length() <= 0)
            {
                net_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            }else
            {
                net_sockaddr.sin_addr.s_addr = inet_addr(address.c_str());
            }

            if(::bind(socket_id, (struct sockaddr * )&net_sockaddr, sizeof(net_sockaddr)) == -1)
            {
                Log.error("bind {0}:({1}) failed", address, port);
                return false;
            }
            return true;
        }
        
        const bool NetWork::listen(const unsigned poolSize, const unsigned loopInterval)
        {
            if(::listen(socket_id, 1) == -1)
            {
                Log.error("listen({0}) failed", poolSize);
                return false;
            }
            running = true;

            thread listenThread([this](const unsigned loopInterval)
            {

                fd_set fdread;
                struct timeval outTime;
                outTime.tv_sec = 0;
                outTime.tv_usec = loopInterval * 1000;

                while(running)
                {
                    FD_ZERO(&fdread);

                    FD_SET(socket_id, &fdread);
                    int maxSocketId = socket_id;
                    for(auto item : clientList)
                    {
                        FD_SET(item.first, &fdread);
                        maxSocketId = item.first > maxSocketId ? item.first : maxSocketId;
                    }

                    switch(select(maxSocketId + 1, &fdread, nullptr, nullptr, &outTime))
                    {
                    case -1:
                        //异常
                        break;
                    case 0:
                        //超时
                        continue;
                    default:
                        int error;
                        socklen_t len;
                        getsockopt(socket_id, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len);
                        if(error)
                        {
                            //没链接成功
                            Log.error("connect socket[{0}] error: {2}", socket_id, error);
                            return;
                        }
                    }

                    ///监听客户端链接
                    static struct sockaddr_in client_addr;
                    static socklen_t length = sizeof(client_addr);

                    int conn = ::accept(socket_id, (struct sockaddr*)&client_addr, &length);
                    if(conn >= 0 && acceptCallBack)
                    {
                        int flag = fcntl(conn, F_GETFL, 0);
                        fcntl(conn, F_SETFL, flag | O_NONBLOCK);

                        struct sockaddr_in * temp = new struct sockaddr_in();
                        memcpy(temp, &client_addr, sizeof(struct sockaddr_in));
                        clientList.insert(pair<const int, struct sockaddr_in *>(conn, temp));
                        acceptCallBack(conn, *temp);
                    }

                    //监听客户端信息
                    for(auto item = clientList.begin(); item != clientList.end(); ++item)
                    {
                        static char recvBuffer[DEFAULT_RECV_BUFFER_SIZE];
                        memset(recvBuffer, 0, sizeof(recvBuffer));
                        ssize_t recvLen = ::recv(item->first, recvBuffer, sizeof(recvBuffer) - 1, 0);
                        if(recvLen < 0)
                        {
                            //无信息
                            continue;
                        }else if(recvLen == 0 && errno != EINTR){
                            //断开链接
                            delete item->second;
                            ::close(item->first);
                            if(closeCallBack){ closeCallBack(item->first); }
                            clientList.erase(item--);
                            continue;
                        }

                        //处理信息
                        stringstream sstr;
                        sstr << recvBuffer;
                        memset(recvBuffer, 0, sizeof(recvBuffer));
                        while(recvLen >= (ssize_t)sizeof(recvBuffer) - 1)
                        {
                            recvLen = ::recv(item->first, recvBuffer, sizeof(recvBuffer) - 1, 0);
                            sstr << recvBuffer;
                            memset(recvBuffer, 0, sizeof(recvBuffer));
                        }
                        if(recvCallBack)
                        {
                            recvCallBack(item->first, sstr.str());
                        }
                    }
                }
            }, loopInterval);

            listenThread.detach();

            return true;
        }

        void NetWork::unlisten()
        {
            running = false;
        }

        const bool NetWork::connect(const string & address, const unsigned port, const unsigned loopInterval)
        {
            struct sockaddr_in net_sockaddr;
            memset(&net_sockaddr, 0, sizeof(net_sockaddr));
            net_sockaddr.sin_family = AF_INET;
            net_sockaddr.sin_port = htons(port);

            if(address.length() <= 0)
            {
                net_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            }else{
                net_sockaddr.sin_addr.s_addr = inet_addr(address.c_str());
            }

            if(::connect(socket_id, (struct sockaddr * )&net_sockaddr, sizeof(net_sockaddr)) == -1 && errno != EINPROGRESS)
            {
                Log.error("connect {0}:({1}) failed", address, port);
                return false;
            }

            struct sockaddr_in * temp = new struct sockaddr_in();
            memcpy(temp, &net_sockaddr, sizeof(struct sockaddr_in));
            clientList.insert(pair<const int, struct sockaddr_in *>(socket_id, temp));

            thread clientThread([this](const unsigned loopInterval)
            {
                running = true;
                
                fd_set fdread;
                struct timeval outTime;
                outTime.tv_sec = 0;
                outTime.tv_usec = loopInterval * 1000;

                bool isConnected = false;

                while(running)
                {

                    FD_ZERO(&fdread);
                    FD_SET(socket_id, &fdread);

                    switch(select(socket_id + 1, &fdread, nullptr, nullptr, &outTime))
                    {
                    case -1:
                        //异常
                        break;
                    case 0:
                        //超时
                        continue;
                    default:
                        int error;
                        socklen_t len;
                        getsockopt(socket_id, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len);
                        if(error)
                        {
                            //没链接成功
                            Log.error("connect socket[{0}] error: {2}", socket_id, error);
                            return;
                        }
                    }

                    if(!isConnected)
                    {
                        if(acceptCallBack) {acceptCallBack(socket_id, *clientList.at(socket_id));}
                        isConnected = true;
                    }


                    static char recvBuffer[DEFAULT_RECV_BUFFER_SIZE];
                    memset(recvBuffer, 0, sizeof(recvBuffer));
                    ssize_t recvLen = ::recv(socket_id, recvBuffer, sizeof(recvBuffer) - 1, 0);
                    if(recvLen < 0)
                    {
                        //无信息
                        continue;
                    }else if(recvLen == 0 && errno != EINTR)
                    {
                        //断开链接
                        ::close(socket_id);
                        if(closeCallBack){ closeCallBack(socket_id); }
                        socket_id = -1;
                        running = isConnected = false;
                        continue;
                    }

                    //处理信息
                    stringstream sstr;
                    sstr << recvBuffer;
                    memset(recvBuffer, 0, sizeof(recvBuffer));
                    while(recvLen >= (ssize_t)sizeof(recvBuffer) - 1)
                    {
                        recvLen = ::recv(socket_id, recvBuffer, sizeof(recvBuffer) - 1, 0);
                        sstr << recvBuffer;
                        memset(recvBuffer, 0, sizeof(recvBuffer));
                    }
                    if(recvCallBack){ recvCallBack(socket_id, sstr.str()); }
                }
            }, loopInterval);
            clientThread.detach();

            return true;
        }

        const bool NetWork::loopRecvFrom(const unsigned loopInterval)
        {
            thread loopRecvThread([this](const unsigned loopInterval)
            {
                running = true;
                
                while(running)
                {
                    //先休息　不然continue会死循环
                    usleep(loopInterval * 1000);
                    
                    static char recvBuffer[DEFAULT_RECV_BUFFER_SIZE];
                    memset(recvBuffer, 0, sizeof(recvBuffer));

                    struct sockaddr_in clientAddr;
                    memset(&clientAddr, 0, sizeof(clientAddr));
                    socklen_t clientAddrLen = 0;

                    ssize_t recvLen = ::recvfrom(socket_id, recvBuffer, sizeof(recvBuffer) - 1, 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
                    
                    if(recvLen < 0)
                    {
                        //无信息
                        continue;
                    }
                    else if(recvLen == 0 && errno != EINTR)
                    {
                        //tcp断开　　udp不清楚
                        running = false;
                        continue;
                    }
                    else if(recvLen == 0)
                    {
                        continue;
                    }

                    //处理信息
                    stringstream sstr;
                    sstr << recvBuffer;

                    if(recvFromCallBack){ recvFromCallBack(&clientAddr, sstr.str()); }
                }
            }, loopInterval);

            loopRecvThread.detach();
            return true;
        }

        void NetWork::accept(const function<void(const int client, const struct sockaddr_in & clientInfo)> & callBack)
        {
            acceptCallBack = callBack;
        }

        void NetWork::close(const function<void (const int client)> & callBack)
        {
            closeCallBack = callBack;
        }

        void NetWork::recv(const function<void (const int client, const string & str)> & callBack)
        {
            recvCallBack = callBack;
        }

        void NetWork::recvFrom(const function<void (const struct sockaddr_in * clientInfo, const string & str)> & callBack)
        {
            recvFromCallBack = callBack;
        }

        const bool NetWork::send(const string & str) const
        {
            return send(-1, str);
        }
        
        const bool NetWork::send(const int client, const string & str) const
        {
            
            if(client != -1)
            {
                bool findClient = false;
                for(auto item : clientList)
                {
                    if(item.first == client)
                    {
                        findClient = true;
                        break;
                    }
                }
                if(!findClient)
                {
                    Log.error("not fined client:{0}", client);
                    return false;
                }

                ::send(client, str.c_str(), str.length(), 0);
                return true;
            }

            for(auto item : clientList)
            {
                ::send(item.first, str.c_str(), str.length(), 0);
            }

            return true;
        }
    }
}