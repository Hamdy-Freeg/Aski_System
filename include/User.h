#pragma once
#include <string>

using namespace std;

struct User {
    int id;
    string name;
    string username;
    string password;
    string email;
    bool allow_anonymous_question;
      
};