#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <memory>
#include "MyFreeStore.h"

//using namespace std;          // Do NOT use using syntax so people won't get conflict when using your header file.

class Worker
{
    public:
        Worker() = default;
        Worker(std::string);        // always specify full namespace in header file
        std::string getName() const;

        virtual std::string getCareer() = 0;  // step1: =0 means this is a pure virtual function. means no implementation in Worker class
                                         // or keep it as virtual but provide an default implementation: virtual string getCareer(){}, so if one child class has no implementation, this empty one will be executed.
                                         // if we don't have virtual keyword at all, just declared a function here, then it is override, need to downcast

        void addPet(std::string);
        const std::string getPetName();

    private:
        std::string _name;
        std::shared_ptr<MyFreeStore> pPet;

};

#endif // WORKER_H
