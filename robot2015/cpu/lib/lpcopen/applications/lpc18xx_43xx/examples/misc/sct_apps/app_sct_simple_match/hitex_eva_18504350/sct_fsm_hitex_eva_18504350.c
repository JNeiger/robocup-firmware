
/* Generated by fzmparser version 1.14 --- DO NOT EDIT! */

/* Uses following resources: */
/* [8 events, 5+1 states, 0 inputs, 5 outputs, 2 match regs, 0 capture regs] */

#include "sct_fsm.h"


void sct_fsm_init (void)
{

/* MATCH/CAPTURE registers */
LPC_SCT->REGMODE_L = 0x0000;         /* L: 1x MATCH, 0x CAPTURE, 15 unused */
LPC_SCT->REGMODE_H = 0x0000;             /* H: 1x MATCH, 0x CAPTURE, 15 unused */
LPC_SCT->MATCH_L[0] = togglePeriodValue;
LPC_SCT->MATCHREL_L[0] = togglePeriodValue;
LPC_SCT->MATCH_H[0] = jumpPeriodValue;
LPC_SCT->MATCHREL_H[0] = jumpPeriodValue;

/* OUTPUT registers */
LPC_SCT->OUT[6].SET = 0x00000080;        /* JUMP_SIGNAL */
LPC_SCT->OUT[6].CLR = 0x0000000C;
LPC_SCT->OUT[2].SET = 0x00000049;        /* CTOUT0 */
LPC_SCT->OUT[2].CLR = 0x00000041;
LPC_SCT->OUT[3].SET = 0x00000029;        /* CTOUT1 */
LPC_SCT->OUT[3].CLR = 0x00000021;
LPC_SCT->OUT[4].SET = 0x0000000B;        /* CTOUT2 */
LPC_SCT->OUT[4].CLR = 0x00000003;
LPC_SCT->OUT[5].SET = 0x0000001D;        /* CTOUT3 */
LPC_SCT->OUT[5].CLR = 0x00000011;
  /* Unused outputs must not be affected by any event */
LPC_SCT->OUT[0].SET = 0;
LPC_SCT->OUT[0].CLR = 0;
LPC_SCT->OUT[1].SET = 0;
LPC_SCT->OUT[1].CLR = 0;
LPC_SCT->OUT[7].SET = 0;
LPC_SCT->OUT[7].CLR = 0;
LPC_SCT->OUT[8].SET = 0;
LPC_SCT->OUT[8].CLR = 0;
LPC_SCT->OUT[9].SET = 0;
LPC_SCT->OUT[9].CLR = 0;
LPC_SCT->OUT[10].SET = 0;
LPC_SCT->OUT[10].CLR = 0;
LPC_SCT->OUT[11].SET = 0;
LPC_SCT->OUT[11].CLR = 0;
LPC_SCT->OUT[12].SET = 0;
LPC_SCT->OUT[12].CLR = 0;
LPC_SCT->OUT[13].SET = 0;
LPC_SCT->OUT[13].CLR = 0;
LPC_SCT->OUT[14].SET = 0;
LPC_SCT->OUT[14].CLR = 0;
LPC_SCT->OUT[15].SET = 0;
LPC_SCT->OUT[15].CLR = 0;
LPC_SCT->OUTPUT = (LPC_SCT->OUTPUT & ~0x00000040) | 0x0000003C;

/* Conflict resolution register */
LPC_SCT->RES = (LPC_SCT->RES & ~0x00000FF0) | 0x00000FF0;

/* EVENT registers */
LPC_SCT->EVENT[0].CTRL = 0x000FD000;     /* L: "event_1" --> state L_ENTRY */
LPC_SCT->EVENT[0].STATE = 0x80000000;
LPC_SCT->EVENT[1].CTRL = 0x00015000;     /* L: "event_7" --> state CTOUT2_toggle */
LPC_SCT->EVENT[1].STATE = 0x00000004;
LPC_SCT->EVENT[2].CTRL = 0x000FE5A0;     /* L: "event_10" --> state L_ENTRY */
LPC_SCT->EVENT[2].STATE = 0x00000008;
LPC_SCT->EVENT[3].CTRL = 0x0000A5A0;     /* L: "event_4" --> state +1 */
LPC_SCT->EVENT[3].STATE = 0x80000007;
LPC_SCT->EVENT[4].CTRL = 0x0001D000;     /* L: "event_9" --> state CTOUT3_toggle */
LPC_SCT->EVENT[4].STATE = 0x00000008;
LPC_SCT->EVENT[5].CTRL = 0x0000D000;     /* L: "event_5" --> state CTOUT1_toggle */
LPC_SCT->EVENT[5].STATE = 0x00000002;
LPC_SCT->EVENT[6].CTRL = 0x00005000;     /* L: "event_3" --> state CTOUT0_toggle */
LPC_SCT->EVENT[6].STATE = 0x00000001;
LPC_SCT->EVENT[7].CTRL = 0x00005010;     /* H: "event_0" --> state H_ENTRY */
LPC_SCT->EVENT[7].STATE = 0x00000001;
  /* Unused events must not have any effect */
LPC_SCT->EVENT[8].STATE = 0;
LPC_SCT->EVENT[9].STATE = 0;
LPC_SCT->EVENT[10].STATE = 0;
LPC_SCT->EVENT[11].STATE = 0;
LPC_SCT->EVENT[12].STATE = 0;
LPC_SCT->EVENT[13].STATE = 0;
LPC_SCT->EVENT[14].STATE = 0;
LPC_SCT->EVENT[15].STATE = 0;

/* STATE registers */
LPC_SCT->STATE_L = 31;
LPC_SCT->STATE_H = 0;

/* state names assignment: */
  /* State L 2: CTOUT2_toggle */
  /* State L31: L_ENTRY */
  /* State L 0: CTOUT0_toggle */
  /* State L 3: CTOUT3_toggle */
  /* State L 1: CTOUT1_toggle */
  /* State H 0: H_ENTRY */

/* CORE registers */
LPC_SCT->START_L = 0x0000;
LPC_SCT->STOP_L =  0x0000;
LPC_SCT->HALT_L =  0x0000;
LPC_SCT->LIMIT_L = 0x00F3;
LPC_SCT->START_H = 0x0000;
LPC_SCT->STOP_H =  0x0000;
LPC_SCT->HALT_H =  0x0000;
LPC_SCT->LIMIT_H = 0x0080;
LPC_SCT->EVEN =    0x00000000;
LPC_SCT->DMA0REQUEST = 0x00000000;
LPC_SCT->DMA1REQUEST = 0x00000000;

}
