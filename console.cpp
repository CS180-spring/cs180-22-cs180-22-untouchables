//terminal console
#include <iostream>
#include <map> //linking documents with databases
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//chatgpt generated sample document structure to store document in database
struct Document {
    string name;
    string content;
    string createdBy;
    time_t uploadedAt;
};

//simulating MongoDB's feature of changing database
struct DataBase {
    string name;
    vector <Document> storedDocuments; //documents linked with this DataBase
};

void messageDisplayer(){
    cout << "input command to interact with the system:" << endl;
    cout << "enter 'db' to display current database" << endl;
    cout << "enter 'db-all' to display all available database" << endl;
    cout << "enter 'add <name>' to add a new database" << endl;
    cout << "enter 'use <name>' to switch to another database" << endl;
    cout << "enter 'rm <name>' to remove an existing database" << endl;
    cout << "enter 'man' to revisit the command list" << endl;
    cout << "enter 'exit' to exit from the system" << endl;
}

//check if user input is within input word limitation
string check_num_word(string user_input, int limit){
    //stringstream code generated from chatgpt
    stringstream ss(user_input);
    string word;
    int word_count = 0;
    vector<string>list;

    while (ss >> word) {
        list.push_back(word);
        word_count++;
    }

    if (word_count != limit){
        return "false";
    }else{
        return list[limit-1];
    }
}

//simple function to get the List of DataBase names
vector<string> getNameList(vector<DataBase> existingDB){
    vector<string>NameList;
    for (int i = 0; i < existingDB.size(); ++i){
        NameList.push_back((existingDB.at(i)).name);
    }
    return NameList;
}

int main(){
    DataBase db = {"default"};
    Document doc1 = {"doc1", "content1", "random", time(nullptr)};

    //DataBase pointer, always points to the current database
    DataBase* currentDataBase = &db;

    //used to store existing Database entries
    vector<DataBase> existingDB;
    existingDB.push_back(db);

    string user_input;
    messageDisplayer();

    while(1){
        getline(cin,user_input);

        //output current database
        if (user_input == "db"){
            cout << "current database is: " << currentDataBase->name << endl;
        }

        //display all available databases
        if (user_input == "db-all"){
            if (existingDB.size() == 0){
                cout << "no available database.";
            } else {
                cout << "all available database include: ";
                for (int i = 0; i < existingDB.size(); ++i){
                    cout << (existingDB.at(i)).name << " ";
                }
            }
            cout << endl;
        }

        //add a new database, if the database does not already exist, name of database have to be one word
        if (user_input.substr(0, user_input.find(" ")) == "add"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "enter one word name for the new database" << endl;
            } else {
                string new_name = check_num_word(user_input, 2);
                vector<string> NameList = getNameList(existingDB);
                if (find(NameList.begin(), NameList.end(), new_name) != NameList.end()){
                    cout << new_name << " already exists" << endl;
                }else{
                    DataBase db_new = {new_name};
                    existingDB.push_back(db_new);
                    cout << "new database: " << new_name << " has been successfully added" << endl;
                }
            }       
        }

        //switch to another database, if the database does not already exist, ask if user want to create a new database
        if (user_input.substr(0, user_input.find(" ")) == "use"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "enter one word name for the target database" << endl;
            } else {
                string database_name = check_num_word(user_input, 2);
                vector<string> NameList = getNameList(existingDB);
                //chatgpt generated auto search, check if there is existing database matching input name
                auto db_iter = find_if(existingDB.begin(), existingDB.end(),
                       [&](const DataBase& db_search){ return db_search.name == database_name; });
                if (db_iter != existingDB.end()){ //chatgpt generated code to switch database by name
                    currentDataBase = &(*db_iter); //chatgpt generated code to switch database by name
                    cout << "current database has been switched to: " << database_name << endl;
                }else{
                    cout << "database does not exist, enter 'yes' to add, anything else to deny" << endl;
                    string new_user_input;
                    getline(cin, new_user_input);
                    if(new_user_input == "yes"){
                        DataBase db_new = {database_name};
                        existingDB.push_back(db_new);
                        cout << "new database: " << database_name << " has been successfully added" << endl;
                        currentDataBase = &db_new;
                        cout << "current database has been switched to: " << database_name << endl;
                    } else {
                        cout << "'use' operation cancelled" << endl;
                        messageDisplayer();
                    }
                }
            }       
        }

        //delete an existing database entry, cannot remove the default database or the currently using database
        if (user_input.substr(0, user_input.find(" ")) == "rm"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "enter one word name for the database to be removed" << endl;
            } else {
                string target_name = check_num_word(user_input, 2);
                vector<string> NameList = getNameList(existingDB);
                if (target_name == "default"){
                    cout << "command failed, cannot remove the default database" << endl;
                } else if (target_name == currentDataBase->name) {
                    cout << "command failed, cannot remove current database" << endl;
                } else if (find(NameList.begin(), NameList.end(), target_name) != NameList.end()){
                    //chatgpt generated code to remove an element from database vector by its name
                    existingDB.erase(std::remove_if(existingDB.begin(), existingDB.end(),
                    [&](const DataBase& db) { return db.name == target_name; }), existingDB.end());
                    cout << "removed database: " << target_name << endl;
                }else{
                    cout << "command failed, target database does not exist" << endl;
                }
            }       
        }

        if (user_input == "man"){
            messageDisplayer();
        }

        //exit the database system
        if (user_input == "exit"){
            exit(1);
            return 0;
        }
    }

    return 0;
}
