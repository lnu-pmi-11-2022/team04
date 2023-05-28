#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <fstream>
#include <stdexcept>
#include "variable.h"
using namespace std;

class Template
{
private:
    string input;
    unordered_map<string, Variable *> variables; // контейнер для зберігання змінних

public:
    Template(string text);                        // конструктор для вхідного тексту
    void add_variable(string name, string value); // додавання змінної типу string
    void add_variable(string name, vector<string> value);
    string process(); // запуски рендера темплейта
    void process_file(string path);
    string render(string str); // функція рендеру
    string evaluate(const string &data_string, unordered_map<string, Variable *> &variables);
    size_t find_close_index(const string &str);
};
#endif