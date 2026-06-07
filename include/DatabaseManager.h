#pragma once
#include <vector>
#include "User.h"
#include "Question.h"
using namespace std;

class DataBaseManager {
public :

    void save_new_user(const User &user);
    vector<User> load_users();


    void save_questions(const vector<Question> &all_questions);
    void save_new_question(const Question &question);
    vector<Question> load_qustions();

};