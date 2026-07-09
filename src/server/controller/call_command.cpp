#include <map>
#include <string>

#include "call_command.h"
#include "../services/register/register.h"
#include "../services/login/login.h"
#include "../services/change_username/change_username.h"
#include "../services/add_friend/add_friend.h"
#include "../services/show_friends/show_friends.h"
#include "../services/show_chats/show_chats.h"
#include "../services/show_group_chats/show_group_chats.h"
#include "../services/show_personal_chats/show_personal_chats.h"
#include "../services/return_personal_chat_str/return_personal_chat_str.h"
#include "../services/return_group_chats_str/return_group_chats_str.h"
#include "../services/send_personal_message/send_personal_message.h"
#include "../services/send_group_message/send_group_message.h"
#include "../services/create_group_chat/create_group_chat.h"
#include "../services/manage_group_user/manage_group_user.h"
#include "../services/group_settings/group_settings.h"
#include "../services/change_group_name/change_group_name.h"

/**
 * @brief Фукнция, которая вызывает сервис по названию команды.
 *
 * @param command - переданная клинтом команда, в формате ключ-значение. Обязательный ключ - "command", в которой хранится значение самой команды. Какие бывают команды, можно будет почитать в README файле.
 * @param client_name - имя клиента, который делает запрос.
 * @return В качестве возвращаемого значение передается карта, где в качестве ключа будет название команды, а в качестве значения возвращаемая строка сервисом.
 */
std::map<std::string, std::string> call_command(std::map<std::string, std::string> command, std::string client_name) {
    std::map<std::string, std::string> map;
    if (command["command"] == "register") {
        map["register"] = client_register(command.at("-l"), command.at("-p"), command.at("-u"));
        return map;
    } else if (command["command"] == "log_in") {
        map["log_in"] = client_log_in(command.at("-l"), command.at("-p"));
    } else if (command["command"] == "change_username") {
        map["change_username"] = client_change_username(client_name, command.at("-u"));
    } else if (command["command"] == "add_friend") {
        map["add_friend"] = client_add_friend(client_name, command.at("-u"));
    } else if (command["command"] == "show_friends") {
        map["show_friends"] = client_show_friends(client_name);
    } else if (command["command"] == "show_chats") {
        map["show_chats"] = client_show_chats(client_name);
    } else if (command["command"] == "show_group_chats") {
        map["show_group_chats"] = client_show_group_chats(client_name);
    } else if (command["command"] == "show_personal_chats") {
        map["show_personal_chats"] = client_show_personal_chats(client_name);
    } else if (command["command"] == "print_personal_chat") {
        map["print_personal_chat"] = client_return_personal_chat_str(client_name, command.at("-u"));
    } else if (command["command"] == "print_group_chat") {
        map["print_group_chat"] = client_return_group_chat_str(client_name, command.at("-gn"));
    } else if (command["command"] == "send_personal_message") {
        map["send_personal_message"] = client_send_personal_message(client_name, command.at("-u"), command.at("-m"));
    } else if (command["command"] == "send_group_message") {
        map["send_group_message"] = client_send_group_message(client_name, command.at("-gn"), command.at("-m"));
    } else if (command["command"] == "create_group_chat") {
        client_create_group_chat(client_name, command.at("-gn"));
        map["create_group_chat"] = "Success!";
    } else if (command["command"] == "group_manage") {
        map["group_manage"] = client_manage_group_user(client_name, command.at("-u"), command.at("-gn"), command.at("-f"), command.at("-g"));
    } else if (command["command"] == "show_group_settings") {
        map["show_group_settings"] = client_group_settings(client_name, command.at("-gn"));
    } else if (command["command"] == "change_group_name") {
        map["change_group_name"] = client_change_group_name(client_name, command.at("-gn"), command.at("-ngn"));
    }
    
    return map;
}
