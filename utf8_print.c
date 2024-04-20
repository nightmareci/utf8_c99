#include "utf8.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static void print_byte_binary(const char* const byte) {
	for (int i = 7; i >= 0; i--) {
		putc((uint8_t)*byte & (1 << i) ? '1' : '0', stdout);
	}
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		goto usage;
	}

	const char* const data = argv[1];
	const char* const data_end = data + strlen(data);

	printf("Direct printf: %s\n", data);

	printf("Hex bytes: ");
	for (const char* str = data; *str != '\0'; str++) {
		printf("%02" PRIX8, (uint8_t)*str);
		if (str[1] != '\0') {
			printf(", ");
		}
	}
	printf("\n");

	printf("Binary bytes: ");
	for (const char* str = data; *str != '\0'; str++) {
		print_byte_binary(str);
		if (str[1] != '\0') {
			printf(", ");
		}
	}
	printf("\n");

	printf("Unicode codepoints: ");
	int bytes;
	for (const char* str = data; *str != '\0'; str += bytes) {
		uint32_t codepoint;
		bytes = utf8_decode(&codepoint, str);
		if (bytes < 0) {
			printf("UTF-8 data found to be invalid\n");
			return EXIT_FAILURE;
		}
		printf("%08" PRIX32, codepoint);
		if (*(str + bytes) != '\0') {
			printf(", ");
		}
	}
	printf("\n");

	return EXIT_SUCCESS;

	usage:
	printf("utf8_print [string]\n");
	return EXIT_FAILURE;
}
