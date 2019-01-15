/*
 * rx.c
 *
 *  @Authors: Michel Jansen, Amjad Yousef Majid
 *  @date: Sep 27, 2017
 */

#include "rx.h"
 rbuf_t rx_buf;
/* rx module private functions prototype */
void *detect_frame();
void *catch_frame();

/* Variables used for bit decoding in ISR */
func_ptr frame_reception_fsm;
volatile uint8_t bit_counter, byte_counter, decoded_bits;
volatile bool potential_zero;
volatile uint16_t timeCapture ;
volatile uint8_t frame[FRAME_LENGTH] = {0};

/**
 * @description     Configure RX port to use as input for TB0 Timer CCR3.
 *                  Initialize the frame reception FSM.
 ----------------------------------------------------------------------------*/
void rx_init(){
    RX_DIR &= ~RX_PIN;     // configure RX port as an input port
    RX_FUNC_SEL |= RX_PIN; // P1.6 options select (primary module func= TB0 CCR3)

    frame_reception_fsm = (func_ptr) detect_frame;     // Initialize state pointer for
                                                   // frame detection and recording

    /* Initialize variables for RX decoding */
	decoded_bits = 0;
	bit_counter = 0;
	byte_counter = 0;
	potential_zero = false;
}

/**
 * @description     Enable interrupts on the RX pin.
 ----------------------------------------------------------------------------*/
void start_capture(){
    TB0CCTL3 =  CM_3    // Capture both rising and falling edge,
              | CCIS_1  // Use CCI3B = P1.6,
              | SCS     // Synchronous capture,
              | CAP     // Enable capture mode,
              | CCIE;   // Enable capture interrupt
    TBCCR0 = 0xFFFF;
}

/**
 * @description     Disnable interrupts on the RX pin.
 ----------------------------------------------------------------------------*/
void stop_capture(){
    TB0CCTL3 &= ~CCIE; // Stop capture interrupts
}

/**
 * @description     detect a preamble byte and set the channel to busy
 *                  detect frame delimiter byte and hand in controls to
 *                  catch_frame
 ----------------------------------------------------------------------------*/
void *detect_frame(){
	if(decoded_bits == PREAMBLE_BYTE){
		 preamble_detected = true;
	}

	if(decoded_bits == START_DELIMITER_BYTE){
		channel_busy = true;
		bit_counter = 0;
		frame[byte_counter] = decoded_bits;
		byte_counter++;
		decoded_bits = 0;
		return catch_frame;
	}
	return detect_frame;
}

/**
 * @description     receive a frame and hand in controls to detect_frame again
 ----------------------------------------------------------------------------*/
void *catch_frame(){
	if(bit_counter == 8){
		bit_counter = 0;
		frame[byte_counter] = decoded_bits;
		byte_counter++;
		decoded_bits = 0;
	}
	if(byte_counter == FRAME_LENGTH){
        stop_capture();     //disable reception
		byte_counter = 0;
		rbuf_write(&rx_buf, (uint8_t *)&frame, FRAME_LENGTH);
		received_frame++;
		set_p1_4();
		clear_p1_4();
//		green_led_blink(1000);
		start_capture();
		return detect_frame;
	}
	return catch_frame;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_B1_VECTOR))) Timer0_B1_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(TB0IV, TB0IV_TBIFG)) {
        case TB0IV_NONE:   break;               // No interrupt
        case TB0IV_TBCCR1: break;               // CCR1 not used
        case TB0IV_TBCCR2: break;               // CCR2 not used
        case TB0IV_TBCCR3:
        /** Decode bits algorithm */

            /* Save captured timer value and reset timer */
            TB0CTL &= ~MC__UP;          // stop the timer
            timeCapture = TB0CCR3;      // read its value
            TB0CTL |= MC__UP;           // set it back to the up mode
			TB0CTL |= TBCLR;            // reset it

			/* Check if time corresponds to a valid zero (= BIT_LEN_SMCLK/2) */
			if( timeCapture >= (BIT_LEN_SMCLK >> 1) - TIMER_JITTER_LOW && timeCapture < (BIT_LEN_SMCLK - (BIT_LEN_SMCLK >> 2)) ){
				if(potential_zero == false){
					potential_zero = true;
				} else {
					potential_zero = false;
					decoded_bits = (decoded_bits <<1);
					bit_counter++;
				}
			/* Check if time corresponds to a valid one (= BIT_LEN_SMCLK) */
			} else if( timeCapture >= (BIT_LEN_SMCLK - (BIT_LEN_SMCLK >> 2)) && timeCapture <= BIT_LEN_SMCLK + TIMER_JITTER_HIGH ){
				potential_zero = false;
				decoded_bits = (decoded_bits << 1) +1;
				bit_counter++;
			} else {
				potential_zero = false;
				decoded_bits = 0;
				bit_counter = 0;
			}

			/* Detection and recording of frames */
			frame_reception_fsm = (func_ptr)(*frame_reception_fsm)();
            break;
        case TB0IV_TBCCR4: break;               // CCR4 not used
        case TB0IV_TBCCR5: break;               // CCR5 not used
        case TB0IV_TBCCR6: break;               // CCR6 not used
        case TB0IV_TBIFG:                       // overflow
          break;
        default: break;
    }
}
