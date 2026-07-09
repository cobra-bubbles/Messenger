#include <dirent.h>
#include <string>

#include "return_group_chats_str.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая возвращает групповой чат строку формата json клиенту.
 *
 * @param client_name - пользователь, который делает запрос.
 * @param group_name - название группового чата.
 * @return В качестве возвращаемого значения передается строка формата json.
 */
std::string client_return_group_chat_str(const std::string client_name, const std::string group_name) {
    dirent* file = return_group_chat(client_name, group_name);
    if (!file) {
        return "Такой группы не существует.";
    }
    std::string full_path = std::string(GROUP_CHATS_FILES_PATH) + std::string(file->d_name);
    return get_json_string_data(full_path);
}
