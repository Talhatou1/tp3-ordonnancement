//
// Created by kevin on 2025-03-25.
//

#ifndef MANAGER_H
#define MANAGER_H

#include <functional>

#include "Device.h"
#include "Machine.h"
#include "Team.h"


class Manager {
private:
    unordered_map<int, Device*> devices;
    unordered_map<int, Machine*> machines;
    vector<Team*> teams;

public:

    Manager(const unordered_map<int, Device*> &devices, const unordered_map<int, Machine*> &machines);

    void displayNotConnectedDevices();

    void setupTeams(const vector<Team*> &teams);

    void buildOrganization(const function<bool(const Machine*, const Machine*)>& comparator);
};



#endif //MANAGER_H
