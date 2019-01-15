#include <stdint.h>

#include "debug.h"
#include "buffers.h"
#include "custom_data_type.h"
#include "frame.h"
#include "node.h"
#include "rx.h"
#include "tx.h"

#ifndef MAC_FRAMEVALIDATION_H_
#define MAC_FRAMEVALIDATION_H_

void frame_validation(func_ptr frameValidationState);
void *wait_frame_state();

rbuf_t rx_data_buf;

#endif /* MAC_FRAMEVALIDATION_H_ */
