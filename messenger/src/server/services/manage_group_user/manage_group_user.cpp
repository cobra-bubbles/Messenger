#include <dirent.h>
#include <string>

#include "manage_group_user.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая меняет настройки группового чата, а именно взаимодействует с пользователями чата: удаляет, добавляет пользователя в группу юзеров.
 *
 * @param client_name - юзернейм пользователя, который хочет кого-то добавить или удалить.
 * @param user_name - юзернейм пользователя, с которым взаимодействуют.
 * @param group_name - название группового чата.
 * @param flag - флаг, который сообщает, что сделать с пользователем: добавить или удалить.
 * @param group - группа пользователей, с которой взаимодействуют.
 * @return В качестве возвращаемого значения передается строка, которая сообщается пользователю.
 */
std::string client_manage_group_user(const std::string client_name, const std::string user_name, const std::string group_name, const std::string flag, std::string group) {
    
    dirent* entry = return_group_chat(client_name, group_name);
    if (!entry) {
        return "Нет такого групового чата.";
    }
    std::string chat_file_path = std::string(GROUP_CHATS_FILES_PATH) + std::string(entry->d_name);
    ordered_json chat = get_json_data(chat_file_path);
    
    bool owner = (chat[GROUP_OWNER_ID] == get_user_ID(client_name));
    bool admin = is_group_admin(client_name, chat);
    
    if (!owner && !admin) {
        return "Простой пользователь группы не может управлять конфигурацией группы.";
    }
    
    if (group == "GROUP_ADMINS_ID") {
        group = GROUP_ADMINS_ID;
    } else if (group == "GROUP_MEMBERS_ID") {
        group = GROUP_MEMBERS_ID;
    }
    
    if (flag == "a") {
        if (group == GROUP_ADMINS_ID) {
            if (owner) {
                if (!is_group_member(user_name, chat)) {
                    return std::string("Пользователь ") + user_name + std::string(" не является участником группы. Для начала добавьте его.");
                } else if (is_group_admin(user_name, chat)) {
                    return std::string("Пользователь ") + user_name + std::string(" уже является админом группы.");
                } else if (is_group_member(user_name, chat) && !is_group_admin(user_name, chat)) {
                    chat[GROUP_ADMINS_ID].push_back(get_user_ID(user_name));
                }
            } else if (admin) {
                return std::string("Админ группы не может управлять другими админами.");
            }
        } else if (group == GROUP_MEMBERS_ID) {
            if (owner || admin) {
                if (is_group_member(user_name, chat)) {
                    return std::string("Пользователь ") + user_name + std::string(" уже является участником группы.");
                } else {
                    int uid = get_user_ID(user_name);
                    chat[GROUP_MEMBERS_ID].push_back(uid);
                    append_group_chat_id(user_name, chat[GROUP_ID]);
                }
            }
        }
    } else if (flag == "d") {
        if (group == GROUP_ADMINS_ID) {
            if (owner) {
                if (!is_group_member(user_name, chat)) {
                    return std::string("Пользователь ") + user_name + std::string(" не является участником группы.");
                } else if (!is_group_admin(user_name, chat)) {
                    return std::string("Пользователь ") + user_name + std::string(" не является админом группы.");
                } else if (is_group_member(user_name, chat) && is_group_admin(user_name, chat)) {
                    delete_user_from_group(user_name, GROUP_ADMINS_ID, chat);
                }
            } else if (admin) {
                return std::string("Админ группы не может управлять другими админами.");
            }
        } else if (group == GROUP_MEMBERS_ID) {
            if (owner) {
                if (!is_group_member(user_name, chat)) {
                    return std::string("Пользователь ") + user_name + std::string(" не является участником группы.");
                } else if (is_group_admin(user_name, chat)) {
                    delete_user_from_group(user_name, GROUP_ADMINS_ID, chat);
                    delete_user_from_group(user_name, GROUP_MEMBERS_ID, chat);
                } else if (!is_group_admin(user_name, chat)) {
                    delete_user_from_group(user_name, GROUP_MEMBERS_ID, chat);
                }
            } else if (admin) {
                if (!is_group_member(user_name, chat)) {
                    return std::string("Пользователь ") + user_name + std::string(" не является участником группы.");
                } else if (is_group_admin(user_name, chat)) {
                    return std::string("Админ группы не может управлять другими админами.");
                } else if (!is_group_admin(user_name, chat)) {
                    delete_user_from_group(user_name, GROUP_MEMBERS_ID, chat);
                }
            }
        }
    }
    
    write_json_data(chat_file_path, chat);
    return "Success!";
}
