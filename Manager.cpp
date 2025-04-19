#include "Manager.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <map>

Manager::Manager(const unordered_map<int, Device*>& devices, const unordered_map<int, Machine*>& machines)
    : devices(devices), machines(machines) {}

void Manager::displayNotConnectedDevices() {
    std::unordered_set<int> used;

    for (auto& [id, machine] : machines) {
        for (Device* d : machine->getRelatedDevices()) {
            used.insert(d->getId());
        }
    }

    std::cout << "Devices not connected to any machine:" << std::endl;
    for (auto& [id, device] : devices) {
        if (used.find(id) == used.end()) {
            std::cout << "- Device " << id << " : " << device->getName() << std::endl;
        }
    }
}

void Manager::setupTeams(const vector<Team*>& teams) {
    this->teams = teams;
}

void Manager::buildOrganization(const function<bool(const Machine*, const Machine*)>& comparator) {
    vector<Machine*> sorted;
    for (const auto& [id, machine] : machines) {
        sorted.push_back(machine);
    }
    std::sort(sorted.begin(), sorted.end(), comparator);

    std::cout << "\nMachines to be locked:" << std::endl;
    for (auto* m : sorted) {
        std::cout << "- " << m->getId() << " : " << m->getName() << std::endl;
    }

    std::unordered_set<int> lockedDevices;
    std::map<Team*, vector<Device*>> teamLocks;

    std::cout << "\nOUTPUT (by Machine) :" << std::endl;
    for (auto* m : sorted) {
        std::cout << "Machine " << m->getId() << " : " << m->getName() << std::endl;
        for (auto* d : m->getRelatedDevices()) {
            if (lockedDevices.count(d->getId())) {
                std::cout << "- Device " << d->getId() << " ( " << d->getName() << " ) already locked out." << std::endl;
                continue;
            }

            bool locked = false;
            for (Team* t : teams) {
                const vector<string>& caps = t->getCapabilities();
                if (std::find(caps.begin(), caps.end(), d->getType()) != caps.end()) {
                    teamLocks[t].push_back(d);
                    lockedDevices.insert(d->getId());
                    std::cout << "- Device " << d->getId() << " ( " << d->getName() << " ) locked out by Team " << t->getName() << std::endl;
                    locked = true;
                    break;
                }
            }
        }
    }

    std::cout << "\nOUTPUT (by Team) :" << std::endl;
    for (auto& [team, devices] : teamLocks) {
        std::cout << "- Team " << team->getName() << " :" << std::endl;
        for (Device* d : devices) {
            std::cout << "-- " << d->getId() << " => " << d->getName() << std::endl;
        }
    }
}
