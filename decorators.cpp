#include <iostream>

using namespace std;

namespace Decorators
{
    class IBeverage
    {
    public:
        virtual double get_cost()
        {};

        virtual string get_description()
        {};
    };

    class HouseBlend : public IBeverage
    {
    public:
        double get_cost() override
        {
            return 10;
        }

        string get_description() override
        {
            return "House blend";
        };
    };

    class DarkRoast : public IBeverage
    {
    public:
        double get_cost() override
        {
            return 100;
        }

        string get_description() override
        {
            return "Dark roast";
        };
    };

    class Decaf : public IBeverage
    {
    public:
        double get_cost() override
        {
            return 150;
        }

        string get_description() override
        {
            return "Without caffeine";
        };
    };

    class Espresso : public IBeverage
    {
    public:
        double get_cost() override
        {
            return 300;
        }

        string get_description() override
        {
            return "Espresso";
        };
    };

    class ICondimentDecorator : public IBeverage
    {
    };

    class MilkDecorator : public ICondimentDecorator
    {
    private:
        IBeverage *Beverage;
    public:
        explicit MilkDecorator(IBeverage *beverage)
        {
            Beverage = beverage;
        }

        double get_cost() override
        {
            return Beverage->get_cost() + 10;
        }

        string get_description() override
        {
            return Beverage->get_description() + ", Milk";
        }
    };

    class SoyDecorator : public ICondimentDecorator
    {
    private:
        IBeverage *Beverage;
    public:
        explicit SoyDecorator(IBeverage *beverage)
        {
            Beverage = beverage;
        }

        double get_cost() override
        {
            return Beverage->get_cost() + 15;
        }

        string get_description() override
        {
            return Beverage->get_description() + ", Soy";
        }
    };

    class MochaDecorator : public ICondimentDecorator
    {
    private:
        IBeverage *Beverage;
    public:
        explicit MochaDecorator(IBeverage *beverage)
        {
            Beverage = beverage;
        }

        double get_cost() override
        {
            return Beverage->get_cost() + 50;
        }

        string get_description() override
        {
            return Beverage->get_description() + ", Mocha";
        }
    };

    class WhipDecorator : public ICondimentDecorator
    {
    private:
        IBeverage *Beverage;
    public:
        explicit WhipDecorator(IBeverage *beverage)
        {
            Beverage = beverage;
        }

        double get_cost() override
        {
            return Beverage->get_cost() + 65;
        }

        string get_description() override
        {
            return Beverage->get_description() + ", Whip";
        }
    };


}

using namespace Decorators;

int main()
{
    auto milk_mocha_coffee = new MilkDecorator(new MochaDecorator(new HouseBlend()));
    cout << milk_mocha_coffee->get_description() << " - price: " << milk_mocha_coffee->get_cost() << endl;
    auto soy_whip_mocha_milk_roast = new SoyDecorator(
            new WhipDecorator(new MilkDecorator(new MochaDecorator(new DarkRoast()))));
    cout << soy_whip_mocha_milk_roast->get_description() << " - price: " << soy_whip_mocha_milk_roast->get_cost();
    return 0;
}