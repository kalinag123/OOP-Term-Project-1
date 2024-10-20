// Author: Kalina Gavrilova
// Project 4
// Desc: Team header file.

#ifndef _TEAM_H
#define _TEAM_H

#include <string>
#include <vector>
#include <memory>
#include "Employee.h"
#include "Task.h"

class Team {
/// <summary>
/// Class Invariants:
/// Name can only be set when an instance is created.
/// Team is not responsible for employees assigned to it, and does not allocate memory for
/// employees added to it.
/// Team copy operator does not create a deep copy of team with its own employees- instead,
/// copy shares the same employee instances with original.
///
/// </summary>
private:
    std::string team_name;
    // should be shared - team and company both point to the same employee, and an employee could be
    // in multiple teams.
    std::vector<std::shared_ptr<Employee>> team_employees;

public:
    /// constructor
    Team(std::string name);
    /// copy constructor
    Team(const Team& other);
    // assignment operator
    Team& operator=(const Team& other);
    /// class methods
    void add(std::shared_ptr<Employee>);
    void remove(const std::string employee_name);
    float timeEstimate(const Task &task);
    /// getters
    std::string getName() const;
    std::vector<std::shared_ptr<Employee>> getEmployees() const;
    /// destructor
    ~Team();

};


#endif //_TEAM_H
