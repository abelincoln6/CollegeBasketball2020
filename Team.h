#pragma once

#include "Global.h"

using namespace std;


class Team {
    public:
        //default constructor sets name to "NOT D1" and rating to -20
        Team();
        Team(string name);
        string getName() const;
        double getRating() const;
        double getSeasonRating() const;
        double getStatRating() const;
		double getPreseasonRating() const;
        int getGP();
        int getWins();
        int getLosses();
        void setName(string name);
        void setRating(double rating);
        void setSeasonRating(double rating);
        void setStats(vector<double>& oStats_in, vector<double>& dStats_in);
		void setStats(vector<double>& oStats_in, vector<double>& dStats_in, double preseasonRating);
		void setStatRating(double rat);
		void setPreseasonRating(double rat);
        //increments GP as well as wins or losses accordingly
        //adds JUST THE RATING the team got for the game
        //updates seasonRating to take all games into account
        void addGame(double rating, bool win);
        void printGameRatings(ofstream& outs);
		vector<double> oStats;
		vector<double> dStats;
		//combines seasonRating and statRating according to weights
		double calculateRating();
    private:
        vector<double> gameRatings;
        string teamName;
        double rating;
        //rating based purely off of scores and opponents
        double seasonRating;
        double statRating;     
		double preseasonRating;
		void setStatsToZero();
		
        int GP;
        int wins;
        int losses;
};

