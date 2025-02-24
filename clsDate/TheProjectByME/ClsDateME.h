#include <iostream>
using namespace std;
#include <ctime>
class MyDate
{
public:
  short Day;
  short Month;
  short Year;

  void LocalTime()
  {
    time_t t = time(0);
    tm *timeNow = localtime(&t);

    Day = timeNow->tm_mday;
    Month = timeNow->tm_mon + 1;
    Year = timeNow->tm_year + 1900;
  }

  MyDate()
  {
    LocalTime();
  }

  void Print()
  {
    cout << Day << "/" << Month << "/" << Year << "\n";
  }

  


};