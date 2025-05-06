#pragma once

#include <filesystem>
#include <cstdint>
#include <optional>
#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "time.hpp"

namespace comp_club {

using std::uint32_t;
using Id = int;

constexpr Id client_in_id = 1;
constexpr Id client_start_id = 2;
constexpr Id client_wait_id = 3;
constexpr Id client_out_id = 4;

constexpr Id client_out_generated_id = 11;
constexpr Id error_id = 13;

struct Comp {
    int total_money = 0;
    Time total_time;
    Time session_start;
    bool available = true;
};

class Club {
public:    
    Club() = default;

    // void handle_client_in(const Time& event_time, std::stringstream& out_buffer);

    int comp_number;
    Time open;
    Time close;
    uint32_t price;
    uint32_t available_comps;
    std::vector<Comp> comps;
    std::map<std::string, int> users;
};

std::optional<Club> parse_club_info(std::ifstream& in);
void simulate(const std::filesystem::path& path);

int get_user_comp(const Club& club, const std::string& username);
int calc_session_cost(const Time& duration, int price);

} // namespace comp_club
