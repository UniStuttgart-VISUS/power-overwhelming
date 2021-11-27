#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_piezo_speaker.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Piezo Speaker Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PiezoSpeaker ps;
	piezo_speaker_create(&ps, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Morse SOS with a frequency of 2kHz
	piezo_speaker_morse_code(&ps, "... --- ...", 2000);

	printf("Press key to exit\n");
	getchar();
	piezo_speaker_destroy(&ps);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
