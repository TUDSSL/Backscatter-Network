/*
 * tx.c
 *
 * @authors: Michel Jansen, Amjad Yousef Majid
 * @date   : 9/Jul/2018
 */

#include "tx.h"

static bool phaseShift = false;

#ifdef DEBUG
uint8_t frameTx[FRAME_LENGTH];
#endif

/* tx module private functions prototypes */
void backscatter(bool phaseShift);
void backscatter_1();
void backscatter_0();
void backscatter_byte(uint8_t byte);
void backscatter_frame_preamble();
void backscatter_frame_helper(uint8_t * frame, bool phaseShift);

/**
 * @description     it toggles the RF switch to backscatter
 * @param           phaseShift indicate with a phase shift is required or not
 ----------------------------------------------------------------------------*/
void backscatter(bool phaseShift)
{
    if(phaseShift)
    {
        RFSW_OUT ^= A0;
        RFSW_OUT |= A1;
    }else{
        RFSW_OUT |= A0;
        RFSW_OUT ^= A1;
    }
}

/**
 * @description this function backscatters a data-1 symbol
 ----------------------------------------------------------------------------*/
void backscatter_1()
{
    backscatter(phaseShift);
    fast_timer_delay( (uint16_t) BIT_LEN_SMCLK);
}

/**
 * @description this function backscatters a data-0 symbol
 ----------------------------------------------------------------------------*/
void backscatter_0()
{
    backscatter(phaseShift);
    fast_timer_delay( (uint16_t) BIT_LEN_SMCLK >> 1);
    backscatter(phaseShift);
    fast_timer_delay( (uint16_t) BIT_LEN_SMCLK >> 1);
}

/**
 * @description this function backscatters a given byte
 * @param       byte: a byte of data to be backscattered
 ----------------------------------------------------------------------------*/
void backscatter_byte(uint8_t byte)
{
	int8_t i;
    for(i = 7; i >= 0; i--){
        if(byte & (0x01<<i)){
            backscatter_1();
        }
        else {
            backscatter_0();
        }
    }
}

/**
 * @description this function backscatters a preamble
 ----------------------------------------------------------------------------*/
void backscatter_frame_preamble()
{
    //if long preamble transmission is required
#if LONG_PREAMBLE_FLAG
    mac_down_cntr(LONG_PREAMBLE_INTERVAL, &tx_preamble_timeout);
    while(!tx_preamble_timeout)
    {
        backscatter_byte(PREAMBLE_BYTE);
    }
#else
    uint8_t i ;
    for(i = 0; i < PREAMBLE_LENGTH; i++){
        backscatter_byte(PREAMBLE_BYTE);
     }
#endif
}

/**
 * @description this function backscatters a given frame, in given phase
 * @param       frame: a pointer to frame data structure
 * @param       phaseShift: phase shift flag
 ----------------------------------------------------------------------------*/
void backscatter_frame_helper(uint8_t * frame, bool phaseShift)
{
    uint8_t i;
  for(i = 0; i < FRAME_LENGTH; i++){
       backscatter_byte( frame[i] );
    }
  backscatter(phaseShift);              // to finish the last bit
}

/**
 * @description this function backscatters a frame twice in two different
 * phases
 ----------------------------------------------------------------------------*/
void backscatter_frame()
{

#if DEBUG
      set_p2_6();
      clear_p2_6();
#endif

#ifndef DEBUG
    uint8_t frameTx[FRAME_LENGTH];
#endif
    rbuf_read(frameTx, &tx_buf, FRAME_LENGTH);  // read the data from tx_buf
                                                // and write it to frameTx
    /* transmission of non-phase shifted frame */
    phaseShift=false;

    backscatter_frame_preamble();
    clear_p4_2();
    set_p4_2();
    backscatter_frame_helper(frameTx, phaseShift);
    fast_timer_delay( (uint16_t) INTERFRAME_TIME);
    receive_state();

#ifdef PHASE_SHIFT
        /* transmission of non-phase shifted frame */
        phaseShift = true;

        backscatter_frame_preamble();
        backscatter_frame_helper(frameTx, phaseShift);
        fast_timer_delay( (uint16_t) INTERFRAME_TIME);
        receive_state();
#endif
}


