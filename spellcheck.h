#pragma once
#include <iostream>
#include <vector>
#include "HashTable.h"
#include <algorithm>
using namespace std;

//if word is not in dict returns all strings in dict that can be made by deleting a single letter from word
vector<string> extraLetter(const HashTable &dict, string word){
    vector<string> result;
    if(dict.find(word)){
        result.push_back(word);
        return result;
    }
    for(int i = 0; i < word.size(); ++i){
        string str = word;
        str.replace(i, 1, "");
        if(dict.find(str)){
            result.push_back(word);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

//if word is not in dict returns all strings in dict that can be made swapping any two adjacent letters in word
vector<string> transposition(const HashTable &dict, string word){
    vector<string> result;
    if(dict.find(word)){
        result.push_back(word);
        return result;
    }
    if(word.size() >= 2){
        for(int i = 0; i < word.size() - 1; ++i) {
            string str = word;
            char character = str[i];
            str[i] = str[i + 1];
            str[i + 1] = character;
            if(dict.find(str)){
                result.push_back(str);
            }
        }
    }
    sort(result.begin(), result.end());
    return result;
}

//if word is not in dict returns all pairs of strings in dict that can be made by inserting a single space in word
vector<string> missingSpace(const HashTable &dict, string word){
    vector<string> result;
    if(dict.find(word)){
        result.push_back(word);
        return result;
    }
    if(word.size() < 2){
        return result;
    }
    for(int i = 1; i < word.size(); ++i){
        string str1 = word.substr(0, i);
        string str2 = word.substr(i);
        //each string in the result should consist of the two strings from dict separated by a space
        if(dict.find(str1) && dict.find(str2)){
            result.push_back(str1 + " " + str2);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

//if word is not in dict returns all strings in dict that can be made by inserting any single letter of the alphabet at any position in word
vector<string> missingLetter(const HashTable &dict, string word) {
    vector<string> result;
    if(dict.find(word)){
        result.push_back(word);
        return result;
    }
    for(int i = 0; i <= word.size(); ++i){
        for(int j = 0; j < 26; ++j){
            string str(1, 'a' + j);
            string words = word;
            words.insert(i, str);
            if(dict.find(words)){
                result.push_back(words);
            }
        }
    }
    sort(result.begin(), result.end());
    return result;
}

//if word is not in dict returns all strings in dict that can be made by changing any single letter of word to a different letter in the alphabet
vector<string> incorrectLetter(const HashTable &dict, string word){
    vector<string> result;
    if(dict.find(word)){
        result.push_back(word);
        return result;
    }
    for(int i = 0; i < word.size(); ++i){
        for(int j = 0; j < 26; ++j){
            string str(1, 'a' + j);
            string words = word;
            words.replace(i, 1, str);
            if(dict.find(words)){
                result.push_back(words);
            }
        }
    }
    sort(result.begin(), result.end());
    return result;
}
