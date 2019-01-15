/*
 * timers.h
 *
 *  Created on: Sep 27, 2017
 *      Author: Michel, Amjad
 */


#include <stdint.h>
#include <stdbool.h>
#include <msp430fr5969.h>
#include "peripherals.h"

#ifndef PHY_TIMERS_H_
#define PHY_TIMERS_H_

/*******************************************************************************
 * Timer functions
 ******************************************************************************/
/* Timers overview:
 * TA0: (Available)
 * TA1: ACLK - Continuous
 *          CCR0: MAC: For RX/TX timeout
 *          CCR1: (Available)
 *          CCR2: Used by slow_timer_delay()
 * TA2: SMCLK - Continuous
 *          CCR0: (Available)
 *          CCR1: Used by fast_timer_delay()
 * TA3: (Available)
 * TB0: SMCLK - Up
 *          CCR0: (Available)
 *          CCR1: (Available)
 *          CCR2: (Available)
 *          CCR3: PHY: Used for Capturing RX events
 *          CCR4: (Available)
 *          CCR5: (Available)
 *          CCR6: (Available)
 */

volatile bool * mac_timeout;
bool rx_timeout;

void slow_timer_delay(uint16_t ticks);
void fast_timer_delay(uint16_t ticks);
void mac_down_cntr(uint16_t ticks, bool * timeout_ptr);

#endif /* PHY_TIMERS_H_ */
