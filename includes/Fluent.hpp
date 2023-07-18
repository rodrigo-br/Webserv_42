#ifndef FLUENT_H
# define FLUENT_H

# include <iostream>
# include <cstdlib>

class Fluent;
class ISetAge;
class ISetHeigth;

class ISetName
{
    public:
        virtual ISetAge *SetName(std::string name) = 0;
        virtual ~ISetName() {};
};

class ISetAge
{
    public:
        virtual ISetHeigth *SetAge(int age) = 0;
        virtual ~ISetAge() {};
};

class ISetHeigth
{
    public:
        virtual Fluent *SetHeigth(float heigth) = 0;
        virtual ~ISetHeigth() {};
};

class Fluent : public ISetName, public ISetAge, public ISetHeigth
{
    private:
        std::string _name;
        int         _age;
        float       _heigth;
        Fluent() {};

    public:
        static ISetName* Configure() { return new Fluent(); };
        ISetAge *SetName(std::string name) { _name = name; return this; };
        ISetHeigth *SetAge(int age) { _age = age; return this; };
        Fluent *SetHeigth(float heigth) { _heigth = heigth; return this; };
        std::string GetName(void) const { return _name; };
        int GetAge(void) const { return _age; };
        float GetHeigth(void) const { return _heigth; };
};

std::ostream& operator<<(std::ostream &o, Fluent const &f) { o << "My name is " << f.GetName() << ", i am " << f.GetAge() << " years old and " << f.GetHeigth() << " of heigth."; return o; }

#endif