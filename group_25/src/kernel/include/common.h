#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

// Scancode -> ASCII
static const char lower_ascii_codes[] = {
    0x00,   27,  '1',  '2',     /* 0x00 */
     '3',  '4',  '5',  '6',     /* 0x04 */
     '7',  '8',  '9',  '0',     /* 0x08 */
     '-',  '=',  '\b', '\t',     /* 0x0C */
     'q',  'w',  'e',  'r',     /* 0x10 */
     't',  'y',  'u',  'i',     /* 0x14 */
     'o',  'p',  '[',  ']',     /* 0x18 */
    '\n', 0x00,  'a',  's',     /* 0x1C */
     'd',  'f',  'g',  'h',     /* 0x20 */
     'j',  'k',  'l',  ';',     /* 0x24 */
    '\'',  '`', 0x00, '\\',     /* 0x28 */
     'z',  'x',  'c',  'v',     /* 0x2C */
     'b',  'n',  'm',  ',',     /* 0x30 */
     '.',  '/', 0x00,  '*',     /* 0x34 */
    0x00,  ' ', 0x00, 0x00,     /* 0x38 */
    0x00, 0x00, 0x00, 0x00,     /* 0x3C */
    0x00, 0x00, 0x00, 0x00,     /* 0x40 */
    0x00, 0x00, 0x00,  '7',     /* 0x44 */
     '8',  '9',  '-',  '4',     /* 0x48 */
     '5',  '6',  '+',  '1',     /* 0x4C */
     '2',  '3',  '0',  '.',     /* 0x50 */
    0x00, 0x00, 0x00, 0x00,     /* 0x54 */
    0x00, 0x00, 0x00, 0x00      /* 0x58 */
};

#endif