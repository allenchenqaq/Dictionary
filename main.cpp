#include "HashTable.h"
#include "spellcheck.h"
#include <fstream>

using std::ifstream;

void readFromFile(const string& filename, vector<string>& ret) {
    ifstream inFile;
    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "error" << endl;
    }
    string tmp;
    while (inFile >> tmp) {
        ret.push_back(tmp);
    }
    inFile.close();
}

void printVec(const vector<string>& vs) {
    cout << "vector size: " << vs.size() << endl;
    int cnt = 0;
    for (auto& ele : vs) {
        cout << ele << " ";
        cnt++;
        if (cnt == 10) {
            cnt = 0;
            cout << endl;
        }
    }
    cout << endl;
}

void testHashTable()
{
    vector<string> vs;
    string filename = "wordlist1000.txt";
    readFromFile(filename, vs);
    cout << "load file done!" << endl;
    cout << "===================TEST DEFAULT CONSTRUCTOR===================" << endl;
    HashTable ht1;
    for (int i = 0; i < 10; i++)
    {
        ht1.insert(vs[i]);
    }
    ht1.print();
    cout << "==================sample out put================== \nindex: 1 string: a\nindex: 5 string : across\nindex: 19 string : accept\nindex: 29 string : act\nindex: 37 string : account\nindex: 57 string : able\nindex: 75 string : about\nindex: 90 string : ability\nindex: 92 string : above\nindex: 94 string : according" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "===================TEST COPY CONSTRUCTOR===================" << endl;
    HashTable ht2(ht1);
    ht2.print();
    cout << "==================sample out put================== \nindex: 1 string: a\nindex: 5 string : across\nindex: 19 string : accept\nindex: 29 string : act\nindex: 37 string : account\nindex: 57 string : able\nindex: 75 string : about\nindex: 90 string : ability\nindex: 92 string : above\nindex: 94 string : according" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "===================TEST OVERLOAD OPERATOR===================" << endl;
    HashTable ht3;
    for (int i = 0; i < 15; i++)
    {
        ht3.insert(vs[i]);
    }
    ht1 = ht3;
    ht1.print();
    cout << "==================sample out put=================="<<endl;
    ht3.print();
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "===================TEST FIND FUNCTION===================" << endl;
    cout << ht2.find("according") << ht3.find("to") << ht2.find("that") << ht1.find("book");
    cout << ht1.find("Eric") <<ht3.find("act")<< ht1.find("as") << ht2.find("Your") << ht3.find("father") << endl;
    cout << "==================sample out put==================" << endl;
    cout << "100001000" << endl;
    cout << endl;
    cout << endl;
    cout << "===================TEST SECOND HASH FUNCTION===================" << endl;
    HashTable ht4;
    for (int i = 0; i < 150; i++)
    {
        ht4.insert(vs[i]);
    }
    HashTable ht5;
    for (int i = 0; i < 650; i++)
    {
        ht5.insert(vs[i]);
    }
    cout << "After insert 150 strings, size of the underlying array=" << ht4.size() << ", current number of items=" << ht4.maxSize() << ", loadFactor=" << ht4.loadFactor() << endl;
    cout << "After insert 650 strings, size of the underlying array=" << ht5.size() << ", current number of items=" << ht5.maxSize() << ", loadFactor=" << ht5.loadFactor() << endl;
    cout << "==================sample out put==================" << endl;
    cout << "After insert 150 strings, size of the underlying array=150, current number of items=431, loadFactor=0.348028" << endl;
    cout<<"After insert 650 strings, size of the underlying array=650, current number of items=1733, loadFactor=0.375072"<<endl;
    cout << endl;
    cout << endl;
}
void testspellcheck()
{
    vector<string> vs;
    string filename = "wordlist1000.txt";
    readFromFile(filename, vs);
    cout << "load file done!" << endl;
    HashTable tab;
    for (auto& ele : vs) {
        tab.insert(ele);
    }
    cout << "After insert the whole txt: " << endl;
    cout << "ori size :" << vs.size() << endl;
    cout << "size :" << tab.size() << endl;
    cout << "maxSize :" << tab.maxSize() << endl;
    cout << "loadFactor :" << tab.loadFactor() << endl;
    cout << "==================sample out put==================" << endl;
    cout << "ori size :991"<< endl;
    cout << "size :991" << endl;
    cout << "maxSize :1733"<< endl;
    cout << "loadFactor :0.571841"<< endl;

    cout << "===================TEST EXTRALETTER===================" << endl;
    string extraLetter1 = "ats";
    string extraLetter2 = "life";
    vector<string> et1 = extraLetter(tab, extraLetter1);
    vector<string> et2 = extraLetter(tab, extraLetter2);
    printVec(et1);
    printVec(et2);
    cout << endl;

    cout << "===================TEST TRANSPOSITION===================" << endl;
    string transposition1 = "atr";
    string transposition2 = "tar";
    auto tr1 = transposition(tab, transposition1);
    auto tr2 = transposition(tab, transposition2);
    printVec(tr1);
    printVec(tr2);
    cout << endl;

    cout << "===================TEST MISSINGSPACE===================" << endl;
    string missingSpace1 = "rateat";
    string missingSpace2 = "nomoney";
    auto ms1 = missingSpace(tab, missingSpace1);
    auto ms2 = missingSpace(tab, missingSpace2);
    printVec(ms1);
    printVec(ms2);
    cout << endl;

    cout << "===================TEST MISSINGLETTER===================" << endl;
    string missingLetter1 = "ou";
    string missingLetter2 = "noice";
    auto ml1 = missingLetter(tab, missingLetter1);
    auto ml2 = missingLetter(tab, missingLetter2);
    printVec(ml1);
    printVec(ml2);
    cout << endl;

    cout << "===================TEST INCORRECT===================" << endl;
    string incorrect1 = "thed";
    string incorrect2 = "aga";
    auto ic1 = incorrectLetter(tab, incorrect1);
    auto ic2 = incorrectLetter(tab, incorrect2);
    printVec(ic1);
    printVec(ic2);

    /*===================TEST EXTRALETTER===================
    vector size: 2
    as at
    vector size: 1
    life

    ===================TEST TRANSPOSITION===================
    vector size: 1
    art
    vector size: 0


    ===================TEST MISSINGSPACE===================
    vector size: 2
    rate at
    vector size: 2
    no money

    ===================TEST MISSINGLETTER===================
    vector size: 3
    you our out
    vector size: 1
    notice

    ===================TEST INCORRECT===================
    vector size: 3
    them then they
    vector size: 2
    age ago*/
}

int main() {
    testHashTable(); 
    testspellcheck();
    system("pause");
    return 0;
}

