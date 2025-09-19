// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

#include "letterman.hpp"

using namespace std;

// Constructor
Letterman::Letterman(int argc, char **argv)
{
  getOptions(argc, argv);
  make_dict();
}

// Letterman does his thing :D
void Letterman::morph()
{
  // go until we find all
  while (investigated < dictionary.size())
  {
    bool found = investigate(); // if found is true that means that the next item from get_next will be end_word
    if (!get_next(found))       // no more items in the container
      break;
    if (found) // we found the end word :D
    {
      break;
    }
  }
}

// prints the output
void Letterman::output()
{
  if (curr_ind != end_ind)
  {
    cout << "No solution, " << discovered << " words discovered." << endl;
  }
  else
  {
    vector<size_t> reverse_order;
    reverse_order.reserve(investigated);

    while (curr_ind != begin_ind)
    {
      reverse_order.push_back(curr_ind);
      curr_ind = dictionary[curr_ind].prev;
    }

    cout << "Words in morph: " << reverse_order.size() + 1 << endl;
    cout << begin_word << endl;

    // create a reverse_ordered vector with the indexes of the words

    if (output_version) // modification
    {
      for (size_t i = reverse_order.size(); i > 0; i--)
      {
        size_t index;
        char letter = '\0';
        string new_word = dictionary[reverse_order[i - 1]].word;
        string current_word = (i == reverse_order.size()) ? begin_word : dictionary[reverse_order[i]].word;
        bool len_check = new_word.length() == current_word.length();

        if (len_check && (c || p))
        {
          if ((index = change(current_word, new_word, letter)) != std::string::npos)
            cout << "c," << index << "," << letter << endl;
          else if ((index = swap(current_word, new_word)) != std::string::npos)
            cout << "s," << index << endl;
        }
        else if (l && (index = length(current_word, new_word, letter)) != std::string::npos)
        {
          if (current_word.length() > new_word.length()) // deletion
            cout << "d," << index << endl;
          else
            cout << "i," << index << "," << letter << endl;
        }
      }
    }
    else // word
    {
      for (size_t i = reverse_order.size(); i > 0; i--)
      {
        cout << dictionary[reverse_order[i - 1]].word << endl;
      }
    }
  }
}

// reads in lines from file specified in CLI
void Letterman::make_dict()
{
  string line;
  char simple = true;

  getline(cin, line);
  if (line == "C")
    simple = false;
  getline(cin, line);

  size_t n = static_cast<size_t>(stoi(line)) + 1;

  if (simple)
    dictionary.reserve(n);

  while (getline(cin, line))
  {
    // skip comment lines or if blank
    if (line[0] == '/' || line.empty())
      continue;

    // if it is simple, we just add in the line and continue
    if (simple)
    {
      if (n == 0)
        return;
      if (!l)
      {
        if (begin_word.length() == line.length())
          dictionary.push_back({line});
      }
      else
      {
        dictionary.push_back({line});
      }
    }
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
      else if (line.find('[') != std::string::npos)
      {
        size_t start = line.find('['), end = line.find(']');
        string insert = line.substr(0, start + 1) + line.substr(end + 1);

        // string insert == "ch[p": start begin at the index after '['
        for (size_t i = start + 1; i < end; ++i)
        {
          insert[start] = line[i];
          dictionary.push_back({insert});
        }
      }
      // swap
      else if (line.find('!') != std::string::npos)
      {
        size_t swap_ind = line.find('!');
        string insert = line.substr(0, swap_ind) + line.substr(swap_ind + 1);
        dictionary.push_back({insert});
        std::swap(insert[swap_ind - 2], insert[swap_ind - 1]);
        dictionary.push_back({insert});
      }
      // double
      else if (line.find('?') != std::string::npos)
      {
        string insert = "";
        size_t index = std::string::npos;
        no_special_char(insert, line, index);
        dictionary.push_back({insert});
        insert = insert.substr(0, index) + insert[index - 1] + insert.substr(index);
        dictionary.push_back({insert});
      }
      // no changes
      else
      {
        dictionary.push_back({line});
      }
    } // if ... else ...
    --n;
  } // while (getline)

  for (size_t i = 0; i < dictionary.size(); ++i)
  {
    if (dictionary[i].word == begin_word)
    {
      begin_ind = i;
      dictionary[i].discovered = true;
    }
    if (dictionary[i].word == end_word)
      end_ind = i;
  }

  if (begin_ind == std::string::npos)
  {
    cerr << "Beginning word does not exist in the dictionary" << endl;
    exit(1);
  }

  if (end_ind == std::string::npos)
  {
    cerr << "Ending word does not exist in the dictionary" << endl;
    exit(1);
  }
  curr_ind = begin_ind;
}

// changes the word without the singular special character,
// and changes the index of special character by reference
void Letterman::no_special_char(string &insert, const string &line, size_t &index)
{
  index = std::string::npos;

  for (size_t i = 0; i < line.length(); i++)
  {
    if (line[i] == '!' || line[i] == '?')
      index = i;
    else
      insert += line[i];
  }
}