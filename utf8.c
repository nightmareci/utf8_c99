#include "utf8.h"
#include <string.h>
#include <stddef.h>

int utf8_decode(uint32_t* const codepoint, const char* const str) {
	// Validate parameters
	if (str == NULL) {
		return -1;
	}

	const char* const end = str + strlen(str);

	// ASCII
	uint32_t temp = (uint8_t)*str;
	if ((temp & 0x80) == 0x00) {
		if (codepoint != NULL) {
			*codepoint = (uint8_t)temp;
		}
		return 1;
	}

	// Check UTF-8 leading byte
	int bytes;
	if ((temp & 0xE0) == 0xC0) {
		if (end - str < 2) {
			return -1;
		}
		temp &= 0x1F;
		bytes = 2;
	}
	else if ((temp & 0xF0) == 0xE0) {
		if (end - str < 3) {
			return -1;
		}
		temp &= 0xF;
		bytes = 3;
	}
	else if ((temp & 0xF1) == 0xF0) {
		if (end - str < 4) {
			return -1;
		}
		temp &= 0x7;
		bytes = 4;
	}

	// Continuation bytes
	const char* const last = str + bytes;
	for (const char* c = str + 1; c < last; c++) {
		const uint8_t byte = (uint8_t)*c;
		if ((byte & 0xC0) != 0x80) {
			return -1;
		}
		temp = (temp << 6) | (byte & 0x3F);
	}

	// No overlong encodings
	switch (bytes) {
	case 2:
		if (temp <= 0x7F) {
			return -1;
		}
		break;

	case 3:
		if (temp <= 0x7FF) {
			return -1;
		}
		break;

	case 4:
		if (temp <= 0xFFFF) {
			return -1;
		}
		break;

	default:
		return -1;
	}

	// Reject codepoints not valid in UTF-16
	if (
		(temp >= UINT32_C(0xD800) && temp <= UINT32_C(0xDFFF)) ||
		temp > UINT32_C(0x10FFFF)
	) {
		return -1;
	}

	if (codepoint != NULL) {
		*codepoint = temp;
	}
	return bytes;
}

int utf8_encode(char* const str, const uint32_t codepoint, char* const str_end) {
	// Validate parameters
	if ((str != NULL && str_end == NULL) || (str == NULL && str_end != NULL) || str_end <= str) {
		return -1;
	}

	// ASCII
	if (codepoint <= 0x7F) {
		if (str != NULL) {
			*str = codepoint;
		}
		return 1;
	}

	// Reject codepoints not valid in UTF-16
	if (
		(codepoint >= UINT32_C(0xD800) && codepoint <= UINT32_C(0xDFFF)) ||
		codepoint > UINT32_C(0x10FFFF)
	) {
		return -1;
	}

	// Select number of bytes, avoiding overlong encoding
	int bytes;
	if (codepoint <= UINT32_C(0x7FF)) {
		bytes = 2;
	}
	else if (codepoint <= UINT32_C(0xFFFF)) {
		bytes = 3;
	}
	else {
		bytes = 4;
	}

	// User did not desire the encoded data
	if (str == NULL) {
		return bytes;
	}

	// No out-of-bounds access
	if (str_end - str < bytes) {
		return -1;
	}

	// Encode leading UTF-8 byte
	switch (bytes) {
	case 2:
		str[0] = 0xC0 | ((codepoint >> 6) & 0x1F);
		break;

	case 3:
		str[0] = 0xE0 | ((codepoint >> 12) & 0x0F);
		break;

	case 4:
		str[0] = 0xF0 | ((codepoint >> 18) & 0x03);
		break;

	default:
		return -1;
	}

	// Encode continuation UTF-8 bytes
	char* byte = str + 1;
	for (int bits = (bytes - 2) * 6; bits >= 0; bits -= 6, byte++) {
		*byte = (char)(0x80 | ((codepoint >> bits) & 0x3F));
	}

	return bytes;
}
