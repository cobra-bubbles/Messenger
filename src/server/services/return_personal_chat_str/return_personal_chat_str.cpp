#include <string>
#include <dirent.h>

#include "return_personal_chat_str.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая возвращает персональный чат двух пользователей в формате string (json).
 *
 * @param username1 - первый пользователь.
 * @param username2 - второй пользователь.
 * @return В качестве возвращаемого значения передается персональный чат.
 */
std::string client_return_personal_chat_str(const std::string username1, const std::string username2) {
    dirent* file = return_personal_chat(username1, username2);
    std::string full_path = std::string(PERSONAL_CHATS_FILES_PATH) + std::string(file->d_name);
    return get_json_string_data(full_path);
}
