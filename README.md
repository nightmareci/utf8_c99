Some tools written in C, only needing C99, for handling UTF-8-encoded text.

You can just copy `utf8.h` and `utf8.c` into another project to get the tools.

Read `utf8.h` for how to use the tools.

Example:
```sh
$ cmake -B build -G Ninja
$ cmake --build build
$ ./build/utf8_print "こんにちは世界！"
Direct printf: こんにちは世界！
Hex bytes: E3, 81, 93, E3, 82, 93, E3, 81, AB, E3, 81, A1, E3, 81, AF, E4, B8, 96, E7, 95, 8C, EF, BC, 81
Binary bytes: 11100011, 10000001, 10010011, 11100011, 10000010, 10010011, 11100011, 10000001, 10101011, 11100011, 10000001, 10100001, 11100011, 10000001, 10101111, 11100100, 10111000, 10010110, 11100111, 10010101, 10001100, 11101111, 10111100, 10000001
Unicode codepoints: 00003053, 00003093, 0000306B, 00003061, 0000306F, 00004E16, 0000754C, 0000FF01
```
