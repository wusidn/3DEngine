#include "NetWork.h"
#include "LogManager.h"

#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#include <cassert>
#include <thread>
#include <unistd.h>

#include <iostream>

using namespace std;

namespace engine::tools
{

    const bool NetWork::init()
    {
        if(!Object::init()){
            return false;
        }
        socket_id = socket(AF_INET, SOCK_STREAM, 0);
        int flag = fcntl(socket_id, F_GETFL, 0);
        fcntl(socket_id, F_SETFL, flag | O_NONBLOCK);

        bind();
        listen();
        accept([](const struct sockaddr_in clientAddr){
            cout << "accepted" << endl;
        });

        return true;
    }

    const bool NetWork::bind(const string & address, const unsigned port) const
    {
        struct sockaddr_in net_sockaddr;
        net_sockaddr.sin_family = AF_INET;
        net_sockaddr.sin_port = htons(port);

        if(address.length() <= 0){
            net_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        }else{
            net_sockaddr.sin_addr.s_addr = inet_addr(address.c_str());
        }

        if(::bind(socket_id, (struct sockaddr * )&net_sockaddr, sizeof(net_sockaddr)) == -1){
            Log.error("bind {0}:({1}) failed", address, port);
            return false;
        }
        return true;
    }
    
    const bool NetWork::listen(const unsigned poolSize) const
    {
        if(::listen(socket_id, 1) == -1){
            Log.error("listen({0}) failed", poolSize);
            return false;
        }
        return true;
    }

    const bool NetWork::accept(const function<void(const struct sockaddr_in clientAddr)> & callBack, const unsigned acceptInterval)
    {
        thread acceptThread([this](const function<void(const struct sockaddr_in clientAddr)> callBack, const unsigned acceptInterval){
            while(true){
                ///客户端套接字
                struct sockaddr_in client_addr;
                socklen_t length = sizeof(client_addr);

                int conn = ::accept(socket_id, (struct sockaddr*)&client_addr, &length);
                if(conn >= 0){
                    callBack(client_addr);
                }
                cout << "no accept" << endl;
                usleep(acceptInterval * 1000);
            }
        }, callBack, acceptInterval);

        acceptThread.detach();

        return true;
    }

}