#include "TcpClient.h"

namespace engine
{
    namespace tools
    {
        TcpClient & TcpClient::create(const string & address, const unsigned port, const unsigned loopInterval)
        {
            TcpClient & result = create();
            result.init(address, port, loopInterval);
            return result;
        }

        const bool TcpClient::init(void)
        {
            if(!NetWork::init()){ return false; }
            
            return true;
        }

        const bool TcpClient::init(const string & address, const unsigned port, const unsigned loopInterval)
        {
            if(!connect(address, port, loopInterval)){ return false; }

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
}