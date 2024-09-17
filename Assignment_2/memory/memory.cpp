#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> parseFileLines(std::ifstream &input)
{
    std::string line;
    std::vector<std::string> lines;

    if (!input.is_open())
    {
        throw std::runtime_error("Error opening file");
    }

    while (std::getline(input, line))
    {
        lines.push_back(line);
    }

    return lines;
}

void char1ToChar2(std::string &originalString, const char character1, const char character2, std::vector<int> &modifiedCharIndices)
{
    for (int i = 0; i < originalString.size(); i++)
    {
        if (originalString[i] == character1)
        {
            originalString[i] = character2;
            modifiedCharIndices.push_back(i);
        }
    }
}

std::vector<std::string> reversed(const std::vector<std::string> &lines)
{
    std::vector<std::string> reversedLines;

    for (int i = lines.size() - 1; i >= 0; i--)
    {
        reversedLines.push_back(lines[i]);
    }

    return reversedLines;
}

std::vector<int> processLine(std::string &line)
{
    std::vector<int> modifiedCharIndices;

    char1ToChar2(line, 'e', '3', modifiedCharIndices);
    char1ToChar2(line, 'l', '1', modifiedCharIndices);
    char1ToChar2(line, 't', '7', modifiedCharIndices);

    return modifiedCharIndices;
}

void counterCompute(const std::string &line, const int lineNumber, const std::vector<int> modifiedCharIndeces, int *counter)
{
    for (const int &index : modifiedCharIndeces)
    {
        int number = (line[index] - '0') * lineNumber;
        *counter += number;
    }
}

std::vector<std::string> processedLines(const std::vector<std::string> &originaLines, int *counter)
{
    std::vector<std::string> processedLines = originaLines;

    for (int i = 0; i < processedLines.size(); i++)
    {
        std::vector<int> modifiedCharIndices = processLine(processedLines[i]);
        counterCompute(processedLines[i], i, modifiedCharIndices, counter);

        modifiedCharIndices.clear();
    }

    processedLines = reversed(processedLines);

    return processedLines;
}

int *createCounter()
{

    int *counter = new int(0);

    return counter;
}

void outputToFile(const std::vector<std::string> &lines, const int &counter, std::ofstream &output)
{

    for (const std::string &line : lines)
    {
        output << line << '\n';
    }

    output << counter << std::endl;
}

int main()
{

    // get the original lines
    std::ifstream input{"input.txt"};
    std::vector<std::string> originalLines = parseFileLines(input);

    // process the lines and compute the counter
    int &counter = *createCounter();
    std::vector<std::string> processed = processedLines(originalLines, &counter);

    // output to file
    std::ofstream output{"output.txt"};
    outputToFile(processed, counter, output);

    delete &counter;
}