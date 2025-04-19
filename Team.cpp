#include "Team.h"
#include "Device.h"
#include "include/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Team::Team(const string& name, const vector<string>& capabilities)
    : name(name), capabilities(capabilities) {}

vector<Team*> Team::BuildTeamsFromJsonFile(const string &path) {
    vector<Team*> teams;
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Cannot open teams file: " + path);

    json data;
    file >> data;

    for (const auto& item : data["teams"]) {
        string name = item["name"];
        vector<string> capabilities = item["capabilities"].get<vector<string>>();
        Team* team = new Team(name, capabilities);
        teams.push_back(team);
    }

    return teams;
}
