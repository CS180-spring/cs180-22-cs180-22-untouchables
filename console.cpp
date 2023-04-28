//terminal console
#include <iostream>
#include <map> //linking documents with databases
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "console.h"

using namespace std;

//chatgpt generated sample document structure to store document in database
struct Movie_Document {
    string series_title;
    int released_year;
    int runtime; //in minutes
    string genre;
    double IMDB_rating; //specific for IMDB movie data, scale 10
    string overview;
    int meta_score; //scale 100
    string Director;
    string Star; //star 1 only
    //vector <string> stars; //keep all stars
};

//simulating MongoDB's feature of changing database
struct DataBase {
    string name;
    vector <Movie_Document> storedDocuments; //documents linked with this DataBase
};

//fyi, I think DataBase should've been Database and no capitalized values in Movie_Document but oh well
void addDocumentManually(DataBase& current) {
    Movie_Document addMe;
    string user_input;
    cout << "Input the series title: " << endl;
    getline(cin,addMe.series_title);
    cout << "Input the release year: " << endl;
    cin >> addMe.released_year;
    cout << "Input the runtime (int): " << endl;
    cin >> addMe.runtime;
    cout << "Input the genre: " << endl;
    cin.ignore();
    getline(cin, addMe.genre);
    cout << "Input the IMDB_rating (double): " << endl;
    cin >> addMe.IMDB_rating;
    cout << "Input the description: " << endl;
    cin.ignore();
    getline(cin, addMe.overview);
    cout << "Input the meta_score: " << endl;
    cin >> addMe.meta_score;
    cout << "Input the Director's name: " << endl;
    cin.ignore();
    getline(cin, addMe.Director);;
    cout << "Input the star: " << endl;
    cin >> addMe.Star;
    current.storedDocuments.push_back(addMe);
    cout << "Movie added successfully" << endl;
}

/*
//helper function that searches based on name, UNFINISHED
Movie_Document findMovie(DataBase& current, string name) {
    for (int i = 0; i < current.storedDocuments.size(); i++) {
        if (name == current.storedDocuments[i].series_title)
            return current.storedDocuments[i];
    }
    //return NULL; //needs to return something if it can't find it, NULL doesn't have a proper converter
}
*/

void deleteDocumentManually(DataBase& current) {
    cout << "input the name of the movie to be removed" << endl;
    string user_input;
    getline(cin, user_input);
    //if the Document exists in the storedDocument array
    for (auto i = current.storedDocuments.begin(); i != current.storedDocuments.end(); ++i) {
        if (i->series_title == user_input) {
            current.storedDocuments.erase(i);
            cout << "Document " << user_input << " has been successfully deleted." << endl;
            return;
        }
    }
    //if the Document does not exist
    cout << "Document does not exist in the current Database" << endl;
}

void printAllTables(DataBase& current) {
    for (int i = 0; i < current.storedDocuments.size(); i++) {
        cout << "Movie title: " << current.storedDocuments.at(i).series_title << endl;
        cout << "Description: " << current.storedDocuments.at(i).overview << endl;
        cout << "Director: " << current.storedDocuments.at(i).Director << endl; 
        cout << "Release Year: " << current.storedDocuments.at(i).released_year << endl;
        cout << "Genre: " << current.storedDocuments.at(i).genre << endl;
        cout << "Runtime: " << current.storedDocuments.at(i).runtime << endl;
        cout << "IMBD Rating: " << current.storedDocuments.at(i).IMDB_rating << endl;
        cout << "Meta Score: " << current.storedDocuments.at(i).meta_score << endl;
        cout << "Star rating: " << current.storedDocuments.at(i).Star << endl << endl;
    }
}

void messageDisplayer() {
    cout << "input command to interact with the system:" << endl;
    cout << "enter 'db' to display current database" << endl;
    cout << "enter 'element <index>' to display an element of the current database" << endl;
    cout << "enter 'db-all' to display all available database" << endl;
    cout << "enter 'add <name>' to add a new database" << endl;
    cout << "enter 'use <name>' to switch to another database" << endl;
    cout << "enter 'rm <name>' to remove an existing database" << endl;
    cout << "enter 'man' to revisit the command list" << endl;
    cout << "enter 'addm' to enter a movie in the current database" << endl;
    cout << "enter 'rmm' to enter a movie in the current database" << endl;
    cout << "enter 'view' to show all tables in the current database" << endl; //this could be combined with 'db', I'm keeping it separate for now 
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
    for (unsigned int i = 0; i < existingDB.size(); ++i){
        NameList.push_back((existingDB.at(i)).name);
    }
    return NameList;
}


void displayMovieDocument(const DataBase& database, unsigned int index) {
    if (index < 0 || index >= database.storedDocuments.size()) {
        cout << "Invalid index\n";
        return;
    }
    const Movie_Document& doc = database.storedDocuments[index];
    cout << "Series Title: " << doc.series_title << "\n";
    cout << "Released Year: " << doc.released_year << "\n";
    cout << "Runtime (in minutes): " << doc.runtime << "\n";
    cout << "Genre: " << doc.genre << "\n";
    cout << "IMDB Rating: " << doc.IMDB_rating << "\n";
    cout << "Overview: " << doc.overview << "\n";
    cout << "Meta Score: " << doc.meta_score << "\n";
    cout << "Director: " << doc.Director << "\n";
    cout << "Star: " << doc.Star << "\n";
}

int main(){
    DataBase db = {"default"};
    //Document doc1 = {"doc1", "content1", "random", time(nullptr)};

    //DataBase pointer, always points to the current database
    DataBase* currentDataBase;

    //used to store existing Database entries
    vector<DataBase> existingDB;
    existingDB.push_back(db);
    currentDataBase = &existingDB.at(existingDB.size()-1);
    
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
                for (unsigned int i = 0; i < existingDB.size(); ++i){
                    cout << (existingDB.at(i)).name << " ";
                }
            }
            cout << endl;
        }

        if (user_input.substr(0, user_input.find(" ")) == "addm") {
            addDocumentManually(*currentDataBase);
        }
        
        if (user_input.substr(0, user_input.find(" ")) == "rmm") {
            deleteDocumentManually(*currentDataBase);
        }
        
         if (user_input.substr(0, user_input.find(" ")) == "view") {
            printAllTables(*currentDataBase);
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

        if (user_input.substr(0, user_input.find(" ")) == "element"){
            if (check_num_word(user_input, 2) == "false"){
                cout << "only enter one element index to print" << endl;
            } else {
                DataBase currDB = *currentDataBase;
                int pos = user_input.find(' ');
                string numStr = user_input.substr(pos + 1);
                int index = stoi(numStr);
                displayMovieDocument(currDB, index);
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
                        currentDataBase = &existingDB.at(existingDB.size()-1);
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
                    //chatgpt generated code to remove an element from database vector by its name
                    currentDataBase = &existingDB.at(0);
                    existingDB.erase(std::remove_if(existingDB.begin(), existingDB.end(),
                    [&](const DataBase& db) { return db.name == target_name; }), existingDB.end());
                    cout << "removed current database and switched to default" << endl;
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
