#ifndef SERVICES_H
#define SERVICES_H

#include <string>

void log_out();
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

#endif
