#pragma waring(disable : 4996)
#pragma once

#include <iostream>
#include <string>
#include "C:\Tutourials\HadhoudAdvices\10_OOP\HadhoudFristProject\HadHoudClsString.h"

using namespace std;

class clsDate
{
private:
  short _Day = 1;
  short _Month = 1;
  short _Year = 1900;

public:
  clsDate()
  {
    time_t t = time(0);
    tm *now = localtime(&t);
    _Day = now->tm_mday;
    _Month = now->tm_mon + 1;
    _Year = now->tm_year = 1900;
  }

  clsDate(string Date)
  {
    vector<string> vDate;
    vDate = clsString::Split(Date, "/");
    _Day = stoi(vDate[0]);
    _Month = stoi(vDate[1]);
    _Year = stoi(vDate[2]);
  }
  clsDate(short Day, short Month, short Year)
  {
    _Day = Day;
    _Month = Month;
    _Year = Year;
  }

  clsDate(short DateOrderInYear, short Year)
  {
    // This will construct a date by date order in year
    clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
    _Day = Date1.Day;
    _Month = Date1.Month;
    _Year = Date1.Year;
  }

  void SetDay(short Day)
  {
    _Day = Day;
  }

  short GetDay()
  {
    return _Day;
  }

  void SetMonth(short Month)
  {
    _Month = Month;
  }

  short GetMonth()
  {
    return _Month;
  }

  void SetYear(short Year)
  {
    _Year = Year;
  }

  short GetYear()
  {
    return _Year;
  }

  ////////////////////////////////////////
  void Print()
  {
    cout << DateToString() << endl;
  }

  static clsDate GetSystemDate()
  {
    // system date
    time_t t = time(0);
    tm *now = localtime(&t);

    short Day, Month, Year;

    Year = now->tm_year + 1900;
    Month = now->tm_mon + 1;
    Day = now->tm_mday;

    return clsDate(Day, Month, Year);
  }

  static bool IsValidDate(clsDate Date)
  {

    if (Date.Day < 1 || Date.Day > 31)
      return false;

    if (Date.Month < 1 || Date.Month > 12)
      return false;

    if (Date.Month == 2)
    {
      if (isLeapYear(Date.Year))
      {
        if (Date.Day > 29)
          return false;
      }
      else
      {
        if (Date.Day > 28)
          return false;
      }
    }

    short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

    if (Date.Day > DaysInMonth)
      return false;

    return true;
  }

  bool IsValid()
  {
    return IsValidDate(*this);
  }

  static string DateToString(clsDate Date)
  {
    return to_string(Date.GetDay()) + "/" + to_string(Date.GetMonth()) + "/" + to_string(Date.GetYear());
  }

  
  };