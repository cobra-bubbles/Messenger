#include <map>
#include <string>

#include "input_handler.h"
#include "../constants.h"
#include "../utils/utils.h"


/*
  Все ниже прописанные функции проверяют, валидная ли команда введенная пользователем
*/

bool is_correct_register(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 4) return false;
    
    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "register") return false;
    
    if (input_map.find("-l") == input_map.end()) return false;
    if (input_map.find("-p") == input_map.end()) return false;
    if (input_map.find("-u") == input_map.end()) return false;
    
    it = input_map.find("-l");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-p");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-u");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    
    return are_allowed_letter(input_map.find("-l")->second) && are_allowed_letter(input_map.find("-p")->second) && are_allowed_letter(input_map.find("-u")->second);
    
}

bool is_correct_log_in(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 3) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "log_in") return false;

    
    if (input_map.find("-l") == input_map.end()) return false;
    if (input_map.find("-p") == input_map.end()) return false;
    
    it = input_map.find("-l");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-p");
    if (it->second.size() < NAME_MIN_LENGTH) return false;

    return true;
}

bool is_correct_logout(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 1) return false;
    
    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "logout") return false;

    return true;
}

bool is_correct_whoami(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 1) return false;
    
    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "whoami") return false;

    return true;
}

bool is_correct_change_username(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 2) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "change_username") return false;
    
    if (input_map.find("-u") == input_map.end()) return false;
    
    it = input_map.find("-u");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    
    return are_allowed_letter(it->second);
}

bool is_correct_add_friend(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 2) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "add_friend") return false;
    
    if (input_map.find("-u") == input_map.end()) return false;
    
    it = input_map.find("-u");
    if (it->second.size() < NAME_MIN_LENGTH) return false;

    return true;
}

bool is_correct_show_friends(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 1) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "show_friends") return false;
        
    return true;
}

bool is_correct_show_chats(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 1) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "show_chats") return false;
    
    return true;
}

bool is_correct_show_group_chats(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 1) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "show_group_chats") return false;
    
    return true;
}

bool is_correct_show_personal_chats(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 1) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "show_personal_chats") return false;
    
    return true;
}

bool is_correct_print_personal_chat(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 4) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "print_personal_chat") return false;
    
    if (input_map.find("-u") == input_map.end()) return false;
    if (input_map.find("-f") == input_map.end()) return false;
    if (input_map.find("-n") == input_map.end()) return false;
    
    it = input_map.find("-u");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-f");
    if (it->second.size() != 2) return false;
    it = input_map.find("-n");
    if (std::stoi(it->second) <= 0) return false;

    return true;
}

bool is_correct_print_group_chat(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 4) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "print_group_chat") return false;
    
    if (input_map.find("-gn") == input_map.end()) return false;
    if (input_map.find("-f") == input_map.end()) return false;
    if (input_map.find("-n") == input_map.end()) return false;
    
    it = input_map.find("-gn");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-f");
    if (it->second.size() != 2) return false;
    it = input_map.find("-n");
    if (std::stoi(it->second) <= 0) return false;

    return true;
}

bool is_correct_send_personal_message(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 3) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "send_personal_message") return false;
    
    if (input_map.find("-u") == input_map.end()) return false;
    if (input_map.find("-m") == input_map.end()) return false;
    
    it = input_map.find("-u");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-m");
    if (it->second.size()  <= 0) return false;
    
    return true;
}

bool is_correct_send_group_message(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 3) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "send_group_message") return false;
    
    if (input_map.find("-gn") == input_map.end()) return false;
    if (input_map.find("-m") == input_map.end()) return false;
    
    it = input_map.find("-gn");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-m");
    if (it->second.size() <= 0) return false;
    
    return true;
}

bool is_correct_create_group_chat(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 2) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "create_group_chat") return false;
    
    if (input_map.find("-gn") == input_map.end()) return false;
    
    it = input_map.find("-gn");
    if (it->second.size() < NAME_MIN_LENGTH) return false;

    return are_allowed_letter(it->second);
}

bool is_correct_group_manage(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 5) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "group_manage") return false;
    
    if (input_map.find("-gn") == input_map.end()) return false;
    if (input_map.find("-u") == input_map.end()) return false;
    if (input_map.find("-f") == input_map.end()) return false;
    if (input_map.find("-g") == input_map.end()) return false;
    
    it = input_map.find("-gn");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-u");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-f");
    if (it->second.size() != 1) return false;
    it = input_map.find("-g");
    if (it->second.size() < NAME_MIN_LENGTH) return false;

    return true;
}

bool is_correct_show_group_settings(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 2) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "show_group_settings") return false;
    
    if (input_map.find("-gn") == input_map.end()) return false;
    
    it = input_map.find("-gn");
    if (it->second.size() < NAME_MIN_LENGTH) return false;

    return true;
}

bool is_correct_change_group_name(std::map<std::string, std::string> input_map) {
    if (input_map.size() != 3) return false;

    auto it = input_map.find("command");
    if (it == input_map.end() || it->second != "change_group_name") return false;
    
    if (input_map.find("-gn") == input_map.end()) return false;
    if (input_map.find("-ngn") == input_map.end()) return false;
    
    it = input_map.find("-gn");
    if (it->second.size() < NAME_MIN_LENGTH) return false;
    it = input_map.find("-ngn");
    if (it->second.size() < NAME_MIN_LENGTH) return false;

    return are_allowed_letter(it->second);
}

std::map<std::string, std::function<bool(std::map<std::string, std::string>)>> is_correct_command_functions = {
    {"register", is_correct_register},
    {"log_in", is_correct_log_in},
    {"logout", is_correct_logout},
    {"whoami", is_correct_whoami},
    {"change_username", is_correct_change_username},
    {"add_friend", is_correct_add_friend},
    {"show_friends", is_correct_show_friends},
    {"show_chats", is_correct_show_chats},
    {"show_group_chats", is_correct_show_group_chats},
    {"show_personal_chats", is_correct_show_personal_chats},
    {"print_personal_chat", is_correct_print_personal_chat},
    {"print_group_chat", is_correct_print_group_chat},
    {"send_personal_message", is_correct_send_personal_message},
    {"send_group_message", is_correct_send_group_message},
    {"create_group_chat", is_correct_create_group_chat},
    {"group_manage", is_correct_group_manage},
    {"show_group_settings", is_correct_show_group_settings},
    {"change_group_name", is_correct_change_group_name}
};
