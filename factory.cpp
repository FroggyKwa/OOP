#include <iostream>
#include <vector>

using namespace std;

namespace PizzaFactory
{
    class PizzaIngredientFactory
    {
    public:
        virtual string create_dough()
        { return "null"; };

        virtual string create_sauce()
        { return "null"; };

        virtual string create_cheese()
        { return "null"; };

        virtual string create_sausage()
        { return "null"; };

        virtual vector<string> create_vegetables()
        { return {"null"}; };
    };

    class NewYorkPizzaIngredientFactory : public PizzaIngredientFactory
    {
    public:
        string create_dough() override
        {
            return "Thick dough";
        }

        string create_sauce() override
        {
            return "Tomato sauce";
        }

        string create_sausage() override
        {
            return "PepperoniPizza";
        }

        string create_cheese() override
        {
            return "Mozzarella";
        }

        vector<string> create_vegetables() override
        {
            return {};
        }
    };

    class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
    {
    public:
        string create_dough() override
        {
            return "Thin dough";
        }

        string create_sauce() override
        {
            return "White sauce";
        }

        string create_sausage() override
        {
            return "Ham";
        }

        string create_cheese() override
        {
            return "Cheddar";
        }

        vector<string> create_vegetables() override
        {
            return {"Basil", "Mushrooms", "Tomatoes"};
        }
    };

    class Pizza
    {
    public:
        string name;

        virtual string dough()
        { return "null"; };

        virtual string sauce()
        { return "null"; };

        virtual string cheese()
        { return "null"; };

        virtual string sausage()
        { return "null"; };

        virtual vector<string> vegetables()
        { return {"null"}; };

        virtual void add_ingredients()
        {};

        virtual void bake()
        { cout << "Baking" << endl; };

        virtual void cut()
        { cout << "Cutting" << endl; };

        virtual void pack()
        { cout << "Packing" << endl; };

        virtual string get_description()
        { return this->name; };
    };

    class CheesePizza : public Pizza
    {
    private:
        PizzaIngredientFactory ingredientFactory;
    public:
        explicit CheesePizza(PizzaIngredientFactory &ingredientFactory)
        {
            this->ingredientFactory = ingredientFactory;
        }

        void add_ingredients() override
        {
            this->name = "Cheese Pizza";
            this->dough() = ingredientFactory.create_dough();
            this->sauce() = ingredientFactory.create_sauce();
            this->sausage() = ingredientFactory.create_sausage();
            this->cheese() = ingredientFactory.create_cheese();
            this->vegetables() = ingredientFactory.create_vegetables();
        }
    };

    class PepperoniPizza : public Pizza
    {
    private:
        PizzaIngredientFactory ingredientFactory;
    public:
        explicit PepperoniPizza(PizzaIngredientFactory &ingredientFactory)
        {
            this->ingredientFactory = ingredientFactory;
        }

        void add_ingredients() override
        {
            this->name = "Pepperoni Pizza";
            this->dough() = ingredientFactory.create_dough();
            this->sauce() = ingredientFactory.create_sauce();
            this->sausage() = ingredientFactory.create_sausage();
            this->cheese() = ingredientFactory.create_cheese();
            this->vegetables() = ingredientFactory.create_vegetables();
        }
    };

    class GreekPizza : public Pizza
    {
    private:
        PizzaIngredientFactory ingredientFactory;
    public:
        explicit GreekPizza(PizzaIngredientFactory &ingredientFactory)
        {
            this->ingredientFactory = ingredientFactory;
        }

        void add_ingredients() override
        {
            this->name = "Greek Pizza";
            this->dough() = ingredientFactory.create_dough();
            this->sauce() = ingredientFactory.create_sauce();
            this->sausage() = ingredientFactory.create_sausage();
            this->cheese() = ingredientFactory.create_cheese();
            this->vegetables() = ingredientFactory.create_vegetables();
        }
    };

    class PizzaStore
    {
    public:
        virtual Pizza *pizza_create(string &name)
        {};

        Pizza *pizza_order(string &name)
        {
            Pizza *pizza = pizza_create(name);
            cout << pizza->get_description() << endl;
            pizza->add_ingredients();
            pizza->bake();
            pizza->cut();
            pizza->pack();

            return pizza;
        }

        static Pizza *get_pizza(const string &name, PizzaIngredientFactory ingredientFactory)
        {
            if (name == "Cheese")
            {
                return new CheesePizza(ingredientFactory);
            }
            if (name == "Pepperoni")
            {
                return new PepperoniPizza(ingredientFactory);
            }
            if (name == "Greek")
            {
                return new GreekPizza(ingredientFactory);
            }
        }
    };

    class NewYorkStore : public PizzaStore
    {
    public:
        Pizza *pizza_create(string &name) override
        {
            PizzaIngredientFactory *ingredientFactory = new NewYorkPizzaIngredientFactory();
            Pizza *pizza = get_pizza(name, *ingredientFactory);

            return pizza;
        }
    };

    class ChicagoStore : public PizzaStore
    {
    public:
        Pizza *pizza_create(string &name) override
        {
            PizzaIngredientFactory *ingredientFactory = new ChicagoPizzaIngredientFactory();
            Pizza *pizza = get_pizza(name, *ingredientFactory);
            pizza->name = name;
            return pizza;
        }
    };
}

using namespace PizzaFactory;

int main(int argc, char *argv[])
{
    string name = "Greek";
    auto pizza = ChicagoStore().pizza_order(name);
    return 0;
}