#define __STDC_FORMAT_MACROS // for PRId64/PRIu64 in C++

#include <stdio.h>
#include <inttypes.h>

#include "ip_connection.h"
#include "bricklet_real_time_clock.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Real-Time Clock Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	RealTimeClock rtc;
	real_time_clock_create(&rtc, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current date and time
	uint16_t year; uint8_t month, day, hour, minute, second, centisecond, weekday;
	if(real_time_clock_get_date_time(&rtc, &year, &month, &day, &hour, &minute, &second,
	                                 &centisecond, &weekday) < 0) {
		fprintf(stderr, "Could not get date and time, probably timeout\n");
		return 1;
	}

	printf("Year: %u\n", year);
	printf("Month: %u\n", month);
	printf("Day: %u\n", day);
	printf("Hour: %u\n", hour);
	printf("Minute: %u\n", minute);
	printf("Second: %u\n", second);
	printf("Centisecond: %u\n", centisecond);

	if(weekday == REAL_TIME_CLOCK_WEEKDAY_MONDAY) {
		printf("Weekday: Monday\n");
	} else if(weekday == REAL_TIME_CLOCK_WEEKDAY_TUESDAY) {
		printf("Weekday: Tuesday\n");
	} else if(weekday == REAL_TIME_CLOCK_WEEKDAY_WEDNESDAY) {
		printf("Weekday: Wednesday\n");
	} else if(weekday == REAL_TIME_CLOCK_WEEKDAY_THURSDAY) {
		printf("Weekday: Thursday\n");
	} else if(weekday == REAL_TIME_CLOCK_WEEKDAY_FRIDAY) {
		printf("Weekday: Friday\n");
	} else if(weekday == REAL_TIME_CLOCK_WEEKDAY_SATURDAY) {
		printf("Weekday: Saturday\n");
	} else if(weekday == REAL_TIME_CLOCK_WEEKDAY_SUNDAY) {
		printf("Weekday: Sunday\n");
	}

	// Get current timestamp
	int64_t timestamp;
	if(real_time_clock_get_timestamp(&rtc, &timestamp) < 0) {
		fprintf(stderr, "Could not get timestamp, probably timeout\n");
		return 1;
	}

	printf("Timestamp: %" PRId64 " ms\n", timestamp);

	printf("Press key to exit\n");
	getchar();
	real_time_clock_destroy(&rtc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
