#pragma once
#include "Team.h"
#include "Game.h"
#include "Global.h"
class League
{
    public:
        //constructor fill TeamList, giving all the teams stats
        //and calculating the stat rating for each team
        League();
        //reads scores from file, adds games to teams
        //games vector via team.addGame
        void readScores(ifstream& ins);
        //prints the teams and stats into readable table format in file
        void printTeams();
		void normalizeSeasonRatings();
		void normalizeStatRatings();
		void makeFinalRatings();

		int getDay() const {
			return day;
		}
		void incrementDay() {
			++day;
		}
    private:
		unordered_map<string, Team> teamList;
		vector<string> teamNames;
        vector<Team> sortedTeamList;
		void normalizeStats();
        //fills teamList and gives all teams their stats and
        //stat rating
        void createTeams();
        //following 3 are all used to extract team from Scores.txt
        int findNumDigits(string str);
        void cropLine(string& str);
        void removeSeed(string& team);

		int day;
        
		double mean(vector<double>& in);
		double sdev(vector<double>& in);
		double sum(vector<double>& in);

		struct sortByRating {
			bool operator()(const Team& t1, const Team& t2) const {
				return t1.getRating() < t2.getRating();
			}
		};
		
};


