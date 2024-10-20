// Author: Kalina Gavrilova
// Project 4
// Desc: Main file containing P4 demo.

#include <iostream>
#include "SkillSet.h"
#include "Employee.h"
#include "Task.h"
#include "Company.h"


int main() {

    /// Creating SkillSet with all subclasses of Skill:
    std::string baking_name = "baking";
    std::string baking_desc = "bake a cake";
    Skill baking = Skill(baking_name, baking_desc);

    std::string programming_name = "programming";
    std::string programming_desc = "write a program";
    StaticSkill programming = StaticSkill(programming_name,programming_desc);

    std::string swimming_name = "swimming";
    std::string swimming_desc = "swim in a river";
    RandomSkill swimming = RandomSkill(swimming_name,swimming_desc);

    std::string accounting_name = "accounting";
    std::string accounting_desc = "journalize entries";
    ExponentialSkill accounting = ExponentialSkill(accounting_name,accounting_desc);

    std::string excel_name = "excel";
    std::string excel_desc = "working in excel";
    Skill excel = Skill(excel_name,excel_desc);

    SkillSet daves_skillset = SkillSet();
    daves_skillset.add(baking, 9.7);
    daves_skillset.add(programming, 5.3);
    daves_skillset.add(swimming, 0.6);
    daves_skillset.add(accounting, 10);


    /// Demonstrating SkillSet functionality:
    SkillSet taras_skillset = SkillSet();
    taras_skillset.add(programming,9.8);

    std::cout << "Do Dave and Tara have equal skillsets? " << (daves_skillset == taras_skillset) << std::endl;
    std::cout << "Do Dave and Tara have different skillsets? " << (daves_skillset != taras_skillset) << std::endl;

    SkillSet cams_skillset = SkillSet();
    cams_skillset = taras_skillset + daves_skillset;
    cams_skillset -= taras_skillset;
    cams_skillset.remove(baking_name);

    SkillSet tough_skillset = SkillSet();
    tough_skillset = daves_skillset * 10;

    SkillSet easy_skillset = SkillSet();
    easy_skillset = cams_skillset / 1.5;

    SkillSet jacobs_skillset = tough_skillset - easy_skillset;

    Employee dave = Employee("Dave",9.8,daves_skillset);
    Employee tara = Employee("Tara",15,taras_skillset);
    Employee cam = Employee("Cam",98,cams_skillset);
    Employee jacob = Employee("Jacob",0,jacobs_skillset);

    SkillSet accounting_skills = SkillSet();
    accounting_skills.add(excel, 9);
    accounting_skills.add(accounting, 10);

    SkillSet tech_skills = SkillSet();
    tech_skills.add(programming,10);
    tech_skills.add(excel, 4.3);

    SkillSet misc_skills = SkillSet();
    misc_skills.add(baking,5);
    misc_skills.add(swimming,5);

    std::string comp_name = "Accounting Firm";
    std::string tech_team_name = "Tech Team";
    std::string acct_team_name = "Accounting Team";


    Company accounting_firm = Company(comp_name);
    std::unique_ptr<Team> tech_team = accounting_firm.createTeam(tech_team_name);
    tech_team->add(accounting_firm.hireEmployee(dave.getName(),0,daves_skillset));
    tech_team->add(accounting_firm.hireEmployee(jacob.getName(),15,jacobs_skillset));


    std::unique_ptr<Team> accounting_team = accounting_firm.createTeam(acct_team_name);
    accounting_team->add(accounting_firm.getEmployee(dave.getName()));
    accounting_team->add(accounting_firm.hireEmployee(tara.getName(),19,taras_skillset));
    accounting_team->add(accounting_firm.hireEmployee(cam.getName(),78,cams_skillset));

    accounting_firm.removeTeam(tech_team_name);
    accounting_team->add(accounting_firm.getEmployee(jacob.getName()));

    std::string a_task_name = "accounting task";
    std::string a_task_desc = "a task related to accounting";


    Task accounting_task = Task(a_task_name, a_task_desc, 120.f, accounting_skills);

    std::string t_task_name = "tech task";
    std::string t_task_desc = "a task related to tech";


    Task tech_task = Task(t_task_name, t_task_desc, 120.f, tech_skills);

    std::string m_task_name = "misc task";
    std::string m_task_desc = "a task related to other stuff";


    Task misc_task = Task(m_task_name, m_task_desc, 120.f, misc_skills);

    std::cout << "Tech task Estimate: " << accounting_team->timeEstimate(tech_task) << std::endl;
    std::cout << "Accounting task Estimate: " << accounting_team->timeEstimate(accounting_task) << std::endl;
    std::cout << "Misc task Estimate: " << accounting_team->timeEstimate(misc_task) << std::endl;

}
