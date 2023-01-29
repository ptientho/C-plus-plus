#include <time.h>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

using namespace std;
class JulianDate {
private:
	static int EPOCH;
	//	int mon, day, year, hour, min, second;
	int mon, day, year, hour, minute, second;
	// this representation would make difference VERY UGLY
	// diff between Jan. 1 2001 12:03:04  and Feb 26 2028 11:19:02
	double jday; // number of days since epoch

public:
	JulianDate(int y, int mo, int d, int hr, int min, int s) : year(y), mon(mo), day(d), hour(hr), 
	minute(min), second(s){ 

		//number of years to days
		int y2d, lyrs, dmonth, mo2d = 0;
		bool isLeap;
		y2d = (year - EPOCH)*365;
		//number of leap years passed
		lyrs = (int)floor((year - EPOCH) / 4 - (year - EPOCH) / 100 + (year - EPOCH) / 400);

		//y2d + lyrs; // this will set JD like this 1 Jan of year y
		
		if(year % 4 == 0){ // check if the year y is leap or not
			if(year % 100 == 0){
				if(year % 400 == 0){
					isLeap = true;
				}else{isLeap = false;}
			}else{isLeap = true;}
		}else{isLeap = false;}

		dmonth = mon - 1; //number of months passed
		for(int m = 1; m <= dmonth; m++){ //count the number of days before 1 of that month
			int mArr[] = {1, 3, 5, 7, 8, 10, 12};
			if(find(begin(mArr), end(mArr), m) != end(mArr)){
				mo2d += 31;
			}else if (m == 2){
				if(isLeap){mo2d += 29;}
				else{mo2d += 28;}
			}else{
				mo2d += 30;
			}	
		}

		//now add m2d with d, so we count JD until day d of that month in that year time 00:00:00
		//First, convert hrs into a fraction in a day
		//Second, convert min to day
		double h2d, min2d, sec2d;
		h2d = (double)hour/ 24;
		min2d = (double)minute / (60*24);
		sec2d = (double)second / (60*60*24);

		jday = y2d + lyrs + mo2d + (day - 1) + h2d + min2d + sec2d;
		
	}
	JulianDate(){
        time_t current = time(0);
        //cout << "Time is: " << current;
        tm* ltm = localtime(&current);
        year = 1900 + ltm->tm_year; mon = 1 + ltm->tm_mon; day = ltm->tm_mday; hour = ltm->tm_hour; minute  = ltm->tm_min; second = ltm->tm_sec;

        //number of years to days
        int y2d, lyrs, dmonth, mo2d = 0;
        bool isLeap;
        y2d = (year - EPOCH)*365;
        //number of leap years passed
        lyrs = (int)floor((year - EPOCH) / 4 - (year - EPOCH) / 100 + (year - EPOCH) / 400);

        //y2d + lyrs; // this will set JD like this 1 Jan of year y

        if(year % 4 == 0){ // check if the year y is leap or not
            if(year % 100 == 0){
                if(year % 400 == 0){
                    isLeap = true;
                }else{isLeap = false;}
            }else{isLeap = true;}
        }else{isLeap = false;}

        dmonth = mon - 1; //number of months passed
        for(int m = 1; m <= dmonth; m++){ //count the number of days before 1 of that month
            int mArr[] = {1, 3, 5, 7, 8, 10, 12};
            if(find(begin(mArr), end(mArr), m) != end(mArr)){
                mo2d += 31;
            }else if (m == 2){
                if(isLeap){mo2d += 29;}
                else{mo2d += 28;}
            }else{
                mo2d += 30;
            }
        }

        //now add m2d with d, so we count JD until day d of that month in that year time 00:00:00
        //First, convert hrs into a fraction in a day
        //Second, convert min to day
        double h2d, min2d, sec2d;
        h2d = (double)hour / 24;
        min2d = (double)minute / (60*24);
        sec2d = (double)second / (60*60*24);

        jday = y2d + lyrs + mo2d + (day - 1) + h2d + min2d + sec2d;


	}

	int getYear() const{

		return year;
	}

	int getMonth() const{

		return mon;
	}

	int getDay() const{

		return day;
	}

	int getHour() const{

		return hour;
	}

	int getMin() const{

		return minute;
	}

	int getSec() const{

		return second;
	}

	friend double operator -(JulianDate left, JulianDate right) {
		return left.jday - right.jday;
	}
	friend ostream& operator <<(ostream& s, JulianDate j){
		return s << j.jday << '\n'; //just test. Make format later
	}
	friend JulianDate operator +(JulianDate& j, int i){
		return JulianDate(j.getYear(), j.getMonth(), j.getDay() + i, j.getHour(), j.getMin(), j.getSec());
	}


};

/*
	how many days in a year? 365
	leap year: if year MOD 4 == 0 LEAP EXCEPT
	           if year MOD 100 == 0 NOT LEAP YEAR Except
						 if year MOD 400 == 0 LEAP

Leap years:
 NO 1900 
 YES 1904
 YES 1908
 YES 2000
 NO 2100
 YES 2400

    days since EPOCH = 365 * (year - 2000) + years/4 - ....

2018 - 2000 = 18

seconds in a day = 24*60*60 = 86400

hh:mm:ss     

00:00:00  0.0
12:00:00  0.5

18*365+18/4 - 18/100 + 18/400
18*365+4 = 6574

6574.041666666 --> Jan 1, 2018, 01:00:00
http://aa.usno.navy.mil/faq/docs/JD_Formula.php
http://www.math.harvard.edu/~knill/3dprinter/exhibits/bc/Meeus1988.pdf

 */

int JulianDate::EPOCH = 2000; // Jan.1 2000, 00:00:00 = 0 base year? yes, the JD is relative to this date

int main() {
	JulianDate newyear(2018, 1, 1, 0,0,0); // how many days since day 0? dy = (2018 - 2000) * 365
	JulianDate valentine(2018, 2, 14, 12,0,0); // 0.5
	JulianDate today; // get it from the system time: time(nullptr)
	                  // localtime
	double days = valentine - newyear;
	JulianDate due = today + 7;
	cout << newyear << '\n';

	cout << "\nyear: " << newyear.getYear()
			 << "\nmonth: " << newyear.getMonth()
			 << "\nday: " << newyear.getDay()
			 << "\nhour: " << newyear.getHour()
			 << "\nmin: " << newyear.getMin()
			 << "\nsec: " << newyear.getSec() << '\n';
	JulianDate d1(2019, 1, 1, 0,0,0);
	for (int i = 0; i < 100; i++)
		cout << d1 + i;

}

		
