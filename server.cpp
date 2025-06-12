#include <zmq.hpp>
#include <iostream>

class FtpSock {
public:
    FtpSock() : sock(ctx, zmq::socket_type::rep) {}
    ~FtpSock() = default; 

protected:
    zmq::context_t ctx;
    zmq::socket_t sock;
    zmq::message_t reply;
};


class CmdFtpSockServer : public FtpSock {
public:

    void bind(std::string addr, int port = 5555)
    {
        std::string endpoint = "tcp://" + addr + ":" + std::to_string(port);
        sock.bind(endpoint); 
    }

    void recvCommand(std::string& cmd_str)
    {
        sock.recv(reply);
        cmd_str = reply.to_string();
        std::cout << "Received command: " << cmd_str << std::endl;
    }

    void sendReply(std::string reply_str)
    {
        reply = zmq::message_t(reply_str.data(), reply_str.size());
        sock.send(reply, zmq::send_flags::none);
    }
};

int main() {
    // zmq::context_t ctx;
    // zmq::socket_t sock(ctx, zmq::socket_type::rep);
    // sock.bind("tcp://*:5555");

    // while (true) {
    //     zmq::message_t req;
    //     sock.recv(req);
    //     std::cout << "Received: " << req.to_string() << std::endl;

    //     zmq::message_t reply("World", 5);
    //     sock.send(reply, zmq::send_flags::none);
    // }

    auto ftp_sock = std::make_unique<CmdFtpSockServer>();
    ftp_sock->bind("127.0.0.1", 5555);

    while (true) {
        std::string cmd_str;
        ftp_sock->recvCommand(cmd_str);
        std::cout << "Received: " << cmd_str << std::endl;
        ftp_sock->sendReply("OK");
    }
}
