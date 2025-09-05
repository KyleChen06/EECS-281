// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#include <iostream>
#include <deque>
#include <vector>

#include "letterman.hpp"

using namespace std;

// Constructor
Letterman::Letterman(istream &input, string begin_word, string end_word)
{
  this->begin_word = begin_word;
  this->end_word = end_word;
  current = begin_word;
  make_dict();
}

// Letterman does his thing :D
void Letterman::morph()
{
}

// prints the output
void Letterman::output()
{
}

// reads in lines from file specified in CLI
void Letterman::make_dict()
{
  string line;
  int n;
  bool simple = 1;

  getline(cin, line);
  if (line == "C")
    simple = 0;
  getline(cin, line);
  n = stoi(line);

  while (getline(cin, line))
  {
    // skip comment lines or if blank
    if (line[0] == '/' || line == "")
      continue;

    // if it is simple, we just add in the line and continue
    if (simple)
      dictionary.push_back({line});
    // if it is complex, we have to loop through each string to check
    else
    {
      // reversal
      if (line.back() == '&')
      {
        string insert = line.substr(0, line.size() - 1);
        dictionary.push_back({insert});
        reverse(insert.begin(), insert.end());
        dictionary.push_back({insert});
      }
      // insert-each
      else if (line.find('['))
      {
        int start, end = -1;
        string insert = "";
        insert_each(insert, line, start, end);

        // string insert == "ch[p": start begin at the index after '['
        for (int i = start + 1; i < end; ++i)
        {
          insert[start] = line[i];
          dictionary.push_back({insert});
        }
      }
      // swap
      else if (line.find('!'))
      {
        string insert = "";
        int swap = -1;
        no_special_char(insert, line, swap);
        dictionary.push_back({insert});
        reverse(insert.begin() + swap - 2, insert.begin() + swap - 1);
        dictionary.push_back({insert});
      }
      // double
      else if (line.find('?'))
      {
        string insert = "";
        int index = -1;
        no_special_char(insert, line, index);
        dictionary.push_back({insert});
        insert = insert.substr(0, index) + insert[index - 1] + insert.substr(index + 1);
        dictionary.push_back({insert});
      }
      // no changes
      else
      {
        dictionary.push_back({line});
      }

    } // if ... else ...

    // stores the begin/end index of the words
    if (dictionary.back().word == begin_word)
      begin_ind = dictionary.size() - 1;
    else if (dictionary.back().word == end_word)
      end_ind = dictionary.size() - 1;
  } // while (getline)

  if (begin_ind == -1)
  {
    cerr << "" << endl;
    exit(1);
  }
  else if (end_ind == -1)
  {
    cerr << "" << endl;
    exit(1);
  }
}

// gets the word with '[' at the index where we insert-each of the characters instead
// i.e line = ch[io]p will return ch[p, we then use the start and end to get each of middle characters
void insert_each(string &insert, const string &line, int &start, int &end)
{

  for (int i = 0; i < line.length(); i++)
  {
    if (line[i] == '[')
    {
      start = i;
      insert += line[i];
    }
    else if (line[i] == ']')
      end = i;
    else
    {
      // dont add to string if it is between '[' && ']'
      if (start != -1 && end == -1)
        continue;
      insert += line[i];
    }
  }
}

// changes the word without the singular special character,
// and changes the index of special character by reference
void no_special_char(string &insert, const string &line, int &index)
{
  for (int i = 0; i < line.length(); i++)
  {
    if (line[i] == '!')
      index = i;
    else
      insert += line[i];
  }
}