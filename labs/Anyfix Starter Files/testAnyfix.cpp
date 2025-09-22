#include <iostream>
#include <string>

#include "evaluate.hpp"

using namespace std;

auto main() -> int
{
  int64_t test = evaluate("5*3+1+4/5*2-9");
  cout << test;
  test = evaluate("-93+7*98-");
  cout << test;
  test = evaluate("*+456");
  cout << test;
}

/*
 * NOTE: Since this file's name matches the glob pattern test*.cpp, the file is
 * a test file, NOT a source file! Nothing written here will be
 * submitted to the autograder.
 *
 * This also means there is no executable for this lab. Do not set EXECUTABLE
 * in your makefile to anything intended to be meaningful. Do not build with
 * `make release` or `make debug` or `make all` or just plain `make`; instead,
 * run `make help` and read the output that gives you, then use what you learn
 * from that to figure out how to build a test executable using this file.
 */
