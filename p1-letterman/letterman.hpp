// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#ifndef LETTERMAN_HPP
#define LETTERMAN_HPP

#include <vector>
#include <deque>
#include <iostream>

class Letterman
{
public:
  // Constructor
  Letterman(std::string begin_word, std::string end_word, bool container_type, bool output_version);

  // Letterman does his thing :D
  void morph(const bool c, const bool p, const bool l);

  // print the output
  void output();

private:
  struct DictStruct
  {
    std::string word;
    size_t prev = std::string::npos;
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
  bool stack_or_queue;     // false for stack, true for queue
  bool output_version = 0; // false for word, true for modification
  size_t begin_ind = std::string::npos;
  size_t end_ind = std::string::npos;
  size_t curr_ind = std::string::npos;
  std::deque<size_t> container;
  size_t discovered = 0;
  size_t investigated = 0;

  // reads in lines from file specified in CLI
  void make_dict();

  // fetches the next word and deletes it from the search container
  bool get_next();

  // finds all sufficiently similar words to current and adds it to container
  bool investigate(const bool c, const bool p, const bool l);

  // helper functions for make_dict();
  void insert_each(std::string &insert, const std::string &line, size_t &start, size_t &end);
  void no_special_char(std::string &insert, const std::string &line, size_t &index);

  // helper functions for investigate, returns index at which change occurred, if needed the letter as well
  size_t change(const std::string &current_word, const std::string &new_word, char &letter);
  size_t swap(const std::string &current_word, const std::string &new_word);
  size_t length(const std::string &current_word, const std::string &new_word, char &letter);
};

#endif // LETTERMAN_HPP