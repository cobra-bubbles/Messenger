#include <string>

#include "add_friend.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;

/**
 * @brief Фукнция, которая добавляет друга (friend_name) пользователю username.
 *
 * @param username - клиент, который хочет добавить друга.
 * @param friend_name - имя нового друга
 * @return В качестве возвращаемого значения передается строка, которая сообщается пользователю.
 */
std::string client_add_friend(const std::string username, const std::string friend_name) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    int user_pos = -1;
    int friend_ID = get_user_ID(friend_name);
    int user_ID = get_user_ID(username);
    
    if (!does_user_exist(friend_name)) {
        return std::string("Пользователя ") + friend_name + std::string(" не существует.");
    } else if (user_ID == friend_ID) {
        return std::string("Вы не можете добавить самого себя в раздел \"друзья\".");
    }
    for (const auto& user: users[USERS]) {
        ++user_pos;
        if (user[USER_ID] == user_ID) {
            
            for (const auto& fr_id: user[FRIENDS_ID]) {
                if (fr_id == friend_ID) {
                    return std::string("Вы уже дружите с пользователем ") + friend_name;
                }
            }
            
            users[USERS][user_pos][FRIENDS_ID].push_back(friend_ID);
        }
    }
    write_json_data(USERS_FILE_PATH, users);
    return "Success!";
}
