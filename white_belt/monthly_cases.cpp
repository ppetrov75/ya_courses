#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>
#include <iomanip>

enum Months {
    JAN = 0, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

namespace {
    const std::vector<unsigned> num_days_v{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
}

class MonthCases {
private:
    Months m_mth_num;
    unsigned m_days;
    std::multimap<unsigned, std::string> m_month_cases;

protected:
    // TODO ?
    MonthCases &operator=(const MonthCases &oth_mth) {
        if (this != &oth_mth) {

        }
        return *this;
    }

public:
    explicit MonthCases(Months mth_num) : m_mth_num(mth_num) {
        m_days = num_days_v.at(mth_num);
    }

    MonthCases(const MonthCases &mth) = delete;

    void next_month() {
        Months new_mth_num = Months(m_mth_num + 1);
        if (new_mth_num > DEC) new_mth_num = JAN;
        unsigned new_days = num_days_v.at(new_mth_num);

        auto lb = m_month_cases.lower_bound(1);
        auto ub = m_month_cases.upper_bound(new_days);
        std::multimap<unsigned, std::string> new_mth_cases(lb, ub);

        if(m_days > new_days) {
            lb = m_month_cases.lower_bound(new_days+1);
            ub = m_month_cases.upper_bound(m_days);
            for(auto it = lb; it != ub; it++) {
                new_mth_cases.insert(std::pair(new_days, it->second));
            }
        }
        m_mth_num = new_mth_num;
        m_days = new_days;
        m_month_cases = new_mth_cases;
    }

    bool add_case(unsigned day, const std::string &mcase) {
        if (day > m_days) {
            throw std::runtime_error("the number of the day is greater than the number of days in the month");
        }

        m_month_cases.insert(std::pair(day, mcase));
        return true;
    }

    void print_case(unsigned day) {
        if (day > m_days) {
            throw std::runtime_error("the number of the day is greater than the number of days in the month");
        }

        std::cout << "day " << std::setw(2) << day << ": ";
        auto cnt = m_month_cases.count(day);

        if (cnt == 0) {
            std::cout << "no cases at this day\n";
        } else {
            std::cout << cnt << " cases: ";
            auto r = m_month_cases.equal_range(day);
            for (auto i = r.first; i != r.second; ++i) {
                std::cout << i->second << "; ";
            }
            std::cout << '\n';
        }
    }

    // TODO
    void print_all_cases(unsigned day) {
    }

    unsigned get_num_days() const {
        return m_days;
    }
};


int main() {
    MonthCases m(JAN);

/*    m.add_case(1, "yoga");
    m.add_case(2, "movie");
    m.add_case(3, "run");
    m.add_case(29, "clean");
    m.add_case(30, "walk");
    m.add_case(31, "call");
    m.next_month();

    m.print_case(1);
    m.print_case(2);
    m.print_case(3);
    m.print_case(28);*/

// error   m.print_case(29);

//    ADD 5 Salary
//    ADD 31 Walk
//    ADD 30 WalkPreparations
    m.add_case(5, "Salary");
    m.add_case(31, "Walk");
    m.add_case(30, "WalkPreparations");
    m.next_month();
    m.print_case(5);
    m.print_case(28);
    m.next_month();
    m.print_case(31);
    m.print_case(30);
    m.print_case(28);
    m.add_case(28, "Payment");
    m.print_case(28);

    /*
    Output:
    day  5: 1 cases: Salary;
    day 28: 2 cases: WalkPreparations; Walk;
    day 31: no cases at this day
    day 30: no cases at this day
    day 28: 2 cases: WalkPreparations; Walk;
    day 28: 3 cases: WalkPreparations; Walk; Payment;
    */
}