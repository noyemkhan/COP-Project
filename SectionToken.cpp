#include <iostream>
#include <vector>
#include <string>
#include "StoryTokenizer.h"
#include "PassageToken.h"
#include "PassageTokenizer.h"
#include "SectionToken.h"
using namespace std;

SectionToken::SectionToken(string str, tokenType_t type)
{
    secTok = str;
    secType = type;
}

//must return an empty string when invalid HAVEN'T DONE THIS YET
//HOW DO WE CHECK IF IT IS INVALID??
string SectionToken::getText()
{
    return secTok;
}

tokenType_t SectionToken::getType()
{
    return secType;
}
