#include <string>
#include <functional>

#include "create_personal_chat.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая создает персональный чат двух пользователей.
 *
 * @param username1 - первый пользователь.
 * @param username2 - второй пользователь.
 * @return В качестве возвращаемого значения передается строка, которая сообщается пользователю.
 */
bool client_create_personal_chat(const std::string username1, const std::string username2) {
    const int client1_ID = get_user_ID(username1);
    const int client2_ID = get_user_ID(username2);
    if (!client1_ID || !client2_ID) {
        return false;
    }
    
    std::hash<std::string> hasher;
    size_t hash = hasher(std::to_string(client1_ID)) ^ hasher(std::to_string(client2_ID));
    while (hash >= 10000) {
        hash /= 10;
    }
    
    std::string new_chat_path = std::string(PERSONAL_CHATS_FILES_PATH) + std::to_string(hash) + ".json";
    ordered_json chat;
    chat[MESSAGES] = json::array();
    write_json_data(new_chat_path, chat);
    
    append_personal_chat_id(client1_ID, client2_ID);
    return true;
}
