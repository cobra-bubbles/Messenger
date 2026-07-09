#include <string>
#include <dirent.h>

#include "../change_group_name/change_group_name.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая отправляет сообщение в групповой чат. Она добавляет это сообщение в json файл.
 *
 * @param client_name - имя пользователя, который отправляет сообщение.
 * @param group_name - название группового чата.
 * @param message - сообщение.
 * @return В качестве возвращаемого значения передается строка, которая сообщает клиенту о статусе запроса.
 */
std::string client_send_group_message(const std::string client_name, const std::string group_name, const std::string message) {
    dirent* entry = return_group_chat(client_name, group_name);
    if (!entry) {
        return "Нет такого групового чата.";
    }
    ordered_json chat = get_json_data(std::string(GROUP_CHATS_FILES_PATH) + std::string(entry->d_name));
    
    chat[MESSAGES].push_back({
        {TIME, get_time()},
        {USERNAME, client_name},
        {MESSAGES, message}
    });
    
    write_json_data(std::string(GROUP_CHATS_FILES_PATH) + std::string(entry->d_name), chat);
    return "Success!";
}
