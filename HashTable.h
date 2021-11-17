#pragma once
#include <iostream>
#include <string>
using namespace std;

class HashTable{
public:
    HashTable();

    HashTable(int n);

    HashTable(const HashTable &hash);

    ~HashTable();

    HashTable &operator=(const HashTable &hash);

    void insert(string data);

    bool find(string data) const;

    int size() const;

    int maxSize() const;

    double loadFactor();

    void print() const;

private:
    string *array;

    int arraySize;

    int len;

    int firstPrime2;

    int hash(int strValue) const;

    int hash2(int strValue) const;

    int setP2();

    bool isPrime(int n) const;

    int prime(int n) const;

    int calculateStringValue(string str) const;

    void innerInsert(string data);
};
