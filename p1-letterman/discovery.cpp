// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9

#include <algorithm>
#include <cmath>
#include <deque>

#include "letterman.hpp"

using namespace std;

// fetches the next word and deletes it from the search container, if successful we return 1, if no more words, return 0
bool Letterman::get_next()
{
  if (container.empty())
    return false;

  if (stack_or_queue) // queue
  {
    current = dictionary[container.front()].word;
    curr_ind = container.front();
    container.pop_front();
  }
  else // stack
  {
    current = dictionary[container.back()].word;
    curr_ind = container.back();
    container.pop_back();
  }

  investigated++;

  return true;
}

// finds all sufficiently similar words to current and adds it to container, if the final word is found, we return true to stop program
bool Letterman::investigate(const bool c, const bool p, const bool l)
{
  // go through the dictionary and find words that are sufficiently similar
  for (size_t i = 0; i < dictionary.size(); ++i)
  {
    string new_word = dictionary[i].word;
    char temp;

    // skip iteration if the word has been discovered or is equal to the current word
    // if length mode is not on and the word lengths don't match continue
    // if length mode is on, skip if length diff > 1
    if (dictionary[i].discovered || current == new_word)
      continue;
    else if (!l && current.length() != new_word.length())
      continue;
    else if (abs(static_cast<int>(new_word.length() - current.length())) > 1)
      continue;

    // if x option is enabled and that word is a viable morph from current then we add to deque
    // make sure to change discovered val
    // set the prev ind to the current words index
    if ((c && change(current, new_word, temp) != std::string::npos) ||
        (p && swap(current, new_word) != std::string::npos) ||
        (l && length(current, new_word, temp) != std::string::npos))
    {
      container.push_back(i);
      dictionary[i].discovered = true;
      dictionary[i].prev = curr_ind;
      discovered++;
      // if we find the final word, stop this and exit to main
      if (i == end_ind)
        return true;
    } // if
  } // for
  return false;
}

size_t Letterman::change(const std::string &current_word, const std::string &new_word, char &letter)
{
  size_t index = std::string::npos;
  size_t diff = 0;

  for (size_t i = 0; i < current_word.length(); ++i)
  {
    if (current_word[i] != new_word[i])
    {
      ++diff;
      if (diff > 1)
        break;
      if (index == std::string::npos)
      {
        index = i;
        letter = new_word[i];
      }
    }
  }
  return (diff == 1) ? index : std::string::npos;
}

size_t Letterman::swap(const std::string &current_word, const std::string &new_word)
{
  size_t diff = 0;
  size_t index = std::string::npos;

  for (size_t i = 0; i < current_word.length(); ++i)
  {
    if (current_word[i] != new_word[i])
    {
      ++diff;
      if (diff > 2)
        return std::string::npos;
      if (index == std::string::npos)
        index = i;
    }
  }

  return (diff == 2) ? index : std::string::npos;
} // swap();

size_t Letterman::length(const std::string &current_word, const std::string &new_word, char &letter)
{
  size_t index = std::string::npos;
  size_t len1 = current_word.length();
  size_t len2 = new_word.length();
  size_t n = max(len1, len2);
  size_t diff = 0;
  size_t ind1 = 0, ind2 = 0;

  // if the length didn't change skip, we already account for being too long in investigate();
  if (abs(static_cast<int>(len1 - len2)) != 1)
    return std::string::npos;

  while (ind1 < n && ind2 < n)
  {
    if (current_word[ind1] != new_word[ind2])
    {
      ++diff;
      if (diff > 1)
        break;
      if (index == std::string::npos)
      {
        index = ind1;
        // current word < new word means we insert so keep ind1 at the same spot
        if (len1 < len2)
        {
          letter = new_word[ind2];
          ++ind2;
        }
      }
    }
    else
    {
      ++ind1;
      ++ind2;
    } // if ... else
  } // while

  return (diff == 1) ? index : std::string::npos;
} // length();