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


int getCount(unordered_map<int, int> &store, int value, vector<int> &dist2) {
    if (store.find(value) != store.end()) {
        int count = store[value];
        cout << value << " " << count << endl;
        return count;
    }
    // iterate through dist2 vector
    int count = 0;
    for (int value2: dist2) {
        if (value2 == value) {
            count++;
        }
        if (value2 > value) {
            break;
        }
    }
    store[value] = count;
    return count;
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

    sort(dist2.begin(), dist2.end());

    // create hashmap to store values int
    unordered_map<int, int> store;

    int total = 0;
    // iterate through dist1 vector
    for (int value: dist1) {
        int count = getCount(store, value, dist2);

        total += value * count;
        cout << value << " " << count << endl;
    }
    cout << total;
    f.close();
    return 0;
}
