#include "PlayerData.h"
#include <string>
#include <sstream>

using namespace std;

string handToString(Hand h) {
    return h == RIGHT ? "RIGHT" : "LEFT";
}

string leagueToString(League l) {
    return l == NL ? "NL" : "AL";
}

PlayerData::PlayerData() {
    year = -1;
}

string PlayerData::toString() {
    stringstream ss;

    ss << "First Name: " << first_name << endl;
    ss << "Last Name: " << last_name << endl;
    ss << "Year Born: " << year << endl;
    ss << "Country born: " << country << endl;
    ss << "Weight: " << weight << endl;
    ss << "Height: " << height << endl;
    ss << "Bats: " << handToString(bats) << endl;
    ss << "Throws: " << handToString(bats) << endl;
    
    for (int i = 0; i < teams.size(); ++i) {
        TeamData t = teams[i];
        ss << t.year << ", " << t.name << ", " << leagueToString(t.league) << ", " << t.salery << endl;
    }

    return ss.str();
}