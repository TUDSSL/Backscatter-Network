/*
 * app.c
 *
 * @author: Amjad Yousef Majid
 * @data : 18/May/2018
 */

#include <msp430fr5969.h>
#include <stdlib.h>
#include <time.h>
#include <net.h>
#include "debug.h"


//#define TX_APP

uint16_t transmitted_frame = 25;
uint16_t dummy_debug;
uint16_t tx_cntr = 0;

void init()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    gpio_init();
    clock_init();
    timers_init();
    radio_init();
    _BIS_SR(GIE);

    srand((unsigned) 9 );

#if DEBUG
    leds_init();
    debug_pins_init();
#endif

}
int main(void) {

    init();
    set_p1_7();
    mac_init();
    uint8_t testFrame[] = {0x00, 0x09, 0x91,0x29};
    set_node_id(1);

    while(1)
    {
        mac_fsm(preamble_sampling);

            dummy_debug = rand();
            slow_timer_delay((SLEEP_PERIOD_ACLK) );    // reduce the transmission rate (random guess)


        //TODO transmit with a probability (use rand)
        if( (dummy_debug % 64) == 0  && (tx_cntr < transmitted_frame))
        {
            set_frame_type(0);
            set_frame_receiver_id(8);
            set_frame_sender_id( get_node_id() );
            set_ttl(10);
            testFrame[0]++;
#ifdef TX_APP
            create_frame( &testFrame[0], &tx_buf);
            tx_cntr++;

#if DEBUG
      set_p2_5();
      clear_p2_5();
#endif

#endif
        }
        if(tx_cntr == transmitted_frame)
            red_led_blink(100000);

    }
    return 0;
}






