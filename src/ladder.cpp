#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

void error(string word1, string word2, string msg){
    cout << "ERROR FROM " << word1 << " to " << word2 << ": " << msg;
}


bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1 - len2) > d) return false;
    
    int i = 0
    int j = 0
    int count = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            count++;
            if (count > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; 
            j++;
        }
    }
    return count + (len1 - i) + (len2 - j) <= d;
}

bool is_adjacent(const string &word1, const string &word2) {
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word){
        error(begin_word, end_word, "Cannot start and end with the same word.");
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> level_visited;
        
        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();
            
            for (const string &word : word_list) {
                if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    
                    if (word == end_word) return new_ladder;
                    
                    ladder_queue.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }
        visited.insert(level_visited.begin(), level_visited.end());
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}


void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        for (const string &word : ladder) {
            cout << word << "->";
        }
        cout << endl;
    } else {
        error("printing", "ladder", "Empty ladder.");
    }
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    print_word_ladder(generate_word_ladder("cat", "dog", word_list));
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    print_word_ladder(generate_word_ladder("car", "cheat", word_list));
    my_assert(generate_word_ladder("car", "car", word_list).size() == 0);
}