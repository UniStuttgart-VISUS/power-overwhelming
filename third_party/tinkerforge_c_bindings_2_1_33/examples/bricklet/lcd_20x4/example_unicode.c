#include <stdio.h>
#include <wchar.h>

#include "ip_connection.h"
#include "bricklet_lcd_20x4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change XYZ to the UID of your LCD 20x4 Bricklet

// Maps a wchar_t string to the LCD charset
static void wchar_to_ks0066u(const wchar_t *wchar, char *ks0066u, int ks0066u_length)
{
	const wchar_t *s = wchar;
	char *d = ks0066u;
	char *e = ks0066u + ks0066u_length;
	char c;
	uint32_t code_point;

	while (*s != '\0' && d < e) {
		// If wchar_t is UTF-16 then handle surrogates
		if (sizeof(wchar_t) == 2 && *s >= 0xd800 && *s <= 0xdbff) {
			code_point = 0x10000 + (*s - 0xd800) * 0x400 + (*(s + 1) - 0xdc00);
			s += 2;
		} else {
			code_point = *s++;
		}

		// ASCII subset from JIS X 0201
		if (code_point >= 0x0020 && code_point <= 0x007e) {
			// The LCD charset doesn't include '\' and '~', use similar characters instead
			switch (code_point) {
			case 0x005c: c = 0xa4; break; // REVERSE SOLIDUS maps to IDEOGRAPHIC COMMA
			case 0x007e: c = 0x2d; break; // TILDE maps to HYPHEN-MINUS
			default: c = code_point; break;
			}
		}
		// Katakana subset from JIS X 0201
		else if (code_point >= 0xff61 && code_point <= 0xff9f) {
			c = code_point - 0xfec0;
		}
		// Special characters
		else {
			switch (code_point) {
			case 0x00a5: c = 0x5c; break; // YEN SIGN
			case 0x2192: c = 0x7e; break; // RIGHTWARDS ARROW
			case 0x2190: c = 0x7f; break; // LEFTWARDS ARROW
			case 0x00b0: c = 0xdf; break; // DEGREE SIGN maps to KATAKANA SEMI-VOICED SOUND MARK
			case 0x03b1: c = 0xe0; break; // GREEK SMALL LETTER ALPHA
			case 0x00c4: c = 0xe1; break; // LATIN CAPITAL LETTER A WITH DIAERESIS
			case 0x00e4: c = 0xe1; break; // LATIN SMALL LETTER A WITH DIAERESIS
			case 0x00df: c = 0xe2; break; // LATIN SMALL LETTER SHARP S
			case 0x03b5: c = 0xe3; break; // GREEK SMALL LETTER EPSILON
			case 0x00b5: c = 0xe4; break; // MICRO SIGN
			case 0x03bc: c = 0xe4; break; // GREEK SMALL LETTER MU
			case 0x03c2: c = 0xe5; break; // GREEK SMALL LETTER FINAL SIGMA
			case 0x03c1: c = 0xe6; break; // GREEK SMALL LETTER RHO
			case 0x221a: c = 0xe8; break; // SQUARE ROOT
			case 0x00b9: c = 0xe9; break; // SUPERSCRIPT ONE maps to SUPERSCRIPT (minus) ONE
			case 0x00a4: c = 0xeb; break; // CURRENCY SIGN
			case 0x00a2: c = 0xec; break; // CENT SIGN
			case 0x2c60: c = 0xed; break; // LATIN CAPITAL LETTER L WITH DOUBLE BAR
			case 0x00f1: c = 0xee; break; // LATIN SMALL LETTER N WITH TILDE
			case 0x00d6: c = 0xef; break; // LATIN CAPITAL LETTER O WITH DIAERESIS
			case 0x00f6: c = 0xef; break; // LATIN SMALL LETTER O WITH DIAERESIS
			case 0x03f4: c = 0xf2; break; // GREEK CAPITAL THETA SYMBOL
			case 0x221e: c = 0xf3; break; // INFINITY
			case 0x03a9: c = 0xf4; break; // GREEK CAPITAL LETTER OMEGA
			case 0x00dc: c = 0xf5; break; // LATIN CAPITAL LETTER U WITH DIAERESIS
			case 0x00fc: c = 0xf5; break; // LATIN SMALL LETTER U WITH DIAERESIS
			case 0x03a3: c = 0xf6; break; // GREEK CAPITAL LETTER SIGMA
			case 0x03c0: c = 0xf7; break; // GREEK SMALL LETTER PI
			case 0x0304: c = 0xf8; break; // COMBINING MACRON
			case 0x00f7: c = 0xfd; break; // DIVISION SIGN

			default:
			case 0x25a0: c = 0xff; break; // BLACK SQUARE
			}
		}

		// Special handling for 'x' followed by COMBINING MACRON
		if (c == (char)0xf8) {
			if (d == ks0066u || (d > ks0066u && *(d - 1) != 'x')) {
				c = 0xff; // BLACK SQUARE
			}

			if (d > ks0066u) {
				--d;
			}
		}

		*d++ = c;
	}

	while (d < e) {
		*d++ = '\0';
	}
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LCD20x4 lcd;
	lcd_20x4_create(&lcd, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Turn backlight on
	lcd_20x4_backlight_on(&lcd);

	// Write some strings using the wchar_to_ks0066u function to map to the LCD charset
	char ks0066u[20];

	wchar_to_ks0066u(L"Stromstärke: 17µA", ks0066u, sizeof(ks0066u));
	lcd_20x4_write_line(&lcd, 0, 0, ks0066u);

	wchar_to_ks0066u(L"Temperatur:  23°C", ks0066u, sizeof(ks0066u));
	lcd_20x4_write_line(&lcd, 1, 0, ks0066u);

	// Write a string directly including characters from the LCD charset
	lcd_20x4_write_line(&lcd, 2, 0, "Drehzahl:   750min\xe9");

	printf("Press key to exit\n");
	getchar();
	lcd_20x4_destroy(&lcd);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
