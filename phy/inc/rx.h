/*
 * rx.h
 *
 *  Created on: Sep 27, 2017
 *      Author: michel
 */

#include "frame.h"
#include "buffers.h"
#include "radio.h"
#include "timers.h"

#ifndef PHY_RX_H_
#define PHY_RX_H_

/* Initialize receiver */
void rx_init();

/* Enable or disable interrupt capability of receiver */
void start_capture();
void stop_capture();

extern rbuf_t rx_buf;

#endif /* PHY_RX_H_ */
