#include <ctime>  // time and localtime
#include <iostream>
#include <fstream>
#include <iomanip>
#include "date.h"

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}
int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

void Date::next() {
    int maxDay = daysPerMonth[getMonth()-1];
    ++day;
    if(day > maxDay){
        day = 1;
        ++month;
        if(month > 12){
            month = 1;
            ++year;
        }
    }
}


istream& operator>> (istream &in, Date &date){
    string str;
    in >> str;
    
    if( (str.length() == 10) && (str.find_first_of('-') == 4) && (str.find_last_of('-') == 7)){
        try {
            date.year = stoi(str.substr(0, 4));
            date.month = stoi(str.substr(5, 2));
            date.day = stoi(str.substr(8, 2));
        } catch (const invalid_argument& e){
            cerr << "Error: " << e.what() << endl;
        }
    } else {
        cout << "invalid input" << endl;
    }
}

ostream& operator<< (ostream &out, Date &date){
    out << setw(4) << setfill('0') << date.year << '-';
	out << setw(2) << setfill('0') << date.month << '-';
	out << setw(2) << setfill('0') << date.day;
    
    //    out << date.year << "-";
    //    if(date.getMonth() < 10){
    //        out << "0" << date.month << "-";
    //    } else {
    //        out << date.month << "-";
    //    }
    //
    //    if(date.getDay() < 10){
    //        out << "0" << date.day << endl;
    //    } else {
    //        out << date.day << endl;
    //    }
}