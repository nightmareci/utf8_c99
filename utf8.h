#ifndef _include_guard_nightmareci_utf8_c_
#define _include_guard_nightmareci_utf8_c_

#include <stdint.h>

/**
 * Decode a Unicode codepoint from a UTF-8-encoded string.
 *
 * \param codepoint a pointer receiving the decoded codepoint or NULL if the
 *                  decoded data isn't desired
 * \param str the start of the UTF-8 data to decode
 * \returns the number of UTF-8-encoded bytes representing the codepoint or -1
 *          if errors were encountered during decoding
 */
int utf8_decode(uint32_t* codepoint, const char* const str);

/**
 * Encode a Unicode codepoint to a UTF-8-encoded string.
 *
 * This could also be used just to get the number of bytes a codepoint needs
 * (str == NULL), allocate that much memory, then call again to store the bytes
 * (str != NULL).
 *
 * \param str the location where the UTF-8-encoded codepoint will be written or
 *            NULL if the encoded data isn't desired
 * \param codepoint the codepoint to encode
 * \param str_end the end of the buffer after str, the buffer being where
 *                UTF-8-encoded data can be written. If str == NULL, this
 *                parameter must be NULL.
 * \returns the number of UTF-8-encoded bytes representing the codepoint or -1
 *          if errors were encountered during encoding
 */
int utf8_encode(char* const str, const uint32_t codepoint, char* const str_end);

#endif
