#include <string>

#include "show_personal_chats.h"
#include "../../constants.h"
#include "../../../json.hpp"
#include "../../utils/utils.h"

/**
 * @brief Фукнция, которая возвращает клиенту строку со списком его персональных чатов.
 *
 * @param client_name - юзернейм, который делает запрос.
 * @return В качестве возвращаемого значения передается строка, в которой хранится список персональных чатов.
 */
std::string client_show_personal_chats(const std::string client_name) {
    ordered_json users = get_json_data(USERS_FILE_PATH);
    std::string chats = "Personal chats:";
    
    for (const auto& user: users[USERS]) {
        if (user[USERNAME] == client_name) {
            for (const auto& pes_ch_id: user[PERSONAL_CHATS_ID]) {
                chats += " " + get_username(pes_ch_id);
            }
        }
    }
    
    return chats;
}
