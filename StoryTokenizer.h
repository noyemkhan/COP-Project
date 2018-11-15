#ifndef STORYTOKR_H
#define STORYTOKR_H

#include <iostream>
#include <vector>
#include <string>
#include "PassageToken.h"
#include "PassageTokenizer.h"
#include "SectionToken.h"
using namespace std;

class StoryTokenizer
{
    private:
        vector<string> passages;
        int tracker = 0;
    public:
        StoryTokenizer(string str);
        bool hasNextPassage();
        PassageToken nextPassage(); //Should return an empty string when there are no more passages (when invalid)
};

#endif