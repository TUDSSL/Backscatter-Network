/*
 * debug.h
 *
 * @author: Amjad Yousef Majid
 * @data  : 14/Jun/2018
 */
#include <stdint.h>
#include <msp430fr5969.h>

#define DEBUG 1

#ifndef SYS_INC_DEBUG_H_
#define SYS_INC_DEBUG_H_

void leds_init();
void red_led_init();
void green_led_init();
void red_led_blink(uint32_t cycles);
void green_led_blink(uint32_t cycles);
void  debug_pins_init();
void clear_p3_0();
void set_p3_0();
void clear_p2_6();
void set_p2_6();
void clear_p2_5();
void set_p2_5();
void set_p1_7();
void clear_p1_7();
void clear_p1_4();
void set_p1_4();
void clear_p1_3();
void set_p1_3();
void clear_p1_2();
void set_p1_2();
void set_p3_5();
void clear_p3_5();
void set_p3_6();
void clear_p3_6();
void set_p4_2();
void clear_p4_2();

uint16_t received_frame_correct;
uint16_t received_frame_incorrect;
uint16_t forward_frame;
volatile uint16_t received_frame;


#endif /* SYS_INC_DEBUG_H_ */
