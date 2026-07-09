#include <string>
#include <functional>

#include "create_group_chat.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая создает групповой чат.
 *
 * @param username - юзернейм пользователя, который хочет создать групповой чат.
 * @param group_name - имя группового чата.
 */
void client_create_group_chat(const std::string username, const std::string group_name) {
    std::hash<std::string> hasher;
    size_t hash = hasher(username) ^ hasher(group_name) ^ hasher(get_time());
    while (hash >= 10000) {
        hash /= 10;
    }
    
    ordered_json conf = get_json_data(std::string(CONF_PATH));
    unsigned group_id = conf[MAX_GROUP_ID];
    std::string new_chat_path = std::string(GROUP_CHATS_FILES_PATH) + std::to_string(hash) + ".json";
    ordered_json chat;
    chat[GROUP_NAME] = group_name;
    chat[GROUP_OWNER_ID] = get_user_ID(username);
    chat[GROUP_ADMINS_ID] = json::array();
    chat[GROUP_MEMBERS_ID].push_back(get_user_ID(username));
    chat[GROUP_ID] = ++group_id;
    chat[MESSAGES] = json::array();
    write_json_data(new_chat_path, chat);
    append_group_chat_id(username, group_id);
    conf[MAX_GROUP_ID] = group_id;
    write_json_data(CONF_PATH, conf);
}
