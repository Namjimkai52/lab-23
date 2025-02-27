#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file!" << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue; 
        
        string name = line.substr(0, colonPos);
        int score1, score2, score3;


        if (sscanf(line.c_str() + colonPos + 1, "%d %d %d", &score1, &score2, &score3) == 3) {
            int totalScore = score1 + score2 + score3;
            names.push_back(name);
            scores.push_back(totalScore);
            grades.push_back(score2grade(totalScore));
        }
    }
    file.close();
}


void getCommand(string &command, string &key) {
    cout << "Please input your command:\n";
    string input;
    getline(cin, input); 

    size_t spacePos = input.find(' '); 
    if (spacePos != string::npos) {
        command = input.substr(0, spacePos);  
        key = input.substr(spacePos + 1);     
    } else {
        command = input ;
      
        key = "";
        
    }

    command = toUpperStr(command);
    key = toUpperStr(key);
}


void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, const string &name) {
    bool found = false;
    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == name) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key) {
    if (key.length() != 1) {
        cout << "---------------------------------\n";
        cout << "Invalid command.\n";
        cout << "---------------------------------\n";
        return;
    }
    
    char grade = key[0];
    bool found = false;
    
    cout << "---------------------------------\n";
    for (size_t i = 0; i < grades.size(); i++) {
        if (grades[i] == grade) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    
    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}