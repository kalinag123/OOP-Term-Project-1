// Author: Kalina Gavrilova
// Project 4
// Desc: Contains Employee method implementations.

#include "Employee.h"
#include <vector>
#include <numeric>
#include <map>

Employee::Employee(const std::string& name, double hours, SkillSet &proficiencies) {
    employee_name = name;
    hoursWorked = hours;
    skillProficiencies = proficiencies;
};

Employee::Employee(const Employee &other) {
    employee_name = other.employee_name;
    hoursWorked = other.hoursWorked;
    skillProficiencies = other.skillProficiencies;
}

Employee& Employee::operator=(const Employee &other) {
    employee_name = other.employee_name;
    hoursWorked = other.hoursWorked;
    skillProficiencies = other.skillProficiencies;

    return *this;
}

/// <summary>
/// Preconditions:
/// Task skill name must match Employee skill name exactly to count as the same skill-
/// for example "Run" and "Running" are two different skills.
/// If an employee does not have a skill associated with the task, their proficiency in that task is
/// assumed to be 0.
///
/// Postconditions:
/// Returns a time estimate for how long it will take an employee to complete a task, but does not
/// change any state.
/// Will add task's skills to the employee's skill dictionary if they don't exist with a skill
/// level of 0.
/// </summary>
double Employee::timeEstimate(const Task &task) {
    // go through skills required for the task. For each one, call the time estimate function of the sill.
// then, average the time cost .

    SkillSet task_set = task.getSkills();

    if(task_set.is_empty())
    {
        return task.getTime();
    }

    double total_time = 0;
    unsigned long long count_skills_required = task_set.size();

    for(auto it = task_set.begin(); it != task_set.end(); ++it) {
        std::string skill_name = it->first;
        auto current = skillProficiencies.find(skill_name);
        if(current == skillProficiencies.end()) {
            Skill new_skill = it->second.first;
            skillProficiencies.add(new_skill,0);
        }
        total_time += it->second.first.calculateCost(task.getTime(),
                                                     it->second.second,
                                                     current->second.second);

    }
    return total_time/count_skills_required;
}

/// <summary>
/// Preconditions:
/// Assumes that client has entered employee information correctly- for example, negative employee skill
/// proficiencies may yield unexpected results.
///
/// Postconditions:
/// If task is already done, no state will be changed- employee will not gain any experience or
/// hours worked if this method is called on a task that is already done, and method will return false.
/// If task is not done, state of task will change to done, and employee will gain proficiency in the
/// skills they needed to complete the task. If the employee did not have any experience in the skill
/// prior to completing the task, they will gain at least one level of proficiency.
/// All skills associated with the task will be added to the Employee's SkillSet.
/// The state of a task cannot be reversed once it is done.
/// An employee's proficiency gained corresponds to the employee's current skill level as well as the
/// difficulty of the task- an inexperienced employee earns more experience for a difficult task than
/// an experienced employee.
/// </summary>
bool Employee::doTask(Task &task) {
    // If the task is not doable (if it is already done) return false.
    if(task.getState())
    {
        return false;
    }

    task.setDone();

    // Adds time to employee's hours worked
    double minutes_worked = timeEstimate(task);
    hoursWorked += minutes_worked / 60;

    auto taskSkills = task.getSkills();

    for(auto it = taskSkills.begin(); it != taskSkills.end(); ++it) {
        std::string skill_name = it->first;
        auto current = skillProficiencies.find(skill_name);
        if(current->second.second > 0) {
            double new_prof = 0.33 * it->second.second / current->second.second;
            skillProficiencies.update_prof(skill_name,new_prof);
        }
        else {
            double new_prof = 1.0f + 0.33f * it->second.second;
            skillProficiencies.update_prof(skill_name,new_prof);
        }
    }

    return true;
}

std::string Employee::getName() const{
    return employee_name;
}

double Employee::getHours() const{
    return hoursWorked;
};

SkillSet Employee::getProficiencies() const{
    return skillProficiencies;
};

Employee::~Employee()=default;