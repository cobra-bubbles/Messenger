#include <string>

#include "change_username.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая меняет имя пользователя username на новое имя new_username.
 *
 * @param username - настоящий юзернейм.
 * @param new_username - новый юзернейм.
 * @return В качестве возвращаемого значения передается строка, которая сообщается пользователю.
 */
std::string client_change_username(const std::string username, const std::string new_username) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    int user_pos_in_array = -1;
    bool found_user = false;
    for (const auto& user: users[USERS]) {
        if (!found_user) {
            ++user_pos_in_array;
        }
        if (user[USERNAME] == username) {
            found_user = true;
            if (username == new_username) {
                return std::string("Вы ввели свой нынешний юзернейм. Пожалуйста, введите новый.");
            }
        } else if ((user[USERNAME] != username) && (user[USERNAME] == new_username)) {
            return std::string("Данный юзерней уже используется. Пожалуйста, придумайте другой.");
        }
    }
    users[USERS][user_pos_in_array][USERNAME] = new_username;
    write_json_data(USERS_FILE_PATH, users);
    
    return new_username + "Success!";
}
