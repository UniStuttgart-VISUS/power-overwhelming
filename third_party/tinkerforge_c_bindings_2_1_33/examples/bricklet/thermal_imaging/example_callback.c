#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_thermal_imaging.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Thermal Imaging Bricklet

// Callback function for high contrast image callback
void cb_high_contrast_image(uint8_t *image, uint16_t image_length, void *user_data) {
	(void)image; (void)image_length; (void)user_data; // avoid unused parameter warning

	// image is an array of size 80*60 with a 8 bit grey value for each element
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	ThermalImaging ti;
	thermal_imaging_create(&ti, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register high contrast image callback to function cb_high_contrast_image
	thermal_imaging_register_callback(&ti,
	                                  THERMAL_IMAGING_CALLBACK_HIGH_CONTRAST_IMAGE,
	                                  (void (*)(void))cb_high_contrast_image,
	                                  NULL);

	// Enable high contrast image transfer for callback
	thermal_imaging_set_image_transfer_config(&ti,
	                                          THERMAL_IMAGING_IMAGE_TRANSFER_CALLBACK_HIGH_CONTRAST_IMAGE);

	printf("Press key to exit\n");
	getchar();
	thermal_imaging_destroy(&ti);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
