#include "TcpClient.h"

namespace engine::tools
{

    TcpClient & TcpClient::create(const string & address, const unsigned port, const unsigned loopInterval)
    {
        TcpClient * result = new TcpClient();
        if(!result->init(address, port, loopInterval)){
            delete result;
            result = nullptr;
        }
        
        return *result;
    }

    const bool TcpClient::init(const string & address, const unsigned port, const unsigned loopInterval)
    {
        if(!NetWork::init()){
            return false;
        }

        if(!connect(address, port, loopInterval)){
            return false;
        }

        return true;
    }

    void TcpClient::close(const function<void (const int client)> & callBack)
    {
        NetWork::close(callBack);
    }

    void TcpClient::recv(const function<void (const int client, const string & str)> & callBack)
    {
        NetWork::recv(callBack);
    }

    const bool TcpClient::send(const string & str) const
    {
        return NetWork::send(socket_id, str);
    }

}