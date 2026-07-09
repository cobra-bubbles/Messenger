#ifndef CONTROLLER_H
#define CONTROLLER_H

bool simple_client_command(const std::string& command);
extern std::map<std::string, std::function<void(const std::string& message)>> handle_server_answer;

#endif
