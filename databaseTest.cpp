//
//  databaseTests.cpp
//  DataBaseCourseProject
//
//  Created by Sergei Ziuzev on 3/17/22.
//  Copyright © 2022 Sergei Ziuzev. All rights reserved.
//

#include "headers/databaseTests.hpp"


void TestAdd() {
    {
        Database database;
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        AssertEqual(database.SizeDaties(), 1, "Check adds two same daties");
        AssertEqual(database.SizeEvents(), 1, "Check adds two same daties and events");
        AssertEqual(DoPrint(database), "2019-04-05 Wonderful day\n", "Check Add 1");
    }
    {
        Database database;
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        AssertEqual(database.SizeDaties(), 1, "Check adds two same other events");
        AssertEqual(database.SizeEvents(), 2, "Check adds two same daties and  other events");
        AssertEqual(DoPrint(database), "2019-04-05 Wonderful day\n2019-04-05 Wonderful\n", "Check Add 2");
    }
    {
        Database database;
        std::string str = "0000-01-01 big sport event\n2019-04-05 Wonderful day\n";
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("0-01-1"), "big sport event");
        AssertEqual(DoPrint(database), str, "Check Add");
    }
    {
        Database database;
        std::string str = "0000-01-01 big sport event\n2019-04-05 Wonderful day\n";
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("0-01-1"), "big sport event");
        std::string err;
        try {
            database.Add(ParseDate("0-0-0"), "big sport event");
        } catch (std::logic_error& error) {
            err = "Error date";
        }
        AssertEqual(err, "Error date", "Check Add");
    }
    {
        Database database;
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(database.SizeDaties(), 4, "Check adds two same other events");
        AssertEqual(database.SizeEvents(), 9, "Check adds two same daties and  other events");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        database.Add(ParseDate("2017-01-01"), "Holiday");
        database.Add(ParseDate("2017-01-01"), "Holiday");
        database.Add(ParseDate("2017-01-01"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-01-01"), "New Year");
        database.Add(ParseDate("2017-01-01"), "New Year");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-03-08"), "Holiday");
        database.Add(ParseDate("2017-01-01"), "Holiday");
        database.Add(ParseDate("2017-01-01"), "Holiday");
        database.Add(ParseDate("2017-01-01"), "Holiday");
        AssertEqual(database.SizeDaties(), 2, "Check adds two same other events");
        AssertEqual(database.SizeEvents(), 3, "Check adds two same daties and  other events");
        AssertEqual(DoPrint(database), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n", "Check Add 2");
    }
}

void TestFind() {
    {
        Database database;
        std::istringstream is(R"(event != "Weekly meeting")");
        std::vector<std::string> respond = { };
        
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"(event != "Weekly meeting")");
        std::vector<std::string> respond = {
            "2017-04-05 Wonderful",
            "2018-04-05 Wonderful day",
            "2019-04-05 Wonderful day",
            "2019-04-05 Wonderful",
            "2019-04-05 AAA",
            "2019-04-05 bbb",
            "2019-04-05 ZZZ",
            "2019-04-05 W",
            "2019-04-05 ccc"
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"()");
        std::vector<std::string> respond = {
            "2017-04-05 Wonderful",
            "2018-04-05 Wonderful day",
            "2019-04-05 Wonderful day",
            "2019-04-05 Wonderful",
            "2019-04-05 AAA",
            "2019-04-05 bbb",
            "2019-04-05 ZZZ",
            "2019-04-05 W",
            "2019-04-05 ccc"
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"(date < "2017-11-06")");
        std::vector<std::string> respond = {
            "2017-04-05 Wonderful"
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2019-04-05")");
        std::vector<std::string> respond = {
            "2019-04-05 Wonderful day",
            "2019-04-05 Wonderful",
            "2019-04-05 AAA",
            "2019-04-05 bbb",
            "2019-04-05 ZZZ",
            "2019-04-05 W",
            "2019-04-05 ccc"
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2019-04-01")");
        std::vector<std::string> respond = {
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"(date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event")");
        std::vector<std::string> respond = {
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"(date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event")");
        std::vector<std::string> respond = {
            "2017-02-05 sport event",
            "2017-04-05 sport event",
            "2017-06-31 sport event"
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "sport event");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        database.Add(ParseDate("2017-02-05"), "sport event");
        database.Add(ParseDate("2017-06-31"), "sport event");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
    {
        Database database;
        std::istringstream is(R"(date < 2017-01-01 AND (event == "holiday" OR event == "sport event"))");
        std::vector<std::string> respond = {
            "2015-02-05 sport event",
            "2015-06-31 sport event",
            "2016-04-05 sport event",
            "2016-04-05 holiday"
        };
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "sport event");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        database.Add(ParseDate("2017-02-05"), "sport event");
        database.Add(ParseDate("2017-06-31"), "sport event");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2016-04-05"), "sport event");
        database.Add(ParseDate("2016-04-05"), "holiday");
        database.Add(ParseDate("2015-02-05"), "sport event");
        database.Add(ParseDate("2015-06-31"), "sport event");
        AssertEqual(DoFind(database, is), respond, "Check Test FindIf");
    }
}

void TestLast() {
    {
        Database database;
        database.Add(ParseDate("2019-04-05"), "Wonderful day");
        database.Add(ParseDate("2019-04-05"), "Wonderful");
        database.Add(ParseDate("2019-04-05"), "AAA");
        database.Add(ParseDate("2019-04-05"), "bbb");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "ZZZ");
        database.Add(ParseDate("2019-04-05"), "W");
        database.Add(ParseDate("2019-04-05"), "ccc");
        database.Add(ParseDate("2018-04-05"), "Wonderful day");
        database.Add(ParseDate("2017-04-05"), "Wonderful");
        AssertEqual(DoLast(database, ParseDate("2019-04-05")), "2019-04-05 ccc", "Check Last 1");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2017-03-31" AND event != "second event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 2, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
        AssertEqual(DoLast(database,ParseDate("2017-03-31")), "2017-03-31 second event", "Check Last3");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2017-03-31" AND event != "second event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 2, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
        AssertEqual(DoLast(database,ParseDate("2018-01-01")), "2017-03-31 second event", "Check Last3");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2017-03-31" AND event != "second event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 2, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
        AssertEqual(DoLast(database,ParseDate("0-1-1")), "0000-01-01 first event", "Check Last3");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2017-03-31" AND event != "second event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 2, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
        AssertEqual(DoLast(database,ParseDate("9999-12-31")), "9999-12-31 first event", "Check Last3");
    }
    {
        Database database;
        
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        std::string last;
        std::string error;
        try {
            last = DoLast(database,ParseDate("0-1-1"));
        } catch (std::invalid_argument&) {
            error = "No entries";
        }
        AssertEqual(error, "No entries", "Check Last");
        
    }
    {
        Database database;
        std::string last;
        std::string error;
        
        try {
            last = DoLast(database,ParseDate("0-1-1"));
        } catch (std::invalid_argument&) {
            error = "No entries";
        }
        AssertEqual(error, "No entries", "Check Last");
        
    }
    {
        Database database;
        std::istringstream is(R"(date == "2017-03-31" AND event != "second event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-30"), "second event");
        database.Add(ParseDate("9999-12-30"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoLast(database,ParseDate("9999-12-31")), "9999-12-30 first event", "Check Last3");
    }
    
}

void TestDel() {
    {
        Database database;
        std::istringstream is(R"(date == "2019-02-02")");
        AssertEqual(DoDelete(database, is), 0, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event == "2019-02-02")");
        AssertEqual(DoDelete(database, is), 0, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"()");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 9, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2019-02-02")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 0, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date == "019-1-2")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 0, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date == "0-1-1")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 1, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2019-04-08")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 3, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date != "2019-02-02")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 9, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date != "2019-04-08")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 6, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date != "0000-01-01")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 8, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date < "0000-01-01")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 0, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date < "2017-03-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 1, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date < "2019-04-08")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 4, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date < "9999-12-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 7, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date < "2019-05-08")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 7, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date > "0-1-1")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 8, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date > "2017-03-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 5, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date > "2019-03-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 5, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date > "2019-04-08")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 2, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date > "9999-12-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 0, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date <= "9999-12-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 9, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date <= "9998-12-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 7, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date <= "2019-04-8")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 7, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date <= "0-1-1")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 1, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date >= "0-1-1")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 9, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date >= "2017-03-30")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 8, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date >= "2017-03-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 8, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date >= "9999-12-31")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 2, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event == "First event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 1, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event == "first event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 4, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 First event\n2017-03-31 second event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event == "first")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 0, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event == "second event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 3, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 First event\n2017-03-31 first event\n2019-04-08 first event\n2019-04-08 third event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event != "second")");
        database.Add(ParseDate("2017-1-1"), "first");
        database.Add(ParseDate("2017-1-1"), "second");
        database.Add(ParseDate("2017-1-1"), "third");
        database.Add(ParseDate("2017-1-1"), "fourth");
        database.Add(ParseDate("2017-1-1"), "five");
        AssertEqual(DoDelete(database, is), 4, "Check Delete events");
        AssertEqual(DoPrint(database), "2017-01-01 second\n", "Check Add");
    }
    {
        Database database;
        std::istringstream is(R"(event != "first")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 9, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event != "first event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 5, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 first event\n2019-04-08 first event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event != "second event")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 6, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 second event\n2019-04-08 second event\n9999-12-31 second event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event < "first")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 1, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n2017-03-31 first event\n2017-03-31 second event\n2019-04-08 first event\n2019-04-08 second event\n2019-04-08 third event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event < "tr")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 9, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event < "ddd")");
        database.Add(ParseDate("2017-03-31"), "aaa");
        database.Add(ParseDate("0-1-1"), "bbb");
        database.Add(ParseDate("2019-04-08"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("2019-04-8"), "ddd");
        database.Add(ParseDate("2019-04-8"), "ddd");
        database.Add(ParseDate("2019-4-8"), "eee");
        database.Add(ParseDate("2017-03-31"), "fff");
        database.Add(ParseDate("2017-03-31"), "fff");
        AssertEqual(DoDelete(database, is), 4, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 fff\n2019-04-08 ddd\n2019-04-08 eee\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event < "ddd")");
        database.Add(ParseDate("2017-03-31"), "aaa");
        database.Add(ParseDate("0-1-1"), "bbb");
        database.Add(ParseDate("2019-04-08"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-4-8"), "eee");
        database.Add(ParseDate("2017-03-31"), "fff");
        database.Add(ParseDate("2017-03-31"), "fff");
        AssertEqual(DoDelete(database, is), 4, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 fff\n2019-04-08 ggg\n2019-04-08 eee\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event > "ddd")");
        database.Add(ParseDate("2017-03-31"), "aaa");
        database.Add(ParseDate("0-1-1"), "bbb");
        database.Add(ParseDate("2019-04-08"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-4-8"), "eee");
        database.Add(ParseDate("2017-03-31"), "fff");
        database.Add(ParseDate("2017-03-31"), "fff");
        AssertEqual(DoDelete(database, is), 3, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 bbb\n2017-03-31 aaa\n2019-04-08 ccc\n9999-12-31 ccc\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event > "eee")");
        database.Add(ParseDate("2017-03-31"), "aaa");
        database.Add(ParseDate("0-1-1"), "bbb");
        database.Add(ParseDate("2019-04-08"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-4-8"), "eee");
        database.Add(ParseDate("2017-03-31"), "fff");
        database.Add(ParseDate("2017-03-31"), "fff");
        AssertEqual(DoDelete(database, is), 2, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 bbb\n2017-03-31 aaa\n2019-04-08 ccc\n2019-04-08 eee\n9999-12-31 ccc\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event <= "ccc")");
        database.Add(ParseDate("2017-03-31"), "aaa");
        database.Add(ParseDate("0-1-1"), "bbb");
        database.Add(ParseDate("2019-04-08"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-4-8"), "eee");
        database.Add(ParseDate("2017-03-31"), "fff");
        database.Add(ParseDate("2017-03-31"), "fff");
        AssertEqual(DoDelete(database, is), 4, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-03-31 fff\n2019-04-08 ggg\n2019-04-08 eee\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(event >= "ddd")");
        database.Add(ParseDate("2017-03-31"), "aaa");
        database.Add(ParseDate("0-1-1"), "bbb");
        database.Add(ParseDate("2019-04-08"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("9999-12-31"), "ccc");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-04-8"), "ggg");
        database.Add(ParseDate("2019-4-8"), "eee");
        database.Add(ParseDate("2017-03-31"), "fff");
        database.Add(ParseDate("2017-03-31"), "fff");
        AssertEqual(DoDelete(database, is), 3, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 bbb\n2017-03-31 aaa\n2019-04-08 ccc\n9999-12-31 ccc\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date < "2019-07-03" AND date > "2017-01-01")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 6, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "0000-01-01 first event\n9999-12-31 second event\n9999-12-31 first event\n", "Check Add 2");
    }
    {
        Database database;
        std::istringstream is(R"(date < "2019-07-03" OR date > "2017-01-01")");
        database.Add(ParseDate("2017-03-31"), "First event");
        database.Add(ParseDate("0-1-1"), "first event");
        database.Add(ParseDate("2019-04-08"), "first event");
        database.Add(ParseDate("9999-12-31"), "second event");
        database.Add(ParseDate("9999-12-31"), "first event");
        database.Add(ParseDate("2019-04-8"), "first event");
        database.Add(ParseDate("2019-04-8"), "second event");
        database.Add(ParseDate("2019-4-8"), "third event");
        database.Add(ParseDate("2017-03-31"), "first event");
        database.Add(ParseDate("2017-03-31"), "second event");
        AssertEqual(DoDelete(database, is), 9, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "", "Check Add 2");
    }
    //_____________________
    {
        Database database;
        std::istringstream is(R"(event == "second" OR event == "fourth")");
        database.Add(ParseDate("2017-01-01"), "first");
        database.Add(ParseDate("2017-01-01"), "second");
        database.Add(ParseDate("2017-01-01"), "third");
        database.Add(ParseDate("2017-01-01"), "fourth");
        database.Add(ParseDate("2017-01-01"), "five");
        AssertEqual(DoDelete(database, is), 2, "Remove several");
        AssertEqual(DoPrint(database), "2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n", "Check print after remove several- 3");
    }
    {
        Database database;
        std::istringstream is(R"(date == "2017-07-08")");
        database.Add(ParseDate("2017-06-01"), "1st of June");
        database.Add(ParseDate("2017-06-02"), "2nd of June");
        database.Add(ParseDate("2017-06-03"), "3rd of June");
        database.Add(ParseDate("2017-06-04"), "4th of June");
        database.Add(ParseDate("2017-06-05"), "5th of June");
        database.Add(ParseDate("2017-07-08"), "8th of July");
        database.Add(ParseDate("2017-07-08"), "Someone's birthday");
        database.Add(ParseDate("2017-07-08"), "Buy groceries");
        database.Add(ParseDate("2017-07-09"), "9th of July");
        database.Add(ParseDate("2017-07-10"), "10th of July");
        database.Add(ParseDate("2017-07-11"), "11th of July");
        database.Add(ParseDate("2017-07-12"), "12th of July");
        database.Add(ParseDate("2017-07-13"), "13th of July");
        database.Add(ParseDate("2017-07-14"), "14th of July");
        AssertEqual(DoDelete(database, is), 3, "Check Delete 0 event");
        AssertEqual(DoPrint(database), "2017-06-01 1st of June\n2017-06-02 2nd of June\n2017-06-03 3rd of June\n2017-06-04 4th of June\n2017-06-05 5th of June\n2017-07-09 9th of July\n2017-07-10 10th of July\n2017-07-11 11th of July\n2017-07-12 12th of July\n2017-07-13 13th of July\n2017-07-14 14th of July\n","Check print after remove several- 3");
    }
    {
        Database database;
        std::istringstream isFind(R"(event != "Weekly meeting")");
        std::istringstream isDelete(R"(date > 2017-11-20)");
        database.Add(ParseDate("2017-11-21"), "Tuesday");
        database.Add(ParseDate("2017-11-20"), "Monday");
        database.Add(ParseDate("2017-11-21"), "Weekly meeting");
        AssertEqual(DoPrint(database), "2017-11-20 Monday\n2017-11-21 Tuesday\n2017-11-21 Weekly meeting\n", "Check print after remove several- 3");
        std::vector<std::string> respond = {
            "2017-11-20 Monday",
            "2017-11-21 Tuesday"
        };
        AssertEqual(DoFind(database, isFind), respond, "Test from tasks");
        AssertEqual(DoDelete(database, isDelete), 2, "Delete from tasks");
        std::string last;
        std::string error;
        try {
            last = DoLast(database,ParseDate("2017-11-30"));
        } catch (std::invalid_argument&) {
            error = "No entries";
        }
        AssertEqual(last, "2017-11-20 Monday", "Check Last");
        try {
            last = DoLast(database,ParseDate("2017-11-01"));
        } catch (std::invalid_argument&) {
            error = "No entries";
        }
        AssertEqual(error, "No entries", "Check Last");
    }
    {
        Database database;
        std::istringstream isDelete(R"(event !="medved")");
        database.Add(ParseDate("2018-03-08"), "preved");
        database.Add(ParseDate("2018-03-08"), "medved");
        AssertEqual(DoDelete(database, isDelete), 1, "Delete from tasks");
        database.Add(ParseDate("2018-03-08"), "krasavcheg");
        std::string last;
        std::string error;
        try {
            last = DoLast(database,ParseDate("2018-03-08"));
        } catch (std::invalid_argument&) {
            error = "No entries";
        }
        AssertEqual(last, "2018-03-08 krasavcheg", "Check Last");
        database.Add(ParseDate("2018-03-08"), "medved");
        try {
            last = DoLast(database,ParseDate("2018-03-08"));
        } catch (std::invalid_argument&) {
            error = "No entries";
        }
        AssertEqual(last, "2018-03-08 krasavcheg", "Check Last");
    }
}
