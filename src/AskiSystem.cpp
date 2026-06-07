#include <iostream>
#include "../include/AskiSystem.h"

using namespace std;


AskiSystem::AskiSystem() {

    current_user_id = -1;
    users = db_manager.load_users();
    questions = db_manager.load_qustions();

    for (int i = 0; i < questions.size(); i++) {
        question_id_to_index[questions[i].id] = i;

        if (questions[i].parent_question_id != -1) {
            question_threads_map[questions[i].parent_question_id].push_back(questions[i].id);
        }
    }

}

void AskiSystem::display_guest_menu() {

        cout << "\n----- Guest Menu -----\n";
        cout << "1: Login \n";
        cout << "2: Sign up \n";
        cout << "3: Exit \n";
        cout << "Enter number in range 1 - 3: ";
    
}

void AskiSystem::display_user_menu() {

        cout << "\n----- User Menu -----\n";
        cout << "1: Print Comming Qustions \n";
        cout << "2: Print Questions From Me \n";
        cout << "3: Answer Question \n";
        cout << "4: Delete Question \n";
        cout << "5: Ask Question \n";
        cout << "6: List System Users \n";
        cout << "7: Feed \n";
        cout << "8: Logout \n";

        cout << "Enter number in range 1 - 8: ";
}


void AskiSystem::sign_up() {
    User new_user;

    cout << "Enter user name(no spaces) \n";
    cin >> new_user.name;

    cout << "Create password \n";
    cin >> new_user.password;

    cout << "Enter your name \n";
    cin.ignore();
    getline(cin, new_user.name);
    
    cout << "Enter your email \n";
    cin >> new_user.email;

    cout << "Allow anonymous questions ? (0 for no - 1 for yes) \n";
    cin >> new_user.allow_anonymous_question;

    if(users.empty()) {
        new_user.id = 1;
    } else {
        new_user.id = users.back().id +1;
    }


    users.push_back(new_user);

    db_manager.save_new_user(new_user);

    cout << "Sign up successful! Your ID is: " << new_user.id << "\n";

}

void AskiSystem::login() {
    
    string in_username, in_password;

    cout << "Please Enter Your Username and Password \n";
    cin >> in_username >> in_password;

    for (const auto &user : users) {
        if(in_username == user.username && in_password == user.password) {

            current_user_id = user.id;
            cout << "Login Successfully, Welcom " << user.name << ". \n";
            return;
        }
    }

    cout << "Error: Invalid Username or Password!! \n";
}





void AskiSystem::print_comming_questions() {

    bool has_question = false;

    cout << "\n----- Comming Questions -----\n";
    for(const auto &question : questions) {
        // if the parent_question id == -1 then its main question not a thread 
        if (question.receiver_id == current_user_id 
        && question.parent_question_id == -1) {

            has_question = true;

            cout << "\nQuestion Id (" << question.id << ") ";

            if (!question.is_anonymous) {
                cout << "from user id(" << question.sender_id << ")\n";
            } else {
                cout << "!AQ \n";
            }

            cout << "Question: " << question.text << "\n";

            if (question.answer_text != "") {
                cout << "Answer: " << question.answer_text << "\n";
            } else {
                cout << "NOt Answred yet! \n";
            }

            for (int thread_id : question_threads_map[question.id]) {

                int idx = question_id_to_index[thread_id];
                const Question& thread_q = questions[idx]; 

                cout << "\tThread: Question Id (" << thread_q.id << ") ";
                if (!thread_q.is_anonymous) cout << "from user id(" << thread_q.sender_id << ")\n";
                else cout << "!AQ \n";
                
                cout << "\tQuestion: " << thread_q.text << "\n";
                if (thread_q.answer_text != "") cout << "\tAnswer: " << thread_q.answer_text << "\n";
                else cout << "\tNOT Answered YET \n";
            }
        }
    }
    if (!has_question) {
        cout << "No questions found for you yet!\n";

    }
}


void AskiSystem::print_quesions_from_me() {

    bool has_questions = false;

    cout << "\n----- Questions From Me -----\n";


    for(const auto &question : questions) {
        if(question.sender_id == current_user_id 
        && question.parent_question_id == -1) {
            has_questions = true;
            cout << "\nQuestion Id (" << question.id << ") ";
            cout << "To user id(" << question.receiver_id << ")\n";
            cout << "Question: " << question.text << "\n";

            if (question.answer_text != "") {
                cout << "Answer: " << question.answer_text << "\n";
            } else {
                cout << "NOt Answred yet! \n";
            }

            for (int thread_id : question_threads_map[question.id]) {
                int idx = question_id_to_index[thread_id];
                const Question& thread_q = questions[idx];

                cout << "\tThread: Question Id (" << thread_q.id << ") ";
                if (thread_q.is_anonymous) cout << "!AQ ";
                cout << "To user id(" << thread_q.receiver_id << ")\n";
                
                cout << "\tQuestion: " << thread_q.text << "\n";
                if (thread_q.answer_text != "") cout << "\tAnswer: " << thread_q.answer_text << "\n";
                else cout << "\tNOT Answered YET \n";
            }
        }
    }

    if (!has_questions) {
        cout << "No questions found for you yet!\n";

    }
}








void AskiSystem::logout() {
    current_user_id = -1;
    db_manager.save_questions(questions);
}


void AskiSystem::run() {

    bool running_system = true;

    while(running_system) {
        if (current_user_id == -1) {
            display_guest_menu();

            int choice;

            cin >> choice;

            if (cin.fail()) {
            cin.clear(); 
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
            }

            switch(choice) {
                case 1:
                    login();
                    break;
                case 2: 
                    sign_up();
                    break;
                case 3: 
                    cout << "Goodbye.. \n";
                    running_system = false;
                    break;
                default:
                    cout << "Error: invalid number... Try again with a number from 1 to 3\n";
                    break;
            }
        } else {            
            display_user_menu();

            int choice;
            cin >> choice;

            if (cin.fail()) {
            cin.clear(); 
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
            }


            switch(choice) {
                case 1:
                    login();
                    break;
                case 2: 
                    sign_up();
                    break;
                case 3: 
                    cout << "Goodbye.. \n";
                    running_system = false;
                    break;
                default:
                    cout << "Error: invalid number... Try again with a number from 1 to 3\n";
                    break;
            }
        } 
    }
}