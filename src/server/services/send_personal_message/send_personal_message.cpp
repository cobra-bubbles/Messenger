#include <string>
#include <dirent.h>

#include "send_personal_message.h"
#include "../create_personal_chat/create_personal_chat.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая отправляет сообщение в персональный чат. Она добавляет это сообщение в json файл.
 *
 * @param client_username_from - имя пользователя, который хочет отправить сообщение.
 * @param client_username_to - имя пользователя, которому отправляется сообщение.
 * @param message - сообщение.
 * @return В качестве возвращаемого значения передается строка, которая сообщает клиенту о статусе запроса.
 */
std::string client_send_personal_message(const std::string client_username_from, const std::string client_username_to, const std::string message) {
    dirent* entry = return_personal_chat(client_username_from, client_username_to);
    if (!entry) {
        bool created = client_create_personal_chat(client_username_from, client_username_to);
        if (!created) {
            return "Данного пользователя не существует";
        }
    }
    entry = return_personal_chat(client_username_from, client_username_to);
    ordered_json chat = get_json_data(std::string(PERSONAL_CHATS_FILES_PATH) + std::string(entry->d_name));
    
    chat[MESSAGES].push_back({
        {TIME, get_time()},
        {USERNAME, client_username_from},
        {MESSAGES, message}
    });
    
    write_json_data(std::string(PERSONAL_CHATS_FILES_PATH) + std::string(entry->d_name), chat);
    return "Success!";
}
