#include <string>
#include <dirent.h>

#include "change_group_name.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая меняет название группы group_name на новое название new_group_name.
 *
 * @param client_name - клиент, который хочет поменять название группы.
 * @param group_name - настоящее имя группы.
 * @param new_group_name - новое имя группы.
 * @return В качестве возвращаемого значения передается строка, которая сообщается пользователю.
 */
std::string client_change_group_name(const std::string client_name, const std::string group_name, const std::string new_group_name) {
    dirent* entry = return_group_chat(client_name, group_name);
    if (!entry) {
        return "Не существует группы с названием " + group_name;
    }
    std::string group_chat_path = std::string(GROUP_CHATS_FILES_PATH) + std::string(entry->d_name);
    ordered_json chat = get_json_data(group_chat_path);
    
    if (is_group_admin(client_name, chat) || (get_user_ID(client_name) == chat[GROUP_OWNER_ID])) {
        chat[GROUP_NAME] = new_group_name;
    } else {
        return std::string("Пользователь ") + client_name + std::string(" не является владельцем или админом группы.");
    }
    write_json_data(group_chat_path, chat);
    return "Success!";
}

