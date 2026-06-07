#pragma once 
#include <string>

using namespace std;

struct Question {

    int id;
    int parent_question_id;
    int sender_id;
    int receiver_id;
    string text;
    string answer_text;
    bool is_anonymous;

};