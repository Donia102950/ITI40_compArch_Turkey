
#ifndef NVIC_INTERFACE.H

#define NVIC_INTERFACE.H

typedef struct 
{
   unsigned long int ISER[8];                     
   unsigned long int RESERVED0[24];
   unsigned long int ICER[8];                     
   unsigned long int RSERVED1[24];
   unsigned long int ISPR[8];                     
   unsigned long int RESERVED2[24];
   unsigned long int ICPR[8];                     
   unsigned long int RESERVED3[24];
   unsigned long int IABR[8];                     
   unsigned long int RESERVED4[56];
   unsigned char  IP[240];                        
   unsigned long int RESERVED5[644];
   unsigned long int STIR;                           

}NVIC_T;


#define NVIC         	((volatile NVIC_T*)	0xE000E100)
#define SCB				((volatile SCB_T*)	0xE000E008)

#define NO_SUBGROUP_PRIORITIES		0x05FA0300
#define 8_SUBGROUP_PRIORITIES 		0x05FA0400
#define 4_SUBGROUP_PRIORITIES	  	0x05FA0500
#define 2_SUBGROUP_PRIORITIES		0x05FA0600
#define PRIORITIES_NO_GROUP    		0x05FA0700


void NVIC_EnableInterrupt(unsigned char InterNum);
void NVIC_DisableInterrupt(unsigned char InterNum);
void NVIC_setPending(unsigned char InterNum);
void NVIC_ClearPending(unsigned char InterNum);

unsigned char NVIC_GetEnabled(unsigned char InterNum);
unsigned char NVIC_GetPending(unsigned char InterNum);
unsigned char NVIC_GetActive(unsigned char InterNum);

void NVIC_SetPeriorty(unsigned char InterNum,unsigned long int Periorty);
void NVIC_InitPriority(unsigned long int Group);

void Write_ToPRIMASK(unsigned long int priMask);
void Write_ToFAULTMASK(unsigned long int FaultMask);
void Write_ToBASEPRI(unsigned long int Basepri);






#endif