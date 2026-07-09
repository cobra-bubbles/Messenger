#ifndef UTILS_H
#define UTILS_H

#include <dirent.h>
#include <string>
#include <map>

#include "../../json.hpp"

using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;

std::string get_time();
int get_user_ID(const std::string username);
std::string get_username(const int user_id);
std::string get_group_name(const int group_id);
bool is_group_admin(const std::string client_name, ordered_json data);
bool is_group_member(const std::string client_name, ordered_json data);
bool does_user_exist(const std::string username);

template<typename F>
int get_pos_in_array_json(const F what, const std::string where, const ordered_json data);
ordered_json get_json_data(const std::string file_path);
std::string get_json_string_data(const std::string file_path);
void write_json_data(const std::string file_path, ordered_json data);

template<typename F, typename... Args>
void try_catch(F&& function, Args&&... args);
dirent* return_personal_chat(const std::string username1, const std::string username2);
dirent* return_group_chat(const int group_id);
dirent* return_group_chat(const std::string client_name, const std::string group_name);
void append_personal_chat_id(const int client1_ID, const int client2_ID);
void append_group_chat_id(const std::string username, const unsigned group_id);
void erase_group_chat_id(const std::string username, const unsigned group_id);
std::map<std::string, std::string> parse_command(const std::string input);

template<typename first, typename second>
void print_map(const std::map<first, second> input_map);
void delete_user_from_group(const std::string user_name, const std::string group, ordered_json& chat);
int generate_token();
std::string map_to_str(std::map<std::string, std::string> map);
std::string get_username_from_token(const int token);

#endif
