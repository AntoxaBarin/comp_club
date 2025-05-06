#pragma once

#include <filesystem>
#include <cstdint>
#include <optional>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <queue>

#include "time.hpp"

namespace comp_club {

using std::uint32_t;
using Id = int;

constexpr Id client_in_id = 1;
constexpr Id client_start_id = 2;
constexpr Id client_wait_id = 3;
constexpr Id client_out_id = 4;

constexpr Id client_out_generated_id = 11;
constexpr Id client_from_queue_start_id = 12;
constexpr Id error_id = 13;

constexpr Id invalid_comp_id = -1;

struct Comp {
    int total_money = 0;
    Time total_time;
    Time session_start;
    bool available = true;
};

class Club {
public:    
    Club() = default;

    void acquire_computer(Id comp_id, const std::string& username, const Time& time);
    void release_computer(Id comp_id, const Time& time);
    bool add_user(const std::string& username);
    bool is_valid_comp_id(Id comp_id) const;

    int comp_number;
    Time open;
    Time close;
    uint32_t price;
    uint32_t available_comps;
    std::vector<Comp> comps;
    std::map<std::string, int> users;
    std::queue<std::string> waiting_users;
};

std::optional<Club> parse_club_info(std::ifstream& in);
void simulate(const std::filesystem::path& path);

int get_user_comp(const Club& club, const std::string& username);
int calc_session_cost(const Time& duration, int price);
bool validate_username(std::string_view username);

} // namespace comp_club
