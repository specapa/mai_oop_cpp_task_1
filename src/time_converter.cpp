#include "TimeConverter.hpp"
#include <stdexcept>
#include <iostream>

unsigned int parse(std::string s) {
    format_state state = HOURS;
    int overflow_counter = 0;
    int houres = 0;
    int minutes = 0;
    bool post_meridiem = false;
    bool meridiem_opened = false;
    bool meridiem_finished = false;

    for (char symb : s) {
        if (symb == '\0' || symb == '\n') break;
        switch (state) {
            case HOURS:
                if (symb == ':') {
                    if (houres > 12) {
                        throw std::invalid_argument("Error: to much HOURS!");
                    }
                    state = MINUTES;
                    overflow_counter = 0;
                } else if (symb >= '0' && symb <= '9') { 
                    ++overflow_counter;
                    if (overflow_counter > 2) {
                        throw std::invalid_argument("Error: use 2 digits in hours!");
                    }
                    houres = houres * 10 + (symb - 48);
                } else {
                    throw std::invalid_argument("Error: wrong HOURS format! Seperate HOURS and MINUTES with <:>!");
                }
                break;
            case MINUTES:
                if (symb == ' ') {
                    if (minutes > 59) {
                        throw std::invalid_argument("Error: to much MINUTES!");
                    }
                    state = MERIDIEM;
                    overflow_counter = 0;
                } else if (symb >= '0' && symb <= '9') { 
                    ++overflow_counter;
                    if (overflow_counter > 2) {
                        throw std::invalid_argument("Error: use 2 digits in minutes!");
                    }
                    minutes = minutes * 10 + (symb - 48);
                } else {
                    throw std::invalid_argument("Error: wrong MINUTES format! Seperate MINUTES and MERIDIEM with <space>!");
                }
                break;
            case MERIDIEM:
                switch (symb) {
                    case 'a':
                    case 'A':
                        meridiem_opened = true;
                        break;
                    case 'p':
                    case 'P':
                        meridiem_opened = true;
                        post_meridiem = true;
                        break;
                    case 'm':
                    case 'M':
                        if (meridiem_opened) {
                            meridiem_finished = true;
                        }
                        break;
                    default:
                        throw std::invalid_argument("Error: wrong MERIDIEM format! Supported formats: am / pm");
                }
                break;
            default:
                throw std::invalid_argument("Error: wrong format");
        }
        if (meridiem_finished) {
            break;
        }
    }
    if (houres == 12) {
        post_meridiem = !post_meridiem;
    }
    return ((houres + post_meridiem * 12) * 60 + minutes) % (60 * 24);
}

std::string convert(unsigned int minutes)
{
    unsigned int hours = minutes / 60 % 24;
    unsigned int mins = minutes % 60;
    std::string hourStr = (hours < 10) ? "0" + std::to_string(hours) : std::to_string(hours);
    std::string minStr = (mins < 10) ? "0" + std::to_string(mins) : std::to_string(mins);
    return hourStr + ":" + minStr;
}
