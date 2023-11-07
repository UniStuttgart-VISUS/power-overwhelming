#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_piezo_speaker_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Piezo Speaker Bricklet 2.0

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PiezoSpeakerV2 ps;
	piezo_speaker_v2_create(&ps, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Make 2 second beep with a frequency of 1kHz
	piezo_speaker_v2_set_beep(&ps, 1000, 0, 2000);

	printf("Press key to exit\n");
	getchar();
	piezo_speaker_v2_destroy(&ps);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
