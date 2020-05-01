#include "Team.h"

Team::Team() {
    teamName = "NOT D1";
    setStatsToZero();
    rating = NOT_D1_RATING;
}

Team::Team(string name) {
    teamName = name;
    setStatsToZero();
}

void Team::setStatsToZero() {
    statRating = 0;
    seasonRating = 0;
    rating = 0;
	GP = 0;
	wins = 0;
	losses = 0;
}

double Team::calculateRating() {
    double rar = statRating * STAT_WEIGHT +
        seasonRating * GAME_WEIGHT  + preseasonRating * PRESEASON_WEIGHT;
    return rar;
}

void Team::addGame(double rat, bool win) {
    GP++;
    if (win) {
        wins++;
    }
    else {
        losses++;
    }

    gameRatings.push_back(rat);
    //change gameRating to new average of all game ratings
    double total = 0;
    for (size_t i = 0; i < gameRatings.size(); i++) {
        total += gameRatings[i];
    }
    seasonRating = total / GP;
    rating = calculateRating();
}

string Team::getName() const{
    return teamName;
}

double Team::getRating() const{
    return rating;
}

double Team::getSeasonRating() const{
    return seasonRating;
}

double Team::getStatRating() const{
    return statRating;
}

double Team::getPreseasonRating() const {
	return preseasonRating;
}

void Team::printGameRatings(ofstream& outs) {
    for (size_t i = 0; i < gameRatings.size(); i++) {
        outs << gameRatings[i] << "\t\t";
    }
}

void Team::setName(string name) {
    teamName = name;
}

void Team::setRating(double rateIn) {
    rating = rateIn;
}

void Team::setSeasonRating(double rat) {
    seasonRating = rat;
	rating = calculateRating();
}

void Team::setStatRating(double rat) {
	statRating = rat;
	rating = calculateRating();
}

void Team::setStats(vector<double>& oStats_in, vector<double>& dStats_in) {
	oStats = oStats_in;
	dStats = dStats_in;
}

void Team::setStats(vector<double>& oStats_in, vector<double>& dStats_in, double preseasonRating_in) {
	oStats = oStats_in;
	dStats = dStats_in;
}

void Team::setPreseasonRating(double rat) {
	preseasonRating = rat;
}

int Team::getGP() {
    return GP;
}

int Team::getWins() {
    return wins;
}

int Team::getLosses() {
    return losses;
}