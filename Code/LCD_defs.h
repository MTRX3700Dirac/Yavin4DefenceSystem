/* 
 * File:   LCD_defs.h
 * Author: Jacob
 *
 * Created on 22 October 2014, 12:01 AM
 */

#define LCD_D0 PORTDbits.RD0        //!LCD data bits
#define LCD_D1 PORTDbits.RD1
#define LCD_D2 PORTDbits.RD2
#define LCD_D3 PORTDbits.RD3
#define LCD_D4 PORTDbits.RD4
#define LCD_D5 PORTDbits.RD5
#define LCD_D6 PORTDbits.RD6
#define LCD_D7 PORTDbits.RD7

#define LCD_D0_DIR TRISDbits.RD0    //!LCD direction for data bits
#define LCD_D1_DIR TRISDbits.RD1
#define LCD_D2_DIR TRISDbits.RD2
#define LCD_D3_DIR TRISDbits.RD3
#define LCD_D4_DIR TRISDbits.RD4
#define LCD_D5_DIR TRISDbits.RD5
#define LCD_D6_DIR TRISDbits.RD6
#define LCD_D7_DIR TRISDbits.RD7

#define LCD_DATA_LINE       PORTD   //!All data bits
#define LCD_DATA_LINE_DIR   TRISD   //!Direction for data bits

//#define LCD_PWR PORTCbits.RC0       //!LCD Power
#define LCD_RS  PORTCbits.RC4      //!LCD register select line
#define LCD_RW  PORTCbits.RC5       //!LCD read/write line
#define LCD_E   PORTAbits.RA4       //!LCD E clock

//#define LCD_PWR_DIR TRISCbits.RC0
#define LCD_RS_DIR  TRISCbits.RC4
#define LCD_RW_DIR  TRISCbits.RC5
#define LCD_E_DIR   TRISAbits.RA4

#define LCD_INS     0               //! instruction
#define LCD_DATA    1               //! data
#define LCD_WRITE   0               //! write
#define LCD_READ    1               //! read
#define LCD_CLKLOW  0               //! clock low
#define LCD_CLKHGH  1               //! clock high
#define LCD_OFF     0               //! power off
#define LCD_ON      1               //! power on

#define LCD_INPUT       0xFF        //! macro for complete register input
#define LCD_OUTPUT      0x00        //! macro for complete register output
#define LCD_PIN_INPUT   1           //! single pin input
#define LCD_PIN_OUTPUT  0           //! single pin output

#define DISPCLR         0x01
#define RTNHOME         0x02
#define SETENTRYMODE    0x04
#define ID_CURSL        0x00
#define ID_CURSR        0x02
#define SH_DISPNSHIFT   0x00
#define SH_DISPSHIFT    0x01
#define DISPOPT         0x08
#define D_DISPOFF       0x00
#define D_DISPON        0x04
#define C_CURSOFF        0x00
#define C_CURSON       0x02
#define B_BLINKOFF      0x00
#define B_BLINKON       0x01
#define DISPSHIFTCURS   0x10
#define SC_CURSMOVE     0x00
#define SC_DISPMOVE     0x08
#define RL_LFTSHFT      0x00
#define RL_RGTSHFT      0x04
#define SETDISPFXN      0x20
#define DL_4BIT         0x00
#define DL_8BIT         0x10
#define N_1LINE         0x00
#define N_2LINE         0x08
#define F_5X7DOT        0x00
#define F_5X10DOT       0x04
#define SETCGRAMADD     0x40
#define SETDDRAMADD     0x80

#define BF_READY 0x00
//#define BF_BUSY 0x80
#define BF_BUSY 1

#define LINE1 0x00
#define LINE2 0x40

#define LINESTART 0x00
#define LINEEND 0x0F
