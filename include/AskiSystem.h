#pragma once 
#include "Question.h"
#include "User.h"
#include "DatabaseManager.h"
#include <map>

class AskiSystem {
private:
    int current_user_id;

    vector<User> users;
    vector<Question> questions;
    DataBaseManager db_manager;
    map<int, int> question_id_to_index;
    map<int, vector<int>> question_threads_map;

    void display_guest_menu();
    void display_user_menu();

    void login();
    void sign_up();
    void logout();

    void print_coming_questions();
    void print_quesions_from_me();
    void answer_question();
    void delete_question();
    void ask_question();
    void list_system_users();
    void show_feed();
    void log_out();

public:
    AskiSystem();

    void run();

};