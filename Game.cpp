#include "Game.h"

using namespace std;

Game::Game() {
    opponent = Team();
    MOV = 0;
    day = 0;
    isWon = false;
    calculateGameRating(isWon, false, MOV, 0);
}

Game::Game(Team o, int MOVin, bool win) {
    opponent = o;
    MOV = MOVin;
    isWon = win;
    calculateGameRating(isWon, home, MOV, 0);
}

Game::Game(Team o, int MOVin, bool win, bool homeGame, int dayin) {
	opponent = o;
	MOV = MOVin;
	isWon = win;
	home = homeGame;
	day = dayin;
	calculateGameRating(isWon, home, MOV, day);
}

double Game::getRating() const {
    return rating;
}

void Game::calculateGameRating(bool win, bool home, int MOV, int day) {
	double oppRating = opponent.getRating();
	double ratingCoef;
    if (oppRating >= 0) {
		ratingCoef = sqrt(oppRating);
        if (oppRating > GOOD_TEAM_CUTOFF) {
            ratingCoef += GOOD_TEAM_BOOST;
        }
    }
    else {
        ratingCoef = -sqrt(abs(oppRating));
    }
    //ratingCoef *= sqrt(oppGP);
    double MOVd = MOV;
    if (win) {
        rating = (ratingCoef * OPP_RATING_WEIGHT) + WIN_BOOST + sqrt(MOVd);
    }
    else {
        rating = (ratingCoef * OPP_RATING_WEIGHT) - WIN_BOOST - sqrt(MOVd);
    }
	if (day > ROAD_GAME_START) {
		if (home) {
			rating -= ROAD_BOOST;
		}
		else {
			rating += ROAD_BOOST;
		}
	}
	double dayCoef = sqrt((day / 1000) + 1);
	rating *= dayCoef;
}

bool Game::isWin() const{
    return isWon;
}

bool Game::isHome() const{
    return home;
}

Team Game::getOpponent() const{
    return opponent;
}

void Game::setOpponent(Team o) {
    opponent = o;
}

int Game::getMOV() const{
    return MOV;
}

void Game::setMOV(int n) {
    MOV = n;
}

int Game::getDay() const{
    return day;
}

void Game::setDay(int d) {
    day = d;
}