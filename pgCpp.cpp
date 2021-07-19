#include <iostream>
#include <fstream>
#include <time.h>
#include <string> // for string functions. won't need it for using string
#include <vector>
#include <algorithm>    // for vector operations
#include <chrono>

#include "Person.h"
#include "Team.h"

#include "Worker.h"
#include "Chef.h"
#include "Driver.h"

#include "MyFreeStore.h"
#include <list>


using namespace std;

// pointer
void pgPointer()
{
	string name = "foo";
	string* pName = &name;

	cout << pName << endl; // 0x61fdd0
	cout << *pName << endl; // foo

	cout << *&name << endl; // foo

	int arr[10];
	int* pArr0 = &arr[0];
	int* pArr1 = &arr[1];
	int* pArr2 = &arr[2];
	int* pArr3 = &arr[3];

	cout << "pArr0 before +2 " << pArr0 << endl; // 0x63fd60
	cout << "pArr2 " << pArr2 << endl; // 0x63fd68
	pArr0 = pArr0 + 2; // pointer doesn't do math +2, but move pointer by +2
	cout << pArr0 << endl; // 0x63fd68, same as pArr2
}

// reference
void pgReference() {
	string name = "foo";
	string& rName = name;
	rName = "bar";
	cout << name << endl;	// changed to "bar"; the benefit of reference is it can be passed around easily w/o creating copies

	Person person;
	Person& rPerson = person;	// reference MUST be assigned at the momnent of declearation, that means reference can NOT reassigned, while pointer can
	rPerson.setName("hello");
	cout << person.getName() << rPerson.getName() << endl;
}

// const with indirection
void pgConstWithIndirection() {	// indirection means pointer or reference
	int i = 123;
	int j = 234;
	int* const cpI = &i;	// CONST POINTER
	// cpI = &j;			// this won't build as the pointer is constant, can't reassign
	*cpI = 1234;			// this will work, is putting value 1234 to same address of i

	int const* cpJ = &j;	// CONST VALUE
	// *cpJ = 345;			// this won't work as value is constant
	cpJ = &i;
	cout << *cpJ << endl;	// 1234, by the way, still can't do *cpJ = 2345, value is locked

	int const* const cpCc = &j;	// const value and const pointer
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
			"adventure", "horror", "document"
		};

		for (int i = 0; i < 3; i++)
		{
			// notice don't use sizeof(), it will return size in bytes. in this case 96
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
		book1, book2
	};
	cout << books[0].toString() << endl;

	book1.setGenre("adventure");
	cout << book1.getGenre() << endl;
	book2.setGenre("invalid genre");
	cout << book2.getGenre() << endl;
}

// extends class
class StemBook : public Book
{
	// must have this public keyword for accessibility; extend class can have access to protected and public members and methods, not private ones
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
	cout << sameVarName << endl; // this is using local variable
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

void passByRef(int* pVal)
{
	*pVal = 201;
}

void passObjByValue(Person person)
{
	person.setName("name set by val");
}

void passObjByRef(Person* pPerson)
{
	pPerson->setName("name set by ref"); // must use arrow selector when using pointer, or dereference first
}

void passObjByRef2(Person& person) // this `&` is not get pointer, it means get and use reference of person instance
{
	person.setName("name set by ref2"); // use reference just like instance itself, but without creating a copy. USE THIS!
}

void passObjByConstRef(const Person& person)
{
	person.methodForConstObj(); // can not use set as other methods, person is a const member, only use const method
	Person person2 = person; // still made a copy for person2, but the key is person object is not a new copy
	person2.setName("new name for new person");
	cout << person2.getName() << endl;
}

void pgPassByValueAndReference()
{
	Person person;
	person.setName("person name");
	cout << "before by value: " << person.getName() << endl; // "person name"
	passObjByValue(person);
	cout << "after by value: " << person.getName() << endl;
	// "person name"; objects passed by val is also a new copy! so getName is reading from old object.
	passObjByRef(&person);
	cout << "after by ref: " << person.getName() << endl; // "name set by ref"; use same object
	passObjByRef2(person);
	cout << "after by ref: " << person.getName() << endl; // "name set by ref2"; use same object
	passObjByConstRef(person);
	// when no change is to object, use this to avoid `pass by val` cost, especially for big object
}


// constant
void pgConstKeyword()
{
	// case 1: const var
	const int cx = 100; // must initiate on define

	// case 2: const obj
	const Person cPerson;
	cPerson.methodForConstObj(); // constant object can only use constant methods
	// other non constant objects can also use this method
	// const keyword on method means this method won't make any data change.

	// case 3: providing value for const var in function, notice it is not const object
	Person person("reg name", "const name");
	cout << person.getNameConst() << endl; // "const name"
}


// composition
void pgComposition()
{
	Person leader;
	leader.setName("the leader");

	Team team("my team", leader);
	cout << team.getName() + ", Leader is: " + team.getLeader().getName() << endl;
}


// friend keyword: a friend can have access to every member, method in a class, even private ones
class Aclass
{
public:
	Aclass(string aString)
	{
		_aString = aString;
	}

private:
	string _aString;

	friend string aFriend(Aclass& aclass); // step1: in class put a friend method stub
};

string aFriend(Aclass& aclass)
{
	// step2: implement friend method
	return aclass._aString;
}

void pgFriendKeyword()
{
	Aclass aclass("hello");
	cout << aFriend(aclass) << endl; // step3: use the friend method to access class
}


void pgThisKeyword()
{
	Person person;
	person.setName("person name");

	cout << person.getName() << endl;
	cout << person.getNameUsingThisRef() << endl;
	cout << person.getNameUsingThisDeRef() << endl;
}

void pgOperatorOverloading()
{
	Person oldPerson(100);
	Person newPerson(200);
	Person person = newPerson + oldPerson; // result from object operation directly
	cout << person.asset << endl;		// 300

	person + 123;
	cout << person.asset << endl;		// 423

	123 + person;		// need to use free function operator overload
	cout << person.asset << endl;		// 546
}


void pgPolyMorphism()
{
	Chef chef("Chloe");
	Worker* pChef = &chef; // upcast
	cout << "my name is: " << pChef->getName()
		<< ", my job is: " << pChef->getCareer()
		<< endl;

	Driver driver("David");
	Worker* pDriver = &driver;
	cout << "my name is: " << pDriver->getName()
		<< ", my job is: " << pDriver->getCareer()
		<< endl;

	cout << static_cast<Chef*>(pDriver)->getCareer() << endl; // result is still "Driver", as both driver and chef has getCareer()
	
	Person* pP = dynamic_cast<Person*>(pDriver);	// cast to a totally different class is not possbile for static_cast. dynamic_cast will return nullptr if can't cast
	cout << (pP ? pP->getName() : "cast from Worker to Person failed") << endl;
}

// Function Template
template <typename MyType>
MyType add(MyType const& a, MyType const& b)
{
	return a + b;
}

void pgFunctionTemplate1()
{
	int a1 = 100, b1 = 200, result1;
	result1 = add(a1, b1);
	cout << result1 << endl;

	double a2 = 1.11, b2 = 2.22, result2;
	result2 = add(a2, b2);		// so add() is reused by int and double input types
	cout << result2 << endl;
}

template <typename Type1, typename Type2>
string concat(Type1 a, Type2 b)
{
	return to_string(a) + ' ' + to_string(b);
}

void pgFunctionTemplate2()
{
	int a = 100;
	double b = 200.22;
	cout << concat(a, b) << endl;		// concat() is reused by different signatures, rather than create 2 similar methods
	cout << concat(b, a) << endl;
}

// Class Template
template <typename T>
class CompareTool
{
public:
	CompareTool(T a, T b)
	{
		_a = a;
		_b = b;
	};

	string getBigger();
private:
	T _a;
	T _b;
};

template <typename T> // must have it for all function body
string CompareTool<T>::getBigger()
{
	return _a > _b ? to_string(_a) : to_string(_b);
}

void pgClassTemplate()
{
	CompareTool<double> compareTool(123.45, 234.56); // must define concrete template type here

	cout << compareTool.getBigger() << endl;
}

// template specialization
template <typename T>
class TemplateSpecialization
{
public:
	TemplateSpecialization(T arg)
	{
		cout << to_string(arg) << ", from default template" << endl;
	}
};

template <>
class TemplateSpecialization<string>	// use this class when constructor has <string> signature
{
public:
	TemplateSpecialization(string arg)
	{
		cout << arg << ", from template specialization" << endl;
	}
};

void pgTemplateSpecialization()
{
	TemplateSpecialization<int> templateSpecialization1(12345);
	TemplateSpecialization<string> templateSpecialization2("I am a string");
}


// template with operator overload
template <typename T>
class TemplateWithOperatorOverload {
private:
	T result;
public:
	TemplateWithOperatorOverload(T const& value)
		: result(value){}

	T operator+= (T const& value) {
		return result = result + value;
	}

	T getTotal() const {
		return result;
	}
};

void pgTemplateWithOperatorOverload() {
	TemplateWithOperatorOverload<double> twoo1(1.23);
	twoo1 += 2.34;
	cout << twoo1.getTotal() << endl;

	TemplateWithOperatorOverload<int> twoo2(100);
	twoo2 += 200;
	cout << twoo2.getTotal() << endl;

	TemplateWithOperatorOverload<string> twoo3("hello");
	twoo3 += " world ";		// same operator overload is reused for different template types
	cout << twoo3.getTotal() << endl;
}

// template with operator overload and specialization
template <>		// common template is using the above sample
class TemplateWithOperatorOverload<Person> {	// notice this specializer is for Person, but constructor can for int
private:
	int result;
public:
	TemplateWithOperatorOverload(int const& asset)
		: result(asset) {}

	int operator+= (Person const& person) {
		return result = result + person.asset;
	}

	int getTotal() const {
		return result;
	}
};

void pgTemplateWithOperatorOverloadAndSpecialization() {
	TemplateWithOperatorOverload<Person> twoo(100);
	Person p1(20);
	twoo += p1;
	cout << twoo.getTotal() << endl;
}


// error handling
void pgErrorHanding()
{
	try
	{
		throw "500.123";
	}
	catch (int err)
	{
		cout << "handling error#: " << err << endl;
	} catch (double err)
	{
		cout << "handling error#: " << err << endl;
	} catch (...)
	{
		cout << "catch all handler" << endl;
	} // C++ don't have finally
}

// file system
string getCurrentTime()
{
	time_t now = time(nullptr);
	struct tm tstruct;
	char buf[80];
	// tstruct = *localtime(&now);
	// strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

void pgFileSystemWrite()
{
	ofstream myFile;
	myFile.open("myFile.txt", ios_base::app);
	// if myFile.txt doesn't exist, C++ will create it for you. `ios_base::app` flag will append new content to file

	if (myFile.is_open())
	{
		// if true then the file and object are successfully linked (a file handle is created), and ready for use.
		cout << "Enter Item, Price" << endl;
		cout << "Press Ctrl+Z to complete" << endl; // `Ctrl+Z` in terminal is EOF, which will stop while loop

		string item;
		double price;

		while (cin >> item >> price)
		{
			// input will be saved to item, then price. Input format like: beef 123 \n egg 234 \n ^Z, the end of each input is defined by white space, so \t works too
			myFile << item << "\t" << price << endl;
		}

		//        myFile << "session completed at " << getCurrentTime() << endl;
		myFile.close(); // otherwise memory leak
	}
	else
	{
		// handle situations like forgot to link object to file
	}
}

void pgFileSystemRead()
{
	ifstream myFile("myFile.txt");

	if (myFile.is_open())
	{
		string item;
		double price;

		while (myFile >> item >> price)
		{
			cout << item << " will cost you: $" << price << endl;
		}
		myFile.close();
	}
	else
	{
	}
}


// string
void pgStringInput()
{
	string myString;

	//    cin >> myString;            // hello world
	//    cout << myString << endl;   // hello    cin will only read first section divided by white space

	getline(cin, myString); // hello world
	cout << myString << endl; // hello world
}

void pgStringCopy()
{
	string s1 = "foo bar"; // other syntax: string s1("foo bar");
	cout << s1 << endl;

	string s2 = s1; // other syntax: s2.assign(s1);
	s2 = "hello world";
	cout << s1 << endl; // foo bar

	string* pS3 = &s1;
	*pS3 = "hello world";
	cout << s1 << endl; // hello world
}

void pgStringFunctions()
{
	string s1 = "hello world";
	cout << s1[1] << endl; // other syntax: s1.at(1);
	cout << s1.substr(6, 5) << endl; // substr(int skip, int take)

	string s2 = "foo bar";
	cout << s1 << "--" << s2 << endl;
	s1.swap(s2); // useful for sorting
	cout << s1 << "--" << s2 << endl;

	// string find
	string s3 = "hey hello world hello foobar";
	cout << s3.find("hello") << endl; // 4    find() returns index of first match found
	cout << s3.rfind("hello") << endl; // 16   rfind() reverse find will return the last match found
	cout << s3.rfind("non exist") << endl; // 18446744073709551615

	// string mutation
	s3.erase(25); // c++ strings are mutable! erase(int start_letter_index)
	cout << s3 << endl;
	s3.replace(10, 5, "Cheers"); // replace(int skip, int take, string new_string)
	cout << s3 << endl;
	s3.insert(4, "there, "); // insert(int skip, string insert_string)
	cout << s3 << endl;
}

// vector
void pgVector()
{
	vector<string> myVector = {"a", "b", "c"}; // similar to JAVA arrayList
	myVector.push_back("d"); // add an element to the end
	myVector[0] = "aa"; // change an element value

	for (string element : myVector)
	{
		// simplified for loop
		cout << element << endl;
	}
}

void pgVectorAlgorithm()
{
	vector<string> myVector = {"rr", "uu", "nn", "pp", "ee", "ii", "xx", "uu"};

	sort(begin(myVector), end(myVector));

	for (auto i = begin(myVector); i != end(myVector); ++i) // iterator. notice here `i` is pointer
	{
		cout << *i << endl;
	}

	cout << "myVector size is: " << myVector.size() << endl;

	cout << "has \"uu\": " << count(begin(myVector), end(myVector), "uu") << endl;
}

class MyItem
{
public:
	int _price;
	string _name;

	MyItem(string name, int price)
	{
		_price = price;
		_name = name;
	}
};

void pgVectorComparable()
{
	vector<MyItem> myVector{
		MyItem("hello", 555),
		MyItem("world", 777),
		MyItem("foo", 666),
		MyItem("bar", 222)
	};

	sort(begin(myVector), end(myVector), [](const auto& a, const auto& b) // TODO: learn lambda
	{
		return a._price < b._price;
	});

	for (MyItem myItem : myVector)
	{
		cout << myItem._name << " | " << myItem._price << endl;
	}
}


// linked list
template <typename Func>
long long timeFunc(Func func, int size) {	// this makes fn being passed as parameters, like in JS!
	auto begin = chrono::steady_clock::now();
	func(size);
	auto end = chrono::steady_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(end - begin).count();
}

void createList(int size) {
	list<int> mylist;
	for (int i = 0; i < size; i++) {
		mylist.push_back((int)rand());
	}
}

void pgList() {
	cout << timeFunc(createList, 10'000) << endl;

	// array: collection size never change
	// vector: collection size auto grow or shrink. will make a copy every time add or remove
	// list: collection size auto grow or shrink. need to traverse when looking up for certain element

	// map: keys must be unique, elements are stored sorted
	// multimap: allows collisions

	// unordered_map, unordered_multimap ... and more
}


// cast
void pgCast()
{
	const double num = 1.23;
	int i = static_cast<int>(num);

	// TODO: more casts: dynamic_cast<>, const_cast<>, reinterpret_cast<>
}

// scope
void pgScope() {
	Person person1;

	{					// curly braces can be put any where to define a scope.
		Person person2;	// person2's scope is between curly braces above and below it.
	}
}

// enum
void pgEnum() {
	// not scoped, must be unique globally
	enum myenumerables {
		STATUS1,	// don't need to specify value here, compiler will give default values from 0; still can set a int value like STATUS1 = 99
		STATUS2,
		STATUS3
	};

	// scoped
	enum class MyScopedEnumerables {
		STATUS1,
		STATUS2,
		STATUS3
	};
	enum class MyScopedEnumerables2 {
		STATUS1,
		STATUS2,
		STATUS3
	};

	myenumerables status1 = STATUS1;
	MyScopedEnumerables MyScopedEnumerableStatus1 = MyScopedEnumerables::STATUS1;
	MyScopedEnumerables2 MyScopedEnumerable2Status1 = MyScopedEnumerables2::STATUS1;
}


// free store
void pgFreeStore() {
	// local instance (aka: stack), constructor and destructor called when out of scope
	{
		MyFreeStore myFreeStore("abc");
		string name = myFreeStore.GetName();
	}

	// free store instance (aka: heap)
	MyFreeStore* pMyFreeStore = new MyFreeStore("123");	// construct, notice returns a pointer
	string name = pMyFreeStore->GetName();
	MyFreeStore* pCopiedFreeStorePointer = pMyFreeStore;	// this is copying a pointer, no new instance will be created.
	delete pMyFreeStore;				// destruct. Manually by `delete` keyword, memory leak if not deleted
	pMyFreeStore = nullptr;

	// bad logic after delete:
	pMyFreeStore->GetName();			// after delete, this becomes a pointer to nowhere
	pCopiedFreeStorePointer->GetName();	// after delete, this also becomes a pointer to nowhere
	delete pMyFreeStore;				// repoint to nullptr prevented crush. will crush if delete non exist free store.
}

void pgFreeStoreAttachToLocalInstance() {
	Person person;
	person.addPet("petName");
}	// should see: person constructor >> free storage constructor >> free storage destructor >> person destructor

void pgFreeStoreWithCopy() {
	Person person;
	person.addPet("petName");

	Person person2 = person;	// This will call `copy constructor`
	Person person3;
	person3.addPet("replacedPetName");
	person3 = person;			// This will call `copy assignment`
	// if copy constructor / assignment are not implemented, this copy acition will make a new copy, including pet pointer, 
	// but pointers are pointing to same instance.
	// so when person destructor called, delete pet will be called twice, which will crush code
}

// smart pointer (since cpp11)
void pgSmartPointer() {
	Chef chef("chefName");

	chef.addPet("petName");
	string petName = chef.getPetName();		// petName
	chef.addPet("petName2");				// without adding delete logic; 
											// need reset() to decrease reference count to pet added earlier.
											// as we only have one reference, so the reset() is triggering delete. then create a new pointer via make_shared()
	petName = chef.getPetName();			// petName2

	Chef chef2 = chef;						// smart make a new copy, without implementing copy constructor / assiignment, reference count increased.
	chef2.addPet("petName3");				// in last line it has 2 references to shared_ptr of "petName2", this line will decrease one reference at reset(), and create a new pointer via make_shared() for chef2
	petName = chef.getPetName();			// petName2
	petName = chef2.getPetName();			// petName3
}	// no delete logic in destructor needed


void pgPolyMorphysm() {
	// prerequest for polymorphysm is using virtual keyword. if implemented as overwrite then when upcast extra members, functions will be sliced. 
	// all below bahaviors applys to function call passing by reference or value

	Worker worker = Chef("myname");
	cout << worker.getName() << endl;			// "myname"; child class slicing when upcast, invoking parent's method. No polymorphysm for concrete instance
	
	Chef chef = Chef("myname2");
	Worker& rChef = chef;
	cout << rChef.getName() << endl;			// "chef myname2"; use reference, polymorphysm works
	Worker* pChef = &chef;
	cout << pChef->getName() << endl;			// "chef myname2"; use pointer, polymorphysm works
	
	Worker* pFreeStoreChef = new Chef("myname3");
	cout << pFreeStoreChef->getName() << endl;	// "chef myname3"; use free store, polymorphysm works
	delete pFreeStoreChef;

	shared_ptr<Worker> spChef = make_shared<Chef>("myname4");
	cout << spChef->getName() << endl;			// "chef myname4"; use smart pointer, polymorphysm works
	spChef.reset();

	// chef = worker;	  // this won't work. can't downcast parent to child
	worker = chef;		  // chef getName() will be sliced
}

// lambda
bool isOdd(int number) {
	return number % 2 != 0;
}

void pgLambda() {
	vector<int> numbers { 2, 3, 4, -1, 1 };

	{
		int odd_count = std::count_if(begin(numbers), end(numbers), isOdd);
		cout << "free method: " << odd_count << endl;
	}

	{
		auto isOdd = [](int number) {	// [] capture clause; () parameters; {} body; auto is type of function, return return type
			return number % 2 != 0;
		};
		int odd_count = std::count_if(begin(numbers), end(numbers), isOdd);
		cout << "lambda expression: " << odd_count << endl;
	}

	{
		auto isOdd = [](int number) -> bool {
			return number % 2 != 0;
		};
		int odd_count = std::count_if(begin(numbers), end(numbers), isOdd);
		cout << "lambda expression w return type: " << odd_count << endl;
	}
}

void pgLambdaCaptures() {
	vector<int> numbers{ 2, 3, 4, -1, 1 };
	int x = 3;
	int y = 7;
	string message = "elements bwtween " + to_string(x) + " and " + to_string(y) + " inclusive:";

	for_each(begin(numbers), end(numbers),
		[x, y, &message](int n) {		// x, y will be copied value and const, message will be reference
			if (n >= x && n <= y) {
				message += (" " + to_string(n));
			}
		});
	// for_each will only provide method with int n, to complete express, 
	// extra variables are needed. They can be passed in via capture clause.
	
	// [ = ] means capture all var used in expressing, by value and const.
	// [ & ] means capture all var used in expressing, by reference.
	
	// all captured values by default are const, which means you can't change value for x,
	// or if &message is captured by value, this message += will not be mutable.


	for_each(begin(numbers), end(numbers),
		[&, x](int number) mutable {	// everything used are by reference, other than x, which is by value and const
			x += number;
			y += number;
		});
	// notice here x is passed by value and const, but still can be edited. because keyword `mutable` is used.
	// changing x in expression won' change x varible outside. It is still a copy.
}


// container algorithm
void pgContainerAlgorithm() {

	vector <int> v;

	// loop 
	{
		for (int i = 0; i < 5; i++)
		{
			v.push_back(i);
		}

		for (int i = 0; i < 5;)
		{
			v.push_back(i++);
		}

		int i = 0;
		generate_n(back_inserter(v), 5, [&]() {return i++;});
	}

	// sum
	{
		int total = 0;
		for (int index = 0; index < 5; index++)
		{
			total += v[index];
		}

		for (int elem : v) {
			total += elem;
		}

		//total = std::accumulate(begin(v), end(v), 0);	// since cpp 20
	}

	// count the number of 3
	{
		int count = 0;
		for (unsigned int i = 0; i < v.size(); i++)
		{
			if (v[i] == 3) { count++; }
		}

		for (auto it = begin(v); it != end(v); it++) {
			if (*it == 3) { count++; }
		}

		count = std::count(begin(v), end(v), 3);
	}

	// remove the number 3
	{
		// DO NOT USE THIS, wrong logic from video
		/*for (unsigned int i = 0; i < v.size(); i++)
		{
			if (v[i] == 3) { v.erase(v.begin() + i); }
		}*/

		 //DO NOT DO THIS, when container content is changed, iterator will become invalid.
		/*for (auto i = begin(v); i != end(v); i++)	
		{
			if (*i == 3) v.erase(i);
		}*/

		// notice: 
		// remove_if does NOT simply removes an element, it moves up the rest of the vector to fill up the element to be removed.
		// it also will leave old elements at the end intact.
		// so we need to use the new end pointer to trim off those old vaules.
		auto newEnd = std::remove_if(begin(v), end(v), [](int element) {return (element == 3);});
		v.erase(newEnd, end(v));
		//std::remove_if(begin(v), end(v), [](int element) {return (element == 3);}, end(v));	// since cpp 20
	}

	// use expression can adapt to different containers easily
	{
		list<int> l;
		
		int i = 0;
		generate_n(back_inserter(l), 5, [&] {return i++;});

		int count = std::count(begin(l), end(l), 3);	// count_if() supports lambda
		
		auto pMax = max_element(begin(l), end(l));
		auto maxValue = *pMax;

		auto newEnd = std::remove_if(begin(l), end(l), [](int element) {return (element == 3);});
		l.erase(newEnd, end(l));

		bool isAllPositive = std::all_of(begin(l), end(l), [](int element) {return element > 0;});
	}
}

// move
template <typename MyFn>
long long timeFn(MyFn fn)
{
	auto start = chrono::steady_clock::now();
	fn();
	auto end = chrono::steady_clock::now();
	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// https://en.cppreference.com/w/cpp/language/move_assignment
class MyMoveClass {
private:
	std::string _fragment;
public:
	MyMoveClass()
		:_fragment("fragment") {}

	MyMoveClass(string fragment)
		:_fragment(fragment) {}

	// copy constructor
	MyMoveClass(const MyMoveClass& mmc)
		:_fragment(mmc._fragment)
	{
		cout << "copy constructor called, move failed" << endl;
	}

	// move constructor
	MyMoveClass(MyMoveClass&& mmc)
		:_fragment(std::move(mmc._fragment))
	{ }

	// copy assignment
	MyMoveClass& operator=(const MyMoveClass& mmc) {
		if (this != &mmc)
		{
			_fragment = mmc._fragment;
			cout << "copy assignment called, move failed" << endl;
		}
		return *this;
	}

	// move assignment
	MyMoveClass& operator=(MyMoveClass&& mmc)
	{
		if (this != &mmc)
		{
			_fragment = std::move(mmc._fragment);
			mmc._fragment.clear();	// disable small string optimization for demo purpose only
		}
		return *this;
	}

	// destructor will prevents implicit move assignment
	//~MyMoveClass() { }
	// TODO: with destructor:
	//	fn1 uses copy-constructor
	//	fn2 uses copy-constructor and move-constructor 
};

MyMoveClass& fn(MyMoveClass myMoveClass) {	 // trigger move-constructor
	return myMoveClass;
}

MyMoveClass fn2(MyMoveClass myMoveClass) {	 // trigger move-constructor, move-assignment
	return myMoveClass;
}

MyMoveClass& fn3(MyMoveClass& myMoveClass) { // trigger nothing
	return myMoveClass;
}

class MyMoveClass2 : MyMoveClass
{
	string _fragment2;
	
};

void runMoveManyTimes() {
	MyMoveClass myMoveClass("dummy string");
	for (int i = 0; i < 100; i++) {
		myMoveClass = MyMoveClass("another dummy string rvalue" + to_string(i));
		// or
		MyMoveClass mmc2 = MyMoveClass("another dummy string xvalue " + to_string(i));	// mmc is lvalue, which can get pointer address, which is not a transient variable.
		myMoveClass = std::move(mmc2);	// std::move() cast lvalue to rvalue, so compiler will choose move assignment over copy assignment, when =
	}
}

void pgMove() {
	MyMoveClass mmc, mmc2;
	mmc= MyMoveClass("dummy string rvalue");	// move-assignment from rvalue temporary
	mmc2 = std::move(mmc);				// move-assignment from xvalue temporary

	fn(mmc2);							// implicit move-constructor
	fn2(mmc);							// move-constructor, move-assignment
	fn3(mmc);							// no move

	cout << timeFn(runMoveManyTimes) << endl;
}

int main()
{
	//    pgPointer();
	//pgReference();
	//pgConstWithIndirection();

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

	//	  pgPassByValueAndReference();

	//    pgConstKeyword();

	//    pgComposition();

	//    pgFriendKeyword();

	//    pgThisKeyword();

	    //pgOperatorOverloading();

	    //pgFunctionTemplate1();
	    //pgFunctionTemplate2();
	    //pgClassTemplate();
	    //pgTemplateSpecialization();
	//pgTemplateWithOperatorOverload();
	//pgTemplateWithOperatorOverloadAndSpecialization();

	//    pgErrorHanding();

	//    pgFileSystemWrite();
	//    pgFileSystemRead();

	//    pgStringInput();
	//    pgStringCopy();
	//    pgStringFunctions();

	// pgVector();
	// pgVectorAlgorithm();
	// pgVectorComparable();

	// pgCast();

	//pgScope();

	//pgEnum();

	//pgFreeStore();
	//pgFreeStoreAttachToLocalInstance();
	//pgFreeStoreWithCopy();
	//pgSmartPointer();

	//pgPolyMorphism();
	//pgList();

	//pgLambda();
	//pgLambdaCaptures();

	//pgContainerAlgorithm();

	pgMove();

	return 0;
}
