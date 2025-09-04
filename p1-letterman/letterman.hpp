// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#ifndef LETTERMAN_HPP
#define LETTERMAN_HPP

#include <vector>
#include <deque>

class Letterman
{
public:
  // Constructor
  Letterman();

  // Letterman does his thing :D
  void morph();

  // prints the output
  void
  output();

private:
  struct DictStruct
  {
    std::string word;
    int prev = -1;
    bool discovered = false;

    // made for std::sort to compare prev values
    bool operator<(const DictStruct &other) const
    {
      return prev < other.prev;
    }
  };

  std::vector<DictStruct> dictionary;
  std::string begin_word;
  std::string end_word;
  std::string current;
  int begin_ind;
  int end_ind;
  std::deque<int> container;
  size_t discovered = 0;

  // reads in lines from file specified in CLI
  void make_dict();

  // gets the next word from container and sets it to current
  void fetch();

  // removes the current word from container
  void remove();

  // finds all sufficiently similar words to current and adds it to container
  void investigate();
};

#endif // LETTERMAN_HPP