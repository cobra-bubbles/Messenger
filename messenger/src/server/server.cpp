#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <map>
#include <dirent.h>
#include <memory>


#include "constants.h"
#include "controller/call_command.h"
#include "server.h"
#include "utils/utils.h"

using tcp = boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

void Server::start_accept() {
        acceptor_.async_accept(socket_, [this](const boost::system::error_code& error) {
            if (!error) {
                std::cout << "Клиент подключился!\n";
                auto session = std::make_shared<Session>(std::move(socket_), ctx_);
                session->start();
            }
            start_accept();
        });
    }
    
Server::Server()
        : io_(),
          acceptor_(io_, tcp::endpoint(tcp::v4(), 8443)),
          socket_(io_),
          ctx_(ssl::context::tlsv12_server)
    {
        ctx_.use_certificate_chain_file("/Users/nikitasemin/Desktop/study/sys_prog/messenger/messenger/src/server/key/server.crt");
        ctx_.use_private_key_file("/Users/nikitasemin/Desktop/study/sys_prog/messenger/messenger/src/server/key/server.key", ssl::context::pem);
    }

void Server::start_server() {
        start_accept();
        std::cout << "Сервер запущен на порту 8443\n";
        io_.run();
    }

void Session::read_message() {
    memset(buffer_, 0, sizeof(buffer_));
    ssl_socket_.async_read_some(
        boost::asio::buffer(buffer_, sizeof(buffer_)),
        [self = shared_from_this()](const boost::system::error_code& error, size_t bytes_read) {
            if (!error) {
                std::string msg(self->buffer_, bytes_read);
                
                std::string reply = self->handle_message_from_client(msg);
                
                self->send_message(reply);
            } else {
                std::cerr << "Read error: " << error.message() << std::endl;
            }
        });
}

void Session::send_message(const std::string& message) {
        auto self = shared_from_this();

        auto data = std::make_shared<std::string>(message + "\n");

        boost::asio::async_write(ssl_socket_,
            boost::asio::buffer(*data),
            [self, data](const boost::system::error_code& error, size_t) {
                if (!error) {
                    self->read_message();
                }
            });
    }

std::string Session::handle_message_from_client(const std::string& message) {
    std::string username = "";
    std::map<std::string, std::string> input_map = parse_command(message);
    
    auto token_it = input_map.find(TOKEN);
    if (token_it != input_map.end()) {
        try {
            int token_val = std::stoi(token_it->second);
            if (token_val != 0) {
                username = get_username_from_token(token_val);
            }
        } catch (...) {

        }
    }

    std::map<std::string, std::string> output_map = call_command(input_map, username);
    return map_to_str(output_map);
}

Session::Session(tcp::socket socket, ssl::context& ctx)
        : ssl_socket_(std::move(socket), ctx) {}

void Session::start() {
        ssl_socket_.async_handshake(ssl::stream_base::server,
            [self = shared_from_this()](const boost::system::error_code& ec) {
                if (!ec) {
                    self->read_message();
                } else {
                    std::cerr << "Handshake failed: " << ec.message() << '\n';
                }
            });
    }

int main() {
    class Server s;
    s.start_server();
    
    return 0;
}
