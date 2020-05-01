#pragma once
#include <string>
#include "Team.h"
using namespace std;

class Game
{
    public:
        //all constructors call calculateRating()
        Game();
        Game(Team o, int MOVin, bool win);
		Game(Team o, int MOVin, bool win, bool homeGame, int dayin);
        double getRating() const;
        bool isWin() const;
        Team getOpponent() const;
        void setOpponent(Team o);
        bool isHome() const;
        int getMOV() const;
        void setMOV(int n);
        int getDay() const;
        void setDay(int d);

    private:
        //modifies rating according to algorithm
        void calculateGameRating(bool win, bool home, int MOV, int day);
        double rating;
        bool isWon;
        bool home;
        Team opponent;
        int MOV;
        int day;
};

