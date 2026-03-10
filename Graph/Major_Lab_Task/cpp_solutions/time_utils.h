#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

// Convert time string (e.g., "5:43 PM") to minutes from midnight
inline int timeToMinutes(const std::string& timeStr) {
    int hour, minute;
    char colon, period[3];
    std::istringstream iss(timeStr);
    iss >> hour >> colon >> minute >> period;
    
    std::string ampm(period);
    if (ampm == "PM" && hour != 12) hour += 12;
    if (ampm == "AM" && hour == 12) hour = 0;
    
    return hour * 60 + minute;
}

// Convert minutes from midnight to time string
inline std::string minutesToTime(int minutes) {
    int hours = (minutes / 60) % 24;
    int mins = minutes % 60;
    std::string period = (hours < 12) ? "AM" : "PM";
    int displayHour = (hours == 0) ? 12 : (hours > 12) ? hours - 12 : hours;
    
    std::ostringstream oss;
    oss << displayHour << ":" << std::setfill('0') << std::setw(2) << mins << " " << period;
    return oss.str();
}

// Schedule class for bus/metro
class TransportSchedule {
public:
    int intervalMinutes;
    int startMinutes;  // From midnight
    int endMinutes;    // From midnight
    
    TransportSchedule(int interval, int startHour, int endHour)
        : intervalMinutes(interval), 
          startMinutes(startHour * 60), 
          endMinutes(endHour * 60) {}
    
    // Get next departure time (returns -1 if no service)
    int getNextDeparture(int currentMinutes) const {
        if (currentMinutes > endMinutes) return -1;
        if (currentMinutes < startMinutes) return startMinutes;
        
        int timeSinceStart = currentMinutes - startMinutes;
        int intervalsPassed = timeSinceStart / intervalMinutes;
        int nextDeparture = startMinutes + (intervalsPassed + 1) * intervalMinutes;
        
        return (nextDeparture > endMinutes) ? -1 : nextDeparture;
    }
    
    // Get waiting time in minutes (returns -1 if no service)
    int getWaitTime(int currentMinutes) const {
        int next = getNextDeparture(currentMinutes);
        return (next == -1) ? -1 : next - currentMinutes;
    }
};

#endif // TIME_UTILS_H
