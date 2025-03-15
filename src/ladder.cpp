#include "ladder.h"
void error(string word1, string word2, string msg){
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
};

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){ //helper function
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;

    int index1 = 0; 
    int index2 = 0;
    int changes = 0;
    while(index1 < len1 && index2 < len2){
        if(str1[index1] != str2[index2]){
            if (++changes > d) return false;
            if (len1 > len2) ++index1;
            else if (len1 < len2) ++index2;
            else {
                ++index1; 
                ++index2;
            }
        } else {
            ++index1; ++index2;
        }
    }
    return changes + (len1 - index1) + (len2 - index2) <= d;
};

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
};

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!(ladder_queue.empty())){
        vector<string> ladder = ladder_queue.front(); // returns a set
        ladder_queue.pop();
        string last_word = ladder.back(); // last word of the set

        for (const string& word: word_list){
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()){
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    visited.insert(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
};

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
};

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); i++) {
            cout << ladder[i] << " ";
        }
        cout << endl;
    }
};
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder1 = generate_word_ladder("cat", "dog", word_list);
    my_assert(ladder1.size() == 4);
    print_word_ladder(ladder1);

    vector<string> ladder2 = generate_word_ladder("marty", "curls", word_list);
    my_assert(ladder2.size() == 6);
    print_word_ladder(ladder2);

    vector<string> ladder3 = generate_word_ladder("code", "data", word_list);
    my_assert(ladder3.size() == 6);
    print_word_ladder(ladder3);

    vector<string> ladder4 = generate_word_ladder("work", "play", word_list);
    my_assert(ladder4.size() == 6);
    print_word_ladder(ladder4);

    vector<string> ladder5 = generate_word_ladder("sleep", "awake", word_list);
    my_assert(ladder5.size() == 8);
    print_word_ladder(ladder5);

    vector<string> ladder6 = generate_word_ladder("car", "cheat", word_list);
    my_assert(ladder6.size() == 4);
    print_word_ladder(ladder6);
};
