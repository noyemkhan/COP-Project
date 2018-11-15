#include <iostream>
#include <vector>
#include <string>
#include "StoryTokenizer.h"
#include "PassageToken.h"
#include "PassageTokenizer.h"
#include "SectionToken.h"
using namespace std;

PassageTokenizer::PassageTokenizer(string str)
{
    //in this constructor, we need to go through the passage token that is the argument and find the section tokens from within
    //where we declare a SectionToken object, store that object in our sections vector using push_back and erase the section token from our string and increment tracker each time
    //might want to consider using emplace_back
    tracker = 0;
    //cout << "str before going into the while loop in PassageTokenizer:" << str << endl;
    while(!str.empty())
    {
        if(str.at(0) == ' ')
        {
            //cout << "we are checking if the first char is a space. If this prints we are inside." << endl;
            str.erase(0, 1);//i have to delete the space char, not the entire string
         //   cout << "\tafter erasing the first char, str is:" << str << endl;
        }
        else if(str.substr(0, 2) == "[[")
        {
            //string setString = str.substr(0, (str.find(']') + 2));
           // cout << "This is what is being emplaced back inside if checking for LINK:" << setString << endl;
            sections.emplace_back(str.substr(0, (str.find(']') + 2)), LINK);
            str.erase(0, str.find(']') + 2);
           // cout << "checking what str is after LINK:" << str << endl;
        }
        else if(str.substr(0, 2) == "(s")
        {
           // cout << "This is what is being emplaced back inside if checking for SET:" << str.substr(0, str.find(')') + 1) << endl;
            sections.emplace_back(str.substr(0, str.find(')') + 1), SET);
            str.erase(0, str.find(')') + 1);
           // cout << "checking what str is after SET:" << str << endl;
        }
        else if(str.substr(0, 2) == "(g")
        {
            //cout << "This is what is being emplaced back inside if checking for GOTO:" << str.substr(0, str.find(')') + 1) << endl;
            sections.emplace_back(str.substr(0, str.find(')') + 1), GOTO);
            str.erase(0, str.find(')') + 1);
           // cout << "checking what str is after GOTO:" << str << endl;
        }
        else if(str.substr(0, 2) == "(i")
        {
           // cout << "This is what is being emplaced back inside if checking for IF:" << str.substr(0, str.find(')') + 1) << endl;
            sections.emplace_back(str.substr(0, str.find(')') + 1), IF);
            str.erase(0, str.find(')') + 1);
           // cout << "checking what str is after IF:" << str << endl;
        }
        else if (str.substr(0, 2) == "(e")
        {
            if(str.substr(0, 6) == "(else-")
            {
               // cout << "This is what is being emplaced back inside if checking for ELSEIF:" << str.substr(0, str.find(')') + 1) << endl;
                sections.emplace_back(str.substr(0, str.find(')') + 1), ELSEIF);
                str.erase(0, str.find(')') + 1);
               // cout << "checking what str is after ELSEIF:" << str << endl;
            }
            else
            {
              //  cout << "This is what is being emplaced back inside if checking for ELSE:" << str.substr(0, str.find(')') + 1) << endl;
                sections.emplace_back(str.substr(0, str.find(')') + 1), ELSE);
                str.erase(0, str.find(')') + 1);
              //  cout << "checking what str is after ELSE:" << str << endl;
            }
        }
        else if (str.substr(0, 1) == "[") //We need to make sure we get the outtermost ']'
        {
            //ok so we need to mayb have a counter where we count all the '[' found after the
            //also have to test if a link is found
            int counter = 0;
            string temp = str.substr(0, str.find(']'));//this string is to check if there is a block/link in a block
//            string link;
//            string stringToPush = temp;//check if the temp var contains more than one [, if it does push it back, if not just push back str
//            bool containsLink = false;
            for (int i = 0 ; i < temp.length(); i++) //mayb considering doing a while loop in case there are multiple links in a block
            {
                if (i != 0 && temp.at(i) == '[')
                {
                    counter++;
                }
            }

//            cout << "This is what is being emplaced back inside if checking for BLOCK:" << str.substr(0, str.find(']') + 1) << endl;
//            cout << "counter = " << counter << endl;

                sections.emplace_back(str.substr(0, str.find(']') + 1 + counter), BLOCK);
                str.erase(0, str.find(']') + 1 + counter);
               // cout << "checking what str is after BLOCK:" << str << endl;
        }
        else if((str.at(0) >= '^' && str.at(0) <= '~') || (str.at(0) >= '*' && str.at(0) <= 'Z') || (str.at(0) >= '!' && str.at(0) <= '&')) //this is where we put text into the vector...
        {
            if(str.find("[[") != string::npos)
            {
               // cout << "This is what is being emplaced back inside if checking for TEXT:" << str.substr(0, str.find('[[')) << endl;
                sections.emplace_back(str.substr(0, str.find("[[")), TEXT);
                str.erase(0, str.find("[["));
               // cout << "checking what str is after TEXT:" << str << endl;
            }
            else
            {
                //cout << "This is what is being emplaced back inside if checking for TEXT:" << str.substr(0, str.find('\0') - 1) << endl;
                sections.emplace_back(str.substr(0, str.find('\0') - 1), TEXT);
                str.erase(0, str.find('\0') - 1);
               // cout << "checking what str is after TEXT:" << str << endl;
            }
        }
    }
    //cout << "str after the while loop is:(should be empty)" << str << endl;
}

//check if the tracker is less than the size of the vector to check if there is a next section
bool PassageTokenizer::hasNextSection()
{
    bool hasSection = false;

    if (tracker != sections.size())
    {
        hasSection = true;
    }
    return hasSection;
}

//We need to break the string apart and return the SectionToken, erase each section as it is getting returned
//Also need to find the section which is leftover and is text
//Go through the sections vector
//HOW ARE WE SUPPOSED TO RETURN AN EMPTY STRING WHEN SECTIONTOKEN IS INVALID
SectionToken PassageTokenizer::nextSection()
{
    int i;
    if(hasNextSection())
    {
        i = tracker;
        tracker++;
    }
    else //this statement wil never be executed it won't call nextSection() if hasNextSection() returns false...
    {
        SectionToken invalidSection("", SET);
        return invalidSection;
    }

    return sections.at(i);
}