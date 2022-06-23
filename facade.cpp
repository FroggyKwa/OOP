#include <iostream>

using namespace std;

namespace Facade
{

    class Amplifier
    {
    private:
        int volume = 0;
    public:
        void on()
        {
            cout << "Amplifier is on" << endl;
        }

        void off()
        {
            cout << "Amplifier is off" << endl;
        }

        void set_volume(int volume)
        {
            this->volume = volume;
            cout << "Amplifier is set on " << volume << "%" << endl;
        }
    };

    class Tuner
    {
    public:
        Amplifier *amplifier;
        int Am = 0;
        int Fm = 0;
        int frequency = 0;

        explicit Tuner(Amplifier *amplifier)
        {
            this->amplifier = amplifier;
        }

        void on()
        {
            cout << "Tuner is on" << endl;
        }

        void off()
        {
            cout << "Tuner is off" << endl;
        }

        void set_frequency(int frequncy)
        {
            this->frequency = frequncy;
        }

        void set_Am(int Am)
        {
            this->Am = Am;
            cout << "Tuner Am is set on " << Am << endl;
        }

        void set_Fm(int Fm)
        {
            this->Fm = Fm;
            cout << "Tuner Fm is set on " << Fm << endl;
        }
    };

    class DVDPlayer
    {
    public:
        Amplifier *amplifier;
        string movie = "";

        explicit DVDPlayer(Amplifier *amplifier)
        {
            this->amplifier = amplifier;
        }


        void on()
        {
            cout << "DVD Player is on" << endl;
        }

        void off()
        {
            cout << "DVD Player is off" << endl;
        }

        void set_dvd(string movie)
        {
            this->movie = movie;
            cout << "DVD is set " << this->movie;
        }

        void play()
        {
            if (this->movie != "")
            {
                cout << "DVD Player is playing " << this->movie << endl;
            } else
            {
                cout << "No DVD, nothing to play" << endl;
            }
        }

        void eject()
        {
            this->movie = "";
            cout << "DVD is ejected" << endl;
        }

        void pause()
        {
            cout << "DVD player is paused." << endl;
        }
    };

    class Projector
    {
    public:
        DVDPlayer *dvdPlayer;

        explicit Projector(DVDPlayer *dvdPlayer)
        {
            this->dvdPlayer = dvdPlayer;
        }


        void on()
        {
            cout << "Projector is on" << endl;
            if (!this->dvdPlayer->movie.empty())
            {
                cout << "Projector is showing " << this->dvdPlayer->movie;
            }
        }

        void off()
        {
            cout << "Projector is off" << endl;
        }
    };

    class PopcornPopper
    {
    public:
        void getPopcorn(const string &type)
        {
            cout << "Popcorn popper dropped some " << type << " popcorn" << endl;
        }

        void on()
        {
            cout << "Popcorn popper is on" << endl;
        }

        void off()
        {
            cout << "Popcorn popper is off" << endl;
        }
    };

    class HomeTheatreFacade
    {
    private:
        Amplifier *amplifier;
        DVDPlayer *dvdPlayer;
        Tuner *tuner;
        PopcornPopper *popcornPopper;
        Projector *projector;

    public:
        explicit HomeTheatreFacade(Amplifier *amplifier, DVDPlayer *dvdPlayer, Projector *projector, Tuner *tuner,
                                   PopcornPopper *popcornPopper)
        {
            this->amplifier = amplifier;
            this->dvdPlayer = dvdPlayer;
            this->projector = projector;
            this->tuner = tuner;
            this->popcornPopper = popcornPopper;
        }

        void watch_movie(const string &film_name, const string &popcorn_type)
        {
            amplifier->on();
            dvdPlayer->on();
            dvdPlayer->set_dvd(film_name);
            projector->on();
            tuner->on();
            amplifier->set_volume(25);
            popcornPopper->on();
            popcornPopper->getPopcorn(popcorn_type);
            dvdPlayer->play();
        }

        void end_watching()
        {
            dvdPlayer->off();
            dvdPlayer->eject();
            projector->off();
            tuner->off();
            amplifier->off();
            popcornPopper->off();
        }
    };


}

using namespace Facade;

int main(int argc, char *argv[])
{
    auto amplifier = new Amplifier();
    auto dvdPlayer = new DVDPlayer(amplifier);
    auto tuner = new Tuner(amplifier);
    auto popcorn_popper = new PopcornPopper();
    auto projector = new Projector(dvdPlayer);
    auto cinema = new HomeTheatreFacade(amplifier, dvdPlayer, projector, tuner, popcorn_popper);
    cinema->watch_movie("The Shawshank Redemption", "caramel");

    cout << "-----------------------------------------" << endl;
    cinema->end_watching();

    return 0;
}