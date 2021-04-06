#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <utility>

class Person
{
public:
    std::string name;
    std::pair<int,int> prev_pos;
    long long prev_time;
    Person();

    bool operator <(const Person &p)
    {
        return name<p.name;
    }
    bool operator >(const Person &p)
    {
        return name>p.name;
    }
    bool operator ==(const Person &p)
    {
        return name==p.name;
    }
    bool operator <=(const Person &p)
    {
        return name<=p.name;
    }
    bool operator >=(const Person &p)
    {
        return name>=p.name;
    }
};

#endif // PERSON_H
