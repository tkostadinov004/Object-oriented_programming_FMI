#include <iostream>

class Time
{
	int hours;
	int minutes;
	public:
		Time(int hours = 0, int minutes = 0)
		{
			this->hours = hours;
			this->minutes = minutes;
		}
		unsigned getHours() const
		{
			return hours;
		}
		void setMinutes(int minutes)
		{
			if (minutes < 0 || minutes > 59)
			{
				return;
			}

			this->minutes = minutes;
		}
		unsigned getMinutes() const
		{
			return minutes;
		}
		void setHours(int hours)
		{
			if (minutes < 0 || minutes > 23)
			{
				return;
			}

			this->hours = hours;
		}
		void addMinutes(int minutes)
		{
			this->minutes += minutes;
			hours += (minutes / 60);
			this->minutes %= 60;
			this->hours %= 24;
		}
		int getMinutesSinceMidnight() const
		{
			return hours * 60 + minutes;
		}
		bool operator<(const Time& other)
		{
			return this->hours < other.hours || (this->hours == other.hours && this->minutes < other.minutes);
		}
		Time operator+(const Time& other)
		{
			Time temp{};
			temp.addMinutes(this->getMinutesSinceMidnight() + other.getMinutesSinceMidnight());
			return temp;
		}
		Time operator-(const Time& other)
		{
			Time temp{};
			temp.addMinutes(abs(this->getMinutesSinceMidnight() - other.getMinutesSinceMidnight()));
			return temp;
		}
		Time operator*(int num)
		{
			Time temp{};
			temp.addMinutes(abs(this->getMinutesSinceMidnight() * num));
			return temp;
		}
};
int operator*(int num, Time time)
{
	return num * time.getMinutesSinceMidnight();
}
std::ostream& operator<<(std::ostream& os, const Time& time)
{
	os << time.getHours() << " " << time.getMinutes();
	return os;
}

int main()
{
	Time t1(15, 23);
	Time t2(17, 54);

	std::cout << t1 + t2 << std::endl;
	std::cout << t1 - t2 << std::endl;
	std::cout << t1 * 2 << std::endl;
	std::cout << 2 * t1 << std::endl;
	std::cout << (t1 < t2) << std::endl;
	std::cout << (t2 < t1) << std::endl;
}