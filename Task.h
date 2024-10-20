// Author: Kalina Gavrilova
// Project 4
// Desc: Task header file.

#ifndef _TASK_H
#define _TASK_H

#include "Skill.h"
#include "SkillSet.h"
#include <string>
#include <map>


class Task {
    /// <summary>
    /// Class Invariants:
    /// Task name can only be set when the instance is created.
    /// Task description can be changed any time.
    /// Base time that it takes to complete a task can only be set when the instance is created.
    /// Task is set to not done when the instance is created, but can be changed to done at any
    /// time. Task cannot be set to not done, however.
    /// Task skills and associated difficulties are publicly readable, but can only be set when
    /// the instance is created.
    /// Client can specify 0 or more skills, but skills and their difficulty level must be in SkillSet
    /// format.
    ///
    /// </summary>
private:
    std::string name;
    std::string description;
    /// in minutes
    float baseTime;
    bool done;
    SkillSet requiredSkills;

public:
    /// constructor
    Task(std::string &name, std::string &description, float time, SkillSet &skills);
    /// copy constructor
    Task(const Task &other);
    /// assignment operator
    Task &operator=(const Task &other);
    /// getters and setters
    float getTime() const;
    bool getState() const;
    const SkillSet& getSkills() const;
    void setDone();
    void setDescription(std::string &new_desc);
    /// destructor
    ~Task();
};


#endif //_TASK_H
