#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <chrono>
#include <set>

using namespace std;
using namespace std::chrono;

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;
using Sec = std::chrono::seconds;
const Clock::duration duration_1day = std::chrono::seconds(86400);

struct RoomReserve {
    Clock::duration time_point;
    int client_id;
    int rooms;
};

struct HotelStatistics {
    int reserved_rooms;
    map<int, int> client_reserve;
};

class HotelBookSystem {
    const Clock::duration duration_period;
    Clock::duration current_time;
    // hotel name, room_reserve
    map<string, queue<RoomReserve>> hotel_book;
    map<string, HotelStatistics> hotel_stat;

    // TODO break class on hotels
    void remove_old_records(const string &hotel_name,
                            queue<RoomReserve> &book_queue) {
        while (!book_queue.empty()) {
            auto record = book_queue.front();
            if (current_time - record.time_point >= duration_period) {
                hotel_stat[hotel_name].reserved_rooms -= record.rooms;
                hotel_stat[hotel_name].client_reserve[record.client_id] -= record.rooms;
                book_queue.pop();
                continue;
            }
            break;
        }
    }

public:
    HotelBookSystem(const Clock::duration &duration = duration_1day) : duration_period(duration) {}

    void book(const Clock::duration &time_point, const string &hotel_name, const int client_id, const int room_cnt) {
        current_time = time_point;

        if (hotel_book.count(hotel_name) != 0)
            remove_old_records(hotel_name, hotel_book[hotel_name]);

        hotel_book[hotel_name].push({time_point, client_id, room_cnt});
        hotel_stat[hotel_name].reserved_rooms += room_cnt;
        hotel_stat[hotel_name].client_reserve[client_id] += room_cnt;
    }

    int hotel_day_client_stat(const string &hotel_name) {
        if (hotel_book.count(hotel_name) == 0)
            return 0;
        // update stat
        remove_old_records(hotel_name, hotel_book[hotel_name]);
        return hotel_stat[hotel_name].client_reserve.size();
    }

    int hotel_day_room_stat(const string &hotel_name) {
        if (hotel_book.count(hotel_name) == 0)
            return 0;
        remove_old_records(hotel_name, hotel_book[hotel_name]);
        return hotel_stat[hotel_name].reserved_rooms;
    }
};

int main() {

    auto t = steady_clock::now();
    auto sec = duration_cast<seconds>(steady_clock::now() - t).count();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelBookSystem hotel_book;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            int client_id, room_count;
            cin >> client_id >> room_count;

            hotel_book.book(std::chrono::seconds(time), hotel_name, client_id, room_count);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS") {
                cout << hotel_book.hotel_day_client_stat(hotel_name) << "\n";
            } else if (query_type == "ROOMS") {
                cout << hotel_book.hotel_day_room_stat(hotel_name) << "\n";
            }
        }
    }

    return 0;
}

//11
//CLIENTS Marriott
//ROOMS Marriott
//BOOK 10 FourSeasons 1 2
//BOOK 10 Marriott 1 1
//BOOK 86409 FourSeasons 2 1
//CLIENTS FourSeasons
//ROOMS FourSeasons
//CLIENTS Marriott
//BOOK 86410 Marriott 2 10
//ROOMS FourSeasons
//ROOMS Marriott
//0
//0
//2
//3
//1
//1
//10