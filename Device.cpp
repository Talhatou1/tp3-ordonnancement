#include "Device.h"
#include "include/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Device::Device(const int id, const string& type, const string& name)
    : id(id), type(type), name(name) {}

unordered_map<int, Device*> Device::BuildDevicesFromJsonFile(const string &path) {
    unordered_map<int, Device*> devices;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open devices file: " + path);
    }

    json data;
    file >> data;

    for (const auto& item : data["devices"]) {
        int id = item["id"];
        string type = item["type"];
        string name = item["name"];
        devices[id] = new Device(id, type, name);
    }

    return devices;
}
