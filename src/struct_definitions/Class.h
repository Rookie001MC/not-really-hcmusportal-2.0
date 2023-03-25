#include <string>
struct Class
{
    unsigned int id;
    std::string name;
    std::string code;
    std::string enter_year;
    unsigned int max_students     = 50;
    unsigned int current_students = 0;
    LLNode *student_list;
};