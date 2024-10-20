// Author: Kalina Gavrilova
// Project 4
// Desc: SkillSet header file.

#ifndef PROJECT4_SKILLSET_H
#define PROJECT4_SKILLSET_H

#include "Skill.h"
#include <map>

class SkillSet {
    /// <summary>
    /// Class Invariants:
    /// Skills in SkillSet are recognized as distinct based on their name.
    /// Client can access or modify a skill's level, add, and remove skills.
    /// Supports copying, comparison operators, addition and subtraction (including compound assignment)
    /// Supports multiplication and division when passed a double as a parameter.
    ///
    /// </summary>
private:
    std::map< std::string, std::pair< Skill, double>> skills;

public:
    SkillSet();
    bool add(Skill &skill, double proficiency);
    bool remove(std::string &name);

    double get_prof(std::string &name) const;
    bool update_prof(std::string &name, double new_prof);

    bool is_empty() const;
    unsigned long long size() const;
    bool contains(std::string &name) const;

    std::map<std::string, std::pair<Skill,double>>::const_iterator begin();
    std::map<std::string, std::pair<Skill,double>>::const_iterator end();
    std::map<std::string, std::pair<Skill,double>>::const_iterator find(std::string &item);

    bool operator==(SkillSet const &other);
    bool operator!=(SkillSet const &other);
    SkillSet operator+(SkillSet const &other) const;
    SkillSet &operator+=(SkillSet const &other);
    SkillSet operator-(SkillSet const &other) const;
    SkillSet &operator-=(SkillSet const &other);
    SkillSet &operator=(SkillSet const &other);
    SkillSet &operator*(double multiplier);
    SkillSet &operator/(double divisor);

    ~SkillSet();

};

#endif //PROJECT4_SKILLSET_H
