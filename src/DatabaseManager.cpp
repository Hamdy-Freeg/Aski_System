#include "../include/DatabaseManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void DataBaseManager::save_new_user(const User &user) {

    ofstream out("data/users.csv", ios::app);
    
    if(out.is_open()) {
        out << user.id << ','
            << user.username << ','
            << user.password << ','
            << user.email << ','
            << user.allow_anonymous_question << ',' 
            << "\n";
        out.close();

    } else {
        cout << "Error: couldn't open users.csv,"
         << " check that you are running the program form root dir. \n";
    }

}


vector<User> DataBaseManager::load_users() {
    vector<User> users;
    ifstream in("data/users.csv");
    string line;

    if (in.is_open()) {
        while (getline(in, line)) {
            stringstream ss(line);
            string id, username ,password
             ,name ,email 
             ,allow_anonymous_question;

            getline(ss, id, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, allow_anonymous_question, ',');


            User new_user;


            new_user.id = stoi(id);
            new_user.username = name;
            new_user.password = password;
            new_user.name = name;
            new_user.email = email;
            new_user.email = stoi(allow_anonymous_question);


            users.push_back(new_user);

        }
        in.close(); 
    } else {
        cout << "Error: couldn't open users.csv,"
         << " check that you are running the program form root dir. \n";
    }
    return users;
}


void DataBaseManager::save_new_question(const Question &question) {
    ofstream out("data/questions.csv", ios::app);

    if(out.is_open()) {
        out << question.id << ',' 
            << question.parent_question_id << ','
            << question.sender_id << ','
            << question.receiver_id << ','
            << question.text << ','
            << question.is_anonymous;

        out.close();        
    } else {
        cout << "Error: couldn't open questions.csv,"
         << " check that you are running the program form root dir. \n";
    }

}


vector<Question> DataBaseManager::load_qustions() {
    vector<Question> questions;

    ifstream in("data/questions.csv");
    string line;

    if(in.is_open()) {

        while (getline(in, line)) {
            stringstream ss(line);
            string id, parent_question_id,
             sender_id, receiver_id, 
             text, is_anonymous;

            getline(ss, id, ',');
            getline(ss, parent_question_id, ',');
            getline(ss, sender_id, ',');
            getline(ss, receiver_id, ',');
            getline(ss, text, ',');
            getline(ss, is_anonymous, ',');


            Question new_q;

            new_q.id = stoi(id);
            new_q.parent_question_id = stoi(parent_question_id);
            new_q.sender_id = stoi(sender_id);
            new_q.receiver_id = stoi(receiver_id);
            new_q.text = text;
            new_q.is_anonymous = stoi(is_anonymous);
            
            questions.push_back(new_q);
        }

        in.close();

    } else {
        cout << "Error: couldn't open questions.csv,"
         << " check that you are running the program form root dir. \n";
    }

    return questions;
}


void DataBaseManager::save_questions(const vector<Question> &all_questions) {

    ofstream out("data/questions.csv", ios::out);
    
    if (out.is_open()) {
        for(const auto &question: all_questions) {
        out << question.id << ',' 
            << question.parent_question_id << ','
            << question.sender_id << ','
            << question.receiver_id << ','
            << question.text << ','
            << question.is_anonymous;

        }
        out.close();
    } else {
        cout << "Error: couldn't open questions.csv,"
         << " check that you are running the program form root dir. \n";
    }

}