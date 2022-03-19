#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <sstream>

using namespace std;

inline static const string unknown_method{"UNKNOWN"};
inline static const array<string, 5> known_methods = {"GET", "POST", "DELETE", "PUT", unknown_method};
inline static const string unknown_uri{"unknown"};
inline static const array<string, 6> known_uris = {"/", "/product", "/basket", "/help", "/order", unknown_uri};

class Stats {
    map<string_view, int> method_stats;
    map<string_view, int> uri_stats;
public:
    Stats() {
        for (const auto &m : known_methods) {
            method_stats[m] = 0;
        }
        for (const auto &u : known_uris) {
            uri_stats[u] = 0;
        }
    }

    void AddMethod(string_view method) {
        auto it = method_stats.find(method);
        if (it != method_stats.end()) {
            ++it->second;
        } else {
            it = method_stats.find(unknown_method);
            ++it->second;
        }
    }

    void AddUri(string_view uri) {
        auto it = uri_stats.find(uri);
        if (it != uri_stats.end()) {
            ++it->second;
        } else {
            it = uri_stats.find(unknown_uri);
            ++it->second;
        }
    }

    const map<string_view, int> &GetMethodStats() const {
        return method_stats;
    }

    const map<string_view, int> &GetUriStats() const {
        return uri_stats;
    }
};

const auto sep = ' ';

string_view get_field(string_view& sw) {
    string_view ret;
    size_t pos{};
    while (!sw.empty()) {
        if (sw[0] == sep)
            sw.remove_prefix(1);
        else
            break;
    }

    size_t count = sw.find(sep);
    ret = sw.substr(0, count);
    sw.remove_prefix(count);
    return ret;
}

HttpRequest ParseRequest(string_view line) {
    string_view method, uri, protocol;

    method = get_field(line);
    uri = get_field(line);
    protocol = get_field(line);

    return {method, uri, protocol};
}
