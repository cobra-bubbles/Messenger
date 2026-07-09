#include <sstream>
#include <iostream>
#include <fstream>

#include "utils.h"
#include "../constants.h"

using json = nlohmann::json;

/**
 * @brief Функция возвращает false или true, в случае есть ли запрещенные символы в переданной строке или нет
 *
 * @param input - переданная строка, которую нужно проверить на валидность
 */
bool are_allowed_letter(const std::string input) {
    return input.find_first_of(NOT_ALLOWED_LETTERS) == std::string::npos;
}

/**
 * @brief Функция парсит переданную строку (которая вводится непосредственно пользователем в терминал) на слова, команду помещает в "command", флаги в ключ, значения флагов в значения ключей
 * 
 * @param input - введенная строка пользователем 
 * 
 * @return Возвращает карту
 */
std::map<std::string, std::string> parse_command(const std::string input) {
    std::istringstream iss(input);
    std::map<std::string, std::string> parsed_command;
    std::string key, value, word, command;
    iss >> value;
    parsed_command["command"] = value;
    command = parsed_command["command"];
    
    while (iss >> key) {
        if ((command != "send_personal_message") && (command != "send_group_message")) {
            if ((key[0] == '-') && (iss >> value && (value[0] != '-')))
            {
                parsed_command[key] = value;
            }
        } else if (key == "-m") {
            value = "";
            while (iss >> word) {
                value += " " + word;
            }
            parsed_command[key] = value;
        } else if ((key[0] == '-') && (iss >> value && (value[0] != '-')))
        {
            parsed_command[key] = value;
        }
    }
    
    return parsed_command;
}

/**
 * @brief Функция печатает переданный вектор в поток вывода
 */
template<typename type>
void print_vector(const std::vector<type>& vector) {
    for (const auto& element: vector) {
        std::cout << element << std::endl;
    }
}

/**
 * @brief Фукнция печатает клиенту в поток вывода сообщение, которые достаются из файла с перепиской (неважно, групповой или личной)
 *
 * @param json_string - json в формате стринг, где хранятся все сообщения конкретного чата
 * @param count - количество сообщений, которое нужно вывести
 */
void print_messages(const std::string& json_string, const ssize_t count) {
    json json_messages = json::parse(json_string);
    std::vector<std::string> messages;
    const ssize_t messages_amount = json_messages["messages"].size();
    for (ssize_t i = messages_amount - 1; i >= messages_amount - 1 - count; --i) {
        std::string input = std::string(json_messages["messages"][i]["time"]) + std::string(": ") + std::string(json_messages["messages"][i]["message"]);
        messages.insert(messages.begin(), input);
    }
    print_vector(messages);
}

/**
 * @brief Функция печатает в поток вывода переданную в качестве аргумента карту
 * @param input_map - переданная карта, которую нужно распечатать
 */
template<typename first, typename second>
void print_map(std::map<first, second> input_map) {
    for (const auto& [key, value]: input_map) {
        std::cout << key << ": " << value << std::endl;
    }
}

/**
 * @brief Функция находит файл json по его полному пути и возвращает его
 */
ordered_json get_json_data(const std::string file_path) {
    std::ifstream file(file_path);
    ordered_json data;
    file >> data;
    file.close();
    return data;
}

/**
 * @brief Функция создает файл с информацией по его полному пути
 *
 * @param file_path - полный путь json файла
 * @param data - информация json файла
 */
void write_json_data(const std::string file_path, ordered_json data) {
    std::ofstream file(file_path);
    file << data.dump(4);
    file.close();
}

/**
 * @brief Функция добавляет токен в начало команды, которую прописывает клиент в формате "TOKEN ***** user_command"
 *
 * @param input - строка, к которой нужно добавить токен
 *
 * @return Возвращает новую строку с добавленным токеном
 */
std::string add_token(const std::string input) {
    ordered_json client_conf = get_json_data(CLIENT_CONF_FILE_PATH.c_str());
    std::string output = std::string(TOKEN) + " " + std::to_string(int(client_conf[TOKEN])) + " " + input;
    return output;
}

/**
 * @brief Функция сохраняет информацию о сессии (username и токен) в json файл
 *
 * @param token - строка токена
 * @param username - юзернейм пользователя с активной сессией
 */
void save_conf(const std::string token, const std::string username) {
    int int_token = std::stoi(token);
    
    ordered_json client_conf = get_json_data(CLIENT_CONF_FILE_PATH.c_str());
    client_conf[TOKEN] = int_token;
    client_conf[USERNAME] = username;
    write_json_data(CLIENT_CONF_FILE_PATH.c_str(), client_conf);
}

/**
 * @brief Функция меняет информацию о сессии в json фале, а именно меняет юзернейм пользователя
 * @param username - новый юзернейм пользователя
 */
void change_conf_username(const std::string username) {
    ordered_json client_conf = get_json_data(CLIENT_CONF_FILE_PATH.c_str());
    client_conf[USERNAME] = username;
    write_json_data(CLIENT_CONF_FILE_PATH.c_str(), client_conf);
}
