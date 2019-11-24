#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"


Dictionary::Dictionary(string filename) {
// пытаемся открыть файл для чтения (код из скиплиста)
    std::ifstream fin(filename);    // opens the file
    if (!fin)
        throw std::invalid_argument("Couldn't open file " + filename);
    string str;
    while (fin >> str) {
        insert(str);
    }
}
