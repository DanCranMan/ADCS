#include <stdio.h>
#include <stdbool.h>

//Sample program for MSP430-5438STK
//Test LCD Display
//Slide on the display the text "www.olimex.com/dev"

//#include "font.h"
#include "msp430f5438.h"


static const unsigned char FontLookup [][5] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00 },  // sp
    { 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0xc4, 0xc8, 0x10, 0x26, 0x46 },   // %
    { 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x50, 0x30, 0x00 },   // ,
    { 0x10, 0x10, 0x10, 0x10, 0x10 },   // -
    { 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x7E, 0x11, 0x11, 0x11, 0x7E },   // A
    { 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x0C, 0x52, 0x52, 0x52, 0x3E },   // g
    { 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x20, 0x40, 0x44, 0x3D, 0x00 },   // j
    { 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x7C, 0x14, 0x14, 0x14, 0x08 },   // p
    { 0x08, 0x14, 0x14, 0x18, 0x7C },   // q
    { 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x0C, 0x50, 0x50, 0x50, 0x3C },   // y
    { 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x08, 0x6C, 0x6A, 0x19, 0x08 },   // { (gramotevichka)
    { 0x30, 0x4E, 0x61, 0x4E, 0x30 }    // | (urche)
};


#define OSC_FREQ 18000000
#define LCD_FREQ  1000000

#define CONTRAST        0x5A
/*
#if   defined  (TLS8204)
#define CONTRAST        0x5A
#elif defined  (PCD8544)
#define CONTRAST        0x7F
#endif
*/
//LCD definitions +
#define SEND_CMD 0
#define SEND_CHR 1
#define LCD_X_RES                  84
#define LCD_Y_RES                  48
#define LCD_START_LINE_ADDR (66-2)
#define MAX                        100
//LCD definitions -

unsigned char text[22] = "Hi Loser", LCDMemory[504], inverse=1;
//unsigned char text[22] = "www.olimex.com/dev    ", LCDMemory[504], inverse=1;
int index=0;

//prototypes
void SPI2_Init(unsigned long freq);
void OBC_Init(void);
void SPI2_Transmit(unsigned char data);
void OBC_Transmit(unsigned char data);
unsigned char SPI2_Receive();
unsigned char OBC_Receive();
void LCD_Init();
void LCD_Send(unsigned char data, unsigned char cd);
void LCD_Clear();
void LCD_Update(unsigned char mode, unsigned char num);
void LCD_Contrast(unsigned char contrast);
void LCD_Clear_Memory();
void LCD_Set_Position(unsigned char x, unsigned int y);

void Delay(unsigned long time)
{
  while (time--);
}

void CLOCK_XT2_Init()
{
    int timeout = 5000;
    P11DIR = P11DIR | 0x02 | 0x04;            //set P11.1 & P11.2 as output
    P11SEL = P11SEL | 0x02 | 0x04;            //set P11.1 & P11.2 as MCLK/SMCLK function
    P5SEL = P5SEL | 0x04 | 0x08;              //set P5.2 & P5.3 as XT2IN/XT2OUT

    UCSCTL6 = UCSCTL6 & (~XT2OFF);            //set XT2OFF=0 (bit8 = 0) --> enable XT2
    UCSCTL3 = UCSCTL3 | 0x20;                 //set SELREF = 010 --> FLL clock source = REFOCLK
    UCSCTL4 = UCSCTL4 | 0x200;                //set SELA = 010 --> ACLK=REFO

    do
    {
      if (!(UCSCTL7 & 0x08)) break;
      UCSCTL7 = UCSCTL7 & ~(0x0F);            // Clear XT2,XT1,DCO fault flags
      SFRIFG1 = SFRIFG1 & ~(0x02);            // Clear fault flags (SFRIFG1.OFIFG = 0)
      timeout--;
    }
    while ((SFRIFG1 & 0x02) && timeout);      // Test oscillator fault flag

    UCSCTL5 = UCSCTL5 | 0x0005;               //MCLK/SMCLK divisor = 32

    UCSCTL4 = UCSCTL4 | 0x55;                 //SMCLK=MCLK=XT2
    UCSCTL4 = ((UCSCTL4 & ~0x100) & ~0x200) & ~0x400;     //ACLK=XT1  (SELA = 0b000)
}



//SPI Functions +

    void SPI2_Init(unsigned long freq)
    {

      //SPI For LCD
      P9SEL = P9SEL | 0x0E;                   //P9.1/P9.2/P9.3 set as alternate function
      P9DIR = P9DIR | 0x0B;                   //P9.0/P9.1/P9.3 set as output
      P9DIR = P9DIR | 0xC0;                   //LCD Reset, LCD data/command bits set as output



      unsigned int prescaler;
      UCB2CTL1 = UCB2CTL1 | 0x01;         //UCSWRST = 1 (reset state enable) LCD


      //set format LCD:
      //set clock polarity and phase (UCCKPH = 0; UCCKPL = 1) --> bit7=0; bit6=1
      //MSB first; bit0 (UCSYNC) = 1; bit3 (master mode) = 1; --> bit5=1; bit4=0; bit3 =3; bit0=1;
      //set mode: 3pin SPI --> bit1=0; bit2=3;
      //UCB2CTL0 = 0b01101001 = 0x69
      UCB2CTL0 = 0x69;





      UCB2CTL1 = UCB2CTL1 | 0x80;                     //clock source - SMCLK

      prescaler = OSC_FREQ / freq;
      UCB2BR0 = prescaler % 256;
      UCB2BR1 = prescaler / 256;

      P9SEL = P9SEL | 0x0E;               //P9.0/P9.1/P9.2/P9.3 set as alternate function
      P9DIR = P9DIR | 0x0B;               //P9.0/P9.1/P9.3 set as output

      UCB2CTL1 = UCB2CTL1 & ~(0x01);       //UCSWRST = 0 (reset state disable)

    }

    void OBC_init(void){

        //SPI pin alternate function
              P10SEL = P10SEL | 0x0E;                   //P10.1/P10.2/P10.3 set as alternate function
              P10DIR = P10DIR | 0x0B;                   //P10.0/P10.1/P10.3 set as output

        UCB3CTL1 = UCB3CTL1 | 0x01;         //UCSWRST = 1 (reset state enable) OBC

              //Set format OBC:
              //set clock polarity and phase bit7-6 = 00
              //MSB First bit5 = 0
              //8 bit data bit4 = 0
              //Set for slave mode bit3 = 0
              //set mode: 3pin SPI --> bit1=0; bit2=0;
              //Synchronous SPi bit0 = 1
              //UCB3CTL0 = 0b00100001
        UCB3CTL0 = 0x21;


        UCB3CTL1 = UCB3CTL1 & ~(0x01);       //UCSWRST = 0 (reset state disable) OBC
    }

    unsigned char SPI2_Receive()
    {
      if (UCB2IFG & 0x01)
        return UCB2RXBUF;
      else
        return 0;
    }

    unsigned char OBC_Receive()
        {
          if (UCB3IFG & 0x01)
            return UCB3RXBUF;
          else
            return 0;
        }

    void OBC_Transmit(unsigned char data)
        {
          while (!(UCB3IFG & 0x02));
            UCB3TXBUF = data;
        }

    void SPI2_Transmit(unsigned char data)
    {
      while (!(UCB2IFG & 0x02));
        UCB2TXBUF = data;
    }

//SPI Functions -

//LCD Functions +

    void LCD_Init()
    {
      P9OUT = P9OUT & 0xBF;         //LCD_RES = 0   //~(1<<6)
      Delay(1000);
      P9OUT = P9OUT | 0x40;         //LCD_RES = 1   //1<<6
      Delay(1000);

      //from Dimitar's PIC source +
        //Send sequence of command +
          LCD_Send(0x21, SEND_CMD);  // LCD Extended Commands.
          //Extended commands +
            LCD_Send(0xC8, SEND_CMD);  // Set Contrast.
            LCD_Send(0x04 | !!(LCD_START_LINE_ADDR&(0x40)), SEND_CMD);      // Set Temp S6 for start line
            LCD_Send(0x40 | (LCD_START_LINE_ADDR & ((0x40)-1)), SEND_CMD);  // Set Temp S[5:0] for start line
            LCD_Send(0x12, SEND_CMD);  // LCD bias mode 1:68.
          //Extended commands -
          LCD_Send(0x20, SEND_CMD);  // LCD Standard Commands, Horizontal addressing mode.
          LCD_Send(0x08, SEND_CMD);  // LCD blank
          LCD_Send(0x0C, SEND_CMD);  // LCD in normal mode.
        //Send sequence of command -
      //from Dimitar's PIC source -

      //Optional commands +
        LCD_Contrast(CONTRAST);       //Increase contrast
        LCD_Clear();              //Clear Screen
        LCD_Set_Position(0, 0);   //0, 0 coordinates of the display
      //Optional Commands -
    }

    void LCD_Send(unsigned char data, unsigned char cd)
    {
      P9OUT = P9OUT & ~(0x01);

      if (cd == SEND_CHR)         //check for sending char/command
        P9OUT = P9OUT | 0x80;     //sending char                    //1<<7
      else
        P9OUT = P9OUT & 0x7F;     //sending command                 //~(1<<7)

      SPI2_Transmit(data);        //transmitting char/command

      P9OUT = P9OUT | 0x01;
    }

    void LCD_Clear_Memory()
    {
      for (index=0; index<504; index++)
        LCDMemory[index] = 0;
      index = 0;
    }

    /*
      mode indicates inverse display:
      (shows black pixels as white and white pixels as black)

      the 1 in binary num indicates which of the lines
      must/must not be inverted
      ex. num = 13 --> 0b001101 --> lines 0, 2, 3 will be inverted
    */
    void LCD_Update(unsigned char mode, unsigned char num)
    {
      char x, y;
      for(y=0; y<48/8; y++)
      {
        LCD_Send(0x80, SEND_CMD);     //x - home
        LCD_Send(0x40|y, SEND_CMD);   //y - next line

        if (((mode==inverse) && !(num & 1<<y)) || ((mode != inverse) && (num & 1<<y)))
          for(x=0; x<84; x++)
            LCD_Send(LCDMemory[y*84+x], SEND_CHR);
        else
          for(x=0; x<84; x++)
            LCD_Send(~LCDMemory[y*84+x], SEND_CHR);
      }
    }

    void LCD_Clear()
    {
      LCD_Clear_Memory();
      LCD_Update(1, 0x00);
    }

    void LCD_Contrast(unsigned char contrast)
    {
        LCD_Send(0x21, SEND_CMD);
        //LCD Extended Commands +
          LCD_Send(0x80 | contrast, SEND_CMD);  // Set LCD Vop (Contrast).
        //LCD Extended Commands -
        LCD_Send(0x20, SEND_CMD);         //LCD Standard Commands, horizontal addressing mode
    }

    void LCD_Set_Position(unsigned char x, unsigned int y)
    {
      //Optional calculations +
        //in case the position is out of the screen:
        //if X > 83 it goes to the next (or more) line.
        //if Y > 5 it return to the 0, 1, 2... line
          y = y + x/84;
          y = y % 6;
          x = x % 84;
      //Optional calculations -
      index = 84*y + x;

      //send cursor to x, y coordinates +
        LCD_Send(0x80 | x, SEND_CMD);
        LCD_Send(0x40 | y, SEND_CMD);
      //send cursor to x, y coordinates -
    }

    void LCD_Write(unsigned char *a, int l)
    {
      unsigned char i;
      while (*a && l)
      {
       l--;
        for (i=0; i<5; i++)
          LCDMemory[index++] = FontLookup[*a-32][i];
        LCDMemory[index++] = 0x00;    //space between signs
        a++;
      }
     //Delay(3000000000);
    }

/*
 * H-Bridge Pins
 *
 * Motor 1
 * 2.0 VCC
 * 2.1 Enable
 * 2.2 Sleep
 *
 * Motor 2
 * 2.4 VCC
 * 2.5 Enable
 * 2.6 Sleep
 *
 * Motor 3
 * 1.0 VCC
 * 1.1 Enable
 * 1.7 Sleep
 */
    void Motor_init(){

           //P2SEL = P2SEL |
           P2DIR = P2DIR | 0x07; //set motor pins at 2.0, 2.1, and 2,2 as outputs
           P2OUT = P2OUT | 0x05; //Turn VCC and sleep always on to supply power to the H-Bridge

           P2DIR = P2DIR | 0x70; //set motor pins at 2.4, 2.5, and 2.6 as outputs
           P2OUT = P2OUT | 0x50; //Turn VCC and sleep always on to supply power to the H-Bridge

           P1DIR = P1DIR | 0x03; //set motor pins at 1.0, and 1.1 as outputs
           P1DIR = P1DIR | 0x80; //set motor pin 1.7 as output
           P1OUT = P1OUT | 0x01; //Turn VCC and sleep always on to supply power to the H-Bridge
           P1OUT = P1OUT | 0x80; //turn sleep on
       }

void Xaxis(unsigned int count, int PWM, int max){

      if(count == PWM){               //Decide if Magnetorquer should be on or off
          P2OUT = P2OUT & 0xFD;       //Turn Enable Off Motor 1
      }

      if(count == max){               //If count has reached the max, then reset
           P2OUT = P2OUT | 0x02;   //Turn Enable on Motor 1

      }
}


void Yaxis(unsigned int count, int PWM, int max){

      if(count == PWM){               //Decide if Magnetorquer should be on or off
          P2OUT = P2OUT & 0xDF;       //Turn Enable Off Motor 2
      }

      if(count == max){               //If count has reached the max, then reset
           P2OUT = P2OUT | 0x20;   //Turn Enable on Motor 2

      }
}

void Zaxis(unsigned int count, int PWM, int max){

      if(count == PWM){               //Decide if Magnetorquer should be on or off
          P1OUT = P1OUT & 0xFD;       //Turn Enable Off Motor 3
      }

      if(count == max){               //If count has reached the max, then reset
           P1OUT = P1OUT | 0x02;      //Turn Enable on Motor 3
      }
}

int main( void )
{
  unsigned char c;

  int rounds = 5;    //The amount of times it should go through pulse width modulation loop before checking B-Dot

  int PWMx = 17;      //initialize the Duty Cycles of all 3 axis'
  int PWMy = 30;
  int PWMz = 50;        //For Demo x=17, y=30, z=50

  unsigned int count = 0;

  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  CLOCK_XT2_Init();
  OBC_init();
  SPI2_Init(LCD_FREQ);
  LCD_Init();
  Motor_init();

  c = text[0];

      text[21] = c;
      LCD_Clear_Memory();
      LCD_Write(text, 14);
      LCD_Update(1, 0);

/*
   P2OUT = P2OUT | 0x02;       //Turn Enable on
   P2OUT = P2OUT | 0x20;     //Turn Enable on Motor 2
   P1OUT = P1OUT | 0x02;      //Turn Enable on Motor 3
*/
  while (1)
  {

          //**************************************************************************************
          //Insert B-Dot Algorithm here to decide the desired Pulse width Modulation for each Axis
          //**************************************************************************************
    int i = 0;
   // while(i < rounds){

      for(count = 0; count <= MAX; count++){

          Xaxis(count, PWMx, MAX);
          Yaxis(count, PWMy, MAX);
          Zaxis(count, PWMz, MAX);

      }
    //}
	/*		This block is meant for demonstration purposes to vary the amount of power sent to the motors going up and down
	if(direction){
              PWMx++;
              PWMy++;
              PWMz++;
          }else{
              PWMx--;
              PWMy--;
              PWMz--;
          }

          if(PWMx >= 40){
              direction = 0;
          }
          if(PWMx <= 0){
              direction = 1;
          }
		  */
  }
}
