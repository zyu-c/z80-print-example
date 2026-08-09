#ifndef IO_H
#define IO_H

#include <stdint.h>

void io_out(uint8_t port, uint8_t value);
uint8_t io_in(uint8_t port);

#endif  // IO_H
