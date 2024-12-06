//
// Created by Oguz Kazkayasi on 4.12.2024.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include "main.h"

using namespace std;

string *splitWords(string &line) {
    auto *words = new string[2];

    istringstream iss(line);
    string token;
    int i = 0;
    while (iss >> token) {
        if (!token.empty()) {
            words[i] = token;
            i++;
        }
    }
    return words;
}


int main() {
    // open the text file
    ifstream f("01_input.txt");

    // check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file";
        return 1;
    }

    // string variable to store the data
    string s;
    vector<int> dist1;
    vector<int> dist2;

    // read each line and print to std output stream
    while (getline(f, s)) {
        string *words = splitWords(s);
        cout << stoi(words[0]) << " and " << stoi(words[1]) << endl;
        dist1.push_back(stoi(words[0]));
        dist2.push_back(stoi(words[1]));
        delete[] words;
    }

    sort(dist1.begin(), dist1.end());
    sort(dist2.begin(), dist2.end());

    int total = 0;
    // iterate through vector
    for (int i = 0; i < dist1.size(); i++) {
        int temp = dist1.at(i) - dist2.at(i);
        // get absolute value of temp
        temp = abs(temp);
        if (temp > 0) {
            total += temp;
        }
    }

    cout << total;
    f.close();
    return 0;
}
