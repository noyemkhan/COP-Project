#include <iostream>
#include <vector>
#include <string>
#include "StoryTokenizer.h"
#include "PassageToken.h"
#include "PassageTokenizer.h"
#include "SectionToken.h"
using namespace std;

PassageToken::PassageToken(string str)
{
    text = str;
}

PassageToken::PassageToken()
{
    text = "";
}

string PassageToken::getText()
{
    string taglessText;
    if(text.empty())
    {
        taglessText = text;
        return taglessText;
    }
    else
    {
        for (int i = text.find('>'); text.at(i) != '<'; i++)
        {
            if (text.at(i) != '>')
            {
                taglessText += text.at(i);
            }
        }
        return taglessText;
    }
}