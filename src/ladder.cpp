#include "ladder.h"
#include <fstream>
#include <iostream>
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << msg << ": " << word1 << "->" << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;
    int i = 0, j = 0, diff_count = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            ++diff_count;
            if (diff_count > d) return false;
            if (len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else { ++i, ++j; }
        }
        else { ++i, ++j; }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    cout << "Generating word ladder..." << endl;
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];
        cout << "Last word " << last_word << endl;
        for (const string& word : word_list) {
            cout << "word " << word << endl;
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                cout << "New word " << word << endl;
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
                break;
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in)
        throw runtime_error("Can't open input file");
    string word;
    while(in >> word)
        word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    string last_word = ladder[ladder.size() - 1];
    for (const string& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    if (word_list.empty()) {
        cout << "Word list is empty" << endl;
        return;
    }
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    // my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    // my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
