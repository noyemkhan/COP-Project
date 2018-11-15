#ifndef PASSTOKR_H
#define PASSTOKR_H

#include <iostream>
#include <vector>
#include <string>
#include "StoryTokenizer.h"
#include "PassageToken.h"
#include "SectionToken.h"
using namespace std;

class PassageTokenizer
{
    private:
        vector<SectionToken> sections;
        int tracker;
    public:
        PassageTokenizer(string str);
        SectionToken nextSection(); //Should return an empty string when there are no more sections (when invalid)
        bool hasNextSection();
};


#endif
