#include <string>
#include <map>
#include <functional>

#include "controller.h"
#include "../services/services.h"

bool simple_client_command(const std::string& command) {
     if (command == "whoami") {
         whoami();
         return true;
     } else if (command == "log_out") {
         log_out();
         return true;
     }
     return false;
 }

std::map<std::string, std::function<void(const std::string& message)>> handle_server_answer = {
    {"register", answer_register},
    {"log_out", [](const auto&){return log_out();}},
    {"whoami", [](const auto&){return whoami();}},
    {"log_in", answer_log_in},
    {"change_username", answer_change_username},
    {"add_friend", answer_add_friend},
    {"show_friends", answer_show_friends},
    {"show_chats", answer_show_chats},
    {"show_group_chats", answer_show_group_chats},
    {"show_personal_chats", answer_show_personal_chats},
    {"print_personal_chat", answer_print_personal_chat},
    {"print_group_chat", answer_print_group_chat},
    {"send_personal_message", answer_send_personal_message},
    {"send_group_message", answer_send_group_message},
    {"create_group_chat", answer_create_group_chat},
    {"group_manage", answer_group_manage},
    {"show_group_settings", answer_show_group_settings},
    {"change_group_name", answer_change_group_name}
};
