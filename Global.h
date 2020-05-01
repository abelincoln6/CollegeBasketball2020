#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

const int NUM_TEAMS = 353;
const double ROAD_BOOST = 2;
const double STAT_WEIGHT = 1;
const double GAME_WEIGHT = 1;
const double PRESEASON_WEIGHT = 0.4;
const double OPP_RATING_WEIGHT = 1.5;
const double GOOD_TEAM_CUTOFF = 2;
const double GOOD_TEAM_BOOST = 1;
const double NOT_D1_RATING = -20;
const double WIN_BOOST = 0;
const int TOTAL_GAMES = 5700;
const int NUM_CATEGORIES = 11;
const int ROAD_GAME_START = 1300;

const vector<double> O_STAT_WEIGHTS = { 51.8927, 50.2205, 62.7159, 61.5399, 54.4836, 54.943, 57.3502, 62.4403, -38.2212, 56.652, 53.9691 };
const vector<double> D_STAT_WEIGHTS = { -56.0639, -51.7824, -66.097, -62.6057, -57.24, -58.7284, -52.7931, -64.9577, 46.5638, -57.3502, -56.3396 };
//just for reference, for now
const vector<string> CATEGORY_ORDER = { "FTr", "3PAr", "TS%","TRB%", "AST%", "STL%", "BLK%", "eFG%", "TOV%", "ORB%", "FTFGA" };