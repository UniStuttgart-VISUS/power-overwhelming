#define __STDC_FORMAT_MACROS // for PRId64/PRIu64 in C++

#include <stdio.h>
#include <inttypes.h>

#include "ip_connection.h"
#include "bricklet_real_time_clock.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Real-Time Clock Bricklet

// Callback function for date and time callback
void cb_date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute,
                  uint8_t second, uint8_t centisecond, uint8_t weekday, int64_t timestamp,
                  void *user_data) {
	(void)user_data; // avoid unused parameter warning

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

	printf("Timestamp: %" PRId64 "\n", timestamp);
	printf("\n");
}

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

	// Register date and time callback to function cb_date_time
	real_time_clock_register_callback(&rtc,
	                                  REAL_TIME_CLOCK_CALLBACK_DATE_TIME,
	                                  (void (*)(void))cb_date_time,
	                                  NULL);

	// Set period for date and time callback to 5s (5000ms)
	// Note: The date and time callback is only called every 5 seconds
	//       if the date and time has changed since the last call!
	real_time_clock_set_date_time_callback_period(&rtc, 5000);

	printf("Press key to exit\n");
	getchar();
	real_time_clock_destroy(&rtc);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
