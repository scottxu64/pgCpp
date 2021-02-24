#ifndef PERSON_H        // ifndef = if not defined
#define PERSON_H
#include <iostream>

class Person
{
    public:
        Person();
        ~Person();      // deconstructor

        std::string getName();
        void setName(std::string name);

        void methodForConstObj() const;

        Person(std::string name, std::string nameConst);
        std::string getNameConst();


    private:
        std::string _name;

        const std::string _nameConst;
};

#endif // PERSON_H
