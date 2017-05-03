#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H


#include <string>
#include <vector>

using string = std::string;

enum Hand {RIGHT, LEFT};
enum League {NL, AL};

struct TeamData {
    int year;
    string name;
    League league;
    int salery;
};

class PlayerData {
    public:
        string first_name;
        string last_name;
        int year;
        string country;
        int weight;
        int height;
        Hand bats;
        Hand throws;

        std::vector<TeamData> teams;

        PlayerData();
        string toString();
};




#endif