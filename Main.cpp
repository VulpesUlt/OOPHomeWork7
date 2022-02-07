#include <iostream>
#include <time.h>


// Task 1

class Date 
{
private:
	uint16_t m_day;
	uint16_t m_month;
	uint16_t m_year;
public:
	Date(): m_day(0), m_month(0), m_year(0) { }
	Date(uint16_t day, uint16_t month, uint16_t year) : m_day(day), m_month(month), m_year(year) { }
	
	uint16_t getDay() const { return m_day; }
	uint16_t getMonth() const { return m_month; }
	uint16_t getYear() const { return m_year; }

	void setDay(uint16_t day) { m_day = day; }
	void setMonth(uint16_t month) { m_month = month; }
	void setYear(uint16_t year) { m_year = year; }

	friend std::ostream& operator<< (std::ostream& stream, Date& date);
};

std::ostream& operator<< (std::ostream& stream, Date& date)
{
	stream << static_cast<int>(date.getDay()) << "/" << static_cast<int>(date.getMonth()) << "/" << static_cast<int>(date.getYear());
	return stream;
}

// Task 2

std::shared_ptr<Date> compareDate (std::shared_ptr<Date> dateOne, std::shared_ptr<Date> dateTwo)
{
	if (dateOne->getYear() == dateTwo->getYear())
	{
		if (dateOne->getMonth() == dateTwo->getMonth())
		{
			if (dateOne->getDay() == dateTwo->getDay())
			{
				return dateOne;
			}
			else if (dateOne->getDay() > dateTwo->getDay())
			{
				return dateOne;
			}
			else
			{
				return dateTwo;
			}
		}
		else if (dateOne->getMonth() > dateTwo->getMonth())
		{
			return dateOne;
		}
		else
		{
			return dateTwo;
		}
	}
	else if (dateOne->getYear() > dateTwo->getYear())
	{
		return dateOne;
	}
	else
	{
		return dateTwo;
	}
}

void swapDate(std::shared_ptr<Date> dateOne, std::shared_ptr<Date> dateTwo)
{
	std::shared_ptr<Date> tmp = std::make_shared<Date>();
	*tmp.get() = *dateOne.get();
	*dateOne.get() = *dateTwo.get();
	*dateTwo.get() = *tmp.get();
}

int main()
{
	
	// Task 1
	std::shared_ptr<Date> today = std::make_shared<Date>(5, 2, 2022);
	
	today->setDay(6);
	today->setMonth(2);
	today->setYear(2022);
	std::cout << *today << std::endl;

	std::shared_ptr<Date> date = std::move(today);
	if (today == nullptr)
		std::cout << "today is a nullptr" << std::endl;
	else
		std::cout << "today isn't a nullptr" << std::endl;

	if (date == nullptr)
		std::cout << "date is a nullptr" << std::endl;
	else
		std::cout << "date isn't a nullptr" << std::endl;

	// Task 2

	std::shared_ptr<Date> date1 = std::make_shared<Date>(1, 2, 2022);
	std::shared_ptr<Date> date2 = std::make_shared<Date>(1, 4, 2022);

	std::cout << *compareDate(date1, date2) << std::endl;

	if (date1 == nullptr)
		std::cout << "date1 is a nullptr" << std::endl;
	else
		std::cout << "date1 isn't a nullptr" << std::endl;

	if (date2 == nullptr)
		std::cout << "date2 is a nullptr" << std::endl;
	else
		std::cout << "date2 isn't a nullptr" << std::endl;

	//date1.swap(date2);
	swapDate(date1, date2);

	std::cout << *date1 << " " << *date2 << std::endl;

	return 0;
}