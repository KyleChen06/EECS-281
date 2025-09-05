// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68251FC9
#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include <string>
#include <vector>

// store all options from CLI
struct Options
{
  bool container = 0; // 0 == stack, 1 == queue
  bool s = 0;
  bool q = 0;
  bool change = 0;
  bool swap = 0;
  bool length = 0;
  bool output = 0; // 0 == W, 1 == M; default to word
  std::string begin;
  std::string end;
}; // Options{}

// Process the command line; there is no return value, but the Options
// struct is passed by reference and is modified by this function to send
// information back to the calling function.
void getOptions(int argc, char **argv, Options &options);

#endif // COMMAND_LINE_HPP