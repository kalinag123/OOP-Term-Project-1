// Author: Kalina Gavrilova
// Project 4
// Desc: Skill header file.

#ifndef PROJECT4_SKILL_H
#define PROJECT4_SKILL_H

#include <iostream>

class Skill {
    /// <summary>
    /// Class Invariants:
    /// Skill name and description are immutable and can only be set when the instance is created.
    /// Skill instances with the same name and description will be considered equal.
    ///
    /// </summary>

protected:
    std::string name;
    std::string description;
public:
    std::string get_name() const;

    std::string get_desc() const;

    bool operator==(Skill &other);

    bool operator!=(Skill &other);

    Skill &operator=(Skill const &other);

    Skill(std::string &Name, std::string &Desc);

    virtual double calculateCost(double baseCost, double taskDifficulty, double empLevel) const;

    ~Skill();
};




class ExponentialSkill : public Skill {
public:
    ExponentialSkill(std::string name, std::string description);

    double calculateCost(double baseCost, double taskDifficulty, double empLevel) const override;
};

class StaticSkill : public Skill {
private:
    Skill base_level_skill;
public:
    StaticSkill(std::string name, std::string description);

    double calculateCost(double baseCost, double taskDifficulty, double empLevel) const override;
};

class RandomSkill : public Skill {
public:
    RandomSkill(std::string name, std::string desc);
    double calculateCost(double baseCost, double taskDifficulty, double empLevel) const override;
};

#endif //PROJECT4_SKILL_H
