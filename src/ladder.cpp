#include "ladder.h"
#include <fstream>
#include <iostream>
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << msg << ": " << word1 << "->" << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) { // returns true if edit distance sis less than or equal to 1
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;
    int i = 0, j = 0, diff_count = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff_count > d) return false;
            if (len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else { ++i, ++j; }
        }
        else { ++i, ++j; } // characters match, nexttt
    }
    return diff_count + abs(len1 - i) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) { // returns a vector of the paths of words 
    cout << "Generating word ladder..." << endl;
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) { // if a word from the qord list is adjacent (only 1 character different) to the last word in the ladder 
                if (visited.find(word) == visited.end()) { // if word not yet visited (part of ladder)
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    visited.insert(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
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
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
