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

bool isValidOperator(const std::string &s)
{
  return s.back() == '+' || s.back() == '*' || s.back() == '/';
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

void performOperation(std::vector<double> &numbers, const char &operation, std::string &result)
{
  if (operation == '+')
  {
    double sum = 0;
    for (double number : numbers)
    {
      sum += number;
    }

    result = std::to_string(sum);
  }
  else if (operation == '*')
  {
    double product = 1;

    if (numbers.size() == 0)
    {
      result = "0";
      return;
    }

    for (double number : numbers)
    {
      product *= number;
    }

    result = std::to_string(product);
  }
  else if (operation == '/')
  {
    result = std::to_string(numbers[0] / numbers[1]);
  }
}

std::string formatResult(const std::string &result)
{
  std::string formattedResult = result;
  if (result.find('.') != std::string::npos)
  {
    while (formattedResult.back() == '0')
    {
      formattedResult.pop_back();
    }
    if (formattedResult.back() == '.')
    {
      formattedResult.pop_back();
    }
  }
  return formattedResult;
}

void parse_line(std::string line, std::string &result)
{
  line.erase(0, line.find_first_not_of(" \t\n\r"));
  line.erase(line.find_last_not_of(" \t\n\r") + 1);
  std::vector<double> numbers;

  std::istringstream lineStream(line);
  std::string token;

  result = "ERROR";
  bool operatorFound = false;

  while (lineStream >> token)
  {

    if (isDouble(token))
    {
      numbers.push_back(std::stod(token));
    }

    if (containsOperator(token))
    {

      if (!isValidOperator(token))
      {
        return;
      }

      const char op = token.back();

      if (!isOperationPossible(numbers, op))
      {
        return;
      }

      performOperation(numbers, op, result);
      result = formatResult(result);

      // After operation, ensure no remaining tokens
      // if (lineStream >> token)
      // {
      //   result = "ERROR";
      // }
      operatorFound = true;
      return;
    }
  }
}

void process_f_stream(std::ifstream &infile, std::ofstream &outfile)
{
  std::string line;
  std::vector<double> numbers;
  std::string result;
  while (!infile.eof())
  {
    std::getline(infile, line);

    if (!line.empty())
    {
      parse_line(line, result);
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
