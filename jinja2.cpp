#include "template.h"
#include "template.cpp"
using namespace std;
void test()
{
    Template template1("Hello, {name}!");
    template1.add_variable("name", "John");
    string result1 = template1.process();
    assert(result1 == "Hello, John!");

    Template template2("My favorite color is {color}, what is yours?");
    template2.add_variable("color", "blue");
    string result2 = template2.process();
    assert(result2 == "My favorite color is blue, what is yours?");

    Template template3("Hi {name}, how r u? {greeting} to {city}. {city} is the best place in the wrld.");
    template3.add_variable("name", "Anna");
    template3.add_variable("greeting", "Welcome");
    template3.add_variable("city", "Dely");
    string result3 = template3.process();
    assert(result3 == "Hi Anna, how r u? Welcome to Dely. Dely is the best place in the wrld.");

    Template template4("Hi my name is {% if true |Hi {MyName}| %}!");
    template4.add_variable("MyName", "Kate");
    template4.add_variable("true", "true");
    string result4 = template4.process();
    assert(result4 == "Hi my name is Hi Kate!");

    Template template5("The fruits are: {% for fruit in fruits |/fruit/, | %}");
    vector<string> fruitList = {"apple", "banana", "orange"};
    template5.add_variable("fruits", fruitList);
    string result5 = template5.process();
    assert(result5 == "The fruits are: apple, banana, orange, ");

    Template template6("You {% if status |are| %} awesome!");
    template6.add_variable("status", "true");
    string result6 = template6.process();
    assert(result6 == "You are awesome!");

    Template template7("Hi {% if greet |Honey| %}. It's {% if name |Artur|%}");
    template7.add_variable("greet", "true");
    template7.add_variable("name", "false");
    string result7 = template7.process();
    assert(result7 == "Hi Honey. It's ");

    Template template8("Hi its new array and this is array variables:{% for var in var_array |\nthis {% if some_state |name: {name_var}| %} is /var/| %}");
    vector<string> vars = {"cool", "nice", "lol"};
    template8.add_variable("var_array", vars);
    template8.add_variable("some_state", "true");
    template8.add_variable("name_var", "Pinocchio");
    string result8 = template8.process();
    assert(result8 == "Hi its new array and this is array variables:\nthis name: Pinocchio is cool\nthis name: Pinocchio is nice\nthis name: Pinocchio is lol");
    cout << result1 << endl;
    // cout << result2 << endl;
    // cout << result3 << endl;
    // cout << result4 << endl;
    // cout << result6 << endl;
    // cout << result7 << endl;
    // cout << result8 << endl;
    Template template9("");
    template9.add_variable("name", "David");
    vector<string> vars9 = {"David", "Vitya", "Eugen"};
    template9.add_variable("vars", vars9);
    template9.process_file("index.html");

    // Template template10("Hi i'ts { //}");
    // string result10 = template10.process();
    // assert(result10 == "Hi i'ts  //");

    Template template11("Hi it's {what} {% if na |sheeeeesh {what} if stat| %} below:\"\n{% extends block.html %}\". End :<");
    template11.add_variable("what", "block");
    template11.add_variable("na", "true");
    string result11 = template11.process();
    cout << result11 << endl;
    cout << "All tests passed!" << endl;
}
int main()
{
    test();

    return 0;
}
