//
// Created by Oguz Kazkayasi on 4.12.2024.
//
#include "main.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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

        if (first == second || (isIncreasing && first > second) ||
            (!isIncreasing && first < second))
            return false;

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

bool isSafeTolerated(vector<int> *words) {
    if(isSafe(words)) return true;
    // iterate through array
    for(int i = 0; i < words->size(); i++) {
        vector<int> modified;
        for(int j = 0; j < words -> size(); j++){
            if(i != j) {
                modified.push_back(words->at(j));
            }
        }
        if(isSafe(&modified)) return true;
    }
    return false;

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
        if (isSafeTolerated(words)) {
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
