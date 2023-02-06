#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

bool endsWith(string const& str, string const& suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

string readFile(const string& fileName) {
    ifstream f(fileName);
    if (!f.is_open())
    {
        cout << "Error! File not found!" << endl;
        exit(0);
    }
    f.seekg(0, ios::end);
    size_t size = f.tellg();
    string s;
    s.resize(size);
    f.seekg(0);
    f.read(&s[0], size);
    return s;
}

void ifFunc(string code, vector<int>& array, int pl);

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
        else if (code[i] == 'I') {
            if (pointerLocation > 0) {
                pointerLocation -= 1;
                array[pointerLocation] += array[pointerLocation + 1];
            }
        }
        else if (code[i] == 'k') {
            pointerLocation += 1;
            if (array.size() <= pointerLocation) {
                array.push_back(0);
            }
        }
        else if (code[i] == 'K') {
            pointerLocation += 1;
            if (array.size() <= pointerLocation) {
                array.push_back(0);
            }
            array[pointerLocation] += array[pointerLocation - 1];
        }
        else if (code[i] == 'c') {
            array[pointerLocation] += 1;
        }
        else if (code[i] == 'C') {
            array[pointerLocation] += 10;
        }
        else if (code[i] == 'o') {
            if (array[pointerLocation] > 0) {
                array[pointerLocation] -= 1;
            }
        }
        else if (code[i] == 'O') {
            if (array[pointerLocation] > 10) {
                array[pointerLocation] -= 10;
            }
        }
        else if (code[i] == 'L')
        {
            array[pointerLocation] = 0;
        }
        else if (code[i] == '(') {
            int ifend = i + 1;
            string to_execute = "";
            while (code[ifend] != ')') {
                to_execute += code[ifend];
                ifend++;
                i++;
            }
            ifFunc(to_execute, array, pointerLocation);
        }
        else if (code[i] == '9') {
            cout << char(array[pointerLocation]);
        }
        else if (code[i] == 'a') {
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
    cout << " " << endl;
}

void ifFunc(string code, vector<int>& array, int pl) {
    int nums[2];
    int action = 0;
    int pointnow = 0;
    bool ends = false;
    string execute = "";
    for (int i = 0; i < code.length(); i++) {
        if (code[i] == 'i') {
            nums[pointnow] = array[pl - 1];
            pointnow += 1;
        }
        else if (code[i] == 'k') {
            nums[pointnow] = array[pl + 1];
            pointnow += 1;
        }
        else if (code[i] == 't') {
            nums[pointnow] = array[pl];
            pointnow += 1;
        }
        else if (code[i] == '>') {
            action = 1;
        }
        else if (code[i] == '<') {
            action = 2;
        }
        else if (code[i] == '=') {
            action = 0;
        }
        else if (code[i] == '!') {
            execute = code.substr(i + 1, code.length());
            bool anif1 = false;
            bool anif2 = false;
            for (int p = 0; p < execute.length(); p++) {
                if (execute[p] == '(') {
                    anif1 = true;
                    for (int j = 0; j < execute.length(); j++) {
                        if (execute[j] == ')') {
                            anif2 = true;
                        }
                    }
                }
            }
            if (anif1 == true && anif2 == false)
            {
                execute += ')';
            }
            ends = true;
            break;
        }
    }
    if (ends == true) {
        if (action == 0) {
            if (nums[0] == nums[1]) {
                interpret(execute);
            }
        }
        else if (action == 1) {
            if (nums[0] > nums[1]) {
                interpret(execute);
            }
        }
        else if (action == 2) {
            if (nums[0] < nums[1]) {
                interpret(execute);
            }
        }
    }
    else {
        cout << "Error! If without body!" << endl;
    }
}

int main()
{
    int mode = 0;
    cout << "Mode(1 - compiler, 2 - interpreter): ";
    cin >> mode;
    if (mode == 1)
    {
        cout << "Welcome to Better Cookie961 language Compiler v2.0" << endl;
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
        cout << "Welcome to Better Cookie961 language Shell v2.0" << endl;
        cout << " " << endl;
        while (true)
        {
            string code;
            cout << "Code: ";
            getline(cin, code);
            interpret(code);
        }
    }

    return 0;
}
