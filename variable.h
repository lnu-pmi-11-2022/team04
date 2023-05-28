
#include <iostream>
#include <vector>
using namespace std;

struct Variable // Тип даних для змінних в темплейті
{

    Variable(string str)
    {
        str_value = str;
    }
    Variable(vector<string> &vec)
    {
        vector_value = vec;
    }
    string to_string()
    {
        return str_value;
    }
    bool operator==(string &condition)
    {
        return condition == str_value;
    }
    string str_value;
    vector<string> vector_value;
};