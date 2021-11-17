#include "HashTable.h"
#include <cmath>

//default constructor
HashTable::HashTable(){
    //creates a hash table of default size: 101
    arraySize = 101;
    array = new string[arraySize];
    //sets all array elements to the empty string ("")
    for(int i = 0; i < arraySize; i++)
        array[i] = "";
    len = 0;
    //sets P2, the value used by h2
    setP2();
}

//constructor
HashTable::HashTable(int n){
    //creates a hash table to store n items where the value of n is given by the constructor's single integer parameter
    arraySize = prime(n);
    array = new string[arraySize];
    //sets all array elements to the empty string
    for(int i = 0; i < arraySize; i++){
        array[i] = "";
    }
    len = 0;
    //sets the value for P2 that is used by h2
    setP2();
}

//a constructor that creates a deep copy of its HashTable reference parameter
HashTable::HashTable(const HashTable &hash){
    arraySize = hash.arraySize;
    array = new string[arraySize];
    for(int i = 0; i < arraySize; i++){
        array[i] = hash.array[i];
    }
    len = hash.len;
    firstPrime2 = hash.firstPrime2;
}

//de-allocates any dynamic memory associated with the calling object
HashTable::~HashTable(){
    delete[] array;
}

//overloads the assignment operator for HashTable objects
HashTable &HashTable::operator=(const HashTable &hash){
    if(this != &hash){
        delete[] array;
        //makes the calling object a deep copy of its HashTable reference parameter
        len = hash.len;
        arraySize = hash.arraySize;
        array = new string[arraySize];
        for(int i = 0; i < arraySize; i++){
            array[i] = hash.array[i];
        }
        firstPrime2 = hash.firstPrime2;
    }
    //returns a reference to the calling object
    return *this;
}


void HashTable::insert(string data){
    //searches the hash table for the method's string parameter, if a matching string is not found it inserts the parameter string into the hash table
    if(!find(data)){
        innerInsert(data);
        if(loadFactor() > 0.67){
            //expand to twice the size
            int oldSize = arraySize;
            arraySize = prime(oldSize);
            len = 0;
            //sets the value used by h2
            setP2();
            string *temp = array;
            array = new string[arraySize];
            for(int i = 0; i < arraySize; i++){
              array[i] = "";
            }
            //inserts the original contents in the new table at the appropriate places
            for(int i = 0; i < oldSize; i++){
                if(temp[i] != "") {
                  innerInsert(temp[i]);
                }
            }
            delete[] temp;
        }
    }
}

//helper method for insert
void HashTable::innerInsert(string data){
    int strVal = calculateStringValue(data);
    int hashedIndex = hash(strVal);
    while(array[hashedIndex] != ""){
        hashedIndex = (hashedIndex + hash2(strVal)) % arraySize;
    }
    array[hashedIndex] = data;
    len++;
}

//returns true if its string parameter is in the hash table, returns false if it is not
bool HashTable::find(string data) const{
    int strVal = calculateStringValue(data);
    int index = hash(strVal);
    for(int i = 0; i < arraySize; ++i){
        if(data == array[index]){
            return true;
        } 
        else if(array[index] == ""){
            return false;
        }
        index += hash2(strVal);
        index = index % arraySize;
    }
    return false;
}

//returns the number of items stored in the hash table
int HashTable::size() const{
    return len;
}

//returns the size of the hash table’s underlying array
int HashTable::maxSize() const{
    return arraySize;
}

//returns the load factor of the hash table as a double
double HashTable::loadFactor(){
    return (len * 1.0) / (arraySize * 1.0);
}

//calculate the value of the string
int HashTable::calculateStringValue(string str) const{
    int res = 0;
    for(int i = 0; i < str.size() - 1; ++i){
      res = (res + (str[i] - 96)) * 32 % arraySize;
    }
    res = (res + (str[str.size() - 1] - 96)) % arraySize;
    return res;
}

//hash function
int HashTable::hash(int strValue) const{
    return strValue % arraySize;
}

//second hash function for collisions
int HashTable::hash2(int strValue) const{
    return firstPrime2 - (strValue % firstPrime2);
}

//set the first prime number greater than arraySize/2
int HashTable::setP2(){
    firstPrime2 = arraySize / 2 + 1;
    while(!isPrime(firstPrime2)){
        firstPrime2++;
    }
    return firstPrime2;
}

//check if its a prime number
bool HashTable::isPrime(int n) const{
    if(n >= 2) {
        for(int i = 2; i <= sqrt(n); i++){
            if(n % i == 0)
                return false;
        }
        return true;
    }
    return false;
}

//smallest prime number equal to or greater than 2n
int HashTable::prime(int n) const{
    int num = n * 2;
    while(!isPrime(num)){
        num++;
    }
    return num;
}


void HashTable::print() const{
    cout << "items:" << endl;
    for(int i = 0; i < arraySize; ++i){
        if(array[i] != "") {
            cout << i << " : " << array[i] << endl;
        }
    }
}