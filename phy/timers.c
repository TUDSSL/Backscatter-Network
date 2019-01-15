/*
 * timers.c
 *
 * @authors:  Michel Jansen, Amjad Yousef Majid
 * @date   : 9/Jul/2018
 */


#include "timers.h"

/* timers module private function prototypes */
static uint16_t read_TA1();

/**
 * @description read TimerA1, without stopping it, using majority vote technique
 *----------------------------------------------------------------------------*/
static uint16_t read_TA1()
{
    uint16_t t1,t2;
    do{
        t1 = TA1R;
        t2 = TA1R;
    }while(t1 != t2);
    return t1;
}

/**
 * @description This function using TimerA1 to control a flag (mac_timeout)
 * @param       ticks: number of ACLK cycles
-----------------------------------------------------------------------------*/
void mac_down_cntr(uint16_t ticks, bool * timeout_ptr)
{
    *timeout_ptr = false;
    mac_timeout = timeout_ptr;
    TA1CCR0 = read_TA1() + ticks;
    TA1CCTL0 = CCIE;     // Enable Interrupts on Comparator register
}

// INT_Timer1_A0 handles interrupts from TA1CCR0, dedicated interrupt
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) Timer1_A0_ISR (void)
{
    *mac_timeout = true;
    TA1CCTL0 = 0x00;
}

/**
 * @description This function provide a delay service using TimerA1 and
                 capture/compare channel 2. It also puts the MCU into Low power
                 mode 0
 * @param       ticks: the length of the delay in ACLK cycles
-----------------------------------------------------------------------------*/
void slow_timer_delay(uint16_t ticks)
{
    TA1CCR2 = read_TA1() + ticks;       // Set compare value
    TA1CTL &= ~TAIFG;                   // Clear interrupt flag
    TA1CCTL2 = CCIE;                    // Enable Register comparator interrupt
    __bis_SR_register(LPM0_bits | GIE); // Put MCU to low-power operation mode 0
                                        // and wait for timer interrupt.
}

/**
* @description  This interrupt handler handles interrupts from:
*               TA1CCR1
*               TA1CCR2
*               TA1R (TAIFG)
*
* Note: INT_Timer1_A0 handles interrupts from TA1CCR0, dedicated interrupt
----------------------------------------------------------------------------*/
void __attribute__ ((interrupt(TIMER1_A1_VECTOR))) Timer1_A1_ISR (void)
{
    switch(__even_in_range(TA1IV, TA1IV_TAIFG)) {
        case TA1IV_NONE:   break;               // No interrupt
        case TA1IV_TACCR1:                      // CCR1 routine
            break;
        case TA1IV_TACCR2:                      // CCR2 routine (slow_timer_delay handler)
            TA1CCTL2 = 0x00;                    // Reset comparator settings
            TA1CTL &= ~TAIFG;                   // Clear Interrupt Flag
            __bic_SR_register_on_exit(LPM0_bits);
            break;
        case TA1IV_TAIFG:                       // overflow
            TA1CTL &= ~TAIFG;
            break;
        default: break;
    }
}


/**
 * @description This function provide a delay service using TimerA2 and
                 capture/compare channel 1. It also puts the MCU into Low power
                 mode 0
 * @param        ticks: the length of the delay in SMCLK cycles
-----------------------------------------------------------------------------*/
void fast_timer_delay(uint16_t ticks)
{
    TA2CTL &=~MC__CONTINUOUS;           // stop the TimerA2 (to read its value)
    TA2CCR1 = TA2R + ticks;             // Set compare value
    TA2CCTL1 = CCIE;                    // Enable Register comparator interrupt
    TA2CTL &= ~TAIFG;                   // Clear interrupt flag
    TA2CTL |= MC__CONTINUOUS;           // resume the timer
    __bis_SR_register(LPM0_bits | GIE); // Put MCU to low-power operation mode 0
                                        // and wait for timer interrupt.
}

/**
* @description  This interrupt handler handles interrupts from:
*               TA2CCR1
*               TA2CCR2
*               TA2R (TAIFG)
*
* Note: INT_Timer2_A0 handles interrupts from TA2CCR0, dedicated interrupt
----------------------------------------------------------------------------*/
void __attribute__ ((interrupt(TIMER2_A1_VECTOR))) Timer2_A1_ISR (void)
{
    switch(__even_in_range(TA2IV, TA2IV_TAIFG)) {
        case TA2IV_NONE:   break;               // No interrupt
        case TA2IV_TACCR1:                      // CCR1 routine (fast_timer_delay handler)
            TA2CTL &= ~TAIFG;
            TA2CCTL1 = 0x00;                    // Reset comparator settings
            __bic_SR_register_on_exit(LPM0_bits);  // #define LPM0_bits (CPUOFF)
            break;
        case TA2IV_TAIFG:                       // overflow
            TA2CTL &= ~TAIFG;
            break;
        default: break;
    }
}

