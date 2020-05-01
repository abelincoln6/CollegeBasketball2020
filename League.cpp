#include "League.h"

League::League()
{
    createTeams();
	day = 0;
	teamNames.reserve(NUM_TEAMS);
	normalizeStats();
	normalizeStatRatings();
}

void League::readScores(ifstream& scores) {
    string str1;
    string str2;
    string team1;
    string team2;
    int score1;
    int score1Digits;
    int score2;
    int score2Digits;
    string winTeam;
    string loseTeam;
    while (scores.good()) {
		incrementDay();
		//cout << day << endl;
        //get two lines at once because two teams in game
        getline(scores, str1);
        getline(scores, str2);
        //remove final and whitespace from scores
        cropLine(str1);
        cropLine(str2);

        score1Digits = findNumDigits(str1);
        score2Digits = findNumDigits(str2);
        string t1 = str1.substr(0, str1.size() - score1Digits - 1);
        string t2 = str2.substr(0, str2.size() - score2Digits - 1);
        removeSeed(t1);
        removeSeed(t2);
        score1 = stoi(str1.substr(str1.size() - score1Digits));
        score2 = stoi(str2.substr(str2.size() - score2Digits));

        int MOV = abs(score1 - score2);
        bool team1win = score1 > score2;
        
		auto it = teamList.find(t1);
		auto it2 = teamList.find(t2);
		Team team1;
		Team team2; 
		bool t1d1 = it != teamList.end();
		bool t2d1 = it2 != teamList.end();
		if (t1d1) {
			team1 = it->second;
		}
		if (t2d1) {
			team2 = it2->second;
		}

		if (t1d1) {
			Game g1(team2, MOV, team1win, false, day);
			(it->second).addGame(g1.getRating(), team1win);
		}
		
		if (t2d1) {
			Game g2(team1, MOV, !team1win, true, day);
			(it2->second).addGame(g2.getRating(), !team1win);
		}
    }

	normalizeSeasonRatings();
}

void League::createTeams() {
    ifstream ins;
	ifstream oStatReader, dStatReader, preseasonReader;
    string fileName;
    ins.open("Teams.txt");
	oStatReader.open("oStats.txt");
	dStatReader.open("dStats.txt");
	preseasonReader.open("PreseasonRatings.txt");
    string teamName;
	double preseasonRating;
	vector<double> oStatsTotals;
	vector<double> dStatsTotals;
    while (getline(ins, teamName)) {
		teamNames.push_back(teamName);
		preseasonReader >> preseasonRating;
		double oStat, dStat;
		vector<double> oStats(NUM_CATEGORIES);
		vector<double> dStats(NUM_CATEGORIES);

		for (int s = 0; s < NUM_CATEGORIES; ++s) {
			oStatReader >> oStat;
			dStatReader >> dStat;
			oStats[s] = oStat;
			dStats[s] = dStat;
		}
       
		Team t(teamName);
		t.setStats(oStats, dStats);
		t.setPreseasonRating(preseasonRating);
		t.setRating(t.calculateRating());
		teamList.emplace(teamName, t);
    }

    ins.close();
	oStatReader.close();
	dStatReader.close();
}

void League::printTeams() {
	vector<Team> sortedTeams;
    for (auto i = teamList.begin(); i != teamList.end(); ++i) {
		sortedTeams.push_back(i->second);
    }
    sort(sortedTeams.begin(), sortedTeams.end(), sortByRating());

    for (int i = NUM_TEAMS - 1; i >= 0; i--) {
        Team t = sortedTeams[i];

        cout << t.getName();
        //for alignment
        int len = t.getName().size();
        for (int i = 0; i < 7 - len / 4; i++) {
             cout << "\t";
        }
        cout << "\t" << round(t.getRating() * 1000) / 1000 + 0.0001 << "\t\t"
            << t.getWins() << "\t\t" << t.getLosses() <<
            "\t" << t.getStatRating() << "\t\t" << t.getSeasonRating() << "\n";
        //outs << "\t\t";
        //t.printGameRatings(outs);
        //outs << endl;
    }
    
}


int League::findNumDigits(string str) {
    int i = str.size() - 1;
    int count = 0;
    while (isdigit(str.at(i))) {
        i--;
        count++;
    }
    return count;
}

void League::removeSeed(string& team) {
    for (size_t i = 0; i < team.size(); i++) {
        if (team.at(i) == '(') {
            //check for number, some teams have () in their name such as
            //St. Johns (NY)
            if (isdigit(team.at(i + 1))) {
                int pos = team.find_last_of('(');
                //-1 is for the space always right before seed
                team = team.substr(0, pos - 1);
            }
        }
    }
}

void League::cropLine(string& str) {
    if (str.size() > 4 && str.substr(str.size() - 5) == "Final") {
        str = str.substr(0, str.size() - 5);
    }
    else if (str.substr(str.size() - 2) == "OT") {
        str = str.substr(0, str.size() - 2);
    }
    //take 2 spaces off if number isn't at 2nd to last position
    if (!isdigit(str.at(str.size() - 2))) {
        str = str.substr(0, str.size() - 2);
    }
    //take 1 off otherwise
    else {
        str = str.substr(0, str.size() - 1);
    }
}

void League::makeFinalRatings() {
	for (size_t i = 0; i < NUM_TEAMS; ++i) {
		auto it = teamList.find(teamNames[i]);
		it->second.setRating(it->second.getSeasonRating() * GAME_WEIGHT + it->second.getStatRating() * STAT_WEIGHT + it->second.getSeasonRating() * PRESEASON_WEIGHT);
	}
}

void League::normalizeStatRatings() {
	vector<double> ratings;

	for (auto it = teamList.begin(); it != teamList.end(); ++it) {
		ratings.push_back(it->second.getStatRating());
	}

	double avg = mean(ratings);
	double dev = sdev(ratings);

	for (size_t i = 0; i < NUM_TEAMS; ++i) {
		auto it = teamList.find(teamNames[i]);
		double newRating = it->second.getStatRating();
		newRating = (newRating - avg) / dev;
		it->second.setStatRating(newRating);
	}
}

void League::normalizeSeasonRatings() {
	vector<double> ratings;

	for (auto it = teamList.begin(); it != teamList.end(); ++it) {
		ratings.push_back(it->second.getSeasonRating());
	}

	double avg = mean(ratings);
	double dev = sdev(ratings);

	for (size_t i = 0; i < NUM_TEAMS; ++i) {
		auto it = teamList.find(teamNames[i]);
		double newRating = it->second.getSeasonRating();
		newRating = (newRating - avg) / dev;
		it->second.setSeasonRating(newRating);
	}
}

void League::normalizeStats() {
	vector<vector<double>> oStats;
	vector<vector<double>> dStats;
	for (int i = 0; i < NUM_CATEGORIES; ++i) {
		vector<double> dummy;
		oStats.push_back(dummy);
		dStats.push_back(dummy);
		for (auto it = teamList.begin(); it != teamList.end(); ++it) {
			Team t = it->second;
			oStats[i].push_back(t.oStats[i]);
			dStats[i].push_back(t.dStats[i]);
		}
	}

	vector<double> oAvgs(NUM_CATEGORIES);
	vector<double> oSdevs(NUM_CATEGORIES);
	vector<double> dAvgs(NUM_CATEGORIES);
	vector<double> dSdevs(NUM_CATEGORIES);

	for (int i = 0; i < NUM_CATEGORIES; ++i) {
		oAvgs[i] = mean(oStats[i]);
		oSdevs[i] = sdev(oStats[i]);
		dAvgs[i] = mean(dStats[i]);
		dSdevs[i] = sdev(dStats[i]);
	}

	for (size_t i = 0; i < NUM_TEAMS; ++i) {
		auto it = teamList.find(teamNames[i]);
		vector<double> newOStats(NUM_CATEGORIES);
		vector<double> newDStats(NUM_CATEGORIES);
		for (int i = 0; i < NUM_CATEGORIES; ++i) {
			double o = it->second.oStats[i];
			double d = it->second.dStats[i];
			o = ((o - oAvgs[i]) / oSdevs[i]) * O_STAT_WEIGHTS[i];
			d = ((d - dAvgs[i]) / dSdevs[i]) * D_STAT_WEIGHTS[i];
			newOStats[i] = o;
			newDStats[i] = d;
		}
		it->second.oStats = newOStats;
		it->second.dStats = newDStats;
		it->second.setStatRating(sum(newOStats) + sum(newDStats));
	}
}

double League::mean(vector<double>& in) {
	double total = 0;

	for (size_t i = 0; i < in.size(); ++i) {
		total += in[i];
	}

	total /= in.size();

	return total;
}

double League::sdev(vector<double>& in) {
	double sdev = 0;
	double avg = mean(in);

	for (size_t i = 0; i < in.size(); ++i) {
		sdev += pow(in[i] - avg, 2);
	}

	sdev /= in.size();

	return sqrt(sdev);
}

double League::sum(vector<double>& in) {
	double total = 0;

	for (size_t i = 0; i < in.size(); ++i) {
		total += in[i];
	}

	return total;
}