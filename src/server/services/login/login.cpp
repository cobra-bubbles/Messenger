#include <string>
#include <functional>

#include "login.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая позволяет пользователю залогиниться.
 *
 * @param login - логин пользователя.
 * @param password - пароль пользователя.
 * @return В качестве возвращаемого значения передается строка, которая сообщается пользователю. В случае успеха в качестве первого слова будет передан токен клиента, второго - юзернейм пользователя.
 */
std::string client_log_in(const std::string login, const std::string password) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    
    std::hash<std::string> hasher;
    size_t hash = hasher(password);
    
    int pos = -1;

    for (const auto& user: users[USERS]) {
        ++pos;
        if (user[LOGIN] == login) {
            if (user[HASH] == hash) {
                int token = generate_token();
                
                users[USERS][pos][TOKEN] = token;
                write_json_data(USERS_FILE_PATH, users);
                
                return std::to_string(token) + " " + std::string(user[USERNAME]) + " Success!";
            }
        }
    }
    return std::string("Неверный логин или пароль.");
}
