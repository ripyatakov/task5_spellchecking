#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);
//my funcs
string transposing(const string& s, const int pos);
string removal(const string& s, const int pos);
string replacement(const string& s, const int pos, const char c);
string insertAfter(const string& s, const int pos, const char c);



// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char* argv[]) {
	
	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);
    
	checkSpelling(inf, d);

	inf.close();

	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict) {

	int line_number = 0;

	while (in) 
    {
		line_number++;
		set<string> totest;
		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;
		
		string word;
		while (ss >> word) 
        {
		    totest.clear();
            word = stripPunct(word);
		    string wordBefore = word;
		    string answ = "";
            lower(word);

            if (!dict.search(word)){
                for (int i = 0; i < word.length() - 1; ++i) {
                    if (dict.search(transposing(word,i)))
                        totest.insert( transposing(word,i) );
                }
                for (int i = 0; i < word.length() ; ++i) {
                    if (dict.search(removal(word,i)))
                        totest.insert(removal(word,i));
                }
                for (int i = 0; i < word.length() ; ++i) {
                    for (char j = 'a'; j < 'z'+1; ++j) {
                        if (dict.search(replacement(word,i,j)))
                            totest.insert(replacement(word,i,j));
                    }
                }
                for (int i = 0; i < word.length() + 1 ; ++i) {
                    for (char j = 'a'; j < 'z'+1; ++j) {
                        if (dict.search(insertAfter(word,i -1,j)))
                            totest.insert(insertAfter(word,i -1,j));
                    }
                }

                for(string a: totest){
                    answ += a + ", ";
                }
                answ = answ.substr(0,answ.length()-2);
                cout << line_number << ") "<< wordBefore << " : " << answ <<"\n";
            }

		}
	}
}

void lower(string& s) {

    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s) {
//	 Remove any single trailing
//	 punctuation character from a word.
	if (ispunct(s[s.length() - 1]) )
    {
		return s.substr (0, s.length() - 1);
	}
	else
    {
		return s;
	}
}
//меняет местами соседние буквы pos  и pos + 1
string transposing(const string& s, const int pos){
    string answ;
    answ = s;
    char hlp = answ[pos];
    answ[pos] = answ[pos+1];
    answ[pos+1] = hlp;
    return answ;
}
//удаляет символ
string removal(const string& s, const int pos){
    return s.substr(0,pos) + s.substr(pos+1, s.length() - pos - 1);
}
//заменяет символ
string replacement(const string& s, const int pos, const char c){
    string answ = s;
    answ[pos] = c;
    return answ;
}
//вставляет символ после
string insertAfter(const string& s, const int pos, const char c){
    if (pos == -1)
        return c + s;
    return s.substr(0,pos + 1) + c + s.substr(pos + 1, s.length() - pos);
}