#include <iostream>
#include <string>
#include "storytokenizer.h"
using namespace std;

int main()
{
  string line, story;

  getline(cin, line);
  while (cin && line != "</html>")
  {
    story += line + '\n';
    getline(cin, line);
  }

  StoryTokenizer st(story);
  int pass = 0;
  while (st.hasNextPassage())
  {
    PassageToken ptok = st.nextPassage();
    pass++;
    cout << "Passage " << pass << ":  " << endl;
    PassageTokenizer pt(ptok.getText());
    while (pt.hasNextSection())
    {
      SectionToken stok = pt.nextSection();
      switch (stok.getType())
      {
      case LINK:
        cout << "  Link:  ";
        break;
      case SET:
        cout << "  Set:  ";
        break;
      case GOTO:
        cout << "  Go-to:  ";
        break;
      case IF:
        cout << "  If:  ";
        break;
      case ELSEIF:
        cout << "  Else-if:  ";
        break;
      case ELSE:
        cout << "  Else:  ";
        break;
      case BLOCK:
        cout << "  Block:  ";
        break;
      case TEXT:
        cout << "  Text:  ";
        break;
      default:
        cout << "  Unknown token:  ";
      }
      cout << stok.getText() << endl;
    }
  }

  return 0;
}
