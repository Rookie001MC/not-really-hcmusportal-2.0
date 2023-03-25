#include "View Information.h"

void viewListOfClasses(SchoolYear school_year)  // view all the classes in a school year.
{
	LLNode* class_list = school_year.class_list;
    for (; class_list != nullptr; class_list->next = class_list->next)
    {
        std::cout << class_list->id << " - " << class_list->name << ".\n";
    }
}

void viewStudentsInClass(Class a)             // view all the students in class. 
{
    for (int i = 0; i < a.current_students; ++i)
    {
        std::cout << i + 1 << " - " << a.student_list->id << " - " << a.student_list->name << ".\n";
    }
}
