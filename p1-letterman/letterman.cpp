// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

#include "letterman.hpp"

using namespace std;

// Constructor
Letterman::Letterman(string begin_word, string end_word)
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
  for (auto &item : dictionary)
  {
    cout << item.word << endl;
  }
}

// reads in lines from file specified in CLI
void Letterman::make_dict()
{
  string line;
  bool simple = true;

  getline(cin, line);
  if (line == "C")
    simple = false;
  getline(cin, line);

  while (getline(cin, line))
  {
    // skip comment lines or if blank
    if (line[0] == '/' || line.empty())
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
      else if (line.find('[') != string::npos)
      {
        size_t start = string::npos, end = string::npos;
        string insert = "";
        insert_each(insert, line, start, end);

        // string insert == "ch[p": start begin at the index after '['
        for (size_t i = start + 1; i < end; ++i)
        {
          insert[start] = line[i];
          dictionary.push_back({insert});
        }
      }
      // swap
      else if (line.find('!') != string::npos)
      {
        string insert = "";
        size_t swap_index = string::npos;
        no_special_char(insert, line, swap_index);
        dictionary.push_back({insert});
        if (swap_index >= 2 && swap_index < insert.length())
        {
          swap(insert[swap_index - 2], insert[swap_index - 1]);
          dictionary.push_back({insert});
        }
      }
      // double
      else if (line.find('?') != string::npos)
      {
        string insert = "";
        size_t index = string::npos;
        no_special_char(insert, line, index);
        dictionary.push_back({insert});
        if (index < insert.length())
        {
          insert = insert.substr(0, index) + insert[index - 1] + insert.substr(index);
          dictionary.push_back({insert});
        }
      }
      // no changes
      else
      {
        dictionary.push_back({line});
      }
    } // if ... else ...
  } // while (getline)

  for (size_t i = 0; i < dictionary.size(); ++i)
  {
    if (dictionary[i].word == begin_word)
      begin_ind = static_cast<int>(dictionary.size() - 1);
    else if (dictionary[i].word == end_word)
      end_ind = static_cast<int>(dictionary.size() - 1);
  }

  if (begin_ind == -1)
  {
    cerr << "Begin word not found" << endl;
    exit(1);
  }
  else if (end_ind == -1)
  {
    cerr << "End word not found" << endl;
    exit(1);
  }
}

// gets the word with '[' at the index where we insert-each of the characters instead
// i.e line = ch[io]p will return ch[p, we then use the start and end to get each of middle characters
void Letterman::insert_each(string &insert, const string &line, size_t &start, size_t &end)
{
  start = string::npos;
  end = string::npos;

  for (size_t i = 0; i < line.length(); i++)
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
      if (start != string::npos && end == string::npos)
        continue;
      insert += line[i];
    }
  }
}

// changes the word without the singular special character,
// and changes the index of special character by reference
void Letterman::no_special_char(string &insert, const string &line, size_t &index)
{
  index = string::npos;

  for (size_t i = 0; i < line.length(); i++)
  {
    if (line[i] == '!' || line[i] == '?')
      index = i;
    else
      insert += line[i];
  }
}