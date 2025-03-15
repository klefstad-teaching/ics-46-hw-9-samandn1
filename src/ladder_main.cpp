#include "ladder.h"


int main() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    verify_word_ladder();
    return 0;
}