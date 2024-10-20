// Author: Kalina Gavrilova
// Project 4
// Desc: Contains SkillSet method implementations.

#include "SkillSet.h"
#include "Skill.h"

SkillSet::SkillSet() = default;

/// <summary>
/// postconditions: If skill does not exist in the SkillSet, invalid argument exception will be thrown.
/// Client is responsible for handling this exception.
/// </summary>
double SkillSet::get_prof(std::string &name) const {
    auto it = skills.find(name);
    if(it != skills.end()) {
        return it->second.second;
    }
    else {
        throw std::invalid_argument("Skill does not exist.");
    }
}

/// <summary>
/// postconditions: Skill is only updated if it is in the SkillSet already. If not updated, function
/// will return false.
/// </summary>
bool SkillSet::update_prof(std::string &name, double new_prof) {
    auto it = skills.find(name);
    if(it != skills.end()) {
        it->second.second = new_prof;
        return true;
    }

    return false;
}

bool SkillSet::is_empty() const{
    if(skills.empty()) {
        return true;
    }
    return false;
}

unsigned long long SkillSet::size() const{
    return skills.size();
}

bool SkillSet::contains(std::string &name) const{
    auto it = skills.find(name);
    if(it != skills.end()) {
        return true;
    }
    return false;
}

/// <summary>
/// postconditions: Const iterator- cannot be used to write to or change the state of member
/// SkillSet variables.
/// </summary>
std::map<std::string, std::pair<Skill,double>>::const_iterator SkillSet::begin() {
    return skills.begin();
}

/// <summary>
/// postconditions: Const iterator- cannot be used to write to or change the state of member
/// SkillSet variables.
/// </summary>
std::map<std::string, std::pair<Skill,double>>::const_iterator SkillSet::end() {
    return skills.end();
}

/// <summary>
/// postconditions: Const iterator- cannot be used to write to or change the state of member
/// SkillSet variables.
/// </summary>
std::map<std::string, std::pair<Skill,double>>::const_iterator SkillSet::find(std::string &item) {
    return skills.find(item);
}

/// <summary>
/// preconditions: Name of skills act as key- so, skills with matching name will be regarded as
/// duplicates even if they have different proficiencies or Skill descriptions or types.
/// postconditions: Will not add duplicate skills to SkillSet. If unsuccessful, will return false.
/// </summary>
bool SkillSet::add(Skill &skill, double proficiency) {
    Skill current = skill;
    std::string skill_name = current.get_name();
    auto skill_and_proficiency = std::pair<Skill,double>(current,proficiency);
    auto it = skills.find(skill_name);
    if(it != skills.end()) {
        return false;
    }
    skills.insert({skill_name,skill_and_proficiency});
    return true;
}

/// <summary>
/// postconditions: Skill can only be removed if it is in the SkillSet. If not, no state is changed,
/// and function will return false.
/// </summary>
bool SkillSet::remove(std::string &name) {
    auto it = skills.find(name);
    if(it != skills.end()) {
        skills.erase(it);
        return true;
    }
    return false;
};

bool SkillSet::operator==(SkillSet const &other) {
    if(skills.size() != other.skills.size()) {
        return false;
    }

    for(auto it = skills.begin(); it != skills.end(); ++it) {
        if(other.skills.count(it->first) == 0) {
            return false;
        }
    }

    return true;
}

bool SkillSet::operator!=(SkillSet const &other) {
    return !(*this == other);
}


/// <summary>
/// postconditions: Returns a SkillSet with a combination of the Skills in each SkillSet.
/// if same skill exists in both SkillSets, applies the maximum proficiency Skill.
/// </summary>
SkillSet SkillSet::operator+(SkillSet const &other) const {
    SkillSet result;

    result += *this;
    result += other;

    return result;
}

/// <summary>
/// postconditions: Modifies this SkillSet with a combination of the Skills in each SkillSet.
/// if same skill exists in both SkillSets, applies the maximum proficiency Skill.
/// </summary>
SkillSet &SkillSet::operator+=(SkillSet const &other) {
    for(auto it = other.skills.begin(); it != other.skills.end(); ++it) {
        auto current = skills.find(it->first);
        if(current == skills.end()) {
            skills.insert({it->first,it->second});
        }
        else {
            double max_prof = std::max(it->second.second, current->second.second);
            current->second.second = max_prof;
        }
    }

    return *this;
}

/// <summary>
/// postconditions: Returns a SkillSet with only the unique skills found in the left SkillSet.
/// </summary>
SkillSet SkillSet::operator-(SkillSet const &other) const {
    SkillSet result;

    result = *this;
    result -= other;

    return result;
}

/// <summary>
/// postconditions: Modifies this SkillSet to contain only the unique skills found in the
/// this SkillSet.
/// </summary>
SkillSet &SkillSet::operator-=(SkillSet const &other) {
    for(auto it = other.skills.begin(); it != other.skills.end(); ++it) {
        auto current = skills.find(it->first);
        if (current != skills.end()) {
            skills.erase(current);
        }
    }

    return *this;
}

/// <summary>
/// postconditions: Sets this SkillSet equal to the other SkillSet. SkillSet class is not
/// responsible for any memory allocation.
/// </summary>
SkillSet &SkillSet::operator=(SkillSet const &other) {
    skills.clear();
    for(auto it = other.skills.begin(); it != other.skills.end(); ++it) {
        skills.insert({it->first,it->second});
    }

    return *this;
}

/// <summary>
/// preconditions: Takes a double as a multiplier.
/// postconditions: Modifies this SkillSet. Multiplies levels of each skill in the SkillSet
/// by this value- for example, SkillSet{(Skill1,5),(Skill2,6)} * 2 = {(Skill1,10),(Skill2,12)}.
/// </summary>
SkillSet &SkillSet::operator*(double multiplier) {
    for(auto it = skills.begin(); it != skills.end(); ++it) {
        it->second.second *= multiplier;
    }

    return *this;
}

/// <summary>
/// preconditions: Takes a double as a divisor.
/// postconditions: Modifies this SkillSet. Divides levels of each skill in the SkillSet
/// by this value- for example, SkillSet{(Skill1,5),(Skill2,6)} / 2 = {(Skill1,2.5),(Skill2,3)}.
/// Throws a runtime_error if 0 is passed as a parameter. It is the client's responsibility to
/// handle this error.
/// </summary>
SkillSet &SkillSet::operator/(double divisor) {
    if(divisor == 0) {
        throw std::runtime_error("Cannot divide by 0.");
    }

    for(auto it = skills.begin(); it != skills.end(); ++it) {
        it->second.second /= divisor;
    }

    return *this;
}

SkillSet::~SkillSet() = default;


