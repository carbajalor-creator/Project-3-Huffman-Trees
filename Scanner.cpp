//
// Created by Ali Kooshesh on 9/27/25.
//

#include "Scanner.hpp"

#include <utility>
#include <iostream>
#include <fstream>
#include <cctype>
#include "utils.hpp"
#include <filesystem>
#include "bst.hpp"

Scanner::Scanner(std::filesystem::path inputPath)
    : inputPath_(std::move(inputPath)) {}

bool Scanner::isLetter(char c) {
    if (isalpha(c)) { //makes sure letter is a valid letter with no accent
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            return true;
        }
    }
    return false;
}


void Scanner::flushToken (std::string& token, std::vector<std::string>& words) {
    for (char& c : token) { //makes sure that all tokens are lowercase
        c = std::tolower(static_cast<unsigned char>(c));
    }
    if (!token.empty()) {
        words.push_back(token); //adds cleaned up tokens to words vector
    }
    token.clear();
}

error_type Scanner::tokenize(std::vector<std::string>& words) {
    std::ifstream inFile(inputPath_);
    if (!inFile) { //opening file
        return UNABLE_TO_OPEN_FILE;
    }
    //std::string token;
    while (true) { //loop takes in words and runs them through flushToken
        std::string token = readWord(inFile);
        if (token.empty() && inFile.eof()) {
            break;
        }
        if (!token.empty()) { //makes sure they are cleaned up
            flushToken(token, words);
        }
    }
    return NO_ERROR;
}

error_type Scanner::tokenize(std::vector<std::string>& words,
                                const std::filesystem::path& outputFile) {
    error_type result = tokenize(words);
    if (result != NO_ERROR) {
        return result;
    }
    std::ofstream outFile(outputFile); //opening output file
    if (!outFile) {
        return UNABLE_TO_OPEN_FILE;
    }
    for (const auto& word : words) {
        std::string lowered;
        for (const auto& c : word) {
            lowered += tolower(c); //catches any letters that haven't been lowercased and lowers them
        }
        outFile << lowered << std::endl; //sends tokens to output file
    }
    return error_type::NO_ERROR;
}

std::string Scanner::readWord(std::istream &in) {
    std::string token;
    char c;

    while (in.get(c)) { //reads in letters and adds them to token if valid letter
        if (isLetter(c)) {
            token += c;
        }
        else if (c == '\'') { //checks previous letter and next letter to add apostrophe if it is between letters
            char next = in.peek();
            if (!token.empty() && isLetter(token.back()) && isLetter(next)) {
                    token += c;
            }
            else if (!token.empty()) {
                token += c;
            }
        }
        else {
            if (!token.empty()) {
                break;
            }
        }
    }
    return token;
}

