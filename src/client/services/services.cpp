#include <string>
#include <map>
#include <sstream>
#include <iostream>

#include "../constants.h"
#include "services.h"
#include "../../json.hpp"
#include "../utils/utils.h"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

/**
 * @brief Функция обнуляет активную сессию, очищает всю информацию об активной сессии в файле
 */
void log_out() {
    ordered_json client_conf = get_json_data(CLIENT_CONF_FILE_PATH.c_str());
    client_conf[TOKEN] = 0;
    client_conf[USERNAME] = "";
    write_json_data(CLIENT_CONF_FILE_PATH.c_str(), client_conf);
    std::cout << "Success!" << std::endl;
}

/**
 * @brief Функция говорит пользователю, кем он является, а именно его юзернейм
 */
void whoami() {
    ordered_json client_conf = get_json_data(CLIENT_CONF_FILE_PATH.c_str());
    if (client_conf[USERNAME] != "") {
        std::cout << client_conf[USERNAME] << std::endl;
    } else {
        std::cout << "Вы никто! Залогиньтесь, пожалуйста." << std::endl;
    }
    write_json_data(CLIENT_CONF_FILE_PATH.c_str(), client_conf);
}

/*
 Все остальные ниже прописанные функции выводят клиенту о статусе запрошенной им команды
*/

void answer_register(const std::string& message) {
    std::cout << message.substr(sizeof("register")) << std::endl;
}

void answer_log_in(const std::string& message) {
    std::istringstream iss(message);
    
    if (message.find("Success!") == std::string::npos) {
        std::cout << message.substr(sizeof("log_in")) << std::endl;
    } else {
        std::string token;
        std::string username;
        
        iss >> token;
        iss >> token;
        iss >> username;
        save_conf(token, username);
        std::string success;
        iss >> success;
        std::cout << success << std::endl;
    }
}

void answer_change_username(const std::string& message) {
    std::istringstream iss;
    std::string word;
    iss >> word; // change_username
    iss >> word; // new_username
    std::cout << "Success!" << std::endl;
    change_conf_username(word);
}

void answer_add_friend(const std::string& message) {
    std::cout << message.substr(sizeof("add_friend")) << std::endl;
}

void answer_show_friends(const std::string& message) {
    std::cout << message.substr(sizeof("show_friends")) << std::endl;
}

void answer_show_chats(const std::string& message) {
    std::cout << message.substr(sizeof("show_chats")) << std::endl;
}

void answer_show_group_chats(const std::string& message) {
    std::cout << message.substr(sizeof("show_group_chats")) << std::endl;
}

void answer_show_personal_chats(const std::string& message) {
    std::cout << message.substr(sizeof("show_personal_chats")) << std::endl;
}

void answer_print_personal_chat(const std::string& message) {
    std::string chat = message.substr(sizeof("print_personal_chat"));
    std::cout << chat << std::endl;
}

void answer_print_group_chat(const std::string& message) {
    std::string chat = message.substr(sizeof("print_group_chat"));
    std::cout << chat << std::endl;
}

void answer_send_personal_message(const std::string& message) {
    std::cout << message.substr(sizeof("send_personal_message")) << std::endl;
}

void answer_send_group_message(const std::string& message) {
    std::cout << message.substr(sizeof("send_group_message")) << std::endl;
}

void answer_create_group_chat(const std::string& message) {
    std::cout << message.substr(sizeof("create_group_chat")) << std::endl;
}

void answer_group_manage(const std::string& message) {
    std::cout << message.substr(sizeof("group_manage")) << std::endl;
}

void answer_show_group_settings(const std::string& message) {
    std::string json_str = message.substr(sizeof("show_group_settings"));
    std::cout << json_str << std::endl;
}

void answer_change_group_name(const std::string& message) {
    std::cout << message.substr(sizeof("change_group_name")) << std::endl;
}
