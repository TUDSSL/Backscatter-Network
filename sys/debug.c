/*
 * debug.c
 *
 *  Created on: 22 Jun 2018
 *      Author: Amjad
 */

#include "debug.h"

/**
 * @description initialize all the debugging pins
 ----------------------------------------------------------------------------*/
void debug_pins_init()
{
    P1DIR |= BIT2 | BIT3 | BIT4| BIT7;
    P2DIR |= BIT5 | BIT6;
    P3DIR |= BIT0 | BIT5 | BIT6;
    P4DIR |= BIT2;
}

/**
 * @description raise port 1 pint 2
 ----------------------------------------------------------------------------*/
void set_p1_2()
{
    P1OUT |= BIT2;
}

/**
 * @description clear port 1 pint 2
 ----------------------------------------------------------------------------*/
void clear_p1_2()
{
    P1OUT &= ~BIT2;
}

/**
 * @description raise port 1 pint 3
 ----------------------------------------------------------------------------*/
void set_p1_3()
{
    P1OUT |= BIT3;
}

/**
 * @description clear port 1 pint 3
 ----------------------------------------------------------------------------*/
void clear_p1_3()
{
    P1OUT &= ~BIT3;
}

/**
 * @description raise port 1 pint 4
 ----------------------------------------------------------------------------*/
void set_p1_4()
{
    P1OUT |= BIT4;
}

/**
 * @description clear port 1 pint 4
 ----------------------------------------------------------------------------*/
void clear_p1_4()
{
    P1OUT &= ~BIT4;
}

/**
 * @description raise port 1 pint 7
 ----------------------------------------------------------------------------*/
void set_p1_7()
{
    P1OUT |= BIT7;
}

/**
 * @description clear port 1 pint 7
 ----------------------------------------------------------------------------*/
void clear_p1_7()
{
    P1OUT &= ~BIT7;
}

/**
 * @description clear port 2 pint 5
 ----------------------------------------------------------------------------*/
void set_p2_5()
{
    P2OUT &= ~BIT5;
}

/**
 * @description clear port 2 pint 5
 ----------------------------------------------------------------------------*/
void clear_p2_5()
{
    P2OUT &= ~BIT5;
}

/**
 * @description clear port 2 pint 6
 ----------------------------------------------------------------------------*/
void set_p2_6()
{
    P2OUT &= ~BIT6;
}

/**
 * @description clear port 2 pint 6
 ----------------------------------------------------------------------------*/
void clear_p2_6()
{
    P2OUT &= ~BIT6;
}

/**
 * @description raise port 3 pint 0
 ----------------------------------------------------------------------------*/
void set_p3_0()
{
    P3OUT |= BIT0;
}

/**
 * @description clear port 3 pint 0
 ----------------------------------------------------------------------------*/
void clear_p3_0()
{
    P3OUT &= ~BIT0;
}

/**
 * @description raise port 3 pint 5
 ----------------------------------------------------------------------------*/
void set_p3_5()
{
    P3OUT |= BIT5;
}

/**
 * @description clear port 3 pint 5
 ----------------------------------------------------------------------------*/
void clear_p3_5()
{
    P3OUT &= ~BIT5;
}

/**
 * @description raise port 3 pint 6
 ----------------------------------------------------------------------------*/
void set_p3_6()
{
    P3OUT |= BIT6;
}

/**
 * @description clear port 3 pint 6
 ----------------------------------------------------------------------------*/
void clear_p3_6()
{
    P3OUT &= ~BIT6;
}

/**
 * @description raise port 4 pint 2
 ----------------------------------------------------------------------------*/
void set_p4_2()
{
    P4OUT |= BIT2;
}

/**
 * @description clear port 4 pint 2
 ----------------------------------------------------------------------------*/
void clear_p4_2()
{
    P4OUT &= ~BIT2;
}

/**
 * @description initialize all the leds
 ----------------------------------------------------------------------------*/
void leds_init()
{
    red_led_init();
    green_led_init();
}

/**
 * @description initialize the red led
 ----------------------------------------------------------------------------*/
void red_led_init()
{
    P4DIR |= BIT6;
}

/**
 * @description initialize the green led
 ----------------------------------------------------------------------------*/
void green_led_init()
{
    P1DIR |= BIT0;
}

/**
 * @description blink red led
 * @param   cycles: number of loops for the delay
 ----------------------------------------------------------------------------*/
void red_led_blink(uint32_t cycles)
{
    volatile uint32_t cycles_cntr = 0;
    P4OUT |= BIT6;    // set the LED pin
    while(cycles_cntr != cycles)
    {
        cycles_cntr++;
    }
    P4OUT &=~BIT6;    // CLear the LED pin
}

/**
 * @description blink green led
 * @param   cycles: number of loops for the delay
 ----------------------------------------------------------------------------*/
void green_led_blink(uint32_t cycles)
{
    volatile uint32_t cycles_cntr = 0;
    P1OUT |= BIT0;    // set the LED pin
    while(cycles_cntr != cycles)
    {
        cycles_cntr++;
    }
    P1OUT &=~BIT0;    // CLear the LED pin
}

