#include "frame.h"
#include "buffers.h"
#include "radio.h"
#include "timers.h"
#include "debug.h"

#ifndef TX_H_
#define TX_H_

void backscatter_frame();
rbuf_t tx_buf;
bool tx_preamble_timeout;

#endif	// end the TX_H_
