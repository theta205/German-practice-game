#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>




using namespace std;

string answer(vector<string> &e, vector<string> &g, unordered_map<string,string> &dict);

int main() {
    string line, german, english, filename;
    bool dash;
    char c;
    unordered_map<string,string> dict;
    cout << "What is the file name: ";
    cin >> filename;
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    while (getline(inputFile, line)){
        dash = false;
        german.clear();
        english.clear();
        for (int i = 0; i < line.length(); i++){
            c = line[i];
            if (c == '-'){
                dash = true;
                i++;
                continue;
            }
            if (dash){
                english += c;
            }
            if (!dash){
                german += c;
            }
        }
        dict[english] = german;
    }
    string ans;

    int count = 0;
    vector <string> e;
    vector <string> g;
    random_device rd;
    mt19937 ra(rd());

    string correct;

    for (auto pair : dict){
        if (count == 5){
            shuffle(e.begin(), e.end(), ra);
            shuffle(g.begin(), g.end(), ra);
            cout << "English definitions: " << endl;
            cout << "-------------------------" << endl;
            for (auto x : e){
                cout << x << endl;
            }
            cout << endl;
            cout << "German definitions: " << endl;
            cout << "-------------------------" << endl;
            for (auto x : g){
                cout << x << endl;
            }
            correct = answer(e,g,dict);
            e.clear();
            g.clear();
            cout << endl;
            cout << "Your Answer: ";
            cin >> ans;
            cout << "Correct Answer is: " << correct << endl;
            count = 0;
        }
        e.push_back(pair.first);
        g.push_back(pair.second);
        count++;
        
    }
}
string answer(vector<string> &e, vector<string> &g, unordered_map<string,string> &dict){
    string ger, ans;
    for (auto x : e){
        ger = dict[x];
        for (int i = 0; i < g.size(); i++){
            if (ger == g[i]) {
                ans += to_string(i+1);
                break;
            }
        }
    }
    return ans;
}