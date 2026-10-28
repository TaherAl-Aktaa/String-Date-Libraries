#pragma once
#include<iostream>
#include"clsDate.h"

using namespace std;

class clsPeriod
{
	clsDate _StartDate, _EndDate;

public:

	clsPeriod(clsDate StartDate, clsDate EndDate)
	{
		_StartDate = StartDate;
		_EndDate = EndDate;
	}

	void setStartDate(clsDate StartDate)
	{
		_StartDate = StartDate;
	}

	clsDate getStartDate()
	{
		return _StartDate;
	}

	__declspec(property (get = getStartDate, put = setStartDate)) clsDate StartDate;

	void setEndDate(clsDate EndDate)
	{
		_EndDate = EndDate;
	}

	clsDate getEndDate()
	{
		return _EndDate;
	}

	__declspec(property (get = getEndDate, put = setEndDate)) clsDate EndDate;

	void printPeriod()
	{
		cout << "Start Date : " << _StartDate.formatDate() << '\n';
		cout << "End Date   : " << _EndDate.formatDate() << '\n';
	}

	static bool doPeriodsOverlap(clsPeriod Period1, clsPeriod Period2)
	{
		if (clsDate::isDateAfterDate2(Period1.StartDate, Period2.StartDate))
			swap(Period1, Period2);

		return clsDate::isDateAfterDate2(Period1.EndDate, Period2.StartDate);
	}

	bool doPeriodsOverlap(clsPeriod Period2)
	{
		return doPeriodsOverlap(*this, Period2);
	}

	static int calculatePeriodLengthInDays(clsPeriod Period, bool IncludeEndDate = false)
	{
		return clsDate::calculateDiffrenceInDays(Period.StartDate, Period.EndDate, IncludeEndDate);
	}

	int PeriodLength(bool IncludeEndDate = false)
	{
		return calculatePeriodLengthInDays(*this, IncludeEndDate);
	}

	static bool isDateWithinPeriod(clsPeriod Period, clsDate Date)
	{
		return !(Date.isDateBeforeDate2(Period.StartDate) || Date.isDateAfterDate2(Period.EndDate));
	}

	bool isDateWithinPeriod(clsDate Date)
	{
		return isDateWithinPeriod(*this, Date);
	}

	static int countOverlappedDays(clsPeriod Period1, clsPeriod Period2)
	{
		if (!doPeriodsOverlap(Period1, Period2))
			return 0;

		clsDate Start = clsDate::isDateAfterDate2(Period1.StartDate, Period2.StartDate) ? Period1.StartDate : Period2.StartDate;
		clsDate End = clsDate::isDateBeforeDate2(Period1.EndDate, Period2.EndDate) ? Period1.EndDate : Period2.EndDate;

		return clsDate::calculateDiffrenceInDays(Start, End, true);
	}

	int countOverlappedDays(clsPeriod Period2)
	{
		return countOverlappedDays(*this, Period2);
	}
};