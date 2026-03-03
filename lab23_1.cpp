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

void importDataFromFile(string filename, vector<string> &name, vector<int> &score, vector<char> &grade){
    ifstream source(filename);
    string textline;
    
    while (getline(source, textline)){
        int namepos = textline.find(':');
        name.push_back(textline.substr(0, namepos));

        string scorepart = textline.substr(namepos + 1);
        int sum_score = 0;

        size_t pos = 0;
        for (int i = 0; i < 3; i++){
            size_t nextpos;
            int val = stoi(scorepart.substr(pos), &nextpos);
            sum_score += val;
            pos += nextpos;
        }
        score.push_back(sum_score);
        grade.push_back(score2grade(sum_score));
        
    }
}

void getCommand(string &command, string &key){
    string line;
    cout << "Please input your command: \n";
    getline(cin, line);
    size_t space_pos = line.find(' ');
    if (space_pos != string::npos){
        command = line.substr(0, space_pos);
        key = line.substr(space_pos + 1);
    }else{
        command = line;
        key = "";
    }
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < names.size(); i++){
        string uppername = toUpperStr(names[i]);
        if (uppername == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            found = true;
        }
    }
    if (!found){
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    } 
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < names.size(); i++){
        if (grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if (!found){
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
