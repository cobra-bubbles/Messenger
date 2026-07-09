#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>

#include "../../json.hpp"

using ordered_json = nlohmann::ordered_json;


bool are_allowed_letter(const std::string input);
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

#endif
