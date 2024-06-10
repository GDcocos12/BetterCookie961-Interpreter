#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <regex>

/*
UPDATE LOG:

3.2 - Fixed Random Number Generator

3.3 - Comments added!

3.4 - Fixed 6-1 cycles and if constructions!

3.5 - Added P and J commands!

3.6 - Added _(break), x/m[+/-0/1], and G

3.7 - Made cross-platform and fixed bugs (comments are now working just fine!)
*/

std::vector<int> array{ 0 };
int pointerLocation = 0;

bool endsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string readFile(const std::string& fileName)
{
    std::ifstream f(fileName);
    if (!f.is_open())
    {
        std::cerr << "Error! File not found!" << std::endl;
        exit(EXIT_FAILURE);
    }
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string s(size, ' ');
    f.seekg(0);
    f.read(&s[0], size);
    return s;
}

void ifFunc(const std::string& code);
void arythm(const std::string& code);

static std::string preprocessCode(const std::string& code) {
    std::string result = code;
    std::regex singleLineComment("//.*");
    std::regex multiLineComment("/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*/");
    result = std::regex_replace(result, singleLineComment, "");
    result = std::regex_replace(result, multiLineComment, "");
    return result;
}

void interpret(const std::string& rawCode)
{
    const std::string code = preprocessCode(rawCode);
    size_t i = 0;
    while (i < code.length())
    {
        switch (code[i])
        {
        case 'i':
            if (pointerLocation > 0)
                pointerLocation -= 1;
            break;
        case 'I':
            if (pointerLocation > 0)
            {
                pointerLocation -= 1;
                array[pointerLocation] = array[pointerLocation + 1];
            }
            break;
        case 'k':
        case 'K':
            pointerLocation += 1;
            if (array.size() <= pointerLocation)
                array.push_back(0);
            if (code[i] == 'K')
                array[pointerLocation] = array[pointerLocation - 1];
            break;
        case 'r':
        {
            std::string flnm;
            std::cout << "File Name: ";
            std::cin >> flnm;
            if (endsWith(flnm, ".bc961"))
            {
                interpret(readFile(flnm));
            }
            else
            {
                std::cerr << "Error! Unknown extension." << std::endl;
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 'N':
            pointerLocation = 0;
            break;
        case 'P':
            if (pointerLocation >= array.size())
            {
                array.resize(pointerLocation + 1, 0);
            }
            std::swap(pointerLocation, array[pointerLocation]);
            break;
        case 'J':
            if (pointerLocation >= array.size())
            {
                array.resize(pointerLocation + 1, 0);
            }
            pointerLocation = array[pointerLocation];
            break;
        case 'n':
            std::cout << array[pointerLocation];
            break;
        case 'g':
            std::cout << pointerLocation;
            break;
        case 'R':
            array[pointerLocation] = rand() % 101;
            break;
        case 'c':
            array[pointerLocation] += 1;
            break;
        case 'C':
            array[pointerLocation] += 10;
            break;
        case 'o':
            if (array[pointerLocation] > 0)
                array[pointerLocation] -= 1;
            break;
        case 'O':
            if (array[pointerLocation] > 10)
                array[pointerLocation] -= 10;
            break;
        case '-':
            std::cout << "Paused. Press Enter to exit." << std::endl;
            std::cin.get();
            exit(EXIT_SUCCESS);
            break;
        case '>':
            std::cout << std::endl;
            break;
        case 'L':
            array[pointerLocation] = 0;
            break;
        case '(':
        {
            int open_braces = 1;
            size_t ifend = i + 1;
            std::string to_execute = "";
            while (open_braces > 0)
            {
                if (code[ifend] == '(')
                    open_braces++;
                else if (code[ifend] == ')')
                    open_braces--;
                if (open_braces > 0)
                    to_execute += code[ifend];
                ifend++;
            }
            i = ifend - 1;
            ifFunc(to_execute);
            break;
        }
        case '{':
        {
            size_t arend = i + 1;
            std::string to_count = "";
            while (code[arend] != '}')
                to_count += code[arend++];
            i = arend;
            arythm(to_count);
            break;
        }
        case 'B':
        {
            if (code[++i] == '[')
            {
                size_t tmp1 = i + 1;
                std::string filename = "";
                while (code[tmp1] != ']')
                    filename += code[tmp1++];
                interpret(readFile(filename));
            }
            else
            {
                std::cerr << "Error! File not found!" << std::endl;
            }
            break;
        }
        case 'S':
        {
            if (code[i + 1] == '[')
            {
                size_t tmp2 = i + 2;
                std::string times = "";
                while (code[tmp2] != ']')
                    times += code[tmp2++];
                std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(times)));
                i = tmp2;
            }
            break;
        }
        case '9':
            std::cout << static_cast<char>(array[pointerLocation] >= 0 ? array[pointerLocation] : 0);
            break;
        case 'a':
            std::cout << array[pointerLocation] << " " << static_cast<char>(array[pointerLocation] >= 0 ? array[pointerLocation] : 0) << std::endl;
            break;
        case 'e':
        {
            std::string x;
            std::cin >> x;
            try
            {
                array[pointerLocation] = std::stoi(x);
            }
            catch (const std::invalid_argument&)
            {
                array[pointerLocation] = static_cast<int>(x[0]);
            }
            break;
        }
        case '6':
        {
            if (array[pointerLocation] == 0)
            {
                int open_braces6 = 1;
                while (open_braces6 > 0)
                {
                    i += 1;
                    if (code[i] == '6')
                        open_braces6++;
                    else if (code[i] == '1')
                        open_braces6--;
                    else if (code[i] == '[')
                    {
                        int open_brackets1 = 1;
                        while (open_brackets1 > 0)
                        {
                            i += 1;
                            if (code[i] == '[')
                                open_brackets1++;
                            else if (code[i] == ']')
                                open_brackets1--;
                        }
                    }
                }
            }
            break;
        }
        case '1':
        {
            int open_braces = 1;
            while (open_braces > 0)
            {
                i -= 1;
                if (code[i] == '6')
                    open_braces--;
                else if (code[i] == '1')
                    open_braces++;
                else if (code[i] == ']')
                {
                    int open_brackets1 = 1;
                    while (open_brackets1 > 0)
                    {
                        i -= 1;
                        if (code[i] == '[')
                            open_brackets1--;
                        else if (code[i] == ']')
                            open_brackets1++;
                    }
                }
            }
            i -= 1;
            break;
        }
        case 'M':
        case 'X':
        {
            if (code[i + 1] == '[')
            {
                size_t m_start = i + 2;
                size_t m_end = m_start;
                while (code[m_end] != ']')
                    m_end++;
                int m = std::stoi(code.substr(m_start, m_end - m_start));
                if (pointerLocation + m < 0)
                {
                    std::cerr << "Error! Pointer Location is negative." << std::endl;
                    exit(EXIT_FAILURE);
                }
                if (pointerLocation + m >= array.size())
                {
                    array.resize(pointerLocation + m + 1, 0);
                }
                if (code[i] == 'M')
                {
                    std::swap(array[pointerLocation], array[pointerLocation + m]);
                }
                else
                {
                    array[pointerLocation + m] = array[pointerLocation];
                }
                i = m_end;
                pointerLocation += m;
            }
            else
            {
                std::cerr << "Error! Invalid syntax for M/X command." << std::endl;
                exit(EXIT_FAILURE);
            }
            break;
        }
        case '/':
            std::cerr << "Passed non preprocessed code!" << std::endl;
            exit(EXIT_FAILURE);
        case '_':
            return;
        case 'x':
        case 'm':
        {
            if (i + 4 < code.length() && code[i + 1] == '[' && (code[i + 2] == '+' || code[i + 2] == '-') &&
                (code[i + 3] == '0' || code[i + 3] == '1') && code[i + 4] == ']')
            {
                int target_index = 0;
                if (code[i + 2] == '+')
                {
                    target_index = array[pointerLocation + 1];
                }
                else if (code[i + 2] == '-')
                {
                    if (pointerLocation == 0)
                    {
                        std::cerr << "Error! No left cell available." << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    target_index = array[pointerLocation - 1];
                }

                if (target_index < 0)
                {
                    std::cerr << "Error! Invalid target index." << std::endl;
                    exit(EXIT_FAILURE);
                }

                if (array.size() <= target_index)
                {
                    array.resize(target_index + 1, 0);
                }

                if (code[i] == 'x')
                {
                    array[target_index] = array[pointerLocation];
                }
                else
                {
                    array[target_index] = array[pointerLocation];
                    array[pointerLocation] = 0;
                }

                if (code[i + 3] == '1')
                {
                    pointerLocation = target_index;
                }

                i += 4;
            }
            break;
        }
        case 'G':
            array[pointerLocation] = pointerLocation;
            break;
        default:
            break;
        }
        i += 1;
    }
}

void arythm(const std::string& code)
{
    int nums[1024];
    std::vector<int> actions;
    int pointnow = 0;
    bool actyes = false;

    for (char ch : code)
    {
        switch (ch)
        {
        case 'k':
            nums[pointnow++] = array[pointerLocation + 1];
            break;
        case 'i':
            nums[pointnow++] = array[pointerLocation - 1];
            break;
        case 't':
            nums[pointnow++] = array[pointerLocation];
            break;
        case '+':
            actions.push_back(1);
            actyes = true;
            break;
        case '-':
            actions.push_back(0);
            actyes = true;
            break;
        case '*':
            actions.push_back(2);
            actyes = true;
            break;
        case '%':
            actions.push_back(3);
            actyes = true;
            break;
        default:
            break;
        }
    }

    if (actyes)
    {
        switch (actions[0])
        {
        case 0:
            array[pointerLocation] = nums[0] - nums[1];
            break;
        case 1:
            array[pointerLocation] = nums[0] + nums[1];
            break;
        case 2:
            array[pointerLocation] = nums[0] * nums[1];
            break;
        case 3:
            if (nums[1] != 0)
                array[pointerLocation] = nums[0] / nums[1];
            else
            {
                std::cerr << "ERROR! Division by zero!" << std::endl;
                exit(EXIT_FAILURE);
            }
            break;
        default:
            break;
        }
    }
    else
    {
        std::cerr << "ERROR! Action not found!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ifFunc(const std::string& code)
{
    int nums[2];
    int action = 0;
    int pointnow = 0;
    bool ends = false;
    std::string execute = "";

    for (size_t i = 0; i < code.length(); i++)
    {
        switch (code[i])
        {
        case 'i':
            nums[pointnow++] = array[pointerLocation - 1];
            break;
        case 'k':
            nums[pointnow++] = array[pointerLocation + 1];
            break;
        case 't':
            nums[pointnow++] = array[pointerLocation];
            break;
        case '>':
            action = 1;
            break;
        case '<':
            action = 2;
            break;
        case '=':
            action = 0;
            break;
        case '~':
            action = 3;
            break;
        case '!':
            execute = code.substr(i + 1);
            ends = true;
            break;
        default:
            break;
        }

        if (ends)
            break;
    }

    if (ends)
    {
        switch (action)
        {
        case 0:
            if (nums[0] == nums[1])
                interpret(execute);
            break;
        case 1:
            if (nums[0] > nums[1])
                interpret(execute);
            break;
        case 2:
            if (nums[0] < nums[1])
                interpret(execute);
            break;
        case 3:
            if (nums[0] != nums[1])
                interpret(execute);
            break;
        default:
            std::cerr << "Error! Unknown action in ifFunc!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "Error! If without body!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int mode = 0;
    std::cout << "Mode(1 - compiler, 2 - interpreter): ";
    std::cin >> mode;
    std::cin.ignore();

    if (mode == 1)
    {
        std::cout << "Welcome to Better Cookie961 language Compiler v3.7" << std::endl;
        std::string foil;
        std::cout << "File Name: ";
        std::cin >> foil;
        if (endsWith(foil, ".bc961"))
        {
            interpret(readFile(foil));
            std::cout << std::endl;
            std::cout << "Paused. Press Enter to exit." << std::endl;
            std::cin.get();
        }
        else
        {
            std::cerr << "Error! Unknown extension." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cout << "Welcome to Better Cookie961 language Shell v3.7" << std::endl;
        std::string code;
        std::cout << "Code: ";
        std::getline(std::cin, code);
        interpret(code);
        std::cout << std::endl;

        system("pause");
    }

    return 0;
}
