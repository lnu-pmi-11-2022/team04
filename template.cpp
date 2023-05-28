#include "template.h"

Template::Template(string text) // конструктор для вхідного тексту
{
    this->input = text;
}

void Template::add_variable(string name, string value) // додавання змінної типу string
{
    variables[name] = new Variable(value);
}
void Template::add_variable(string name, vector<string> value)
{
    variables[name] = new Variable(value);
}
string Template::process() // запуски рендера темплейта
{
    return render(input);
}
void Template::process_file(string path)
{
    input = "";
    fstream inputFile(path);
    if (inputFile.is_open())
    {
        while (inputFile)
        {
            input += inputFile.get();
        }
        input[input.length() - 1] = ' ';
    }
    else
        cout << "Unable to open file";
    inputFile.close();
    string result = process();

    inputFile.open(path, ios::out);
    if (!inputFile)
    {
        cout << "File not created!";
    }
    else
    {
        inputFile << result;
    }
    inputFile.close();
}
string Template::render(string str) // функція рендеру
{
    if (str.find("{") == string::npos) // якшо в строці більше немає "{" то виконуємо evaluate яка замінює значення, в іншому випадку шукаємо {} вкладення в теперішній строці
    {
        return evaluate(str, variables);
    }
    size_t pos = str.find("{");
    while (pos != string::npos) // перевіряємо чи ми не вийшли за межі строки та шукаємо зліва направо {} дужки, якщо знайдено то виконуємо рекурсію і передаємо вкладну в {} строку
    {
        size_t end_pos = pos + find_close_index(str.substr(pos));
        string replacement = str.substr(pos + 1, end_pos - pos - 1);
        string rendered = render(replacement);
        if (replacement.find("{") != string::npos)
        {
            str = str.substr(0, pos) + render(rendered = "{" + rendered + "}") + str.substr(end_pos + 1);
        }
        else
        {
            str = str.substr(0, pos) + rendered + str.substr(end_pos + 1);
        }

        pos = str.find("{", pos + 1);
    }
    return str;
}

string Template::evaluate(const string &data_string, unordered_map<string, Variable *> &variables)
{
    if (data_string.find("% if") != string::npos)
    {
        string condition = data_string.substr(5, data_string.find(" ", 5) - 5);
        string data = data_string.substr(data_string.find("|") + 1, data_string.rfind("|") - data_string.find("|") - 1);
        if (!variables.count(condition))
        {
            cerr << "There is error in if statement!" << endl;
            return "";
        }

        bool if_condition = variables[condition]->str_value == "true";
        if (if_condition)
        {
            return data;
        }
        else
        {
            return "";
        }
    }
    else if (data_string.find("% for") != string::npos)
    {
        string inner_variable = data_string.substr(6, data_string.find(" ", 6) - 6);
        int position_of_data_source = 0;
        for (int i = 0; i < 4; i++)
        {
            position_of_data_source = data_string.find(" ", position_of_data_source + 1);
        }
        string data_source = data_string.substr(position_of_data_source + 1, data_string.find(" ", position_of_data_source + 1) - position_of_data_source - 1);
        string data_set = data_string.substr(data_string.find("|") + 1, data_string.rfind("|") - data_string.find("|") - 1);
        int pos_of_inner_var = data_set.find('/' + inner_variable + '/');
        string data;
        if (!variables.count(data_source))
        {
            cerr << "There is an error in for statement!" << endl;
            return "";
        }
        for (int i = 0; i < variables[data_source]->vector_value.size(); i++)
        {
            string temp_data_set = data_set;
            data += temp_data_set.replace(pos_of_inner_var, inner_variable.length() + 2, variables[data_source]->vector_value[i]);
        }
        return data;
    }
    else if (data_string.find("% extends") != string::npos)
    {
        string path_to_file = data_string.substr(10, data_string.find(" ", 10) - 10);

        fstream inputFile(path_to_file);
        string data_from_file = "";
        if (inputFile.is_open())
        {
            while (inputFile)
            {
                data_from_file += inputFile.get();
            }
            data_from_file = data_from_file.substr(0, -1);
        }
        else
            cerr << "Unable to open file" << endl;
        inputFile.close();
        return data_from_file;
    }
    else
    {
        if (variables.count(data_string))
        {
            return variables[data_string]->str_value;
        }
        return data_string;
    }
    return "";
}

size_t Template::find_close_index(const string &str)
{
    size_t pos = 0;
    size_t level = 1;
    for (size_t i = pos + 1; i < str.length(); i++)
    {
        if (str[i] == '{')
        {
            level++;
        }
        else if (str[i] == '}')
        {
            level--;
            if (level == 0)
            {
                return i;
            }
        }
    }
    return string::npos;
}