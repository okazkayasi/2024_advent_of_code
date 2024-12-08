//
// Created by Oguz Kazkayasi on 4.12.2024.
//
#include "main.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

int countHorizontalWords(const string &line, const string &word) {
    int count = 0;
    size_t pos = 0;
    while ((pos = line.find(word, pos)) != string::npos) {
        ++count;
        pos += word.size();
    }
    return count;
}

vector<string> *createVerticalWords(const vector<string> &lines) {
    vector<string> *verticalWords = new vector<string>();
    for (int i = 0; i < lines.size(); i++) {
        string verticalWord = "";
        verticalWords->push_back(verticalWord);
    }
    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];
        for (int j = 0; j < lines.size(); j++) {
            verticalWords->at(j) += line[j];
        }
    }
    return verticalWords;
}


vector<string> *
createDiagonalLeftTopToRightBottomWords(const vector<string> &lines) {
    auto *diagonalWords = new vector<string>();
    for (int vi = 0; vi < lines.size(); ++vi) {
        const string &line = lines[vi];
        for (int hi = 0; hi < line.size(); ++hi) {
            string word;
            int i = vi;
            int j = hi;
            int lengthOfWord = 0;
            while (j < line.size() && i < lines.size() && lengthOfWord < 4) {
                const string &lineToUse = lines[i];
                word += lineToUse[j];
                i++;
                j++;
                lengthOfWord++;
            }
//            cout << word << endl;
            if (word.size() >= 4) {
                diagonalWords->push_back(word);
            }
        }
    }
    return diagonalWords;
}


vector<string> *
createDiagonalRightTopToLeftBottomWords(const vector<string> &lines) {
    auto *diagonalWords = new vector<string>();
    for (int vi = 0; vi < lines.size(); ++vi) {
        const string &line = lines[vi];
        for (int hi = line.size() - 1; hi >= 0; --hi) {
            string word;
            int i = vi;
            int j = hi;
            int lengthOfWord = 0;
            while (j >= 0 && i < lines.size() && lengthOfWord < 4) {
                const string &lineToUse = lines[i];
                word += lineToUse[j];
                i++;
                j--;
                lengthOfWord++;
            }
//            cout << word << " yes" << endl;
            if (word.size() >= 4) {
                diagonalWords->push_back(word);
            }
        }
    }
    return diagonalWords;
}

int countXMas(vector<string> &lines) {
    int count = 0;
    for (int i = 0; i < lines.size(); i++) {
        const string &line = lines[i];
        for (int j = 0; j < line.size(); ++j) {
            int lastVertInd = line.size() - 1;
            if (line[j] == 'X') {
                // find horizontal
                if (j + 3 <= lastVertInd && line[j + 1] == 'M' && line[j + 2] == 'A' && line[j + 3] == 'S') {
                    count++;
                }
                // find horizontal reverse
                if (j - 3 >= 0 && line[j - 1] == 'M' && line[j - 2] == 'A' && line[j - 3] == 'S') {
                    count++;
                }

                // find vertical
                if (i + 3 <= lines.size() - 1 && lines[i + 1][j] == 'M' && lines[i + 2][j] == 'A' &&
                    lines[i + 3][j] == 'S') {
                    count++;
                }

                // find vertical reverse
                if (i - 3 >= 0 && lines[i - 1][j] == 'M' && lines[i - 2][j] == 'A' && lines[i - 3][j] == 'S') {
                    count++;
                }

                // find left top - right bottom diagonal
                if (j + 3 <= lastVertInd && i + 3 <= lines.size() - 1 &&
                    lines[i + 1][j + 1] == 'M' && lines[i + 2][j + 2] == 'A' && lines[i + 3][j + 3] == 'S') {
                    count++;
                }

                // find right top - left bottom diagonal
                if (j - 3 >= 0 && i - 3 >= 0 &&
                    lines[i - 1][j - 1] == 'M' && lines[i - 2][j - 2] == 'A' && lines[i - 3][j - 3] == 'S') {
                    count++;
                }

                // find left bottom - right top diagonal
                if (i - 3 >= 0 && j + 3 <= lastVertInd &&
                    lines[i - 1][j + 1] == 'M' && lines[i - 2][j + 2] == 'A' && lines[i - 3][j + 3] == 'S'
                        ) {
                    count++;
                }

                // find right bottom - left top diagonal
                if (i + 3 <= lines.size() - 1 && j - 3 >= 0 &&
                    lines[i + 1][j - 1] == 'M' && lines[i + 2][j - 2] == 'A' && lines[i + 3][j - 3] == 'S'
                        ) {
                    count++;
                }
            }
        }
    }
    return count;
}

int countXShapedMas(vector<string> &lines) {
    int count = 0;
    for (int i = 0; i < lines.size(); i++) {
        const string &line = lines[i];
        for (int j = 0; j < line.size(); j++) {
            if (line[j] == 'A' && i >= 0 && j >= 0 && i <= lines.size() - 2 && j <= line.size() - 2) {
                char lt = lines[i - 1][j - 1];
                char rt = lines[i - 1][j + 1];
                char lb = lines[i + 1][j - 1];
                char rb = lines[i + 1][j + 1];
                if (((lt == 'M' && rb == 'S') || (lt == 'S' && rb == 'M')) &&
                    ((lb == 'M' && rt == 'S') || (lb == 'S' && rt == 'M'))
                        ) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    // open the text file
    ifstream f2("input.txt");
    vector<string> lines2;
    string s2;
    // read each line and print to std output stream
    while (getline(f2, s2)) {
        lines2.push_back(s2);
    }

    // v1
    int totalXMas = countXMas(lines2);
    cout << totalXMas << endl;

    // v2
    int totalXShapedMAS = countXShapedMas(lines2);
    cout << totalXShapedMAS << endl;


    f2.close();
    return 0;
}
