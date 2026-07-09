#ifndef SERVER_H
#define SERVER_H

#include "../json.hpp"

using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;
using tcp = boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

class Session;

class Server {
private:
    boost::asio::io_context io_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    ssl::context ctx_;
    
    void start_accept();
public:
    Server();

    void start_server();
};

class Session : public std::enable_shared_from_this<Session> {
private:
    void read_message();
    void send_message(const std::string& message);
    std::string handle_message_from_client(const std::string& message);
    ssl::stream<tcp::socket> ssl_socket_;
    char buffer_[1024];
    
public:
    Session(tcp::socket socket, ssl::context& ctx);
    void start();
};

#endif
