#ifndef PASSTOKN_H
#define PASSTOKN_H

#include <iostream>
#include <vector>
#include <string>
#include "StoryTokenizer.h"
#include "PassageTokenizer.h"
#include "SectionToken.h"
using namespace std;

class PassageToken
{
    private:
        string text;
    public:
        PassageToken(string str);
        PassageToken();
        string getText();
};

#endif
