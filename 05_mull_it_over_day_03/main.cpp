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

vector<string> *splitLineByWord(const string &line, const string &delimiter) {
    vector<string> *words = new vector<string>();
    size_t start = 0;
    size_t end = line.find(delimiter);

    while (end != string::npos) {
        words->push_back(line.substr(start, end - start));
        start = end + delimiter.length();
        end = line.find(delimiter, start);
    }
    words->push_back(line.substr(start));
    return words;
}

vector<string> *splitIntoTwo(const string &word, const string &delimiter) {
    vector<string> *words = new vector<string>();

    size_t start = 0;
    size_t end = word.find(delimiter);

    if (end != string::npos) {
        words->push_back(word.substr(start, end - start));
        words->push_back(word.substr(end + delimiter.length()));
    } else {
        words->push_back(word);
        words->push_back("");
    }
    return words;

}

// https://stackoverflow.com/a/4654718/4379563
bool isInteger(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int calculateLine(string &s) {
    int total = 0;
    vector<string> *splittedWords = splitLineByWord(s, "mul(");
    for (const auto &splittedWord: *splittedWords) {
        vector<string> *rest = splitLineByWord(splittedWord, ")");
        string inParenthesis = rest->at(0);

        vector<string> *nums = splitLineByWord(inParenthesis, ",");
        if (nums->size() != 2) {
            continue;
        }
        // check if string is number
        if (!isInteger(nums->at(0)) || !isInteger(nums->at(1))) {
            continue;
        }
        int first = stoi(nums->at(0));
        int second = stoi(nums->at(1));
        cout << first << " * " << second << " = " << first * second << endl;
        total += first * second;
        delete rest;
        delete nums;
    }
    return total;
}

int calculateSection(string &s) {
    int total = 0;
    vector<string> *dividedByDont = splitIntoTwo(s, "don't()");
    string first = dividedByDont->at(0);
    string second = dividedByDont->at(1);
    delete dividedByDont;
    if (!first.empty()) {
        int firstValue = calculateLine(first);
        total += firstValue;
        vector<string> *dividedByDo = splitIntoTwo(second, "do()");
        string newSecond = dividedByDo->at(1);
        delete dividedByDo;
        if (!newSecond.empty()) {
            total += calculateSection(newSecond);
        }
    } else {
        total += 0;
    }
    return total;
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
    string allString;
    // read each line and print to std output stream
    while (getline(f, s)) {
        allString += s;
    }
    int total = calculateSection(allString);
    cout << "total: " << total;

    f.close();
    return 0;
}
