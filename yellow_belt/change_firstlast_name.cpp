#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::cin;
using std::endl;


class Person {
    using PersonMap = map<int, string>;

public:
    void ChangeFirstName(int year, const string &first_name) {
        // добавить факт изменения имени на first_name в год year
        first_names[year] = first_name;
    }

    void ChangeLastName(int year, const string &last_name) {
        // добавить факт изменения фамилии на last_name в год year
        last_names[year] = last_name;
    }

    string GetFullName(int year) {
        string fname;
        string lname;
        fname = find_name(first_names, year);
        lname = find_name(last_names, year);

        std::ostringstream ss;

        if( fname.empty() && lname.empty())
            ss << "Incognito";
        else if (fname.empty())
            ss << lname << " with unknown first name";
        else if (lname.empty())
            ss << fname << " with unknown last name";
        else
            ss << fname << ' ' << lname;

        return ss.str();
    }

private:
    string find_name(const PersonMap& m, int year) {
        auto it = m.upper_bound(year);

        if(it == m.begin()) return "";
        return std::prev(it)->second;
    }

    PersonMap first_names;
    PersonMap last_names;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
//Incognito
//Polina with unknown last name
//Polina Sergeeva
//Polina Sergeeva
//Appolinaria Sergeeva
//Polina Volkova
//Appolinaria Volkova