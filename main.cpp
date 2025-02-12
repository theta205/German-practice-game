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
    char c, code;
    unordered_map<string,string> dict;
    cout << "Options: " << "\n";
    cout << "Nouns (N), " << "\n";
    cout << "Verbs (V), " << "\n";
    cout << "Adjectives (A), " << "\n";
    cout << "Adverbs (a), " << "\n";
    cout << "Pronouns (P), " << "\n";
    cout << "Conjunctions (C), " << "\n";
    cout << "Prepositions (p), " << "\n";
    cout << "Phrases (x), " << "\n";
    cout << "What would you like to practice \n (type the code seen in parenthesises): ";
    cin >> code;
    switch (code)
    {
    case 'N':
        filename = "./words/Nouns.txt";
        break;
    case 'V':
        filename = "./words/Verbs.txt";
        break;
    case 'A':
        filename = "./words/Adjectives.txt";
        break;
    case 'a':
        filename = "./words/Adverbs.txt";
        break;
    case 'C':
        filename = "./words/Conjunctions.txt";
        break;
    case 'p':
        filename = "./words/Prepositions.txt";
        break;
    case 'P':
        filename = "./words/Pronoun.txt";
        break;
    case 'x':
        filename = "./words/Phrases.txt";
        break;
    default:
        cout << endl;
        cout << "Invalid choice. Please choose a valid option." << endl;
        break;
    }
    cout << endl;
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

    vector<string> keys;
    for (const auto& entry : dict) {
        keys.push_back(entry.first);
    }

    string ans;
    int count = 0;
    vector <string> e;
    vector <string> g;
    random_device rd;
    mt19937 ra(rd());


    string correct;
    pair<string, string> pair;
    shuffle(keys.begin(), keys.end(), ra);
    for (auto key : keys){
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
        pair.first = key;
        pair.second = dict[key];
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