#ifndef WORKER_H
#define WORKER_H

#include <iostream>

//using namespace std;          // Do NOT use using syntax so people won't get conflict when using your header file.

class Worker
{
    public:
        Worker(std::string);        // always specify full namespace in header file
        std::string getName();

        virtual std::string getCareer() = 0;  // step1: =0 means this is a pure virtual function. means no implementation in Worker class
                                         // or keep it as virtual but provide an default implementation: virtual string getCareer(){}, so if one child class has no implementation, this empty one will be executed.
                                         // if we don't have virtual keyword at all, just declared a function here, then it is override, need to downcast

    private:
        std::string _name;
};

#endif // WORKER_H
