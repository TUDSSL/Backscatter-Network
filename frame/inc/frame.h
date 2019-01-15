#include <stdint.h>
#include <stdbool.h>
#include "buffers.h"
#include "peripherals.h"

#ifndef FRAME_H_
#define FRAME_H_

rbuf_t crc_buf;

/*---------------------------------------------------
 * Frame structure (11b):
 * - Preamble               Time-based
 * - StartFrameDelimiter    1b
 * - SenderID               1b
 * - ReceiverID             1b
 * - MessageType            1b
 * - MessageID              1b
 * - Payload                4b
 * - CRC                    2b
 ---------------------------------------------------*/
/* Define positions of frame components */
#define START_DELIMITER_IDX         0
#define SENDER_ID_IDX               1
#define RECEIVER_ID_IDX             2
#define FRAME_TYPE_IDX              3
#define TTL_IDX                     4
#define PAYLOAD_IDX                 5
#define CRC_IDX                     FRAME_LENGTH - CRC_LENGTH

/* Definition of bytes */
#define PREAMBLE_BYTE           0xBB
#define START_DELIMITER_BYTE    0xAA
#define BROADCAST_ID_BYTE       255

/* Length in bytes */
#define PAYLOAD_LENGTH          4
#define CRC_LENGTH              2
#define PREAMBLE_LENGTH         60 // Preamble length is only used in PER_TX_MODE or PER_RX_MODE
#define FRAME_LENGTH            11

/* Message types */
#define DATA_FRAME              0       // Data message
#define ACK_FRAME               1       // Acknowledgment message

void set_frame_type(uint8_t frame_type_val);
void set_frame_receiver_id(uint8_t id);
void set_frame_sender_id(uint8_t id);
void set_ttl(uint8_t ttl_val);
uint16_t frame_crc_checksum( uint8_t * frameBxIn );
void update_frame_crc(uint8_t * frameBxIn, uint16_t crc);
void create_frame(uint8_t *payloadPtr, rbuf_t * buf);

#endif /* FRAME_FRAMEBUILDER_H_ */
