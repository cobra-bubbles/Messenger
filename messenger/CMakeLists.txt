cmake_minimum_required(VERSION 3.15)
project(Messenger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED)

set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
find_package(OpenSSL REQUIRED)

# Добавляем папку src в пути поиска (для json.hpp)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Сервер
add_executable(server
    src/server/server.cpp
    src/server/controller/call_command.cpp
    src/server/services/add_friend/add_friend.cpp
    src/server/services/return_group_chats_str/return_group_chats_str.cpp
    src/server/services/change_group_name/change_group_name.cpp
    src/server/services/return_personal_chat_str/return_personal_chat_str.cpp
    src/server/services/change_username/change_username.cpp
    src/server/services/send_group_message/send_group_message.cpp
    src/server/services/create_group_chat/create_group_chat.cpp
    src/server/services/send_personal_message/send_personal_message.cpp
    src/server/services/create_personal_chat/create_personal_chat.cpp
    src/server/services/show_chats/show_chats.cpp
    src/server/services/group_settings/group_settings.cpp
    src/server/services/show_friends/show_friends.cpp
    src/server/services/login/login.cpp
    src/server/services/show_group_chats/show_group_chats.cpp
    src/server/services/manage_group_user/manage_group_user.cpp
    src/server/services/show_personal_chats/show_personal_chats.cpp
    src/server/services/register/register.cpp
    src/server/utils/utils.cpp
)

target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(server PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Клиент
add_executable(client
    src/client/client.cpp
    src/client/utils/utils.cpp
    src/client/controller/controller.cpp
    src/client/services/services.cpp
    src/client/input_handler/input_handler.cpp
)

target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(client PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
)
