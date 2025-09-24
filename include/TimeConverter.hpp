#include <string>

typedef enum format_states_ {
    HOURS,
    MINUTES,
    MERIDIEM
} format_state;

unsigned int parse(std::string s);
std::string convert(unsigned int minutes);