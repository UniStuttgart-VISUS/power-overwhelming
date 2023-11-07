#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_sound_pressure_level.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Sound Pressure Level Bricklet

// Callback function for decibel callback
void cb_decibel(uint16_t decibel, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Decibel: %f dB(A)\n", decibel/10.0);
}

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

	// Register decibel callback to function cb_decibel
	sound_pressure_level_register_callback(&spl,
	                                       SOUND_PRESSURE_LEVEL_CALLBACK_DECIBEL,
	                                       (void (*)(void))cb_decibel,
	                                       NULL);

	// Set period for decibel callback to 1s (1000ms) without a threshold
	sound_pressure_level_set_decibel_callback_configuration(&spl, 1000, false, 'x', 0, 0);

	printf("Press key to exit\n");
	getchar();
	sound_pressure_level_destroy(&spl);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
