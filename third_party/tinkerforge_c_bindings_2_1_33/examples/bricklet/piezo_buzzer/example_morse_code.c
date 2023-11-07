#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_piezo_buzzer.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your Piezo Buzzer Bricklet

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	PiezoBuzzer pb;
	piezo_buzzer_create(&pb, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Morse SOS
	piezo_buzzer_morse_code(&pb, "... --- ...");

	printf("Press key to exit\n");
	getchar();
	piezo_buzzer_destroy(&pb);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
