#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_gps.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your GPS Bricklet

// Callback function for coordinates callback
void cb_coordinates(uint32_t latitude, char ns, uint32_t longitude, char ew,
                    uint16_t pdop, uint16_t hdop, uint16_t vdop, uint16_t epe,
                    void *user_data) {
	(void)pdop; (void)hdop; (void)vdop; (void)epe;
	(void)user_data; // avoid unused parameter warning

	printf("Latitude: %f °\n", latitude/1000000.0);
	printf("N/S: %c\n", ns);
	printf("Longitude: %f °\n", longitude/1000000.0);
	printf("E/W: %c\n", ew);
	printf("\n");
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	GPS gps;
	gps_create(&gps, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register coordinates callback to function cb_coordinates
	gps_register_callback(&gps,
	                      GPS_CALLBACK_COORDINATES,
	                      (void (*)(void))cb_coordinates,
	                      NULL);

	// Set period for coordinates callback to 1s (1000ms)
	// Note: The coordinates callback is only called every second
	//       if the coordinates has changed since the last call!
	gps_set_coordinates_callback_period(&gps, 1000);

	printf("Press key to exit\n");
	getchar();
	gps_destroy(&gps);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
