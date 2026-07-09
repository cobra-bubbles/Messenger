#include <string>

#include "show_friends.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая отправляет клиенту список его друзей.
 *
 * @param client_name - имя пользователя, который делает запрос.
 * @return В качестве возвращаемого значения передается строка, в которой хранится список друзей клиента.
 */
std::string client_show_friends(const std::string client_name) {
    std::string friend_array;
    
    ordered_json users = get_json_data(USERS_FILE_PATH);
    for (const auto& user: users[USERS]) {
        if (user[USERNAME] == client_name) {
            for (const auto& friend_id: user[FRIENDS_ID]) {
                friend_array += get_username(friend_id) + std::string(" ");
            }
        }
    }
    if (friend_array == "") {
        friend_array = "У вас нет друзей.";
    }
    
    return friend_array;
}
