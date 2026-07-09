#include <string>
#include <chrono>
#include <sstream>
#include <iostream>
#include <ctime>
#include <dirent.h>
#include <fstream>

#include "../constants.h"
#include "utils.h"

/**
 * @brief Фукнция, которая возвращает настоящее время в строковом формате "Y-m-d H:M".
 *
 * @return В качестве возвращаемого значения передается строка, в которой хранится настоящее время в строковом формате "Y-m-d H:M".
 */
std::string get_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M");
    std::string time = ss.str();
    return time;
}

/**
 * @brief Фукния, которая возвращает user_ID по имени пользователя.
 *
 * @param username - имя пользователя.
 *
 * @return Возвращает user_ID в int формате.
 */
int get_user_ID(const std::string username) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    
    for (const auto& user: users[USERS]) {
        if (user[USERNAME] == username) {
            return user[USER_ID];
        }
    }
    return -1;
}

/**
 * @brief Фукнция, которая возвращает username пользователя по его user_ID
 *
 * @param user_id - ID пользователя
 *
 * @return Возвращает username в строковом формате.
 */
std::string get_username(const int user_id) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    for (const auto& user: users[USERS]) {
        if (user[USER_ID] == user_id) {
            return user[USERNAME];
        }
    }
    return "";
}

/**
 * @brief Функция, которая возвращает название группового чата по group_ID.
 *
 * @param group_id - ID группового чата.
 *
 * @return Возвращает название группового чата в строковом формате.
 */
std::string get_group_name(const int group_id) {
    dirent* file = return_group_chat(group_id);
    
    std::string file_path = std::string(GROUP_CHATS_FILES_PATH) + std::string(file->d_name);
    ordered_json chat = get_json_data(file_path);
    
    return chat[GROUP_NAME];
}

/**
 * @brief Функция, которая вычисляет, является ли пользователь админом группового чата.
 *
 * @param client_name - имя пользователя, которого нужно проверить.
 * @param data - json файл, в котором хранится групповой чат.
 *
 * @return Возвращает true или false.
 */
bool is_group_admin(const std::string client_name, ordered_json data) {
    for (const auto& admin_ID: data[GROUP_ADMINS_ID]) {
        if (admin_ID == get_user_ID(client_name)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Функция, которая вычисляет, является ли пользователь участником группового чата.
 *
 * @param client_name - имя пользователя, которого нужно проверить.
 * @param data - json файл, в котором хранится групповой чат.
 *
 * @return Возвращает true или false.
 */
bool is_group_member(const std::string client_name, ordered_json data) {
    for (const auto& member_ID: data[GROUP_MEMBERS_ID]) {
        if (member_ID == get_user_ID(client_name)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Функция, которая вычисляет, существует ли пользователем с данным юзернеймом.
 *
 * @param username - юзернейм пользователя, которого нужно проверить.
 *
 * @return Возвращает true или false.
 */
bool does_user_exist(const std::string username) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    for (const auto& user: users[USERS]) {
        if (user[USERNAME] == username) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Фукнция, которая вычисляет позицию элемента массива в json файле.
 *
 * @param what - что нужно проверить. Это может быть int или строковый формат или что угодно, что может храниться в json файле.
 * @param where - гре нужно найти позицию, а именно название массива.
 * @param data - json файл, с которым мы работаем.
 *
 * @return Возвращает позицию элемента в формате int.
 */
template<typename F>
int get_pos_in_array_json(const F what, const std::string where, const ordered_json data) {
    int pos = 0;
    for (; pos < data[where].size(); ++pos) {
        if (what == data[where][pos]) {
            return pos;
        }
    }
    return -1;
}

/**
 * @brief Фукнция, которая возвращает json файл по его полному пути.
 *
 * @param file_path - полный путь json файла.
 *
 * @return Возвращает json файл.
 */
ordered_json get_json_data(const std::string file_path) {
    std::ifstream file(file_path);
    ordered_json data;
    file >> data;
    file.close();
    return data;
}

/**
 * @brief Фукнция, которая возвращает json файл в формате string.
 *
 * @param file_path - полный путь json файла.
 *
 * @return Возвращает сроковый формат json файла.
 */
std::string get_json_string_data(const std::string file_path) {
    ordered_json chat = get_json_data(file_path);
    std::string data = chat.dump();
    return data;
}

/**
 * @brief Фукцния, которая создает json файл
 *
 * @param file_path - полный путь файла, где он будет создан и в последующем храниться.
 * @param data - json файл, который мы создаем.
 */
void write_json_data(const std::string file_path, ordered_json data) {
    std::ofstream file(file_path);
    file << data.dump(4);
    file.close();
}

/**
 * @brief Фукнция, которая возвращает ошибку, если та была поймана в не зависимости от функции, которую мы хотим передать.
 *
 * @param function - фукнция, которая првоеряется на ошибки
 * @param args - аргументы функции
 */
template<typename F, typename... Args>
void try_catch(F&& function, Args&&... args) {
    try {
        function(std::forward<Args>(args)...);
    } catch (const std::string& error) {
        std::cout << error << std::endl;
    }
}

/**
 * @brief Функция, которая возвращает указатель на файл с личной перепиской двух пользователей
 *
 * @param username1 - юзернейм первого пользователя
 * @param username2 - юзернейм второго пользователя
 *
 * @return Возвращает либо указатель на файл, либо nullptr
 */
dirent* return_personal_chat(const std::string username1, const std::string username2) {
    const int client1_ID = get_user_ID(username1);
    const int client2_ID = get_user_ID(username2);

    std::hash<std::string> hasher;
    size_t hash = hasher(std::to_string(client1_ID)) ^ hasher(std::to_string(client2_ID));
    while (hash >= 10000) {
        hash /= 10;
    }
    
    DIR* dir = opendir(PERSONAL_CHATS_FILES_PATH.c_str());
    if (dir == nullptr) {
        std::cerr << "Папка с чатами не открылась." << std::endl;
    }
    
    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (std::string(entry->d_name) == (std::to_string(hash) + ".json")) {
            return entry;
        }
    }
    return nullptr;
}

/**
 * @brief Функция, которая возвращает указатель на файл с групповым чатом
 *
 * @param group_id - ID группового чата
 *
 * @return Возвращает либо указатель на файл, либо nullptr
 */
dirent* return_group_chat(const int group_id) {
    DIR* dir = opendir(GROUP_CHATS_FILES_PATH.c_str());
    if (dir == nullptr) {
        std::cerr << "Папка с чатами не открылась." << std::endl;
    }
    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string json_file = std::string(entry->d_name);
        if (json_file.size() > sizeof(".json")) {
            ordered_json data = get_json_data(std::string(GROUP_CHATS_FILES_PATH) + std::string(entry->d_name));
            if (data[GROUP_ID] == group_id) {
                return entry;
            }
        }
    }
    return nullptr;
}

/**
 * @brief Функция, которая возвращает указатель на файл с групповым чатом
 *
 * @param client_name - юзернейм пользователя, который делает запрос
 * @param group_name - название группового чата
 *
 * @return Возвращает либо указатель на файл, либо nullptr
 */
dirent* return_group_chat(const std::string client_name, const std::string group_name) {
    DIR* dir = opendir(GROUP_CHATS_FILES_PATH.c_str());
    if (dir == nullptr) {
        std::cerr << "Папка с чатами не открылась." << std::endl;
    }
    
    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string json_file = std::string(entry->d_name);
        if (json_file.size() > sizeof(".json")) {
            ordered_json data = get_json_data(std::string(GROUP_CHATS_FILES_PATH) + std::string(entry->d_name));
            if (data[GROUP_NAME] == group_name) {
                for (const auto& member_id: data[GROUP_MEMBERS_ID]) {
                    if (member_id == get_user_ID(client_name)) {
                        return entry;
                    }
                }
            }
        }
    }
    return nullptr;
}

/**
 * @brief Функция добавляет в файл users.json (файл, где хранится информация обо всех пользователях) ID пользователей, с которыми есть личная переписка
 *
 * @param client1_ID - ID первого клиента
 * @param client2_ID - ID второго клиента
 */
void append_personal_chat_id(const int client1_ID, const int client2_ID) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    int user_pos = -1;

    for (const auto& user: users[USERS]) {
        ++user_pos;
        if (user[USER_ID] == client1_ID) {
            users[USERS][user_pos][PERSONAL_CHATS_ID].push_back(client2_ID);
        } else if (user[USER_ID] == client2_ID) {
            users[USERS][user_pos][PERSONAL_CHATS_ID].push_back(client1_ID);
        }
    }
    
    write_json_data(USERS_FILE_PATH, users);
}

/**
 * @brief Функция добавляет в файл users.json (файл, где хранится информация обо всех пользователях) ID группового чата, в котором состоит пользователь
 *
 * @param username - юзернейм пользователя, к которому нужно добавить информацию
 * @param group_id - ID группового чата
 */
void append_group_chat_id(const std::string username, const unsigned group_id) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    int user_pos = -1;
    for (const auto& user: users[USERS]) {
        ++user_pos;
        if (user[USER_ID] == get_user_ID(username)) {
            users[USERS][user_pos][GROUP_CHATS_ID].push_back(group_id);
        }
    }

    write_json_data(USERS_FILE_PATH, users);
}

/**
 * @brief Функция удаляет из файла users.json (файл, где хранится информация обо всех пользователях) ID группового чата, в котором пользователь более не состоит
 *
 * @param username - юзернейм пользователя, к которому нужно добавить информацию
 * @param group_id - ID группового чата
 */
void erase_group_chat_id(const std::string username, const unsigned group_id) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    int user_pos = -1;
    
    for (const auto& user: users[USERS]) {
        ++user_pos;
        if (user[USER_ID] == get_user_ID(username)) {
            unsigned pos = 0;
            for (; pos < user[GROUP_CHATS_ID].size(); ++pos) {
                if (user[GROUP_CHATS_ID][pos] == group_id) {
                    users[USERS][user_pos][GROUP_CHATS_ID].erase(pos);
                }
            }
        }
    }
    
    write_json_data(USERS_FILE_PATH, users);
}

/**
 * @brief Функция парсит команду, которая приходит от клиента на составляющие: флаги, название команды
 *
 * @param input - строка с командой, которую нужно распарсить
 *
 * @return Возвращает карту распаршенной команды
 */
std::map<std::string, std::string> parse_command(const std::string input) {
    std::istringstream iss(input);
    std::map<std::string, std::string> parsed_command;
    std::string key, value;
    iss >> key;
    iss >> value;
    parsed_command[key] = value;
    iss >> value;
    parsed_command["command"] = value;
    
    if ((parsed_command["command"] == "send_personal_message") || (parsed_command["command"] == "send_group_message")) {
        while (iss >> key) {
            if (key != "-m") {
                iss >> value;
                parsed_command[key] = value;
            } else {
                while (iss >> value) {
                    parsed_command[key] += " " + value;
                }
            }
        }
    } else {
        while (iss >> key) {
            iss >> value;
            parsed_command[key] = value;
        }
    }
    return parsed_command;
}

/**
 * @brief Фукнция выводит в поток вывода переданную карту
 *
 * @param input_map - переданная карта, которую нужно распечатать
 */
template<typename first, typename second>
void print_map(const std::map<first, second> input_map) {
    for (const auto& [key, value]: input_map) {
        std::cout << key << ": " << value << std::endl;
    }
}

/**
 * @brief Функция работает с удаленным из группового чата пользователем, а именно удаляет ID пользователя из json файла, в котором хранится информация о групповом чате. Также обновляет информацию в файле users.json, то есть удаляет у пользователя ID группы, из которой он был удален
 *
 * @param user_name - юзернейм пользователя
 * @param group - "группа" пользовтелей, из которых нужно удалить юзера (ADMINS_ID, MEMBERS_ID, и т д)
 * @param chat - json файл группового чатая
 */
void delete_user_from_group(const std::string user_name, const std::string group, ordered_json& chat) {
    int pos = get_pos_in_array_json(get_user_ID(user_name), group, chat);
    chat[group].erase(pos);
    erase_group_chat_id(user_name, chat[GROUP_ID]);
}

/**
 * @brief Функция генерирует "уникальный" токен клиента
 *
 * @return Возвращает int значение токена
 */
int generate_token() {
    std::srand(unsigned(std::time(nullptr)));
    int token = std::rand() % 100000 + 1;
    return token;
}

/**
 * @brief Фукнция переводит переданную карту в строку
 *
 * @param map - карта, которую нужно перевести в строковый формат
 */
std::string map_to_str(std::map<std::string, std::string> map) {
    std::string output;
    for (const auto& [key, value]: map) {
        output += key + " " + value;
    }
    return output;
}

/**
 * @brief Функция находит юзерней клиента по его токену
 *
 * @return Возвращает строку с юзернеймом
 */
std::string get_username_from_token(const int token) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    for (const auto& user: users[USERS]) {
        if (user[TOKEN] == token) {
            return user[USERNAME];
        }
    }
    return "";
}
