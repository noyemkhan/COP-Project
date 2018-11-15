#include <iostream>
#include <vector>
#include <string>
#include "StoryTokenizer.h"
#include "PassageToken.h"
#include "PassageTokenizer.h"
#include "SectionToken.h"
using namespace std;

//StoryTokenizer constructor
StoryTokenizer::StoryTokenizer(string str)
{
    while(str.substr(0, str.find('\n')) != "</body>")
    {

        if(str.substr(0, 15) == "<tw-passagedata")
        {
            passages.push_back(str.substr(0, str.find('\n')));
        }

        str.erase(0, str.find('\n') + 1);
    }
}

//Checking if there is a next passage...
bool StoryTokenizer::hasNextPassage()
{
    bool hasPassage = false;

    if(tracker != passages.size())
    {
        hasPassage = true;
    }

    return hasPassage;
}

//Go through the vector of passages and return the PassageToken containing the next passage
//Will need to call getText() from PassageToken.cpp
PassageToken StoryTokenizer::nextPassage()
{
    if(tracker < passages.size())
    {
        PassageToken pass(passages.at(tracker)); //Calls PassageToken Constructor
        tracker++; //Increments tracker each time a PassageToken is returned
        return pass;
    }
    else
    {
        PassageToken emptyPass;
        tracker++;
        return emptyPass;
    }
}