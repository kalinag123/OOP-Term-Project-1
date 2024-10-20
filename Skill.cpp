// Author: Kalina Gavrilova
// Project 4
// Desc: Contains Skill method implementations.

#include "Skill.h"
#include <cmath>

Skill::Skill(std::string &Name, std::string &Desc)
{
    name = Name;
    description = Desc;
}

/// <summary>
/// preconditions: None.
/// postconditions: Will consider two skill instances equal if their names, descriptions,
/// and types match.
/// </summary>
bool Skill::operator==(Skill &other) {

    return name == other.name && description == other.description && typeid(this) == typeid(other);
}

/// <summary>
/// preconditions: None.
/// postconditions: Will consider two skill instances not equal if their names, descriptions, or
/// types do not match.
/// </summary>
bool Skill::operator!=(Skill &other) {

    return name != other.name || description != other.description || typeid(this) == typeid(other);
}

Skill &Skill::operator=(Skill const &other) {
    name = other.name;
    description = other.description;

    return *this;
}

/// <summary>
/// preconditions: None.
/// postconditions: Does not change any variable state- just returns an estimate.
/// </summary>
double Skill::calculateCost(double baseCost, double taskDifficulty, double empLevel) const {
    double timeMultiplier;

    if (empLevel > 0)
    {
        timeMultiplier = taskDifficulty / empLevel;
    }

    else
    {
        timeMultiplier = taskDifficulty + 1;
    }

    return baseCost * timeMultiplier;

}

std::string Skill::get_name() const{
    return name;
}

std::string Skill::get_desc() const{
    return description;
}

ExponentialSkill::ExponentialSkill(std::string name, std::string description) : Skill(name, description) {};

/// <summary>
/// preconditions: Skill must be defined as an ExponentialSkill to have access to this method.
/// postconditions: None.
/// </summary>
double ExponentialSkill::calculateCost(double baseCost, double taskDifficulty, double empLevel) const
{
    double difference = empLevel - taskDifficulty;
    double timeMultiplier;

    if (difference > 0)
    {
        timeMultiplier = 1 / pow(difference, 2.0);
    }

    else { timeMultiplier = pow(difference, 2.0); }


    return baseCost * timeMultiplier;
}

StaticSkill::StaticSkill(std::string name, std::string description) :
        Skill(name, description), base_level_skill(Skill(name,description)) {};

/// <summary>
/// preconditions: Skill must be defined as a StaticSkill to have access to this method.
/// postconditions: None.
/// </summary>
double StaticSkill::calculateCost(double baseCost, double taskDifficulty, double empLevel) const {
    double originalEstimate = base_level_skill.calculateCost(baseCost, taskDifficulty, empLevel);

    return (baseCost + originalEstimate) / 2;
}

RandomSkill::RandomSkill(std::string name, std::string description) : Skill(name, description) {};

/// <summary>
/// preconditions:
/// Skill must be defined as a RandomSkill to have access to this method.
/// </summary>
double RandomSkill::calculateCost(double baseCost, double taskDifficulty, double empLevel) const {

    int max = std::max(empLevel,taskDifficulty);
    int min = std::min(empLevel,taskDifficulty);
    double timeMultiplier = std::rand() % (max - min + 1) + min;

    int faster = std::rand() % (2 - 0 + 1) + 0;

    if(faster == 1)
    {
        return baseCost / timeMultiplier;
    }

    return baseCost * timeMultiplier;
}

Skill::~Skill() = default;
