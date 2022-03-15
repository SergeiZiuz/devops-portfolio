//
//  database.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#include "headers/database.hpp"

void Database::Add(const Date& date, const std::string& event) {
    checkRepeat[date].insert(event);
    if (checkRepeat.find(date)->second.size() != storage.find(date)->second.size()) {
        storage[date].push_back(event);
    }
}

std::vector<std::string> Database::FindIf(std::function<bool (const Date& date, const std::string& event)> evaluate) const {
    std::vector<std::string> result;
    auto current = storage.begin();
    while (current != storage.end()) {
        auto currentEvents = current->second.begin();
        while (currentEvents != current->second.end()) {
            if (evaluate(current->first, *currentEvents)) {
                std::ostringstream os;
                os << current->first;
                result.push_back(os.str() + " " + *currentEvents);
            }
            currentEvents++;
        }
        current++;
    }
    return result;
}

int Database::RemoveIf(std::function<bool (const Date& date, const std::string& event)> evaluate) {
    long eraseElements = 0;
    std::map<Date, std::vector<std::string>>::iterator current;
    current = storage.begin();
    while (current != storage.end()) {
        bool flagBeginCurrent = false;
        std::vector<std::string>::iterator currentEvent = current->second.begin();
        while (currentEvent != current->second.end()) {
            bool flagBerinCurrentEvent = false;
            if (evaluate(current->first, *currentEvent)) {
                Date tempDate = current->first;
                if (currentEvent != current->second.begin()) {
                    currentEvent = std::prev(currentEvent);
                    checkRepeat.at(current->first).erase(*std::next(currentEvent));
                    storage.at(current->first).erase(std::next(currentEvent));
                    current = storage.lower_bound(tempDate);
                } else {
                    checkRepeat.at(current->first).erase(*currentEvent);
                    storage.at(current->first).erase(currentEvent);
                    current = storage.lower_bound(tempDate);
                    currentEvent = current->second.begin();
                }
                flagBerinCurrentEvent = true;
                
                if (current->second.empty()) {
                    checkRepeat.erase(current->first);
                    storage.erase(current);
                    current = storage.lower_bound(tempDate);
                    eraseElements++;
                    flagBeginCurrent = true;
                    break;
                }
                eraseElements++;
            }
            
            if (flagBerinCurrentEvent) {
                flagBerinCurrentEvent = false;
            } else {
                currentEvent = std::next(currentEvent);
            }
        }
        if (flagBeginCurrent) {
            flagBeginCurrent = false;
        } else {
            current = std::next(current);
        }
    }
    return int(eraseElements);
}

std::string Database::Last(Date date) const {
    Date dateResopnd = Date();
    std::string eventRespond = std::string();
    auto upperIt = storage.upper_bound(date);
    auto lowerIt = storage.lower_bound(date);
    if (storage.empty()) {
        throw std::invalid_argument("No entries");
    } else if (upperIt == storage.begin()) {
        throw std::invalid_argument("No entries");
    } else if (upperIt != lowerIt && !lowerIt->second.empty()) {
        dateResopnd = lowerIt->first;
        eventRespond = *lowerIt->second.rbegin();
    } else if (upperIt == lowerIt && !storage.empty() && !storage.rbegin()->second.empty()) {
        dateResopnd = std::prev(lowerIt)->first;
        eventRespond = *std::prev(lowerIt)->second.rbegin();
    } else {
        throw std::invalid_argument("No entries");
    }
    std::stringstream ss;
    ss << dateResopnd << " " << eventRespond;
    return ss.str();
}

void Database::Print(std::ostream &cout) const {
    for (const auto& item : storage) {
        for (const std::string& event : item.second) {
            cout << item.first << " " << event << std::endl;
        }
    }
}

int Database::SizeDaties() const {
    return int(storage.size());
}

int Database::SizeEvents() const {
    long sizeEvents = 0;
    auto currentIt = storage.begin();
    while (currentIt != storage.end()) {
        sizeEvents = sizeEvents + currentIt->second.size();
        currentIt = std::next(currentIt);
    }
    return int(sizeEvents);
}
