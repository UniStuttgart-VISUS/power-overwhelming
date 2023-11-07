#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_gps_v3.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your GPS Bricklet 3.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	GPSV3 gps;
	gps_v3_create(&gps, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current coordinates
	uint32_t latitude, longitude; char ns, ew;
	if(gps_v3_get_coordinates(&gps, &latitude, &ns, &longitude, &ew) < 0) {
		fprintf(stderr, "Could not get coordinates, probably timeout\n");
		return 1;
	}

	printf("Latitude: %f °\n", latitude/1000000.0);
	printf("N/S: %c\n", ns);
	printf("Longitude: %f °\n", longitude/1000000.0);
	printf("E/W: %c\n", ew);

	printf("Press key to exit\n");
	getchar();
	gps_v3_destroy(&gps);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
