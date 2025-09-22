// Project identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768

#include "evaluate.hpp"

#include <cstdint>
#include <stack>

using namespace std;

std::int64_t evaluate(std::string const &expression)
{
  stack<int64_t> nums;
  stack<char> operands;

  for (size_t i = 0; i < expression.length(); i++)
  {
    if (isdigit(expression[i]))
      nums.push(expression[i] - '0');
    else
      operands.push(expression[i]);

    if (nums.size() >= 2 && operands.size() >= 1)
    {
      int64_t right = nums.top();
      nums.pop();
      int64_t left = nums.top();
      nums.pop();

      char operand = operands.top();
      operands.pop();

      switch (operand)
      {
      case '*':
        nums.push(left * right);
        break;
      case '/':
        nums.push(left / right);
        break;
      case '+':
        nums.push(left + right);
        break;
      case '-':
        nums.push(left - right);
        break;
      }
    }
  } // for
  return nums.top();
}
