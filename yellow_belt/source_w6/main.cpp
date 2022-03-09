#include <iostream>
#include <stdexcept>
#include <sstream>

#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "event.h"
#include "unit_tests.h"

using namespace std;

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument &) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("Event");
        AssertEqual(ParseEvent(is), "Event", "Parse Event without leading spaces");
    }
    {
        istringstream is("   sport Event  ");
        AssertEqual(ParseEvent(is), "sport Event", "Parse Event with leading spaces");
    }
    {
        istringstream is("  first Event  \n  second Event");
        vector <string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector < string > {"first Event", "second Event"}, "Parse multiple events");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");

    tr.RunTest(TestParseDate, "TestParseDate");
    tr.RunTest(TestEmptyNode, "TestEmptyNode");
    tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
    tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
    tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");
    tr.RunTest(TestInsertionOrder, "TestInsertionOrder");
    tr.RunTest(TestAdd, "TestAdd");
    tr.RunTest(TestLast, "TestLast");
    tr.RunTest(TestRemove, "TestRemoveIf");
    tr.RunTest(TestFind, "TestFindIf");
    tr.RunTest(TestDatabase, "TestDatabase");
}
