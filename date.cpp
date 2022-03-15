//
//  date.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#include "headers/date.hpp"

Date::Date() {
    year = 1900;
    month = 1;
    day = 1;
}
Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
        throw std::logic_error("Month value is invalid: " + std::to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
        throw std::logic_error("Day value is invalid: " + std::to_string(new_day));
    }
    day = new_day;
}

int Date::GetYear() const {
    return year;
}
int Date::GetMonth() const {
    return month;
}
int Date::GetDay() const {
    return day;
}

Date ParseDate(std::istream& date_stream) {
    
    int year = 0;
    date_stream >> year;

    if (date_stream.peek() != '-') {
        throw std::logic_error("Wrong date format: ");
    }
    date_stream.ignore();

    int month = 0;
    date_stream >> month;
    
    if (date_stream.peek() != '-') {
        throw std::logic_error("Wrong date format: ");
    }
    date_stream.ignore();

    int day = 0;
    date_stream >> day;
    
    return Date(year, month, day);
}

Date ParseDate(const std::string& dateString) {
    std::istringstream isStream(dateString);
    return ParseDate(isStream);
}

bool operator < (const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
    std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator <= (const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <=
    std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator > (const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >
    std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator >= (const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >=
    std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator == (const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} == std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator != (const Date& lhs, const Date& rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} != std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

std::ostream& operator << (std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.GetYear() <<
    "-" << std::setw(2) << std::setfill('0') << date.GetMonth() <<
    "-" << std::setw(2) << std::setfill('0') << date.GetDay();
    return stream;
}
