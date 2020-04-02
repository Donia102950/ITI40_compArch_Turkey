/* Author : Noran Mamdouh 		*/
/* Date : 20 FEB 2020		 	*/
/* Version : V01 				*/
/****************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

typedef struct 
{
   uint_32t ISER[8];
   uint_32t RESERVED0[24];
   uint_32t ICER[8];
   uint_32t RSERVED1[24];
   uint_32t ISPR[8];
   uint_32t RESERVED2[24];
   uint_32t ICPR[8];
   uint_32t RESERVED3[24];
   uint_32t IABR[8];
   uint_32t RESERVED4[56];
   uint_8t  IPR[240];
   uint_32t RESERVED5[644];
   uint_32t STIR;

}NVIC_T;


#define NVIC         	((volatile NVIC_T*)	0xE000E100)

#define NO_SUBGROUP_PRIORITIES		0x05FA0300
#define SUBGROUP_PRIORITIES_8 		0x05FA0400
#define SUBGROUP_PRIORITIES_4	  	0x05FA0500
#define SUBGROUP_PRIORITIES_2		0x05FA0600
#define PRIORITIES_NO_GROUP    		0x05FA0700


void NVIC_EnableInterrupt(uint_8t InterNum);
void NVIC_DisableInterrupt(uint_8t InterNum);
void NVIC_setPending(uint_8t InterNum);
void NVIC_ClearPending(uint_8t InterNum);

uint_8t NVIC_GetEnabled(uint_8t InterNum);
uint_8t NVIC_GetPending(uint_8t InterNum);
uint_8t NVIC_GetActive(uint_8t InterNum);

void NVIC_SetPeriorty(uint_8t InterNum,uint_32t Periorty);
void NVIC_InitPriority(uint_32t Group);

void Write_ToPRIMASK(uint_32t priMask);
void Write_ToFAULTMASK(uint_32t FaultMask);
void Write_ToBASEPRI(uint_32t Basepri);






#endif
