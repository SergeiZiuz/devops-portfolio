//
//  date.hpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/15/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#ifndef date_h
#define date_h

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <set>
#include <utility>
#include <iomanip>      // std::get_time
#include <ctime>        // struct std::tm


class Date {
public:
    // конструктор выбрасывает исключение, если его аргументы некорректны
    Date();
    Date(int new_year, int new_month, int new_day);
    
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    
private:
    int year;
    int month;
    int day;
};

Date ParseDate(std::istream& is);
Date ParseDate(const std::string& dateString);

bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date& lhs, const Date& rhs);
bool operator > (const Date& lhs, const Date& rhs);
bool operator >= (const Date& lhs, const Date& rhs);
bool operator == (const Date& lhs, const Date& rhs);
bool operator != (const Date& lhs, const Date& rhs);
std::ostream& operator << (std::ostream& stream, const Date& date);



#endif /* date_h */