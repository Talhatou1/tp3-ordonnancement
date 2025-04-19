#include "Machine.h"
#include "include/json.hpp"
#include <fstream>

using json = nlohmann::json;

Machine::Machine(const int id, const string& name) : id(id), name(name) {}

vector<Device*> Machine::getRelatedDevices() const {
    return related_devices;
}

unordered_map<int, Machine*> Machine::BuildMachinesFromJsonFile(
    const string &path,
    const unordered_map<int, Device*> &devices
) {
    unordered_map<int, Machine*> machines;
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Cannot open machines file: " + path);

    json data;
    file >> data;

    for (const auto& m : data["machines"]) {
        int id = m["id"];
        string name = m["name"];
        Machine* machine = new Machine(id, name);

        for (int deviceId : m["related_devices"]) {
            if (devices.count(deviceId)) {
                machine->related_devices.push_back(devices.at(deviceId));
            }
        }

        machines[id] = machine;
    }

    return machines;
}
