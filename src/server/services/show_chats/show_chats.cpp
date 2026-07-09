#include <string>

#include "show_chats.h"
#include "../show_personal_chats/show_personal_chats.h"
#include "../show_group_chats/show_group_chats.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая возвращает клиенту строку со списком всех его чатов: персональных и групповых.
 *
 * @param client_name - юзернейм, который делает запрос.
 * @return В качестве возвращаемого значения передается строка, в которой хранится список персональных и групповых чатов.
 */
std::string client_show_chats(const std::string client_name) {
    std::string chats = client_show_personal_chats(client_name) + "\n" + client_show_group_chats(client_name);
    return chats;
}
