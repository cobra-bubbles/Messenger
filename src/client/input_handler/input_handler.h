#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

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

#endif
