#include "View Information.h"

void viewListOfClasses(SchoolYear school_year)  // view all the classes in a school year.
{
    // To do: Need to read school_year.name to open the correct file !!!

    // Read data in a file.
    std::ifstream fin;
    fin.open("D://school_year.txt");

    if (!fin.is_open()) std::cout << "Cannot open file!";

    LLNode* class_l = nullptr;
    LLNode* cur = class_l;

    while (!fin.eof())
    {
        LLNode* tmp = new LLNode;
        std::getline(fin, tmp->name);
        tmp->next = nullptr;
        if (cur == nullptr)
        {
            class_l = cur = tmp;
        }
        else
        {
            cur->next = tmp;
            cur = tmp;
        }
    }

    for (; class_l != nullptr; class_l = class_l->next)
    {
        std::cout << "\n" << class_l->name;
    }

    fin.close();
}

void viewStudentsInClass(const std::string& filename)           // view all the students in class. 
{   
	Student* students = new Student[MAX];
	std::ifstream file(filename + ".txt");
	int cnt = 0;
	if (file.is_open())
	{
		int i = 0;
		std::string line;
		std::getline(file, line);
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string token;

			Student stu;

			std::getline(ss, token, ',');

			std::getline(ss, token, ',');
			stu.id = token;

			std::getline(ss, token, ',');
			stu.first_name = token;

			std::getline(ss, token, ',');
			stu.last_name = token;

			std::getline(ss, token, ',');
			stu.gender = token;

			std::getline(ss, token, ',');
			stu.dob = token;

			std::getline(ss, token);
			stu.social_id = token;

			students[i] = stu;
			i++;
		}
		cnt = i;
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file" << std::endl;
	}

	for (int j = 0; j < cnt; ++j)
	{
		std::cout << j + 1 << "/ " << students[j].id << " - " << students[j].last_name
			<< " " << students[j].first_name << " - " << students[j].gender << " - " <<
			students[j].dob << " - " << students[j].social_id << ". \n";
	}
}

void viewListOfCourse(Course* course ,int numCourse)     // View a list of courses.
{
    for (int i = 0; i < numCourse; i++)
    {
        std::cout << Course[i].name << " - " << Course[i].code << "\n\n";
    }
}

void viewStudentsInCourse(Course* a)
{
    int i = 0;
    std::cout << "Number of students registered: " << a.current_students << " / " << a.max_students
         << '\n';
    while (a->student_list)
    {
        std::cout << i + 1 << " - " << a->student_list->ID << " - " << a->student_list->name << ".\n";
        i++;
        a->studentList = a->studentList->studentNext;
    }
}
