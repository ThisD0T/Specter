#include <vector>
#include <string>
#include <map>
#include "ymd.h"

std::map<std::string, int> get_days_in_months() {
    std::map<std::string, int> days;
    days["Jan"] = 31;
    days["Feb"] = 28;
    days["Mar"] = 31;
    days["Apr"] = 30;
    days["May"] = 31;
    days["Jun"] = 30;
    days["Jul"] = 31;
    days["Aug"] = 31;
    days["Sep"] = 30;
    days["Oct"] = 31;
    days["Nov"] = 30;
    days["Dec"] = 31;

    return days;
}