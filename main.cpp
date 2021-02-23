#include <iostream>
#include "Person.h"

using namespace std;


// pointer
void pgPointer(){
    string name = "foo";
    string *pName = &name;

    cout<<pName<<endl;  // 0x61fdd0
    cout<<*pName<<endl; // foo

    cout<<*&name<<endl; // foo

    int arr[10];
    int *pArr0 = &arr[0];
    int *pArr1 = &arr[1];
    int *pArr2 = &arr[2];
    int *pArr3 = &arr[3];

    cout << "pArr0 before +2 " << pArr0 << endl;    // 0x63fd60
    cout << "pArr2 " << pArr2 << endl;              // 0x63fd68
    pArr0 = pArr0 + 2;          // pointer doesn't do math +2, but move pointer by +2
    cout << pArr0 << endl;      // 0x63fd68, same as pArr2
}

// class
class Book{
    private:
        string genre;


    public:
        string title;
        string author;
        int pages;

        string toString(){
            return "title: "+title + ", author: "+author + ", pages: " + std::to_string(pages);
        }

        // constructors
        Book(){
        }

        Book(string _title, string _author, int _pages){
            title = _title;     // notice do not use: this.title = title;
            author = _author;
            pages = _pages;
        }

        // getters, setters
        void setGenre(string _genre){
            string validGenres[] = {
                "adventure", "horror", "document"
            };

            for(int i=0; i<3; i++){ // notice don't use sizeof(), it will return size in bytes. in this case 96
                if(validGenres[i] == _genre){
                    genre = _genre;
                }
            }
        }
        string getGenre(){
            return genre;
        }
};

void pgClass(){
    Book book1;     // notice no bracket
    book1.title = "book 1 title";
    book1.author = "book 1 author";
    book1.pages = 100;
    cout << book1.title << endl;

    Book book2("book 2 title", "book 2 author", 200);
    book2.title = "new book 2 title";
    cout << book2.title << endl;

    Book books[2] = {
        book1, book2
    };
    cout << books[0].toString() << endl;


    book1.setGenre("adventure");
    cout << book1.getGenre() << endl;
    book2.setGenre("invalid genre");
    cout << book2.getGenre() << endl;
}

// extends class
class StemBook : public Book{       // must have this public keyword for accessibility
    public:
        string technology;

        string getGenre(){
            return "STEM";
        }
};

void pgExtension(){
    StemBook stemBook;
    stemBook.technology = "C++";
    cout << stemBook.technology << endl;
    cout << stemBook.getGenre() << endl;

}

// global vs local variables
int sameVarName = 100;

void pgVariableScopes(){
    int sameVarName = 200;
    cout << ::sameVarName << endl;  // this is using global variable
    cout << sameVarName << endl;    // this is using local variable
}

// pass value by reference and/or value
int x = 100;
int y = 200;
void passByValue(int val){
    val = 101;
}
void passByRef(int *pVal){
    *pVal = 201;
}
void passObjByValue(Person person){
    person.setName("name set by val");
}
void passObjByRef(Person *pPerson){
    pPerson -> setName("name set by ref");      // must use arrow selector when using reference
}

int main()
{
//     pgPointer();
//     pgClass();
//     pgExtension();

//    Person person;
//    cout << person.getName() << endl;

//    pgVariableScopes();

//    passByValue(x);
//    passByRef(&y);
//    cout << x << endl;      // 100
//    cout << y << endl;      // 201

    Person person;
    person.setName("person name");
    cout << "before by value: " << person.getName() << endl;        // "person name"
    passObjByValue(person);
    cout << "after by value: " << person.getName() << endl;         // "person name"; objects passed by val is also a new copy! so getName is reading from old object.
    passObjByRef(&person);
    cout << "after by ref: " << person.getName() << endl;           // "name set by ref"


    return 0;
}

