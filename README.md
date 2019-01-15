# A communication stack for Backscatter Networks
The code has four layers:
1. Sys: Provides utilites to access needed hardware modules (i.e. timers).
2. Phy: Controls the backcatter tranceiver (Harware dependent code [MSP430FR5969]).
3. Mac: The Medium Access Contorl layer.
4. framer: Creates and validates messages.
