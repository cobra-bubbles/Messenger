#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>


#include "client.h"
#include "utils/utils.h"
#include "constants.h"
#include "input_handler/input_handler.h"
#include "services/services.h"
#include "controller/controller.h"

using json = nlohmann::json;


Client::Client():
ctx_(boost::asio::ssl::context::tlsv12_client),
ssl_socket_(io_, ctx_) {
    ctx_.set_verify_mode(boost::asio::ssl::verify_peer);
    ctx_.set_verify_callback([](bool preverified, boost::asio::ssl::verify_context& ctx) {
            if (!preverified) {
                std::cout << "Верификация сертификата не пройдена!" << std::endl;
            }
            return true;
        });
    boost::asio::ip::tcp::resolver resolver(io_);
    auto endpoints = resolver.resolve(SERVER_IP_PV4, "8443");
    boost::asio::connect(ssl_socket_.lowest_layer(), endpoints);
    ssl_socket_.handshake(boost::asio::ssl::stream_base::client);
}
    
Client::~Client() {
    boost::system::error_code ec;
    ssl_socket_.shutdown(ec);
    ssl_socket_.lowest_layer().close(ec);
}

std::string Client::handle_command(const std::string& message) {
    boost::asio::write(ssl_socket_, boost::asio::buffer(message));
    memset(buffer_, 0, sizeof(buffer_));
    ssl_socket_.read_some(boost::asio::buffer(buffer_, sizeof(buffer_)));
    std::string message_string = std::string(buffer_);
    return message_string;
}

std::string Client::return_input() {
    memset(buffer_, 0, sizeof(buffer_));
    read(STDIN_FILENO, buffer_, sizeof(buffer_) - 1);
    std::string input = std::string(buffer_);
    
    return input;
}

int main() {
    log_out();
    class Client c;
    std::string message_from_server, message_to_server, input;
    ordered_json client_conf = get_json_data(CLIENT_CONF_FILE_PATH.c_str());

    while (true) {
        input = c.return_input();
        std::map<std::string, std::string> map = parse_command(input);
        auto it = is_correct_command_functions.find(map["command"]);
        if (it == is_correct_command_functions.end()) {
            std::cout << "Неверная команда." << std::endl;
            continue;
        } else if (!is_correct_command_functions[map["command"]](map)) {
            std::cout << "Команда введена некорректно." << std::endl;
            continue;
        } else if ((client_conf[USERNAME] == "") &&
            (map["command"] != "register") && map["command"] != "log_in") {
            std::cout << "Войдите в учетную запись или зарегистрируйтесь." << std::endl;
        } else {
            if (!simple_client_command(map["command"])) {
                message_to_server = add_token(input);
                message_from_server = c.handle_command(message_to_server);
                
                handle_server_answer[map["command"]](message_from_server);
                if (map["command"] == "log_in") {
                    client_conf = get_json_data(CLIENT_CONF_FILE_PATH.c_str());

                }
            }
        }
    }
    return 0;
}
