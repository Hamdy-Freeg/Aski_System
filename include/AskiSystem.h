#pragma once 
#include "User.h"

class AskiSystem {
private:
    int current_user_id;

    void display_guest_menu();
    void display_user_menu();

    void login();
    void sign_up();
    void logout();

public:
    AskiSystem();

    void run();

};