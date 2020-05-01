#include "Team.h"
#include "Game.h"
#include "Global.h"
#include "League.h"

using namespace std;

int main() {

    League league;

    ifstream scoresIn;
    scoresIn.open("Scores.txt");
	if (scoresIn.fail()) {
		cout << "DUHDUH";
	}
    league.readScores(scoresIn);
    scoresIn.close();

	league.makeFinalRatings();

	league.printTeams();

	return 0;
}

