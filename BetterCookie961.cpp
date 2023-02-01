#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

bool endsWith(std::string const& str, std::string const& suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
    if (!f.is_open())
    {
        cout << "Error! File not found!" << endl;
        exit(0);
    }
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string s;
    s.resize(size);
    f.seekg(0);
    f.read(&s[0], size);
    return s;
}

void interpret(string code) {
    vector<int> array = { 0 };
    int pointerLocation = 0;
    int i = 0;
    int c = 0;
    while (i < code.length()) {
        if (code[i] == 'i') {
            if (pointerLocation > 0) {
                pointerLocation -= 1;
            }
        }
        else if (code[i] == 'k') {
            pointerLocation += 1;
            if (array.size() <= pointerLocation) {
                array.push_back(0);
            }
        }
        else if (code[i] == 'c') {
            array[pointerLocation] += 1;
        }
        else if (code[i] == 'o') {
            if (array[pointerLocation] > 0) {
                array[pointerLocation] -= 1;
            }
        }
        else if (code[i] == '9') {
            cout << array[pointerLocation] << " " << char(array[pointerLocation]) << endl;
        }
        else if (code[i] == 'e') {
            string x;
            cin >> x;
            int y;
            try {
                y = stoi(x);
            }
            catch (invalid_argument) {
                y = int(x[0]);
            }
            array[pointerLocation] = y;
        }
        else if (code[i] == '6') {
            if (array[pointerLocation] == 0) {
                int open_braces = 1;
                while (open_braces > 0) {
                    i += 1;
                    if (code[i] == '6') {
                        open_braces += 1;
                    }
                    else if (code[i] == '1') {
                        open_braces -= 1;
                    }
                }
            }
        }
        else if (code[i] == '1') {
            int open_braces = 1;
            while (open_braces > 0) {
                i -= 1;
                if (code[i] == '6') {
                    open_braces -= 1;
                }
                else if (code[i] == '1') {
                    open_braces += 1;
                }
            }
            i -= 1;
        }
        i += 1;
    }
}

int main()
{
    int mode = 0;
    cout << "Mode(1 - compiler, 2 - interpreter): ";
    cin >> mode;
    if (mode == 1)
    {
        cout << "Welcome to Better Cookie961 language Compiler v1.0" << endl;
        cout << " " << endl;
        string foil;
        cout << "File Name: ";
        cin >> foil;
        if (endsWith(foil, ".bc961"))
        {
            interpret(readFile(foil));
            system("pause");
        }
        else
        {
            cout << "Error! Unknown extension.";
            exit(0);
        }
    }
    else
    {
        cout << "Welcome to Better Cookie961 language Shell v1.0" << endl;
        cout << " " << endl;
        while (true)
        {
            string code;
            cout << "Code: ";
            cin >> code;
            interpret(code);
        }
    }

    return 0;
}