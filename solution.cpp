//
//  main.cpp
//  DataBase
//
//  Created by Sergei Ziuzev on 29/06/2017.
//  Copyright © 2017 Sergei Ziuzev. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <string>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

class Date {
public:
    Date (int new_year = 0, int new_month = 0, int new_day = 0) {
        year = new_year;
        month = new_month;
        day = new_day;
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
    void SetYear(int& new_year) {
        //        if (new_year > 0 && new_year < 9999) {
        year = new_year;
        //        } else {
        //            stringstream ss;
        //            ss << "Month value is invalid: " << to_string(new_year);
        //            throw runtime_error(ss.str());
        //        }
    }
    void SetMonth(int& new_month) {
        if (new_month > 0 && new_month < 13) {
            month = new_month;
        } else {
            stringstream ss;
            ss << "Month value is invalid: " << to_string(new_month);
            throw runtime_error(ss.str());
        }
        
    }
    void SetDay (int& new_day) {
        if (new_day > 0 && new_day < 32) {
            day = new_day;
        } else {
            stringstream ss;
            ss << "Day value is invalid: " << to_string(new_day);
            throw runtime_error(ss.str());
        }
    }
private:
    int year;
    int month;
    int day;
};

bool operator < (const Date& lhs, const Date& rhs) {
    int total_lhs = lhs.GetYear() * 365 + lhs.GetMonth() * 31 + lhs.GetDay();
    int total_rhs = rhs.GetYear() * 365 + rhs.GetMonth() * 31 + rhs.GetDay();
    return total_lhs < total_rhs;
}

bool operator == (const Date& lhs, const Date& rhs) {
    int total_lhs = lhs.GetYear() * 365 + lhs.GetMonth() * 31 + lhs.GetDay();
    int total_rhs = rhs.GetYear() * 365 + rhs.GetMonth() * 31 + rhs.GetDay();
    return total_lhs == total_rhs;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        database[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        for (auto& item : database) {
            if (item.first == date) {
                for (const string& s : item.second) {
                    if (s == event) {
                        item.second.erase(s);
                        return true;
                    }
                }
            }
        }
        return false;
    }
    long DeleteDate(const Date& date) {
        long count_evant = 0;
        for (auto& item : database) {
            if (item.first == date) {
                count_evant = item.second.size();
                database.erase(date);
                return count_evant;
            }
        }
        return count_evant;
    }
    
    void Find(const Date& date) const {
        for (const auto& item : database) {
            if (item.first == date) {
                for (const string& s : item.second) {
                    cout << s << endl;
                }
            }
        }
    }
    
    void Print() const {
        for (const auto& item : database) {
            for (const string& s : item.second) {
                cout << setw(4) << setfill('0') << item.first.GetYear() << '-' << setw(2) << setfill('0') << item.first.GetMonth() << '-' << setw(2) << setfill('0') << item.first.GetDay() << " " << s << endl;
            }
        }
    }
private:
    map<Date, set<string>> database;
};

void EnsureNextSymbolAndSkip (istream& stream, string s) {
    if (stream.peek() != '-') {
        //        string date;
        stringstream ss;
        //        stream >> date;
        ss << "Wrong date format: " << s;//char(stream.peek());
        throw runtime_error(ss.str());
    }
    stream.ignore(1);
}


Date ParseDate(string& temp_date) {
    //stringstream stream(s);
    int year = 0;
    int month = 0;
    int day = 0;
    int number = 0;
    int desh = 0;
    Date date;
    
    for (const char& c : temp_date) {
        if (static_cast<int>(c) >= 48 && static_cast<int>(c) <= 57) {
            number++;
        } else if (c == '-') {
            desh++;
        } else {
            stringstream ss;
            ss << "Wrong date format: " << temp_date;
            throw runtime_error(ss.str());
        }
    }
    if (desh != 2 || (number < 3 || number > 8)) {
        stringstream ss;
        ss << "Wrong date format: " << temp_date;
        throw runtime_error(ss.str());
    }
    
    stringstream stream(temp_date);
    
    stream >> year;
    if (year >= 0 && year <= 9999) {
        date.SetYear(year);
        EnsureNextSymbolAndSkip(stream, temp_date);
        stream >> month;
        date.SetMonth(month);
        EnsureNextSymbolAndSkip(stream, temp_date);
        stream >> day;
        date.SetDay(day);
        
        //        string temp = to_string(year) + '-' + to_string(month) + '-' + to_string(day);
        //        if (temp_date.size() != temp.size()) {
        //            stringstream ss;
        //            ss << "Wrong date format: " << temp_date;
        //            throw runtime_error(ss.str());
        //        }
    } else {
        stringstream ss;
        ss << "Wrong date format: " << temp_date;
        throw runtime_error(ss.str());
    }
    
    return date;
}

Date ParseDate1 (string& temp_date) {
    Date date;
    char year = '0';
    string month;
    string day;
    int number = 0;
    int desh = 0;
    if (static_cast<int>(year) != 0) {
        ;
    }
    
    stringstream stream(temp_date);
    for (const char& c : temp_date) {
        if ((int) c >= 0 && (int)c <= 9) {
            number++;
        } else if (c == '-') {
            desh++;
        } else {
            stringstream ss;
            ss << "Wrong date format: " << temp_date;
            throw runtime_error(ss.str());
        }
    }
    if (desh != 2) {
        stringstream ss;
        ss << "Wrong date format: " << temp_date;
        throw runtime_error(ss.str());
    }
    
    return date;
}



int main(int argc, const char * argv[]) {
    Database db;
    string command;
    while (getline(cin, command)) {
        try {
            if (command.size() == 0) {
                throw exception();
            }
            // Считайте команды с потока ввода и обработайте каждую
            stringstream stream(command);
            string event;
            stream >> command;
            stream.ignore(1);
            string temp_date;
            stream >> temp_date;
            stream.ignore(1);
            
            if (command == "Add") {
                try {
                    Date date = ParseDate(temp_date);
                    stream >> event;
                    if (event.size() != 0) {
                        db.AddEvent(date, event);
                    }
                } catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                
            } else if (command == "Del") {
                Date date;
                try {
                    date = ParseDate(temp_date);
                    stream >> event;
                    if (event.size() != 0) {
                        if (db.DeleteEvent(date, event)) {
                            cout << "Deleted successfully" << endl;
                        } else {
                            cout << "Event not found" << endl;
                        }
                    } else {
                        long n = db.DeleteDate(date);
                        cout << "Deleted " << n << " events" << endl;
                    }
                } catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                
            } else if (command == "Find") {
                try {
                    Date date = ParseDate(temp_date);
                    db.Find(date);
                } catch (exception& ex) {
                    cout << ex.what() << endl;
                    
                }
            } else if (command == "Print") {
                db.Print();
            } else {
                cout << "Unknown command: " << command << endl;
            }
        } catch (exception& ex) {
            
        }
    }
    
    return 0;
}
