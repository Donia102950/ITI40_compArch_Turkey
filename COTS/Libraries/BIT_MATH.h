/*******************************************************************************************************************************************************/
/*Author: Donia Mohamed Mahmoud*/
/*Version: V1.0*/
/*NAME: BIT_MATH operations */
/*******************************************************************************************************************************************************/

#define SET_BIT(VAR,BIT_NO)         (VAR|=(1<<BIT_NO))
#define CLR_BIT(VAR,BIT_NO)         (VAR&=(~(1<<BIT_NO)))
#define TOGGLE_BIT(VAR,BIT_NO)      (VAR^=(1<<BIT_NO))
#define GET_BIT(VAR,BIT_NO)         (((VAR>>BIT_NO)&0x01))
