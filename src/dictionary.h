#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function
{
public:

    unsigned int operator()( const string& s )  const {
        
        unsigned int max = -1;
        unsigned int res = 0;
        unsigned int p = 1;
        for (int i = s.length()-1; i >= 0; --i) {
            res += (s[0] - 'a')*p % max;
            p = p * 26 % max;
        }
        return res;

    }
};

class equality
{
public:
    equality() {}
    bool  operator()( const string& A, const string& B )  const 
    {
        return  (A == B);
    }
};

class Dictionary: public HashSet<string, hash_function, equality> {

    // Complete definition
public:
	Dictionary(string filename);

};
#endif // _DICTIONARY_H_
