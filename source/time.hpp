#pragma once

#include <stdexcept>
#include <cstdint>
#include <iomanip>

namespace comp_club {

using std::uint32_t;

class Time {
public:
    Time(uint32_t hours = 0, uint32_t minutes = 0) {
        if (hours >= 24 || minutes >= 60) {
            throw std::invalid_argument("Invalid time value " + std::to_string(hours));
        }
        hours_ = hours;
        minutes_ = minutes;
    }

    uint32_t hours() const { 
        return hours_; 
    }

    uint32_t minutes() const { 
        return minutes_; 
    }

    int difference(const Time &other) const {
        int total_minutes = hours_ * 60 + minutes_;
        int other_total_minutes = other.hours_ * 60 + other.minutes_;
        return total_minutes - other_total_minutes;
    }

    Time& operator+=(Time& other) {
        this->hours_ += other.hours_;
        this->minutes_ += other.minutes_;
        if (this->minutes_ >= 60) {
            ++this->hours_;
            this->minutes_ %= 60; 
        }
        return *this;
    }

    Time operator-(const Time& other) const {
        int total_minutes = hours_ * 60 + minutes_;
        int other_total_minutes = other.hours_ * 60 + other.minutes_;
        int diff = total_minutes - other_total_minutes;
        
        if (diff < 0) {
            diff += 24 * 60;
        }
        
        return Time(diff / 60, diff % 60);
    }

    bool operator<(const Time &other) const {
        return (hours_ < other.hours_) ||
                (hours_ == other.hours_ && minutes_ < other.minutes_);
    }

    bool operator==(const Time &other) const {
        return hours_ == other.hours_ && minutes_ == other.minutes_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Time& time) {
        return out << std::setw(2) << std::setfill('0') << time.hours_ << ":"
                   << std::setw(2) << std::setfill('0') << time.minutes_;
    }

    friend std::istream& operator>>(std::istream& in, Time& time) {
        int hours = 0;
        int minutes = 0;
        char separator;

        in >> hours >> separator >> minutes;
        if (separator != ':') {
            throw std::runtime_error("Bad time separator symbol");
        }
        time = Time(hours, minutes);
        return in;
    }

private:
    uint32_t hours_;
    uint32_t minutes_;
};

} // namespace comp_club
