# Правила работы с мессенджером.

## Далее будут описаны правила, по которым нужно клиенту делать запросы серверу, какие команды существуют и флаги.

### Длина login, password, username или group_name должна быть не менее 4 символов.

- **register -l** "login" **-p** "password" **-u** "username"
- **log_in -l** "login" **-p** "password"
- **log_out**
- **whoami**
- **change_username -u** "username"

- **add_friend -u** "username"
- **show_friends**
- **show_chats**
- **show_group_chats**
- **show_personal_chats**
- **print_personal_chat -u** "username" **-f** "flag" **-n** "number"
- **print_group_chat -gn** "group_name" **-f** "flag" **-n** "number"
 
- **send_personal_message -u** "username" **-m** "msg"
- **send_group_message -gn** "group_name" **-m** "msg" 
- **create_group_chat -gn** "group_name"
- **group_manage -gn** "group_name" **-u** "username" **-f** "flag" **-g** "group"
- **show_group_settings -gn** "group_name"
- **change_group_name -gn** "group_name" **-ngn** "new_group_name" 
