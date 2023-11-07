#include <iostream>
#include <ctime>
using namespace std;





struct stDate
{
    short day;
    short month;
    short year;
};

short readNumber(string msg)
{
    short num;

    cout << msg;
    cin >> num;

    return num;
}

stDate readStDate()
{
    stDate Date;

    Date.day = readNumber("Please Enter a Day ");
    Date.month = readNumber("Please Enter a Month ");
    Date.year = readNumber("Please Enter a Year ");

    return Date;
}

bool isLeapYear(short year)
{
    return (year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0)));
}

short numberOfDaysInMonth(short year, short month)
{
    if (month == 2)
    {
        if (isLeapYear(year))
            return  29;
        else
            return  28;
    }

    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return  31;

    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    else
        return 0;
}

short numberOfDaysInYear(short year)
{
    return isLeapYear(year) ? 366 : 365;
}

short orderOfDay(short year, short month, short day)
{
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a) - 2;

    return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short orderOfDay(stDate Date)
{
    return orderOfDay(Date.year, Date.month, Date.day);
}

string nameOfDay(short order)
{
    if (order == 0)
        return "Sun";

    else if (order == 1)
        return "Mon";

    else if (order == 2)
        return "Tue";

    else if (order == 3)
        return "Wed";

    else if (order == 4)
        return "Thur";

    else if (order == 5)
        return "Fri";

    else if (order == 6)
        return "Sat";
    else
        return "Wrong day input";
}

bool isEndOfWeek(stDate Date)
{
    return orderOfDay(Date) == 6;
}

bool isWeekEnd(stDate Date)
{
    short dayOrder = orderOfDay(Date);
    return dayOrder == 5 || dayOrder == 6;
}

bool isBusinessDay(stDate Date)
{
    return !isWeekEnd(Date);
}

short daysUntillTheEndOfWeek(stDate Date)//   23/9/2022
{
    return 6 - orderOfDay(Date);
}

int dateDiff(stDate Date1, stDate Date2, bool isIncludeEndDay = false)
{
    int numberOfDays = 0;

    for (short year = Date1.year; year < Date2.year; year++)
        numberOfDays += numberOfDaysInYear(year);

    if (Date1.year == Date2.year)
    {
        for (short month = Date1.month; month < Date2.month; month++)
            numberOfDays += numberOfDaysInMonth(Date1.year, month);
    }

    numberOfDays += Date2.day - Date1.day;

    return (isIncludeEndDay) ? ++numberOfDays : numberOfDays;
}

short daysFromBeginningOfYear(short year, short month, short day)
{
    short numberOfDays = 0;

    for (short mon = 1; mon < month; mon++)
    {
        numberOfDays += numberOfDaysInMonth(year, mon);
    }
    numberOfDays += day;

    return numberOfDays;
}

short daysUntillTheEndOfMonth(stDate Date)//   23/9/2022
{
    stDate DateOfEndOfYear;

    DateOfEndOfYear.day = numberOfDaysInMonth(Date.year, Date.month);
    DateOfEndOfYear.month = Date.month;
    DateOfEndOfYear.year = Date.year;

    return dateDiff(Date, DateOfEndOfYear, 1);
    //return (numberOfDaysInMonth(Date.year, Date.month) - Date.day)+1;
}

short daysUntillTheEndOfYear(stDate Date)//   23/9/2022
{
    //short daysOfTodayDate = daysFromBeginningOfYear(Date.year, Date.month, Date.day);
    //return (numberOfDaysInYear(Date.year) - daysOfTodayDate)+1;

    stDate DateOfEndOfYear;

    DateOfEndOfYear.day = 31;
    DateOfEndOfYear.month = 12;
    DateOfEndOfYear.year = Date.year;

    return dateDiff(Date, DateOfEndOfYear, 1);
}

void printDate(string msg, stDate Date)
{
    cout << msg;
    cout << nameOfDay(orderOfDay(Date)) << " , ";
    cout << Date.day << "/" << Date.month << "/" << Date.year << "\n";
}

short claculateVacationDays(stDate DateFrom, stDate DateTo)
{//    1/9/2022    5/9/222
    short vacationPeriod = 0;
    short weekEnd = 0;
    short dateDifference = dateDiff(DateFrom, DateTo);

    for (short day = 1; day <= dateDifference; day++)
    {
        DateFrom.day = day;
        if (isWeekEnd(DateFrom))
            weekEnd++;
        else
            vacationPeriod++;
    }
    vacationPeriod = dateDifference - weekEnd;

    return vacationPeriod;
}



int main()
{
    stDate startDate, endDate;

    cout << "Vacation starts:\n";
    startDate = readStDate();
    //startDate.day = 1;
    //startDate.month = 9;
    //startDate.year = 2022;
    cout << "\n";

    cout << "Vacation ends:\n";
    endDate = readStDate();
    //endDate.day = 5;
    //endDate.month = 9;
    //endDate.year = 2022;
    cout << "\n";

    printDate("Vacation from: ", startDate);
    printDate("Vacation to: ", endDate);

    cout << "\nActual vacation Days is: " << claculateVacationDays(startDate, endDate);
    cout << "\n\n";



    system("pause>0");
    return main();
}