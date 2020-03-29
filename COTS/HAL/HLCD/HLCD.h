#ifndef HLCD_H_
#define HLCD_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long uint_64t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK       0
#define NOT_OK   1

uint_8t LCD_Init (void);
uint_8t LCD_WriteData (const uint_8t *data,uint_8t DataLength);
uint_8t LCD_ClearLCD (void);

#endif
