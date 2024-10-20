// Author: Kalina Gavrilova
// Project 4
// Desc: Employee header file.

#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#include "Task.h"
#include <string>
#include <map>


class Employee {
    /// <summary>
/// Class Invariants:
/// Name of employee can only be set when employee instance is created.
/// Client can specify 0 or more skills, but skills and their proficiency level must be of SkillSet
/// type.
/// If client tries to do a task that has already been done, no state will be changed.
/// When an Employee does a task, the state of the task cannot be reversed.
/// </summary>
private:
    std::string employee_name;
    double hoursWorked;

    //std::map<std::string, float> proficiencyDict;
    SkillSet skillProficiencies;

public:
    /// constructor
    Employee(const std::string& name, double hours, SkillSet& proficiencies);
    /// copy constructor
    Employee(const Employee &other);
    /// assignment operator
    Employee &operator=(const Employee &other);
    /// class methods
    double timeEstimate(const Task &task);
    bool doTask(Task &task);
    /// getters
    std::string getName() const;
    double getHours() const;
    SkillSet getProficiencies() const;
    /// destructor
    ~Employee();
};


#endif //_EMPLOYEE_H
