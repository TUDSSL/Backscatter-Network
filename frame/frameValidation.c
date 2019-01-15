/*
 * frameValidation.c
 *
 *  @Authors: Amjad Yousef Majid, Michel Jansen
 *  @date   : 27/May/2018
 */

#include <stdbool.h>
#include "frameValidation.h"

// this buffer specify the size of the network
#ifdef LINEAR_BUF
uint16_t crc_linear_buf[100] = {0}
#endif


/* frameValidation module private variables*/
static bool frame_validation_flag = true;
uint8_t frameRx[FRAME_LENGTH];

/* frameValidation module private functions prototypes */
uint8_t get_frame_sender_id(uint8_t* frame);
uint8_t get_frame_receiver_id(uint8_t* frame);
uint8_t get_frame_type(uint8_t* frame);
uint16_t get_frame_crc(uint8_t* frame);
uint16_t get_buffered_crc(uint8_t *frame);
void update_buffered_crc(uint8_t *frame);
bool update_ttl(uint8_t* frame);
bool check_ttl(uint8_t* frame);
void *check_crc_state();
void *save_payload_state();

/**
 * @description     return the sender id from a frame data structure
 * @param           frame: a pointer to a frame data structure
 ----------------------------------------------------------------------------*/
uint8_t get_frame_sender_id(uint8_t *frame)
{
    return frame[SENDER_ID_IDX];
}

/**
 * @description     return the receiver id from a frame data structure
 * @param           frame: a pointer to a frame data structure
 ----------------------------------------------------------------------------*/
uint8_t get_frame_receiver_id(uint8_t *frame)
{
    return frame[RECEIVER_ID_IDX];
}

/**
 * @description     return the frame type from a frame data structure
 * @param           frame: a pointer to a frame data structure
 ----------------------------------------------------------------------------*/
uint8_t get_frame_type(uint8_t *frame)
{
    return frame[FRAME_TYPE_IDX];
}

/**
 * @description     return the CRC of a frame data structure
 * @param           frame: a pointer to a frame data structure
 ----------------------------------------------------------------------------*/
uint16_t debug_crc;
uint16_t get_frame_crc(uint8_t *frame)
{
    debug_crc = ( ((uint16_t) frame[CRC_IDX]) << 8 )  | frame[CRC_IDX + 1];
    return debug_crc;
}

#ifdef LINEAR_BUF
/**
 * @description     return the CRC of crc_buf data structure
 * @param           frame: a pointer to a frame data structure
 ----------------------------------------------------------------------------*/
uint16_t get_buffered_crc(uint8_t *frame)
{
    return crc_linear_buf[get_frame_sender_id(frame)];
}


/**
 * @description     update a cell in  crc_buf data structure
 * @param           frame: a pointer to a frame data structure
 ----------------------------------------------------------------------------*/
void update_buffered_crc(uint8_t *frame)
{
    crc_linear_buf[get_frame_sender_id(frame)] = get_frame_crc(frame);
}
#endif

/**
 * @description     reduce the TTL value in a frame
 * @param           frame: a pointer to a frame data structure
 * @return          if TTL is bigger than 0, it returns true, otherwise false
 ----------------------------------------------------------------------------*/
bool update_ttl(uint8_t *frame)
{
    if( check_ttl(frame) )
    {
        frame[TTL_IDX]--;
        return true;
    }
    return false;
}

/**
 * @description     reduce the TTL value in a frame
 * @param           frame: a pointer to a frame data structure
 * @return          if TTL is 0, it returns true, otherwise false
 ----------------------------------------------------------------------------*/
bool check_ttl(uint8_t *frame)
{
    return frame[TTL_IDX] ==0;
}

/**
 * @description     Execute FSM to process frames
 * @param           validation_state: a pointer to a function that represents
 *                  a state of the frame processing FSM. The state machine will
 *                  break when the frame_validation_flag becomes false
 ----------------------------------------------------------------------------*/
void frame_validation(func_ptr validation_state)
{
    while( frame_validation_flag == true )
    {
        validation_state = (func_ptr)(*validation_state)();
    }
    frame_validation_flag = true;
}

/**
 * @description     read a frame from the rx_buf, and returns it the
 *                  check_crc_state
 ----------------------------------------------------------------------------*/
void *wait_frame_state()
{
    /* If any frames are waiting, start processing them */
    error_t error = rbuf_read(&frameRx[0], &rx_buf, FRAME_LENGTH);
    if(error == E_SUCCESS){
        return check_crc_state;
    }
    frame_validation_flag = false;
    return wait_frame_state;
}

/**
 * @description     check the crc value of the received frame. If the received
 *                  crc is valid return the save_payload_state, Else returns
 *                  wait_frame_state and set the frame_validation_flag to false
 ----------------------------------------------------------------------------*/

#if DEBUG
    uint16_t checksum;
    uint16_t CRC_Result;
    uint16_t frame_crc;
#endif

void *check_crc_state()
{
#ifndef  DEBUG
    uint16_t
#endif
    checksum =  frame_crc_checksum( &frameRx );

#ifndef  DEBUG
    uint16_t
#endif
    CRC_Result = calCRC(checksum);    // Save results (per CRC-CCITT standard)

#ifndef  DEBUG
    uint16_t
#endif
    frame_crc = get_frame_crc(&frameRx );

    // check the crc and check if the message is new
    if( (CRC_Result == frame_crc) && (!rbuf_crc_search( &crc_buf, frame_crc)) )
    {
        rbuf_write( &crc_buf, (uint8_t *) &frame_crc, 2);
        return save_payload_state;
    }
    else
    {
        frame_validation_flag = false;
        return wait_frame_state;
    }
}

/**
 * @description     ...
 ----------------------------------------------------------------------------*/
void *save_payload_state()
{

#if DEBUG
        set_p1_2();
        clear_p1_2();
#endif
        uint16_t r_id =  get_frame_receiver_id( (uint8_t*) frameRx);

        if(r_id == BROADCAST_ID_BYTE)              // broadcasting
        {
            // * saving
            rbuf_write( &rx_data_buf, &frameRx[PAYLOAD_IDX] , PAYLOAD_LENGTH);
            // * re-transmission
            rbuf_write( &tx_buf, &frameRx[0] , FRAME_LENGTH);
        }
        else if (r_id == get_node_id())         // point-to-point (intended receiver)
        {
            rbuf_write( &rx_data_buf, &frameRx[PAYLOAD_IDX] , PAYLOAD_LENGTH);
            received_frame_correct++;
        }
        else  // point-to-point (relay node)
        {
                rbuf_write( &tx_buf, &frameRx[0] , FRAME_LENGTH);
//                slow_timer_delay( rand() % 100 );    // reduce the transmission rate (random guess)
                forward_frame++;
        }
    frame_validation_flag = false;
    return wait_frame_state;
}




