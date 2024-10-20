// Author: Kalina Gavrilova
// Project 4
// Desc: Contains Task method implementations.

#include "Task.h"

Task::Task(std::string &name, std::string &description, float time, SkillSet &skills) {
    this->name = name;
    this->description = description;
    baseTime = time;
    done = false;

    requiredSkills = skills;
}

Task::Task(const Task &other) {
    name = other.name;
    description = other.description;
    baseTime = other.baseTime;
    done = other.done;
    requiredSkills = other.requiredSkills;
}

Task& Task::operator=(const Task &other) {
    name = other.name;
    description = other.description;
    baseTime = other.baseTime;
    done = other.done;
    requiredSkills = other.requiredSkills;

    return *this;
}

float Task::getTime() const {
    return baseTime;
}

bool Task::getState() const {
    return done;
}

const SkillSet& Task::getSkills() const {
    return requiredSkills;
}

/// <summary>
/// preconditions: Done is always set to false when the object is created.
/// postconditions: Sets done to true- this cannot be reversed. Client is responsible for changing state
/// of Task instance responsibly.
/// </summary>
void Task::setDone() {
    done = true;
}

void Task::setDescription(std::string &new_desc) {
    description = new_desc;
}

Task::~Task()=default;




