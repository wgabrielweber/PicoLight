#include "login_manager.hpp"

bool LoginManager::authenticate() const {
    std::string username, password;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    // Replace this with your actual authentication logic
    return (username == "admin" && password == "password");
}
