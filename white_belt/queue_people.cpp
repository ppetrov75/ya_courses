#include <iostream>
#include <vector>
#include <algorithm>

enum CMDS {WORRY_COUNT = 0, COME, SET_QUIET, SET_WORRY };
enum STATUS {QUIET = 0, WORRY};

void do_cmd(std::vector<STATUS>& v, CMDS cmd, int par = 0) {

    int cnt = 0;
    switch (cmd) {
        case WORRY_COUNT:
            cnt = std::count_if(v.begin(), v.end(), [](STATUS st) { return st == WORRY;} );
            std::cout << "WORRY_COUNT --> " << cnt << '\n';
            break;
        case COME:
            v.resize(v.size() + par);
            std::cout << "COME " << par << '\n';
            break;
        case SET_QUIET:
            v[par - 1] = QUIET;
            std::cout << "QUIET " << par << '\n';
            break;
        case SET_WORRY:
            v[par - 1] = WORRY;
            std::cout << "WORRY " << par << '\n';
            break;
    }
}

int main() {
    std::vector<STATUS> queue_people;

    do_cmd(queue_people, COME, 5);
    do_cmd(queue_people, SET_WORRY, 1);
    do_cmd(queue_people, SET_WORRY, 4);
    do_cmd(queue_people, COME, -2);
    do_cmd(queue_people, WORRY_COUNT);
    do_cmd(queue_people, COME, 3);
    do_cmd(queue_people, SET_WORRY, 3);
    do_cmd(queue_people, WORRY_COUNT);

}