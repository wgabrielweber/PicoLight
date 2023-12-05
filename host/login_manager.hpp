 /**
 * @file login_manager.hpp
 * @brief Login Manager header file
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 28/11/2023
 * @institution UFSC
 */

#ifndef LOGIN_MANAGER_HPP
#define LOGIN_MANAGER_HPP

#include <iostream>
#include <string>

class LoginManager {
public:
    LoginManager() {}

    bool authenticate() const;
};

#endif // LOGIN_MANAGER_HPP
