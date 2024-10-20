// Author: Kalina Gavrilova
// Project 4
// Desc: Contains Company method implementations.

#include "Company.h"

Company::Company(std::string company_name){
    name = company_name;

}

Company::Company(const Company&other) {
    *this = other;
}


Company& Company::operator=(const Company&other) {
    name = other.name;

    company_teams.clear();
    company_employees.clear();

    for(auto it = other.company_employees.begin(); it != other.company_employees.end();
        ++it) {
        hireEmployee((*it)->getName(),(*it)->getHours(),
                     (*it)->getProficiencies());
    }

    for(auto it = other.company_teams.begin(); it != other.company_teams.end(); ++it) {
        std::unique_ptr<Team> copy_team = createTeam((*it)->getName());
        std::vector<std::shared_ptr<Employee>> team_employees = (*it)->getEmployees();
        for(auto it2 = team_employees.begin(); it2 != team_employees.end(); ++it2) {
            copy_team->add(getEmployee((*it2)->getName()));
        }
    }

    return *this;
}

/// <summary>
/// Preconditions: None.
/// Postconditions: Employee will be added to the company's employee list if they are not already
/// part of the company. If an employee with this name already exists, nothing will happen.
/// </summary>
std::shared_ptr<Employee> Company::hireEmployee(const std::string& employee_name, double hours_worked,
                           SkillSet proficiencies) {
    std::shared_ptr<Employee> employee = getEmployee(employee_name);

    if(employee == nullptr) {
        std::shared_ptr<Employee> new_employee = std::make_shared<Employee>(employee_name,
                                                                            hours_worked,
                                                                            proficiencies);
        company_employees.push_back(new_employee);
        return std::make_shared<Employee>(employee_name,
                                          hours_worked,
                                          proficiencies);
    }

    return nullptr;
}

/// <summary>
/// Preconditions: None.
/// Postconditions: Employee will be removed from the company's employee list, as well as from all
/// teams' employee lists. If employee does not exist in the company, nothing will happen.
/// </summary>
void Company::fireEmployee(std::string employee_name) {
    std::shared_ptr<Employee> employee = nullptr;
    // go through employee list and remove this employee.
    for(auto it = company_employees.begin(); it != company_employees.end(); ++it) {
        if((*it)->getName() == employee_name) {
            employee = *it;
            company_employees.erase(it);
            break;
        }
    }

    if(employee != nullptr) {
        // go through every employee in every team and remove the employee.
        for (auto i = company_teams.begin(); i != company_teams.end(); ++i) {
            (*i)->remove(employee_name);
        }

        employee.reset();
    }
}

/// <summary>
/// Preconditions: None.
/// Postconditions: Team will be added to the company's teams list. Company has unique ownership over
/// its teams.
/// </summary>
std::unique_ptr<Team> Company::createTeam(std::basic_string<char> team_name) {
    std::unique_ptr<Team> new_team = std::make_unique<Team>(team_name);
    company_teams.push_back(std::move(new_team));

    return std::make_unique<Team>(team_name);
}

/// <summary>
/// Preconditions: None.
/// Postconditions: Team will be removed from the company's teams list, and its destructor will be
/// invoked.
/// </summary>
void Company::removeTeam(std::string team_name) {
    for(auto it = company_teams.begin(); it != company_teams.end(); ++it) {
        if((*it)->getName() == team_name) {
            company_teams.erase(it);
            break;
        }
    }
}

/// <summary>
/// Preconditions: None.
/// Postconditions: By nature of getting a unique pointer, caller will have ownership of team.
/// invoked.
/// </summary>
std::unique_ptr<Team> Company::getTeam(std::string team_name) {
    for(auto it = company_teams.begin(); it != company_teams.end(); ++it) {
        if((*it)->getName() == team_name) {
            return (std::move(*it));
        }
    }

    return nullptr;
}

std::shared_ptr<Employee> Company::getEmployee(std::string employee_name) {
    for(auto it = company_employees.begin(); it != company_employees.end(); ++it) {
        if((*it)->getName() == employee_name) {
            return *it;
        }
    }

    return nullptr;
}


Company::~Company() {
    company_teams.clear();
    company_employees.clear();

}

