#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_sound_pressure_level.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Sound Pressure Level Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SoundPressureLevel spl;
	sound_pressure_level_create(&spl, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current decibel
	uint16_t decibel;
	if(sound_pressure_level_get_decibel(&spl, &decibel) < 0) {
		fprintf(stderr, "Could not get decibel, probably timeout\n");
		return 1;
	}

	printf("Decibel: %f dB(A)\n", decibel/10.0);

	printf("Press key to exit\n");
	getchar();
	sound_pressure_level_destroy(&spl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
