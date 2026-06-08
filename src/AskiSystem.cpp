#include <iostream>
#include "../include/AskiSystem.h"

using namespace std;


AskiSystem::AskiSystem() {

    current_user_id = -1;
    users = db_manager.load_users();
    questions = db_manager.load_questions();

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
    cin >> new_user.username;

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





void AskiSystem::print_coming_questions() {

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


void AskiSystem::answer_question() {

    int question_id;
    cout << "Please Enter Question ID or -1 to cancel: ";
    cin >> question_id;


    if(question_id == -1) {
        return;
    }

    if(question_id_to_index.count(question_id) == 0) {
        cout << "Error: Question ID doesn't Exists! \n";
        return;
    }

    int idx = question_id_to_index[question_id];

    Question &question = questions[idx];
    
    if(question.receiver_id == current_user_id) {
        string answer;
        cout << "Enter Your Answer: \n";
        cin.ignore();
        getline(cin, answer);

        question.answer_text = answer;

        cout << "Qusetion has been answered successfully! \n";

        db_manager.save_questions(questions);
    } else {
        cout << "Error: You can't answer a question that is not sent to you! \n";
    }
}


void AskiSystem::delete_question() {

    int question_id;

    cout << "Please Enter Question ID or -1 to cancel: ";
    cin >> question_id;


    if(question_id == -1) {
        return;
    }

    if(question_id_to_index.count(question_id) == 0) {
        cout << "Error: Question ID doesn't Exists! \n";
        return;
    }

    int idx = question_id_to_index[question_id];

    Question &question = questions[idx];

    if(question.receiver_id != current_user_id && question.sender_id != current_user_id) {
        cout << "Error: You are not authorized to delete this question!\n";
        return;
    }

    map<int, bool> ids_to_delete;
    ids_to_delete[question_id] = true;


    if (question_threads_map.count(question_id) > 0) {
        for (int thread_id : question_threads_map[question_id]) {
            ids_to_delete[thread_id] = true;
        }
    }


    vector<Question> new_questions;
    for (const auto& current_q : questions) {

        if (ids_to_delete.count(current_q.id) == 0) {
            new_questions.push_back(current_q);

        }
    }


    questions = new_questions;

    question_id_to_index.clear();
    question_threads_map.clear();

    for (int i = 0; i < questions.size(); i++) {
        question_id_to_index[questions[i].id] = i;
        if (questions[i].parent_question_id != -1) {
            question_threads_map[questions[i].parent_question_id].push_back(questions[i].id);
        }
    }

    db_manager.save_questions(questions);

    cout << "Question of ID: (" << question_id << ") deleted successfully!\n";
}

void AskiSystem::ask_question() {
    Question new_question;
    new_question.sender_id = current_user_id;
    new_question.answer_text = "";

    cout << "Enter Receiver User ID: ";
    cin >> new_question.receiver_id;

    //------- checking if receiver is exists by using binary search -------

    bool receiver_exists = false;
    int left = 0;
    int right = users.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (users[mid].id == new_question.receiver_id) {
            receiver_exists = true;
            
            if (new_question.receiver_id == current_user_id) {
                cout << "Error: You can't ask yourself a question!\n";
                return;
            }
            break;
        } else if (users[mid].id < new_question.receiver_id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!receiver_exists) {
        cout << "Error: Receiver User ID doesn't exist in the system!\n";
        return;
    }

    // ------------------------------------------------------------------------------------
    
    cout << "Is this a thread? (Enter parent Question ID, or -1 for new question): ";
    cin >> new_question.parent_question_id;

    if (new_question.parent_question_id != -1 && question_id_to_index.count(new_question.parent_question_id) == 0) {
        cout << "Error: Parent Question ID doesn't exist!\n";
        return;
    }

    
    cout << "Ask anonymously? (0 for NO, 1 for YES): ";
    cin >> new_question.is_anonymous;

    cout << "Enter your question text: \n";
    cin.ignore();
    getline(cin, new_question.text);


    if (questions.empty()) {
        new_question.id = 1;
    } else {
        new_question.id = questions.back().id + 1;
    }

    questions.push_back(new_question);
    question_id_to_index[new_question.id] = questions.size() - 1;


    if (new_question.parent_question_id != -1) {
        question_threads_map[new_question.parent_question_id].push_back(new_question.id);
    }
    
    db_manager.save_new_question(new_question);
    cout << "Question posted successfully! Your Question ID is: " << new_question.id << "\n";

}


void AskiSystem::list_system_users() {

    cout << "\n----- System Users -----\n";
    
    if (users.empty()) {
        cout << "No users registered in the system yet!\n";
        return;
    }

    for (const auto &user : users) {
        cout << "ID: " << user.id << "\t Name: " << user.name << "\n";
    }
}

void AskiSystem::show_feed() {
    cout << "\n----- Public Feed -----\n";
    bool has_feed = false;

    for (const auto &question : questions) {

        if (question.parent_question_id == -1 && question.answer_text != "") {
            has_feed = true;

            cout << "\nQuestion Id (" << question.id << ") ";
            if (!question.is_anonymous) {
                cout << "from user id(" << question.sender_id << ") ";
            } else {
                cout << "(!AQ) ";
            }
            cout << "to user id(" << question.receiver_id << ")\n";
            cout << "Question: " << question.text << "\n";
            cout << "Answer: " << question.answer_text << "\n";

            if (question_threads_map.count(question.id) > 0) {

                for (int thread_id : question_threads_map[question.id]) {

                    int idx = question_id_to_index[thread_id];
                    const Question &thread_q = questions[idx];

                    if (thread_q.answer_text != "") {
                        cout << "\tThread: Question Id (" << thread_q.id << ") ";
                        if (!thread_q.is_anonymous) {
                            cout << "from user id(" << thread_q.sender_id << ")\n";
                        } else {
                            cout << "(!AQ)\n";
                        }
                        cout << "\tQuestion: " << thread_q.text << "\n";
                        cout << "\tAnswer: " << thread_q.answer_text << "\n";
                    }
                }
            }
        }
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
                    print_coming_questions();
                    break;
                case 2: 
                    print_quesions_from_me();
                    break;
                case 3: 
                    answer_question();
                    break;
                case 4:
                    delete_question();
                    break;
                case 5: 
                    ask_question();
                    break;
                case 6: 
                    list_system_users();
                    break;
                case 7: 
                    show_feed();
                    break;
                case 8: 
                    cout << " Logout Successfully... \n";
                    log_out();
                    break;
                default:
                    cout << "Error: invalid number... Try again with a number from 1 to 8\n";
                    break;
            }
        } 
    }
}