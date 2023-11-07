#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_sound_intensity.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Sound Intensity Bricklet

// Callback function for intensity reached callback
void cb_intensity_reached(uint16_t intensity, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Intensity: %u\n", intensity);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	SoundIntensity si;
	sound_intensity_create(&si, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get threshold callbacks with a debounce time of 1 second (1000ms)
	sound_intensity_set_debounce_period(&si, 1000);

	// Register intensity reached callback to function cb_intensity_reached
	sound_intensity_register_callback(&si,
	                                  SOUND_INTENSITY_CALLBACK_INTENSITY_REACHED,
	                                  (void (*)(void))cb_intensity_reached,
	                                  NULL);

	// Configure threshold for intensity "greater than 2000"
	sound_intensity_set_intensity_callback_threshold(&si, '>', 2000, 0);

	printf("Press key to exit\n");
	getchar();
	sound_intensity_destroy(&si);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
