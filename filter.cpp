#include "filter.hpp"

// constructor with member initializer list
// to set reference to db so db reference does
// not have to be passed to filter class every time
Filter::Filter(Database& db): db{db}{workingClt = nullptr;}

// filter constructor function to call display
// function, set working collection, and get user input
void Filter::filterMain(){
 
    string userInput = "";
    string selectedClt = "";

    displayMenu();
    
    // Stay in filter menu until user types exit
    while(userInput != "exit"){

        // check if working collection is selected
        if(workingClt == nullptr){
            userInput = selectCollection();
        }

        // check if user input from selectCollection() is exit 
        if(userInput == "exit"){
            break;
        }

        // get user for filter options
        getline(cin,userInput);
        
        // call filter functions based off of user input
        if(userInput == "filter" || userInput == to_string(1)){
            filterDisplay();

        }
        else if(userInput == "query" || userInput == to_string(2)){
            query();
        }
        else if(userInput == "sort" || userInput == to_string(3)){

        }
        else if(userInput == "sort"){

        }
        else if(userInput == "collections"){
            db.dbAll();
            cout << ">>> ";
        }
        else if(userInput == "mainDB"){
            workingClt = db.rtnMainDB();
            displayMenu();
        }
        else if(userInput == "change"){
            userInput = selectCollection();
        }
        else if(userInput == "menu"){
            displayMenu();
        }
    }

    // set working collection to
    // nullptr when function exits
    workingClt = nullptr;
};

// simple function to display filter menu
void Filter::displayMenu(){
    
    int width = 5;
    system("clear");

        cout << "********************************************************************************************************\n";
        cout << "*                                      Movie Database                                                  *\n";
        cout << "********************************************************************************************************\n";
        cout << "*                                                                                                      *\n";
        cout << left << setw(width) << "*" << left << setw(40) << "1.filter" << left << setw(50) << "filter menu" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "2.query" << left << setw(50) << "query menu" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "3.sort" << left << setw(50) << "sort menu" << right << setw(9) << "*" << endl; //added this to import .csv/JSON files into specified collection
        cout << left << setw(width) << "*" << left << setw(40) << "4.collections" << left << setw(50) << "display available collections" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.mainDB" << left << setw(50) << "select main database" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.change" << left << setw(50) << "change collection" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "exit" << left << setw(50) << "return to database menu" << right << setw(9) << "*" << endl;
        cout << "*                                                                                                      *" << endl;
        cout << "********************************************************************************************************" << endl;
        cout << "Selected collection: ";
        // conditional statement to display
        // working collection if selected
        if(workingClt != nullptr){
            cout << workingClt->name << endl;
            cout << "Select option\n\n";
            cout << ">>> ";

        }    
}

// function gets working collection from
// user 
string Filter::selectCollection(){

    //string tmpName = cltName;
    string userInput = "";

    cout << "\nInput collection to work on:\n\n";
    cout << ">>> ";

    getline(cin,userInput);

    // continue to get user input until working
    // collection is selected or user exit
    while(!db.collectionExists(userInput)){ 
        
        // check if user wants 
        // to work on mainDB
        if(userInput == "mainDB"){
            workingClt = db.rtnMainDB();
            displayMenu();
            return userInput;
        }
        // check if user wants to 
        // display available collections
        else if(userInput == "collections"){
            db.dbAll();
            cout << ">>> ";

            getline(cin,userInput); 
        }
        // need to check if user wants to exit menu
        else if(userInput == "exit"){
            return userInput;
        }
        // collection does not exist prompt 
        // user to enter a working collection
        else{
            cout << "Collection does not exist\n";
            cout << "input collection to work on: \n\n";

            cout << ">>> ";
            
            getline(cin,userInput); 
        }
    }
    // set working collection
    if(db.collectionExists(userInput)){
    
        workingClt = db.getCollectionByName(userInput);

        displayMenu();
        return userInput;
    }
    // need to return something but may not be used
    return userInput;
}

//string to be searched, string you are searching for
bool Filter::isSubstring(const std::string& str1, const std::string& str2) {
    size_t found = str1.find(str2);
    return (found != std::string::npos);
}


//HUGE DEPENDENCY, THE NEW COLLECTION MADE HERE IS MADE OF POINTERS, WHICH MEANS IF YOU DELETE STUFF FROM THE ORIGINAL COLLECTION AND TRY TO VIEW THE QUERIED COLLECTION,
//A SEGFAULT OCCURS, DON'T KNOW HOW TO FIX THIS PLS HELP, TODO
void Filter::query() {
    string user_input;
    string newName;
    cout << "What phrase would you like to search for?" << endl;
    getline(cin, user_input);
    cout << "What would you like the new queried collection to be called?" << endl;
    getline(cin, newName);
    vector <Movie_Document*> pings;
    //quite literally checks if the phrase is in any of the important string fields, if it is then movie doc pointer gets added to new collection
    for (int i = 0; i < workingClt->movieDocs.size(); i++) {
        if (isSubstring(workingClt->movieDocs[i]->Director, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->overview, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->series_title, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->genre, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star1, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star2, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star3, user_input))
            pings.push_back(workingClt->movieDocs[i]);
        else if (isSubstring(workingClt->movieDocs[i]->Star4, user_input))
            pings.push_back(workingClt->movieDocs[i]);
    }
    if (pings.size() > 0) {
        db.addFltCollection(newName, pings);
    }
    else {
        cout << "No matches found, queried collection could not be created" << endl;
    }
}

// fuction displays filter menu and gets user input
// and will call specific function specific to user input
void Filter::filterDisplay(){
    
    int width = 5;
    string userInput = "";
    
    while(userInput != "exit"){
        system("clear");

        cout << "********************************************************************************************************\n";
        cout << "*                                            Filter Menu                                               *\n";
        cout << "********************************************************************************************************\n";
        cout << "*                                                                                                      *\n";
        cout << left << setw(width) << "*" << left << setw(40) << "1.title" << left << setw(50) << "by title" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "2.release year" << left << setw(50) << "by release year" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "3.rated" << left << setw(50) << "by rating" << right << setw(9) << "*" << endl; //added this to import .csv/JSON files into specified collection
        cout << left << setw(width) << "*" << left << setw(40) << "4.runtime" << left << setw(50) << "by runtime" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "5.genre" << left << setw(50) << "by genre" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "6.IMDB rating" << left << setw(50) << "by IMDB rating" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "7.meta score" << left << setw(50) << "by meta score" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "8.director" << left << setw(50) << "by director" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "9.starring" << left << setw(50) << "by actor/actress" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "10.number of votes" << left << setw(50) << "by number of votes" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "11.Gross" << left << setw(50) << "by gross earnings" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "12.multiple filters" << left << setw(50) << "apply multiple filters" << right << setw(9) << "*" << endl;
        cout << left << setw(width) << "*" << left << setw(40) << "exit" << left << setw(50) << "exit filter menu" << right << setw(9) << "*" << endl;
        cout << "*                                                                                                      *" << endl;
        cout << "********************************************************************************************************" << endl;
        cout << "Selected collection: ";
        if(workingClt != nullptr){cout << workingClt->name << endl;}
        cout << endl;
        cout << ">>> ";

        getline(cin,userInput);
        string counter;
        if(userInput == "1" || userInput == "title"){            
            featureFilter("title");
        }
        else if(userInput == "2" || userInput == "release year"){
            
            cout << "0 for shortest to longest" << endl;
            cout << "1 for longest to shortest" << endl;
            getline(cin, userInput);
            counter = userInput;
        }
        else if(userInput == "3" || userInput == "rated"){
            featureFilter("rated");                    
        }
        else if(userInput == "4" || userInput == "runtime"){
            cout << "0 for shortest to longest" << endl;
            cout << "1 for longest to shortest" << endl;
            getline(cin, userInput);
            counter = userInput;
        }
        else if(userInput == "5" || userInput == "genre"){
            featureFilter("genre");
        }
        else if(userInput == "6" || userInput == "IMDB rating"){
            cout << "0 for shortest to longest" << endl;
            cout << "1 for longest to shortest" << endl;
            getline(cin, userInput);
            counter = userInput;
        }
        else if(userInput == "7" || userInput == "meta score"){
            cout << "0 for shortest to longest" << endl;
            cout << "1 for longest to shortest" << endl;
            getline(cin, userInput);
            counter = userInput;
        }
        else if(userInput == "8" || userInput == "director"){
            featureFilter("director");
        }
        else if(userInput == "9" || userInput == "starring"){
            featureFilter("star");
        }
        else if(userInput == "10" || userInput == "number of votes"){
            cout << "0 for shortest to longest" << endl;
            cout << "1 for longest to shortest" << endl;
            getline(cin, userInput);
            counter = userInput;
        }
        else if(userInput == "11" || userInput == "gross revenue"){
            cout << "0 for shortest to longest" << endl;
            cout << "1 for longest to shortest" << endl;
            getline(cin, userInput);
            counter = userInput;
        }
        else if(userInput == "12" || userInput == "multiple filters"){
            cout << "Enter filters: ";
            getline(cin, userInput);


        }
        else if(userInput == "exit"){
            displayMenu();

        }
       else{
            filterDisplay();
       }
    }
}


void multipleFilters(vector<string> fltNames){


}


void Filter::titleFilter(string titleName){

    vector<Movie_Document*> filteredMov;
    for(auto i : workingClt->movieDocs){
        if(i->series_title == titleName){
            filteredData.push_back(i);
        }
    }

    for(auto i : filteredData){

        cout << "poster-link: " << i->poster_Link << endl;
        cout << "series-title: " << i->series_title << endl;
        cout << "released-year: " << i->released_year << endl;
        cout << "certificate: " << i->certificate << endl;
        cout << "runtime: " << i->runtime << endl;
        cout << "genre: " << i->genre<< endl;
        cout << "IMDB-rating: " << i->IMDB_rating << endl;
        cout << "overview: " << i->overview << endl;
        cout << "meta-score: " << i->meta_score << endl;
        cout << "director: " << i->Director << endl;
        cout << "Stars: " << i->Star1 << ", " << i->Star2 << ", " << i->Star3 << ", " << i->Star4 << endl;
        cout << "number-votes: " << i->numVotes << endl;
        cout << "gross: " << i->gross << endl << endl;
    }

    cin.get();

}

// Filters movies by feature and pushes to temp vector
// user has option to display, create new collection, or export
void Filter::featureFilter(string fltFeature){

    string userInput;

    vector<Movie_Document*> copyVec = copyMovieDocs(workingClt->name);
    vector<Movie_Document*> sortedVec;
    //Series_Title,Rated,Genre,Director,Star

    if(fltFeature == "title"){
        cout << "Enter title: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->series_title.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "rated"){
        cout << "Movie ratings are: 16, A, Approved, G, GP, Passed, PG, PG-13, R, TV-14, TV-MA, TV-PG, U, U/A, UA, Unrated\n";
        cout << "Enter rating: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->certificate.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "genre"){
        cout << "Enter genre: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->genre.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "director"){
        cout << "Enter director: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if(i->Director.find(userInput) != string::npos){
                sortedVec.push_back(i);
            }
        }
    }
    else if(fltFeature == "star"){
        cout << "Enter star name: \n\n";
        cout << ">>> ";

        getline(cin, userInput);

        for(auto i : copyVec){
            if((i->Star1.find(userInput) != string::npos) || (i->Star2.find(userInput) != string::npos) 
                || (i->Star3.find(userInput) != string::npos) || (i->Star4.find(userInput) != string::npos)){
                sortedVec.push_back(i);
            }
        }
    }

    filterResults(sortedVec);
}

// Menu to implement displaying, creating new 
// collection, or exporting from filter/sorted data
void Filter::filterResults(vector<Movie_Document*> fsData){

    string userInput = "";

    if(!fsData.empty()){
        cout << "Found " << fsData.size() << " result(s)\n";
        cout << "1.Display\n";
        cout << "2.Create new collection\n";
        cout << "3.Export movie data\n\n";
        cout << ">>> ";

        getline(cin, userInput);

        if(userInput == "1" || userInput == "Display"){

            printData(fsData);
        }
        else if(userInput == "2" || userInput == "create"){
            cout << "name of new collection: ";
            getline(cin,userInput);

            db.addFltCollection(userInput, fsData);
        }
        else if(userInput == "3" || userInput == "export"){
            cout << "name of file: \n\n";
            cout << ">>> ";
            getline(cin, userInput);

            db.fltExportCSV(fsData, userInput);
            cout << "hit enter to continue\n";
            cin.get();
            //need to change up export to take new parameters
        }
    }
    else if(fsData.empty()){
        cout << "Found 0 results\n";
    }
}

// Simple function to print movie data in 5 document increments
void Filter::printData(vector<Movie_Document*> movieData){

    string userInput = "";

    for(int i = 0; i < movieData.size(); i++){
        cout << "series-title: " << movieData[i]->series_title << endl;
        cout << "released-year: " << movieData[i]->released_year << endl;
        cout << "certificate: " << movieData[i]->certificate << endl;
        cout << "runtime: " << movieData[i]->runtime << endl;
        cout << "genre: " << movieData[i]->genre<< endl;
        cout << "IMDB-rating: " << movieData[i]->IMDB_rating << endl;
        cout << "overview: " << movieData[i]->overview << endl;
        cout << "meta-score: " << movieData[i]->meta_score << endl;
        cout << "director: " << movieData[i]->Director << endl;
        cout << "Stars: " << movieData[i]->Star1 << ", " << movieData[i]->Star2 << ", " << movieData[i]->Star3 << ", " << movieData[i]->Star4 << endl;
        cout << "number-votes: " << movieData[i]->numVotes << endl;
        cout << "gross: " << movieData[i]->gross << endl << endl;

        if((i % 4) == 0 && (i != 0)){
            cout << "hit enter to display next 5 results\n";
            cout << "exit to exit any time\n";
            getline(cin, userInput);
            if(userInput == "exit"){
                break;
            }
        }

    }
        
}


// Helper function for sorting
bool alphaSortHelper( Movie_Document* x, Movie_Document* y){

    return x->series_title < y->series_title;
}

vector<Movie_Document*> Filter::copyMovieDocs(string cltName){
    
    // use db function to get collection by name
    // pointer to collection is returned
    collection* clt = db.getCollectionByName("default");

    // set variable to size of vector to be copied
    int size = clt->movieDocs.size();

    // vector to hold copied movie data
    vector<Movie_Document*> copyVec(size);

    // copy takes beginning iterator, end iterator, and beginning iterator of new vector to copy to
    copy(clt->movieDocs.begin(),clt->movieDocs.begin() + size, copyVec.begin());

    return copyVec;

}

// sorts by series title right now 
void Filter::alphabetSort(string cltName, string feature){

    // gets movie data copied over
    vector<Movie_Document*> copyVec = copyMovieDocs("default"); // can change this to a passed string variable passed to alphasort()
    
    // sorts with a helper function
    sort(copyVec.begin(), copyVec.end(), alphaSortHelper);

    // add new collection
    // the parameters can be changed within your class so you can let user
    // pick name of new collection for example.
    db.addFltCollection("alphaSort", copyVec);

}

void Filter::numberSort(){
}

void Filter::output(){
}

/*
void Filter::titleView(){
cout << "A = View all" << endl;
cout << "T = Just titles" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
titleView();
}
}


void Filter::titleSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
cout << "Would you like to view all information or just the title?" << endl;
titleView();
}
else if(userinput == "1"){
alphabetSort();
cout << "Would you like to view all information or just the title?" << endl;
titleView();
}
else if (userinput == "2"){
}
else{
cout << "Please give a valid input:" << endl;
titleSort();
}
}

void Filter::titleFilter(){
cout << "Input:" << endl;
cout << "0 for A-Z" << endl;
cout << "1 for Z-A" << endl;
cout << "2 for no alphabetization" << endl;
titleSort();
}

void Filter::yearView(){
cout << "A = View all" << endl;
cout << "T = Just titles and years" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
yearView();
}
}


void yearSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
yearView();
}
else if(userinput == "1"){
numberSort();
yearView();
}
else if (userinput == "2"){
yearView();
}
else{
cout << "Please give a valid input:" << endl;
yearSort();
}
}

void yearFilter(){
cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
yearSort();
}

void certificateView(){
cout << "A = View all" << endl;
cout << "T = Just titles and certificates" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
certificateView();
}
}


void certificateSort(){
getline(cin, userinput);
if (userinput == "0"){
certificateView();
}
else if(userinput == "1"){
certificateView();
}
else if (userinput == "2"){
certificateView();
}
else if(userinput == "3"){
certificateView();
}
else if(userinput == "4"){
certificateView();
}
else if (userinput == "5"){
certificateView();
}
else if(userinput == "6"){
certificateView();
}
else if(userinput == "7"){
certificateView();
}
else if (userinput == "8"){
certificateView();
}
else if(userinput == "9"){
certificateView();
}
else if(userinput == "a"){
certificateView();
}
else if (userinput == "b"){
certificateView();
}
else{
cout << "Please give a valid input:" << endl;
certificateView();
}
}

void certificateFilter(){
cout << "Input:" << endl;
cout << "0 for A film certification" << endl;
cout << "1 for U film certification" << endl;
cout << "2 for G film certification" << endl;
cout << "3 for R film certification" << endl;
cout << "4 for PG film certification" << endl;
cout << "5 for PG-13 film certification" << endl;
cout << "6 for UA and U/A film certification" << endl;
cout << "7 for TV-14 certification" << endl;
cout << "8 for TV-PG certification" << endl;
cout << "9 for TV-MA certification" << endl;
cout << "a for Passed certification" << endl;
cout << "b for Approved certification" << endl;
certificateSort();
}

void runtimeView(){
cout << "A = View all" << endl;
cout << "T = Just titles and runtimes" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
runtimeView();
}
}


void runtimeSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
runtimeView();
}
else if(userinput == "1"){
numberSort();
runtimeView();
}
else if (userinput == "2"){
runtimeView();
}
else{
cout << "Please give a valid input:" << endl;
runtimeView();
}
}

void runtimeFilter(){
cout << "Input:" << endl;
cout << "0 for shortest to longest" << endl;
cout << "1 for longest to shortest" << endl;
cout << "2 for no numerical sort" << endl;
runtimeSort();
}

void genreView(){
cout << "A = View all" << endl;
cout << "T = Just titles and genres" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
genreView();
}
}

void genreSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
genreView();
}
else if(userinput == "1"){
alphabetSort();
genreView();
}
else if (userinput == "2"){
genreView();
}
else{
cout << "Please give a valid input:" << endl;
genreSort();
}
}

void genreFilter(){
cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
genreSort();
}

void imdbRatingView(){
cout << "A = View all" << endl;
cout << "T = Just titles and IMDB ratings" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
imdbRatingView();
}
}


void imdbRatingSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
imdbRatingView();
}
else if(userinput == "1"){
numberSort();
imdbRatingView();
}
else if (userinput == "2"){
imdbRatingView();
}
else{
cout << "Please give a valid input:" << endl;
imdbRatingSort();
}
}

void imdbRatingFilter(){
cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
imdbRatingSort();
}

void overviewView(){
cout << "A = View all" << endl;
cout << "T = Just titles and overviews" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
overviewView();
}
}

void overviewSort(){ //Have to do query
overviewView();
}

void overviewFilter(){
cout << "Would you like to filter overviews that include all keywords or at least one keyword?" << endl;
cout << "a for all keywords" << endl;
cout << "o for at least one keyword" << endl;
getline(cin, userinput);
cout << "Input all desired keywords, each separated by a space and when finished press enter" << endl;
getline(cin, userinput);
overviewSort();
}

void metaScoreView(){
cout << "A = View all" << endl;
cout << "T = Just titles and meta scores" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
metaScoreView();
}
}

void metaScoreSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
metaScoreView();
}
else if(userinput == "1"){
numberSort();
metaScoreView();
}
else if (userinput == "2"){
metaScoreView();
}
else{
cout << "Please give a valid input:" << endl;
metaScoreSort();
}
}

void metaScoreFilter(){
cout << "Input:" << endl;
cout << "0 for lowest to highest" << endl;
cout << "1 for highest to lowest" << endl;
cout << "2 for no numerical sort" << endl;
metaScoreSort();
}

void directorView(){
cout << "A = View all" << endl;
cout << "T = Just titles and directors" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
directorView();
}
}


void directorSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
directorView();
}
else if(userinput == "1"){
alphabetSort();
directorView();
}
else if (userinput == "2"){
directorView();
}cout << "Input:" << endl;
cout << "0 for oldest to newest" << endl;
cout << "1 for newest to oldest" << endl;
cout << "2 for no numerical sort" << endl;
yearSort();
}
}
}

void directorFilter(){
cout << "Input:" << endl;
cout << "0 for A-Z" << endl;
cout << "1 for Z-A" << endl;
cout << "2 for no alphabetization" << endl;
directorSort();
}

void starsView(){
cout << "A = View all" << endl;
cout << "T = Just titles and stars" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
starsView();
}
}


void starsSort(){
getline(cin, userinput);
if (userinput == "0"){
alphabetSort();
starsView();
}
else if(userinput == "1"){
alphabetSort();
starsView();
}
else if (userinput == "2"){
starsView();
}
else{
cout << "Please give a valid input:" << endl;
starsSort();
}
}

void starsFilter(){
cout << "Input:" << endl;
cout << "0 for A-Z" << endl;
cout << "1 for Z-A" << endl;
cout << "2 for no alphabetization" << endl;
starsSort();
}

void noOfVotesView(){
cout << "A = View all" << endl;
cout << "T = Just titles and number of votes" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
noOfVotesView();
}
}


void noOfVotesSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
noOfVotesView();
}
else if(userinput == "1"){
numberSort();
noOfVotesView();
}
else if (userinput == "2"){
noOfVotesView();
}
else{
cout << "Please give a valid input:" << endl;
noOfVotesSort();
}
}

void noOfVotesFilter(){
cout << "Input:" << endl;
cout << "0 for lowest to highest" << endl;
cout << "1 for highest to lowest" << endl;
cout << "2 for no numerical sort" << endl;
noOfVotesSort();
}

void grossRevenueView(){
cout << "A = View all" << endl;
cout << "T = Just titles and gross revenues" << endl;
getline(cin, userinput);
if (userinput == "A"){
output();
}
else if(userinput == "T"){

}
else{
cout << "Please give a valid input." << endl;
grossRevenueView();
}
}


void grossRevenueSort(){
getline(cin, userinput);
if (userinput == "0"){
numberSort();
grossRevenueView();
}
else if(userinput == "1"){
numberSort();
grossRevenueView();
}
else if (userinput == "2"){
grossRevenueView();
}
else{
cout << "Please give a valid input:" << endl;
grossRevenueSort();
}
}

void grossRevenueFilter(){
cout << "Input:" << endl;
cout << "0 for lowest to highest" << endl;
cout << "1 for highest to lowest" << endl;
cout << "2 for no numerical sort" << endl;
grossRevenueSort();
}

void filter(){
cout << "Filter by inputting the respective character(s):" << endl;
cout << "T = Series_Title" << endl;
cout << "Y = Released_Year" << endl;
cout << "C = Certificate" << endl;
cout << "R = Runtime" << endl;
cout << "G = Genre" << endl;
cout << "I = IMDB_Rating" << endl;
cout << "O = Overview" << endl;
cout << "M = Meta_score" << endl;
cout << "D = Director" << endl;
cout << "S = Stars" << endl;
cout << "N = No_of_Votes" << endl;
cout << "GR = Gross Revenue" << endl;
cout << "B to go back" << endl;
string userinput;
getline(cin, userinput);
if(userinput == "T"){
titleFilter();
}
else if(userinput == "Y"){
yearFilter();
}
else if(userinput == "C"){
certificateFilter();
}
else if(userinput == "R"){
runtimeFilter();
}
else if(userinput == "G"){
genreFilter();
}
else if(userinput == "I"){
imdbRatingFilter();
}
else if(userinput == "O"){
overviewFilter();
}
else if(userinput == "M"){
metaScoreFilter();
}
else if(userinput == "D"){
directorFilter();
}
else if(userinput == "S"){
starsFilter();
}
else if(userinput == "N"){
noOfVotesFilter();
}
else if(userinput == "GR"){
grossRevenueFilter();
}
else if(userinput == "B"){
messageDisplayer();
}
else{
cout << "Please give a valid input" << endl;
filter();
}
}
*/
