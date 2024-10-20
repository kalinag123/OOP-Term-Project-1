// Author: Kalina Gavrilova
// Project 4
// Desc: Company header file.

#ifndef _COMPANY_H
#define _COMPANY_H

#include "Task.h"
#include "Employee.h"
#include "Team.h"
#include <string>
#include <vector>


class Company {
/// <summary>
/// Class invariants:
/// Name can only be set when instance is created.
/// Company is responsible for its employee and team instances.
/// </summary>
private:
    std::string name;
    std::vector<std::shared_ptr<Employee>> company_employees;
    std::vector<std::unique_ptr<Team>> company_teams;
public:
    /// constructor
    Company(std::string company_name);
    /// copy constructor
    Company(const Company &other);
    /// assignment operator
    Company &operator=(const Company&other);
    /// class methods
    std::shared_ptr<Employee> hireEmployee(const std::string& employee_name, double hours_worked, SkillSet proficiencies);
    void fireEmployee(std::string employee_name);
    std::unique_ptr<Team> createTeam(std::basic_string<char> team_name);
    void removeTeam(std::string team_name);
    /// getters
    std::unique_ptr<Team> getTeam(std::string team_name);
    std::shared_ptr<Employee> getEmployee(std::string employee_name);
    /// destructors
    ~Company();
};


#endif //_COMPANY_H
