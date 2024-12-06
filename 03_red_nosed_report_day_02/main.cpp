//
// Created by Oguz Kazkayasi on 4.12.2024.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include "main.h"

using namespace std;

vector<int> *splitLineByWhitespace(const string &line) {
    vector<int> *words = new vector<int>();
    istringstream iss(line);
    string word;
    while (iss >> word) {
        words->push_back(stoi(word));
    }
    return words;
}

bool isSafe(vector<int> *words) {
    int SAFE_LEVEL = 3;
    if (words->size() < 2) {
        return false;
    }

    bool isIncreasing = words->at(0) < words->at(1);
    for (size_t i = 1; i < words->size(); ++i) {
        int first = words->at(i - 1);
        int second = words->at(i);

        if (first == second || (isIncreasing && first > second) || (!isIncreasing && first < second)) return false;

        if (isIncreasing) {
            if (first + SAFE_LEVEL < second) {
                return false;
            }
        } else {
            if (first - SAFE_LEVEL > second) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    // open the text file
    ifstream f("input.txt");

    // check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file";
        return 1;
    }

    // string variable to store the data
    string s;
    // read each line and print to std output stream
    vector<int> *words;
    int count = 0;
    while (getline(f, s)) {
        words = splitLineByWhitespace(s);
        if (isSafe(words)) {
            cout << "safe" << endl;
            count++;
        } else {
            cout << "unsafe" << endl;
        }
        delete words;
    }
    cout << count;

    f.close();
    return 0;
}
