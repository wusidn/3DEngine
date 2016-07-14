#include "NetWork.h"
#include <cassert>
#include <sys/types.h>
#include <netinet/in.h>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

namespace engine::tools
{
    NetWork * NetWork::create(const string & address, const unsigned port)
    {
        NetWork * result = new NetWork();
        if(!result->init(address, port)){
            delete result;
            result = nullptr;
        }
        return result;
    }

    const bool NetWork::init(const string & address, const unsigned port)
    {
        if(!Object::init()){
            return false;
        }
        socket_id = socket(AF_INET, SOCK_STREAM, 0);
        int flag = fcntl(socket_id, F_GETFL, 0);
        fcntl(socket_id, F_SETFL, flag | O_NONBLOCK);
        thread listenThread([this, port]()->void{

            struct sockaddr_in net_sockaddr;
            net_sockaddr.sin_family = AF_INET;
            net_sockaddr.sin_port = htons(port);
            net_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            if(bind(socket_id, (struct sockaddr * )&net_sockaddr, sizeof(net_sockaddr)) == -1){
                assert(!"bind failed");
            }

            ///listen，成功返回0，出错返回-1
            if(listen(socket_id, 1) == -1){
                assert(!"listen failed");
            }

            ///客户端套接字
            struct sockaddr_in client_addr;
            socklen_t length = sizeof(client_addr);
            while(true){
                int conn = accept(socket_id, (struct sockaddr*)&client_addr, &length);
                if(conn >= 0)
                {
                    cout << "connected" << endl;
                    break;
                }
                cout << "connect failed" << endl;
                sleep(1);
            }
            
        });
        cout << listenThread.get_id() << endl;
        listenThread.detach();

        return true;
    }
    
}