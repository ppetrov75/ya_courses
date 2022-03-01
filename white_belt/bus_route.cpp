#include <iostream>
#include <vector>
#include <algorithm>

class BusRoute {
private:
    std::vector<std::string> m_bus_stops;

public:
    BusRoute(const std::vector<std::string> &stops) : m_bus_stops(stops) {
    }

    void add_bus_stop(const std::string &stop, unsigned pos = 0) {
        if (pos && (m_bus_stops.size() > pos - 1)) {
            m_bus_stops.insert(m_bus_stops.begin() + pos - 1, stop);
        } else {
            m_bus_stops.push_back(stop);
        }
    }

    bool contain_bus_stop(const std::string& stop) {
        return (std::find(m_bus_stops.begin(), m_bus_stops.end(), stop) != m_bus_stops.end());
    }

    void print_bus_stops() const {
        for (const auto &s : m_bus_stops) {
            std::cout << s << ' ';
        }
        std::cout << '\n';
    }
};

int main() {

    BusRoute r1({"one", "two", "three"});

    r1.add_bus_stop("two_a", 2);
    r1.print_bus_stops();

    std::cout << "contain bus stop 'two'? - " << std::boolalpha << r1.contain_bus_stop("two") <<'\n';
}
