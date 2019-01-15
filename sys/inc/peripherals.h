/*
 * peripherals.h
 *
 * @author: Amjad Yousef Majid
 * @data  : 21/Jun/2018
 */

#include <msp430fr5969.h>
#include <stdint.h>

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

uint16_t calCRC(uint16_t checksum);
void gpio_init();
void clock_init();
void slow_timer_init();
void fast_timer_init();
void decode_timer_init();
void timers_init();


#endif // End of the PERIPHERALS_H_
