//
// Created by kevin on 2025-03-25.
//

#ifndef MACHINE_H
#define MACHINE_H
#include <string>

#include "Device.h"

using namespace std;

class Machine {
private:
    int id;
    string name;
    vector<Device*> related_devices;
public:
    Machine(const int id, const string& type);

    int getId() const { return id; }
    string getName() const { return name; }
    vector<Device*> getRelatedDevices() const;

    static unordered_map<int, Machine*> BuildMachinesFromJsonFile(const string &path, const unordered_map<int, Device *> &devices);
    static unordered_map<int, Device*> deviceMap;
};



#endif //MACHINE_H
