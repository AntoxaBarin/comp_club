#include "simulation.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace comp_club {

std::optional<Club> parse_club_info(std::ifstream& in) {
    Club club{};
    std::string line;
    
    try {
        std::getline(in, line);
        club.comp_number = std::stoul(line);

        std::getline(in, line);
        std::stringstream ss(line);
        ss >> club.open;
        ss >> club.close;

        std::getline(in, line);
        club.price = std::stoul(line);
    } catch (...) {
        std::cout << line << std::endl;
        return std::nullopt;
    }
    
    return club;
}

void simulate(const std::filesystem::path& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Failed to open input file");
    }

    auto opt_club_info = parse_club_info(in);
    if (!opt_club_info.has_value()) {
        return;
    }
    Club club = opt_club_info.value();
    club.available_comps = club.comp_number;
    club.comps.resize(club.comp_number, Comp{0, Time(), Time(), true});

    std::stringstream buffer;
    buffer << club.open << '\n';

    std::string line;
    while (std::getline(in, line)) {
        try {
            std::stringstream ss(line);
            Time event_time;
            Id event_id = 0;
            std::string username = "";
            
            ss >> event_time >> event_id >> username;
            
            bool is_valid_username = validate_username(username);
            if (!is_valid_username) {
                std::cout << line << std::endl;
                return;
            }
            
            if (event_id == client_in_id) {
                buffer << event_time << ' ' << event_id << ' ' << username << '\n';
                
                if (event_time < club.open) {
                    buffer << event_time << ' ' << error_id << " NotOpenYet\n";
                    continue;
                }
                if (get_user_comp(club, username) != -1) {
                    buffer << event_time << ' ' << error_id << " YouShallNotPass\n";
                    continue;
                }
                club.users.insert({username, -1});
            } 
            else if (event_id == client_start_id) {
                int comp_id = 0;
                ss >> comp_id;
                buffer << event_time << ' ' << event_id << ' ' << username << ' ' << comp_id << '\n';

                if (comp_id < 1 || comp_id > club.comp_number) { // incorrect comp_id
                    std::cout << line << std::endl;
                    return;
                }
                if (!club.comps[comp_id - 1].available) {
                    buffer << event_time << ' ' << error_id << " PlaceIsBusy\n";
                    continue;
                }
                else { // correct comp_id, user takes place
                    club.comps[comp_id - 1].available = false;
                    club.comps[comp_id - 1].session_start = event_time;
                    club.available_comps--;
                    club.users[username] = comp_id;
                }
            }
            else if (event_id == client_wait_id) { 
                buffer << event_time << ' ' << client_wait_id << ' ' << username << '\n';

                if (club.available_comps > 0) {
                    buffer << event_time << ' ' << error_id << " ICanWaitNoLonger!\n";
                    continue;
                }
                // todo: add queue
            }
            else if (event_id == client_out_id) {
                buffer << event_time << ' ' << event_id << ' ' << username << '\n';
                
                int comp_id = get_user_comp(club, username);
                if (comp_id == -1) {
                    buffer << event_time << ' ' << error_id << " ClientUnknown\n";
                    continue;
                }
                Comp& comp = club.comps[comp_id - 1];
                comp.available = true;
                club.available_comps++;
                club.users.erase(username);

                auto session_duration = event_time - comp.session_start;
                comp.total_time += session_duration;
                comp.total_money += calc_session_cost(session_duration, club.price);
                 
                // todo: add client_start for user from queue head
            }

        } catch (...) {
            std::cout << line << std::endl;
            return;
        }    
    }

    for (auto [username, comp_id] : club.users) {
        buffer << club.close << ' ' << client_out_generated_id << ' ' << username << '\n';
        Comp& comp = club.comps[comp_id - 1];
        auto session_duration = club.close - comp.session_start;
        comp.total_time += session_duration;
        comp.total_money += calc_session_cost(session_duration, club.price);
    }

    for (size_t i = 0; i < club.comps.size(); ++i) {
        buffer << i + 1 << ' ' << club.comps[i].total_money << ' ' << club.comps[i].total_time << '\n';
    }

    buffer << club.close << '\n';
    std::cout << buffer.str();
}

int get_user_comp(const Club& club, const std::string& username) {
    auto it = club.users.find(username);
    if (it != club.users.end()) {
        return it->second;
    }
    return -1;
}

int calc_session_cost(const Time& duration, int price) {
    if (duration.minutes() == 0) {
        return duration.hours() * price;
    }
    return (duration.hours() + 1) * price;
}

bool validate_username(std::string_view username) {
    for (char c : username) {
        if (!(c >= 'a' && c <= 'z') && !(c >= '0' && c <= 'z') && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}


// void Club::handle_client_in(const Time& event_time, std::stringstream& out_buffer) {

// }

} // namespace comp_club
