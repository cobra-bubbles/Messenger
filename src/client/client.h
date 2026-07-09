#ifndef CLIENT_H
#define CLIENT_H

#include "../json.hpp"

using ordered_json = nlohmann::ordered_json;


class Client {
private:
    char buffer_[1024];
    bool error_ = false;
    boost::asio::io_context io_;
    boost::asio::ssl::context ctx_;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket_;

public:
    Client();
    ~Client();
    
    std::string handle_command(const std::string& message);
    std::string return_input();
};

/*
 Далее будут описаны вспомогательные функции.
 */
std::map<std::string, std::string> parse_command(const std::string input);
template<typename type>
void print_vector(const std::vector<const type> vector);
void print_messages(const std::string json_string);
template<typename first, typename second>
void print_map(std::map<first, second> input_map);
ordered_json get_json_data(const std::string file_path);
void write_json_data(const std::string file_path, ordered_json data);
std::string add_token(const std::string input);
void handle_message_from_server(const std::string message);
void save_conf(const std::string token, const std::string username);
void change_conf_username(const std::string username);
bool simple_client_command();



/*
 Далее будут описаны булевы функции, которые проверяют, валидная ли команда, отправленная клиентом.
 */
bool is_correct_register(std::map<std::string, std::string> input_map);
bool is_correct_log_in(std::map<std::string, std::string> input_map);
bool is_correct_logout(std::map<std::string, std::string> input_map);
bool is_correct_whoami(std::map<std::string, std::string> input_map);
bool is_correct_change_username(std::map<std::string, std::string> input_map);
bool is_correct_add_friend(std::map<std::string, std::string> input_map);
bool is_correct_show_friends(std::map<std::string, std::string> input_map);
bool is_correct_show_chats(std::map<std::string, std::string> input_map);
bool is_correct_show_group_chats(std::map<std::string, std::string> input_map);
bool is_correct_show_personal_chats(std::map<std::string, std::string> input_map);
bool is_correct_print_personal_chat(std::map<std::string, std::string> input_map);
bool is_correct_print_group_chat(std::map<std::string, std::string> input_map);
bool is_correct_send_personal_message(std::map<std::string, std::string> input_map);
bool is_correct_send_group_message(std::map<std::string, std::string> input_map);
bool is_correct_create_group_chat(std::map<std::string, std::string> input_map);
bool is_correct_group_manage(std::map<std::string, std::string> input_map);
bool is_correct_show_group_settings(std::map<std::string, std::string> input_map);
bool is_correct_change_group_name(std::map<std::string, std::string> input_map);

extern std::map<std::string, std::function<bool(std::map<std::string, std::string>)>> is_correct_command_functions;

/*
 Далее будут описаны фукнции, которые обрабатывают ответ сервера и дают ответ клиенту.
 */
void logout();
void whoami();
void answer_register(const std::string& message);
void answer_log_in(const std::string& message);
void answer_change_username(const std::string& message);
void answer_add_friend(const std::string& message);
void answer_show_friends(const std::string& message);
void answer_show_chats(const std::string& message);
void answer_show_group_chats(const std::string& message);
void answer_show_personal_chats(const std::string& message);
void answer_print_personal_chat(const std::string& message);
void answer_print_group_chat(const std::string& message);
void answer_send_personal_message(const std::string& message);
void answer_send_group_message(const std::string& message);
void answer_create_group_chat(const std::string& message);
void answer_group_manage(const std::string& message);
void answer_show_group_settings(const std::string& message);
void answer_change_group_name(const std::string& message);

extern std::map<std::string, std::function<void(const std::string& message)>> handle_server_answer;



#endif
