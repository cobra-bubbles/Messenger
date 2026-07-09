#include <string>
#include <functional>

#include "register.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая регистрирует пользователя.
 *
 * @param login - логин пользователя.
 * @param password - пароль пользователя.
 * @param username - юзернейм пользователя.
 * @return В качестве возвращаемого значения передается строка, которая сообщается пользователю.
 */
std::string client_register(const std::string login, const std::string password, const std::string username) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    int new_id = 0;

    for (const auto& user: users[USERS]) {
        if (user[USERNAME] == username) {
            return std::string("Юзернейм ") + username + std::string(" уже используется.");
        }
        new_id = user[USER_ID];
    }
    
    std::hash<std::string> hasher;
    size_t hash = hasher(password);
    
    users[USERS].push_back({
        {LOGIN, login},
        {HASH, hash},
        {PASSWORD, password},
        {USER_ID, ++new_id},
        {USERNAME, username},
        {FRIENDS_ID, json::array()},
        {PERSONAL_CHATS_ID, json::array()},
        {GROUP_CHATS_ID, json::array()},
        {TOKEN, 0}
    });
    
    write_json_data(USERS_FILE_PATH, users);
    return "Success!";
}
