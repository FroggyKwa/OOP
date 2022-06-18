#include <iostream>
#include <utility>

using namespace std;

class QuackStrategy
{
public:
    virtual void quack()
    {}
};

class DuckQuack : public QuackStrategy
{
public:
    void quack() override
    {
        cout << "quack!" << endl;
    }
};

class FakeDuckQuack : public QuackStrategy
{
public:
    void quack() override
    {
        cout << "Woof!" << endl;
    }
};

class SwimStrategy
{
public:
    virtual void swim()
    {}
};

class DuckSwim : public SwimStrategy
{
public:
    void swim() override
    {
        cout << "I'm swimming like duck!" << endl;
    }
};

class FakeDuckSwim : public SwimStrategy
{
public:
    void swim() override
    {
        cout << "I'm swimming like dog!" << endl;
    }
};

class FlightStrategy
{
public:
    virtual void fly()
    {}
};

class DuckFlight : public FlightStrategy
{
public:
    void fly() override
    {
        cout << "I'm flying!" << endl;
    }
};

class FakeDuckFlight : public FlightStrategy
{
public:
    void fly() override
    {
        cout << "I can't fly! (sad doggy emotions)" << endl;
    }
};

class DisplayStrategy
{
public:
    virtual void display()
    {

    }
};

class Display : public DisplayStrategy
{
private:
    string name;
public:
    Display()
    {
        name = "null";
    }

    explicit Display(string duck_name)
    { name = move(duck_name); }

    void display() override
    {
        cout << name << ":" << endl;
    }
};

class Duck
{
private:
    QuackStrategy &quackStrategy;
    SwimStrategy &swimStrategy;
    FlightStrategy &flightStrategy;
    DisplayStrategy &displayStrategy;
public:
    Duck (QuackStrategy& quack, SwimStrategy& swim, FlightStrategy& flight, DisplayStrategy& display):
    quackStrategy(quack), swimStrategy(swim), flightStrategy(flight), displayStrategy(display) {}
    void Quack()
    {
        quackStrategy.quack();
    }
    void Swim()
    {
        swimStrategy.swim();
    }
    void Fly()
    {
        flightStrategy.fly();
    }
    void Display()
    {
        displayStrategy.display();
    }
};

void TestingDuck(Duck& duck)
{
    duck.Display();
    duck.Quack();
    duck.Swim();
    duck.Fly();
    cout << endl;
}

int main()
{
    Duck normal_duck = * new Duck(* new DuckQuack, * new DuckSwim, * new DuckFlight, * new Display("Bob"));
    Duck dog = * new Duck(* new FakeDuckQuack, * new FakeDuckSwim, * new FakeDuckFlight, * new Display("Doge"));
    Duck abnormal_duck = * new Duck(* new FakeDuckQuack, * new FakeDuckSwim, * new DuckFlight, * new Display("DogeDuck"));
    TestingDuck(normal_duck);
    TestingDuck(dog);
    TestingDuck(abnormal_duck);

    return 0;
}
