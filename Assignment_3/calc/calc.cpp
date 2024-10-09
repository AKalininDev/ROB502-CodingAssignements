#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> // for formatting results

bool isDouble(const std::string &s)
{
  std::string trimmed = s;

  if (!s.empty() && s.back() == '+')
  {
    trimmed.pop_back();
  }

  if (!s.empty() && s.back() == '*')
  {
    trimmed.pop_back();
  }

  std::istringstream ss(trimmed);
  double d;
  return (ss >> d) && (ss.eof());
}

bool containsOperator(const std::string &s)
{

  return s.find_first_of("+*/") != std::string::npos;
}

bool isValidOperator(const char &s)
{
  return s == '+' || s == '*' || s == '/';
}

bool isOperationPossible(const std::vector<double> &numbers, const char operation)
{
  if (operation == '+')
  {
    return true;
  }
  else if (operation == '*')
  {
    return true;
  }
  else if (operation == '/')
  {
    return (numbers.size() == 2) && (numbers[1] != 0);
  }
  return false;
}

void performOperation(std::vector<double> &numbers, const char &operation, double &result)
{
  if (operation == '+')
  {
    double sum = 0;
    for (double number : numbers)
    {
      sum += number;
    }

    result = sum;
  }
  else if (operation == '*')
  {
    double product = 1;

    if (numbers.size() == 0)
    {
      result = 0.0;
      return;
    }

    for (double number : numbers)
    {
      product *= number;
    }

    result = product;
  }
  else if (operation == '/')
  {
    result = numbers[0] / numbers[1];
  }
}

void parse_line(std::string line, double &result, bool &error)
{

  std::istringstream lineStream(line);
  std::vector<double> numbers;
  double token;

  error = true;
  bool operatorFound = false;

  while (lineStream >> token)
  {

    numbers.push_back(token);
  }

  if (numbers.empty())
  {
    return;
  }

  lineStream.clear();

  char op = '\0';
  if (!line.empty())
  {
    for (int i = line.size() - 1; i >= 0; --i)
    {
      if (!isspace(line[i]))
      {
        op = line[i];
        break;
      }
    }
  }

  if (!isValidOperator(op))
  {
    return;
  }

  if (!isOperationPossible(numbers, op))
  {
    return;
  }

  performOperation(numbers, op, result);
  error = false;

  return;
}

void process_f_stream(std::ifstream &infile, std::ofstream &outfile)
{
  std::string line;
  std::vector<double> numbers;
  double result;
  bool error = true;

  while (std::getline(infile, line))
  {
    parse_line(line, result, error);

    if (error)
    {
      outfile << "ERROR" << std::endl;
    }
    else
    {
      outfile << result << std::endl;
    }
  }
}

int main()
{
  std::ifstream infile("input.txt");
  std::ofstream outfile("output.txt");

  process_f_stream(infile, outfile);
  return 0;
}
