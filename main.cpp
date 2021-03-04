#include <iostream>
#include "Person.h"
#include "Team.h"

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
{ // must have this public keyword for accessibility
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

void pgFriend(){
    Aclass aclass("hello");
    cout << aFriend(aclass) << endl;        // step3: use the friend method to access class
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

    pgFriend();

    return 0;
}
