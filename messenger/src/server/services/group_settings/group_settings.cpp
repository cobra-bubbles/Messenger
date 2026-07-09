#include <dirent.h>
#include <string>

#include "group_settings.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Функция, которая возвращает строку с настройками группового чата.
 *
 * @param client_name - юзернейм пользователя, который делает запрос на настройки группового чата.
 * @param group_name - название группового чата.
 * @return В качестве возвращаемого значения передается строка, содержащая настройки группового чата.
 */
std::string client_group_settings(const std::string client_name, const std::string group_name) {
    std::string settings;

    dirent* file = return_group_chat(client_name, group_name);
    if (!file) {
        return std::string("Вы не состоите в группе ") + group_name;
    }
    std::string group_chat_file_path = std::string(GROUP_CHATS_FILES_PATH) + std::string(file->d_name);
    
    ordered_json temp_group_chat;
    ordered_json group_chat = get_json_data(group_chat_file_path);
    temp_group_chat["GROUP_ADMINS_USERNAMES"] = json::array();
    temp_group_chat["GROUP_MEMBERS_USERNAMES"] = json::array();
    
    temp_group_chat[GROUP_NAME] = group_chat[GROUP_NAME];
    temp_group_chat["GROUP_OWNER_USERNAME"] = get_username(group_chat[GROUP_OWNER_ID]);
    for (const auto& admin: group_chat[GROUP_ADMINS_ID]) {
        temp_group_chat["GROUP_ADMINS_USERNAMES"].push_back(get_username(admin));
    }
    for (const auto& member: group_chat[GROUP_MEMBERS_ID]) {
        temp_group_chat["GROUP_MEMBERS_USERNAMES"].push_back(get_username(member));
    }
    
    settings = temp_group_chat.dump();

    return settings;
}

