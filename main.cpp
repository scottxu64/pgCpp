#include <iostream>
#include <fstream>
#include <time.h>

#include "Person.h"
#include "Team.h"

#include "Worker.h"
#include "Chef.h"
#include "Driver.h"

using namespace std;

// pointer
void pgPointer()
{
    string name = "foo";
    string *pName = &name;

    cout << pName << endl;  // 0x61fdd0
    cout << *pName << endl; // foo

    cout << *&name << endl; // foo

    int arr[10];
    int *pArr0 = &arr[0];
    int *pArr1 = &arr[1];
    int *pArr2 = &arr[2];
    int *pArr3 = &arr[3];

    cout << "pArr0 before +2 " << pArr0 << endl; // 0x63fd60
    cout << "pArr2 " << pArr2 << endl;           // 0x63fd68
    pArr0 = pArr0 + 2;                           // pointer doesn't do math +2, but move pointer by +2
    cout << pArr0 << endl;                       // 0x63fd68, same as pArr2
}


// class
class Book
{
private:
    string genre;

public:
    string title;
    string author;
    int pages;

    string toString()
    {
        return "title: " + title + ", author: " + author + ", pages: " + std::to_string(pages);
    }

    // constructors
    Book()
    {
    }

    Book(string _title, string _author, int _pages)
    {
        title = _title; // notice do not use: this.title = title;
        author = _author;
        pages = _pages;
    }

    // getters, setters
    void setGenre(string _genre)
    {
        string validGenres[] = {
            "adventure", "horror", "document"};

        for (int i = 0; i < 3; i++)
        { // notice don't use sizeof(), it will return size in bytes. in this case 96
            if (validGenres[i] == _genre)
            {
                genre = _genre;
            }
        }
    }
    string getGenre()
    {
        return genre;
    }
};

void pgClass()
{
    Book book1; // notice no bracket
    book1.title = "book 1 title";
    book1.author = "book 1 author";
    book1.pages = 100;
    cout << book1.title << endl;

    Book book2("book 2 title", "book 2 author", 200);
    book2.title = "new book 2 title";
    cout << book2.title << endl;

    Book books[2] = {
        book1, book2};
    cout << books[0].toString() << endl;

    book1.setGenre("adventure");
    cout << book1.getGenre() << endl;
    book2.setGenre("invalid genre");
    cout << book2.getGenre() << endl;
}

// extends class
class StemBook : public Book
{ // must have this public keyword for accessibility; extend class can have access to protected and public members and methods, not private ones
public:
    string technology;

    string getGenre()
    {
        return "STEM";
    }
};

void pgExtension()
{
    StemBook stemBook;
    stemBook.technology = "C++";
    cout << stemBook.technology << endl;
    cout << stemBook.getGenre() << endl;
}


// global vs local variables
int sameVarName = 100;

void pgVariableScopes()
{
    int sameVarName = 200;
    cout << ::sameVarName << endl; // this is using global variable
    cout << sameVarName << endl;   // this is using local variable
}

// default value
void pgDefaultValue(int a = 100, int b = 200, int c = 300)
{
    cout << "a " << a << endl;
    cout << "b " << b << endl;
    cout << "c " << c << endl;
}


// pass value by reference and/or value
int x = 100;
int y = 200;
void passByValue(int val)
{
    val = 101;
}
void passByRef(int *pVal)
{
    *pVal = 201;
}
void passObjByValue(Person person)
{
    person.setName("name set by val");
}
void passObjByRef(Person *pPerson)
{
    pPerson->setName("name set by ref"); // must use arrow selector when using reference
}

void pgPassByValueAndReference(){
    Person person;
    person.setName("person name");
    cout << "before by value: " << person.getName() << endl;        // "person name"
    passObjByValue(person);
    cout << "after by value: " << person.getName() << endl;         // "person name"; objects passed by val is also a new copy! so getName is reading from old object.
    passObjByRef(&person);
    cout << "after by ref: " << person.getName() << endl;           // "name set by ref"
}


// constant
void pgConstKeyword()
{
    // case 1: const var
    const int x = 100; // must initiate on define

    // case 2: const obj
    const Person personConst;
    personConst.methodForConstObj(); // constant object can only use constant methods

    // case 3: providing value for const var in function, notice it is not const object
    Person person("reg name", "const name");
    cout << person.getNameConst() << endl; // "const name"
}


// composition
void pgComposition(){
    Person leader;
    leader.setName("the leader");

    Team team("my team", leader);
    cout << team.getName() + ", Leader is: " + team.getLeader().getName() << endl;
}


// friend keyword: a friend can have access to every member, method in a class, even private ones
class Aclass{

public:
    Aclass(string aString){
        _aString = aString;
    }
private:
    string _aString;

friend string aFriend(Aclass &aclass);      // step1: in class put a friend method stub
};

string aFriend(Aclass &aclass){             // step2: implement friend method
    return aclass._aString;
}

void pgFriendKeyword(){
    Aclass aclass("hello");
    cout << aFriend(aclass) << endl;        // step3: use the friend method to access class
}


void pgThisKeyword(){
    Person person;
    person.setName("person name");

    cout << person.getName() << endl;
    cout << person.getNameUsingThisRef() << endl;
    cout << person.getNameUsingThisDeRef() << endl;
}

void pgOperatorOverloading(){
    Person oldPerson(100);
    Person newPerson(200);
    Person person  = newPerson + oldPerson;     // result from object operation directly
    cout << person.asset << endl;
}

void pgPolyMorphism(){
    Chef chef("Chloe");
    Worker *pChef = &chef;                          // upcast
    cout << "my name is: " << pChef->getName()
         << ", my job is: " << pChef->getCareer()
         << endl;

    Driver driver("David");
    Worker *pDriver = &driver;
    cout << "my name is: " << pDriver->getName()
         << ", my job is: " << pDriver->getCareer()
         << endl;

     cout << ((Chef*)pDriver)->getCareer() << endl;     // downcast. result is still "Driver"
}

// Function Template
template<typename MyType>
MyType add(MyType a, MyType b){
    return a+b;
}
void pgFunctionTemplate1(){
    int a1 = 100, b1 = 200, result1;
    result1 = add(a1, b1);
    cout << to_string(result1) << endl;

    double a2 = 1.11, b2 = 2.22, result2;
    result2 = add(a2, b2);
    cout << to_string(result2) << endl;
}

template <typename Type1, typename Type2>
string concat(Type1 a, Type2 b){
    return to_string(a) + to_string(b);
}

void pgFunctionTemplate2(){
    int a = 100;
    double b = 200.22;
    cout << concat(a, b) << endl;
}

// Class Template
template<typename T>
class CompareTool {
    public:
        CompareTool(T a, T b){
            _a = a;
            _b = b;
        };

        string getBigger();
    private:
        T _a;
        T _b;
};

template<typename T>      // must have it for all function body
string CompareTool<T>::getBigger(){
    return _a > _b ? to_string(_a) : to_string(_b);
}

void pgClassTemplate(){
    CompareTool<double> compareTool(123.45, 234.56);    // must define concrete template type here

    cout << compareTool.getBigger() << endl;
}

// template specialization
template <typename T>
class TemplateSpecialization {
public:
    TemplateSpecialization(T arg){
        cout << to_string(arg) << ", from default template" << endl;
    }
};

template<>
class TemplateSpecialization<string>{     // use this class when constructor has <string> signature
public:
    TemplateSpecialization(string arg){
        cout << arg << ", from template specialization" << endl;
    }
};

void pgTemplateSpecialization(){
    TemplateSpecialization<int> templateSpecialization1(12345);
    TemplateSpecialization<string> templateSpecialization2("I am a string");
}


// error handling
void pgErrorHanding(){
    try {
        throw "500.123";
    } catch(int err) {
        cout << "handling error#: " << err << endl;
    } catch(double err){
        cout << "handling error#: " << err << endl;
    } catch(...){
        cout << "catch all handler" << endl;
    }             // C++ don't have finally
}

// file system
string getCurrentTime(){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

void pgFileSystemWrite(){
    ofstream myFile;
    myFile.open("myFile.txt", ios_base::app);   // if myFile.txt doesn't exist, C++ will create it for you. `ios_base::app` flag will append new content to file

    if(myFile.is_open()){   // if true then the file and object are successfully linked, and ready for use.
        cout << "Enter Item, Price" << endl;
        cout << "Press Ctrl+Z to complete" << endl;     // `Ctrl+Z` in terminal is EOF, which will stop while loop

        string item;
        double price;

        while(cin >> item >> price){    // input will be saved to item, then price. Input format like: beef 123 \n egg 234 \n ^Z
            myFile << item << "\t" << price << endl;
        }

//        myFile << "session completed at " << getCurrentTime() << endl;
        myFile.close();             // otherwise memory leak
    } else {
        // handle situations like forgot to link object to file
    }
}

void pgFileSystemRead(){
    ifstream myFile("myFile.txt");

    if(myFile.is_open()){
        string item;
        double price;

        while(myFile >> item >> price){
            cout << item << " will cost you: $" << price << endl;
        }
        myFile.close();
    } else {
    }

}

int main()
{
    //    pgPointer();

    //    pgClass();

    //    pgExtension();

    //    Person person;
    //    cout << person.getName() << endl;

    //    pgVariableScopes();

    //    pgDefaultValue();
    //    pgDefaultValue(101);

    //    passByValue(x);
    //    passByRef(&y);
    //    cout << x << endl;      // 100
    //    cout << y << endl;      // 201

//    pgPassByValueAndReference();

//    pgConstKeyword();

//    pgComposition();

//    pgFriendKeyword();

//    pgThisKeyword();

//    pgOperatorOverloading();

//    pgFunctionTemplate1();
//    pgFunctionTemplate2();
//    pgClassTemplate();
//    pgTemplateSpecialization();

//    pgErrorHanding();

//    pgFileSystemWrite();
    pgFileSystemRead();
    return 0;
}
