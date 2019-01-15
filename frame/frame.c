/*
 * frame.c
 *
 *  @Authors: Amjad Yousef Majid, Michel Jansen
 *  @date   : 27/May/2018
 */
#include <frame.h>

uint8_t frame_receiver_id = 0;
uint8_t frame_sender_id = 0;
uint8_t frame_ttl = 0;
uint8_t frame_type = DATA_FRAME;
uint8_t frameBx[FRAME_LENGTH] = {0};
/**
 * @description     set the frameBx type
 * @param           frame_type_val: frameBx type value
 ----------------------------------------------------------------------------*/
void set_frame_type(uint8_t frame_type_val)
{
	frame_type = frame_type_val;
}

/**
 * @description     set the frameBx receiver id
 * @param           id: frameBx receiver id
 ----------------------------------------------------------------------------*/
void set_frame_receiver_id(uint8_t id)
{
	frame_receiver_id = id;
}

/**
 * @description     set the frameBx sender id
 * @param           id: frameBx sender id
 ----------------------------------------------------------------------------*/
void set_frame_sender_id(uint8_t id)
{
	frame_sender_id = id;
}

/**
 * @description     set the frameBx TTL value
 * @param           ttl_val: the TTL value
 ----------------------------------------------------------------------------*/
void set_ttl(uint8_t ttl_val)
{
	frame_ttl = ttl_val;
}

uint16_t frame_crc_checksum( uint8_t * frameBxIn )
{
    uint8_t i = 0;
    uint16_t checksum = 0;
        for(i = 0; i < (FRAME_LENGTH - CRC_LENGTH); i++){
        checksum += (*(frameBxIn + i));
    }

    return checksum;
}

/**
 * @description     update the crc value (called after changing anything in
 *                  a received frameBx)
 * @param           frameBx: a pointer to frameBx data structure
 ----------------------------------------------------------------------------*/

void update_frame_crc(uint8_t * frameBxIn, uint16_t crc)
{

    //  frameBx [byte 0| byte 1 ....| high CRC byte: low CRC byte  ]
    frameBxIn[FRAME_LENGTH - CRC_LENGTH] = ((crc >> 8) & 0xff);
    frameBxIn[FRAME_LENGTH - CRC_LENGTH + 1] = (crc & 0xff);
}

/**
 * @description this function creates a frameBx. and saves it into the frameBx
                global variable 
 * @param       payload_ptr: a pointer to the payload
 * @param       buf: a pointer to a buffer to write the created frameBx to
 ----------------------------------------------------------------------------*/
#ifdef DEBUG
    uint16_t crc ;
#endif

void create_frame(uint8_t *payload_ptr, rbuf_t * buf)
{
    uint8_t i;

    /* Prepare frameBx */
    frameBx[START_DELIMITER_IDX]  = START_DELIMITER_BYTE;
    frameBx[SENDER_ID_IDX]        = frame_sender_id;
    frameBx[RECEIVER_ID_IDX]      = frame_receiver_id;
    frameBx[FRAME_TYPE_IDX]       = frame_type;
    frameBx[TTL_IDX]              = frame_ttl;

    /* Copy payload into the frameBx */
    for(i = 0; i < PAYLOAD_LENGTH; i++){
        frameBx[PAYLOAD_IDX + i] = (*(payload_ptr + i));
    }

    uint16_t checksum = frame_crc_checksum(frameBx);
#ifndef DEBUG
    uint16_t 
#endif
    crc = calCRC(checksum);
    update_frame_crc(frameBx, crc);
    rbuf_write(&crc_buf,  (uint8_t *) &crc, 2);

    rbuf_write(buf, &frameBx[0], FRAME_LENGTH);
}

