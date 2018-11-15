#ifndef SECTOKN_H
#define SECTOKN_H

#include <iostream>
#include <vector>
#include <string>
#include "StoryTokenizer.h"
#include "PassageToken.h"
#include "PassageTokenizer.h"
using namespace std;
enum tokenType_t {LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT};

class SectionToken
{
    private:
        string secTok;
        tokenType_t secType;
    public:
        SectionToken(string str, tokenType_t secType);
        string getText();
        tokenType_t getType();
};


#endif
