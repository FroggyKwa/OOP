#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

namespace Observer
{

    class Observer
    {
    private:
        double temperature{};
        double humidity{};
        double pressure{};
    public:
        virtual void update(double temperature_t, double humidity_t, double pressure_t)
        {};

        virtual void display()
        {};

        bool operator==(const Observer &a)
        {
            return &a == this;
        }
    };

    class Subject
    {
    public:
        virtual void registerObserver(Observer &observer)
        {};

        virtual void removeObserver(Observer &observer)
        {};

        virtual void notifyObservers()
        {};
    };

    class WeatherData : public Subject
    {
    private:
        vector<Observer> observers;
    public:
        void registerObserver(Observer &observer) override
        {
            observers.push_back(observer);
        }

        void removeObserver(Observer &observer) override
        {
            observers.erase(find(observers.begin(), observers.end(), observer));
        }

        void notifyObservers() override
        {
            for (Observer observer: observers)
            {
                observer.update(getTemperature(), getHumidity(), getPressure());
            }
        }

        static double getTemperature()
        { return 0.0; }

        static double getHumidity()
        { return 0.0; }

        static double getPressure()
        { return 0.0; }

        void measurementsChanged()
        {
            notifyObservers();
        }
    };

    class CurrentConditionsDisplay : public Observer
    {
    private:
        double temperature{};
        double humidity{};
        double pressure{};
    public:
        explicit CurrentConditionsDisplay(WeatherData &weatherData)
        {
            weatherData.registerObserver(*this);
        }

        void update(double temperature_t, double humidity_t, double pressure_t) override
        {
            temperature = temperature_t;
            humidity = humidity_t;
            pressure = pressure_t;
            display();
        }

        void display() override
        {
            cout << "Temperature: " << temperature << "C\n";
            cout << "Humidity: " << humidity << "%\n";
            cout << "Pressure: " << pressure;
        }
    };

    class StatisticsDisplay : public Observer
    {
    private:
        double temperature{};
        double humidity{};
        double pressure{};
    public:
        explicit StatisticsDisplay(WeatherData &weatherData)
        {
            weatherData.registerObserver(*this);
        }

        void update(double temperature_t, double humidity_t, double pressure_t) override
        {
            temperature = temperature_t;
            humidity = humidity_t;
            pressure = pressure_t;
            display();
        }

        void display() override
        {
            cout << "Old Temperature: " << temperature - 10 << "C\n";
            cout << "Old Humidity: " << (humidity + 12) * 2 << "%\n";
            cout << "Old Pressure: " << pressure + 10e4 << "Pa\n";
        }
    };

    class ForecastDisplay : public Observer
    {
    private:
        double temperature{};
        double humidity{};
        double pressure{};
    public:
        explicit ForecastDisplay(WeatherData &weatherData)
        {
            weatherData.registerObserver(*this);
        }

        void update(double temperature_t, double humidity_t, double pressure_t) override
        {
            temperature = temperature_t;
            humidity = humidity_t;
            pressure = pressure_t;
            display();
        }

        void display() override
        {
            cout << "New Temperature: " << temperature + 3 << "C\n";
            cout << "New Humidity: " << humidity + 20 << "%\n";
            cout << "New Pressure: " << pressure + 10e3 << "Pa\n";
        }
    };
}

using namespace Observer;

int main()
{
    auto weatherData = new WeatherData();
    auto currentConditionsDisplay = new CurrentConditionsDisplay(*weatherData);
    auto statisticsDisplay = new StatisticsDisplay(*weatherData);
    auto forecastDisplay = new ForecastDisplay(*weatherData);


    return 0;
}
 
 