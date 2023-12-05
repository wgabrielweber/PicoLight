 /**
 * @file login_manager.cpp
 * @brief login_manager implementation file
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 28/11/2023
 * @institution UFSC
 */

#include "login_manager.hpp"

bool LoginManager::authenticate() const {
    std::string username, password;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    // Replace this with your actual authentication logic
    return (username == "admin" && password == "0000");
}
