#include <zmq.hpp>
#include <iostream>

class FtpSock {
public:
    FtpSock() : sock(ctx, zmq::socket_type::req) {}
    ~FtpSock() = default; 

protected:
    zmq::context_t ctx;
    zmq::socket_t sock;
    zmq::message_t reply;
};


class CmdFtpSockClient : public FtpSock {
public:
    void CmdConnect(const std::string& address, int port = 5555) 
    {
        sock.connect("tcp://" + address + ":" + std::to_string(port));
    }

    void sendCommand(const std::string& cmd) 
    {
        zmq::message_t req(cmd.data(), cmd.size());
        sock.send(req, zmq::send_flags::none);
    }

    void recvResponse(std::string& reply_str) 
    {
        sock.recv(reply);
        reply_str = reply.to_string();
    }
};

// class FtpClient {
// public:
//     FtpClient() {
//         // Initialize FTP client
//     }

//     void cmdConnect(const std::string& address, int port = 21) {
//         // Connect to the FTP server
//     }

//     void ctrlConnect(const std::string& address, int port = 22) {
//         // Connect to the FTP server
//     }

//     void disconnect() {
//         // Disconnect from the FTP server
//     }

//     bool login(const std::string& username, const std::string& password) {
//         // Send login request to the FTP server
//         // Receive login response from the FTP server
//         // Return true if login successful, false otherwise
//     }
// private:
//     zmq::socket_t cmd_sock_
// }

int main() {
    // zmq::context_t ctx;
    // zmq::socket_t sock(ctx, zmq::socket_type::req);
    // sock.connect("tcp://localhost:5555");

    // zmq::message_t req("Hello", 5);
    // sock.send(req, zmq::send_flags::none);

    // zmq::message_t reply;
    // sock.recv(reply);
    // std::cout << "Received: " << reply.to_string() << std::endl;

    auto ftp_sock = std::make_unique<CmdFtpSockClient>();
    ftp_sock->CmdConnect("127.0.0.1", 5555);
    ftp_sock->sendCommand("hello");

    std::string reply_str;
    ftp_sock->recvResponse(reply_str);
    std::cout << "Received: " << reply_str << std::endl;
}
