// Author: Kalina Gavrilova
// Project 4
// Desc: Contains Team method implementations.

#include "Team.h"
#include <stdexcept>

Team::Team(std::string name) {
    team_name = name;
}

Team::Team(const Team& other) {
    *this = other;
}

Team& Team::operator=(const Team& other) {
    team_name = other.team_name;

    team_employees.clear();
    for(auto it = other.team_employees.begin(); it != other.team_employees.end(); ++it) {
        add(*it);
    }

    return *this;
}

void Team::add(std::shared_ptr<Employee> employee) {
    team_employees.push_back(employee);
}

void Team::remove(const std::string employee_name) {
    for(auto it = team_employees.begin() ; it != team_employees.end() ; ++it) {
        if((*it)->getName() == employee_name) {
            team_employees.erase(it);
            break;
        }
    }
}
/// preconditions:
///
/// postconditions:
/// if a team has no team_employees assigned to it, function will throw an out of range exception.

float Team::timeEstimate(const Task &task) {

    if(team_employees.size() == 0) {
        throw std::out_of_range("This team does not have any team_employees assigned to it.");
    }

    auto it = team_employees.begin();
    float minimum_time = (*it)->timeEstimate(task);

    for (it+1; it != team_employees.end(); ++it) {
        if((*it)->timeEstimate(task) < minimum_time) {
            minimum_time = (*it)->timeEstimate(task);
        }
    }

    return minimum_time;
}

std::string Team::getName() const{
    return team_name;
}

std::vector<std::shared_ptr<Employee>> Team::getEmployees() const {
    return team_employees;
}

Team::~Team()=default;