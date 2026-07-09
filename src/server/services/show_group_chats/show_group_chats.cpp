#include <string>

#include "show_group_chats.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая возвращает клиенту строку со списком его групповых чатов.
 *
 * @param client_name - юзернейм, который делает запрос.
 * @return В качестве возвращаемого значения передается строка, в которой хранится список групповых чатов.
 */
std::string client_show_group_chats(const std::string client_name) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    std::string chats = "Group chats:";
    
    for (const auto& user: users[USERS]) {
        if (user[USERNAME] == client_name) {
            for (const auto& gr_ch_id: user[GROUP_CHATS_ID]) {
                chats += " " + get_group_name(gr_ch_id);
            }
        }
    }
    
    return chats;
}
