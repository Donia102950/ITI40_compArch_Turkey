/******************************************************************************************/
/*
 Author  : Hammam Mazen
 Date    : 10 March 2020
 Version : V01
 */
/******************************************************************************************/

/************************************INCLUDES**********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_private.h"
#include "RCC_interface.h"
#include "RCC_config.h"

/******************************************************************************************/

StdError RCC_ErrSysClk(myclock Clk, uint_32t Clock_Value) {
	StdError Local_Error;

	if (Clk < 3 && Clock_Value < 72000000)
	{
		Local_Error = OK;
		switch (Clk) {
		case HSI:
			switch (Clock_Value) {
			case HSI_CLK_VALUE:
				RCC->CR |= (1 << RCC_CR_HSI_ON);
				while (GET_BIT(RCC->CR,RCC_CR_HSI_RDY) == 0);
				RCC->CFGR &=SYS_CLOCK_CLEAR_MASK;
				RCC->CFGR |= HSI_SYS_CLOCK_MASK;

				break;
			default:
				Local_Error = NOK;
				break;
			}
			break;

			case HSE:
				if (Clock_Value >= 4000000 && Clock_Value <= 16000000) {
					SET_BIT(RCC->CR, RCC_CR_HSE_ON);
					while (GET_BIT(RCC->CR , RCC_CR_HSE_RDY) == 0);
					switch (HSE_TYPE) {
					case HSE_RC:
						SET_BIT(RCC->CR, RCC_CR_HSE_BYP);
						break;

					case HSE_OSCILLATOR:
						CLR_BIT(RCC->CR, RCC_CR_HSE_BYP);
						break;
					}
					switch (RCC_CSS) {
					case ON:
						RCC->CR |= RCC_CR_CSS_SET_MASK;
						break;

					case OFF:
						RCC->CR &= RCC_CR_CSS_CLEAR_MASK;
						break;
					}
					RCC->CFGR &=SYS_CLOCK_CLEAR_MASK;
					RCC->CFGR |= HSE_SYS_CLOCK_MASK;
				} else {
					Local_Error = NOK;
				}
				break;

			case PLL:
				RCC->CFGR &=SYS_CLOCK_CLEAR_MASK;
				RCC->CFGR |= HSI_SYS_CLOCK_MASK;
				CLR_BIT(RCC->CR,RCC_CR_PLL_ON);

				if (GET_BIT(RCC->CR,RCC_CR_PLL_ON) == 0) {
					switch (PLL_CLK_SOURCE) {
					case PLL_HSE:
						RCC->CFGR |= RCC_CFGR_PLL_SRC_HSE_MASK;
						switch (Clock_Value) {

						case (HSE_CLK_VALUE * 2):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_2_MASK;
						break;
						case (HSE_CLK_VALUE * 3):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_3_MASK;
						break;
						case (HSE_CLK_VALUE * 4):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_4_MASK;
						break;
						case (HSE_CLK_VALUE * 5):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_5_MASK;
						break;
						case (HSE_CLK_VALUE * 6):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_6_MASK;
						break;
						case (HSE_CLK_VALUE * 7):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_7_MASK;
						break;
						case (HSE_CLK_VALUE * 8):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_8_MASK;
						break;
						case (HSE_CLK_VALUE * 9):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
						RCC->CFGR |= PLL_MUL_9_MASK;
						break;
						default:
							Local_Error = NOK;
							break;
						}
						break;

						case PLL_HSE_DIV_2:

							RCC->CFGR |= RCC_CFGR_PLL_SRC_HSE_DIV_2_MASK;
							switch (Clock_Value)
							{

							case (PLL_HSE_DIV_2_Value *2):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_2_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 3):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_3_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 4):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_4_MASK;;
							break;
							case (PLL_HSE_DIV_2_Value * 5):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_5_MASK;;
							break;
							case (PLL_HSE_DIV_2_Value * 6):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_6_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 7):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_7_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 8):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_8_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 9):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_9_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 10):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_10_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 11):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_11_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 12):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_12_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 13):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_13_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 14):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_14_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 15):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_15_MASK;
							break;
							case (PLL_HSE_DIV_2_Value * 16):
											RCC->CFGR &= PLL_MUL_CLEAR_MASK;
							RCC->CFGR |= PLL_MUL_16_MASK;
							break;
							default:
								Local_Error = NOK;
								break;
							}
							break;

							case PLL_HSI:
								RCC->CFGR &= RCC_CFGR_PLL_SRC_HSI_MASK;
								switch (Clock_Value) {

								case (PLL_HSI_VAL*2):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_2_MASK;
								break;
								case (PLL_HSI_VAL*3):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_3_MASK;
								break;
								case (PLL_HSI_VAL*4):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_4_MASK;
								break;
								case (PLL_HSI_VAL*5):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_5_MASK;
								break;
								case (PLL_HSI_VAL*6):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_6_MASK;
								break;
								case (PLL_HSI_VAL*7):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_7_MASK;
								break;
								case (PLL_HSI_VAL*8):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_8_MASK;
								break;
								case (PLL_HSI_VAL*9):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_9_MASK;
								break;
								case (PLL_HSI_VAL*10):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_10_MASK;
								break;
								case (PLL_HSI_VAL*11):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_11_MASK;
								break;
								case (PLL_HSI_VAL*12):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_12_MASK;
								break;
								case (PLL_HSI_VAL*13):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_13_MASK;
								break;
								case (PLL_HSI_VAL*14):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_14_MASK;
								break;
								case (PLL_HSI_VAL*15):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_15_MASK;
								break;
								case (PLL_HSI_VAL*16):
										RCC->CFGR &= PLL_MUL_CLEAR_MASK;
								RCC->CFGR |= PLL_MUL_16_MASK;
								break;
								default:
									Local_Error = NOK;
									break;
								}

								break;
					}
					RCC->CR |= PLL_ON_MASK;
					while (GET_BIT(RCC->CR,RCC_CR_PLL_RDY) == 0);

					RCC->CFGR &=SYS_CLOCK_CLEAR_MASK;
					RCC->CFGR |= PLL_SYS_CLOCK_MASK;
				} else {
					Local_Error = NOK;
				}
				break;
		}
	}
	else
	{
		Local_Error = NOK;
	}
	return Local_Error;
}
/*********************************************************************************************************************/


uint_8t RCC_u8GetClockSource(void) {
	uint_8t SWS_Value = (GET_BIT(RCC->CFGR,SWS1) << 1) + GET_BIT(RCC->CFGR, SWS0);
	return SWS_Value;
}
/*********************************************************************************************************************/


StdError RCC_voidEnPeriClk(uint_8t Peripheral) {
	StdError LocalError;
	uint_8t Bus = Peripheral / 32;
	uint_8t Peripheral_Number = Peripheral % 32;
	if (Peripheral < 86) {
		LocalError = OK;
		switch (Bus) {
		case AHB:
			SET_BIT(RCC->AHBENR, Peripheral_Number);
			return LocalError;
			break;
		case APB1:
			SET_BIT(RCC->APB1ENR, Peripheral_Number);
			return LocalError;
			break;

		case APB2:
			SET_BIT(RCC->APB2ENR, Peripheral_Number);
			return LocalError;
			break;
		default:
			LocalError = NOK;
			return LocalError;
		}
	} else {
		LocalError = NOK;
	}
	return LocalError;
}
/*********************************************************************************************************************/

StdError RCC_voidDisPeriClk(uint_8t Peripheral) {
	StdError LocalError;
	uint_8t Bus = Peripheral / 32;
	uint_8t Peripheral_Number = Peripheral % 32;
	if (Peripheral < 86) {
		LocalError = OK;
		switch (Bus) {
		case AHB:
			CLR_BIT(RCC->AHBENR, Peripheral_Number);
			return LocalError;
			break;
		case APB1:
			CLR_BIT(RCC->APB1ENR, Peripheral_Number);
			return LocalError;
			break;

		case APB2:
			CLR_BIT(RCC->APB2ENR, Peripheral_Number);
			return LocalError;
			break;
		default:
			LocalError = NOK;
			return LocalError;
		}
	} else {
		LocalError = NOK;
	}
	return LocalError;

}
/*********************************************************************************************************************/

uint_32t RCC_u32GetSysClkValue(void) {
	uint_32t PLL_CLK_Value, SysClkValue;
	uint_8t PLLMul_Value = (RCC->CFGR >> 18) & (0x0000000F);
	uint_8t SysClk = RCC_u8GetClockSource();

	switch (SysClk) {
	case HSI:
		SysClkValue = 8000000;
		break;

	case HSE:
		SysClkValue = HSE_CLK_VALUE;
		break;
	case PLL:
		if (GET_BIT(RCC->CFGR,RCC_CFGR_PLL_SRC) == 0) {
			PLL_CLK_Value = PLL_HSI_VAL;
		} else if (GET_BIT(RCC->CFGR,RCC_CFGR_PLL_SRC) == 1) {
			if (GET_BIT(RCC->CFGR,RCC_CFGR_PLL_PRE) == 1)
				PLL_CLK_Value = PLL_HSE_DIV_2_Value;

			else if (GET_BIT(RCC->CFGR,RCC_CFGR_PLL_PRE) == 0)
				PLL_CLK_Value = HSE_CLK_VALUE;
		}
		switch (PLLMul_Value) {
		case 0b0000:
			SysClkValue = 2 * PLL_CLK_Value;
			break;

		case 0b0001:
			SysClkValue = 3 * PLL_CLK_Value;
			break;

		case 0b0010:
			SysClkValue = 4 * PLL_CLK_Value;
			break;

		case 0b0011:
			SysClkValue = 5 * PLL_CLK_Value;
			break;

		case 0b0100:
			SysClkValue = 6 * PLL_CLK_Value;
			break;

		case 0b0101:
			SysClkValue = 7 * PLL_CLK_Value;
			break;

		case 0b0110:
			SysClkValue = 8 * PLL_CLK_Value;
			break;

		case 0b0111:
			SysClkValue = 9 * PLL_CLK_Value;
			break;

		case 0b1000:
			SysClkValue = 10 * PLL_CLK_Value;
			break;

		case 0b1001:
			SysClkValue = 11 * PLL_CLK_Value;
			break;

		case 0b1010:
			SysClkValue = 12 * PLL_CLK_Value;
			break;

		case 0b1011:
			SysClkValue = 13 * PLL_CLK_Value;
			break;

		case 0b1100:
			SysClkValue = 14 * PLL_CLK_Value;
			break;

		case 0b1101:
			SysClkValue = 15 * PLL_CLK_Value;
			break;

		case 0b1110:
			SysClkValue = 16 * PLL_CLK_Value;
			break;
		}

	}
	return SysClkValue;
}
/*********************************************************************************************************************/

uint_32t RCC_u32GetAHBClkValue(void) {
	uint_32t AHB_Clk;
	uint_8t Pre_Val = (RCC->CFGR >> 4) & 0x0000000F;
	uint_32t SysClkValue = RCC_u32GetSysClkValue();

	switch (Pre_Val) {
	case 0b0000:
		AHB_Clk = SysClkValue;
		break;

	case 0b1000:
		AHB_Clk = SysClkValue / 2;
		break;

	case 0b1001:
		AHB_Clk = SysClkValue / 4;
		break;

	case 0b1010:
		AHB_Clk = SysClkValue / 8;
		break;

	case 0b1011:
		AHB_Clk = SysClkValue / 16;
		break;

	case 0b1100:
		AHB_Clk = SysClkValue / 64;
		break;

	case 0b1101:
		AHB_Clk = SysClkValue / 128;
		break;

	case 0b1110:
		AHB_Clk = SysClkValue / 256;
		break;

	case 0b1111:
		AHB_Clk = SysClkValue / 512;
		break;
	}
	return AHB_Clk;
}
/*********************************************************************************************************************/

StdError APB2_Divider(APB_Pre Prescaler) {
	StdError LocalError;
	if (Prescaler <= 16) {
		LocalError = OK;
		switch (Prescaler) {
		case 0:
			RCC->CFGR =	((RCC->CFGR & APB2_CLEAR_MASK) | APB2_NO_PRESCALER_MASK);
			break;
		case 2:
			RCC->CFGR = ((RCC->CFGR & APB2_CLEAR_MASK) | APB2_PRESCALER_2_MASK);
			break;
		case 4:
			RCC->CFGR = ((RCC->CFGR & APB2_CLEAR_MASK) | APB2_PRESCALER_2_MASK);
			break;
		case 8:
			RCC->CFGR = ((RCC->CFGR & APB2_CLEAR_MASK) | APB2_PRESCALER_2_MASK);
			break;
		case 16:
			RCC->CFGR = ((RCC->CFGR & APB2_CLEAR_MASK) | APB2_PRESCALER_2_MASK);
			break;
		default:
			LocalError = NOK;
			break;
		}
	} else {
		LocalError = NOK;
	}
	return LocalError;
}
/*********************************************************************************************************************/

StdError APB1_Divider(APB_Pre Prescaler) {
	StdError LocalError;
	if (Prescaler <= 16) {
		LocalError = OK;
		switch (Prescaler) {
		case 0:
			RCC->CFGR =
					((RCC->CFGR & APB1_CLEAR_MASK) | APB1_NO_PRESCALER_MASK);
			break;
		case 2:
			RCC->CFGR = ((RCC->CFGR & APB1_CLEAR_MASK) | APB1_PRESCALER_2_MASK);
			break;
		case 4:
			RCC->CFGR = ((RCC->CFGR & APB1_CLEAR_MASK) | APB1_PRESCALER_4_MASK);
			break;
		case 8:
			RCC->CFGR = ((RCC->CFGR & APB1_CLEAR_MASK) | APB1_PRESCALER_8_MASK);
			break;
		case 16:
			RCC->CFGR =	((RCC->CFGR & APB1_CLEAR_MASK) | APB1_PRESCALER_16_MASK);
			break;
		default:
			LocalError = NOK;
			break;
		}
	} else {
		LocalError = NOK;
	}
	return LocalError;
}
/*********************************************************************************************************************/

StdError AHB_Divider(AHB_Pre Prescaler) {
	StdError LocalError;
	if (Prescaler <= 512) {
		LocalError = OK;
		switch (Prescaler) {
		case 0:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_NO_PRESCALER_MASK);
			break;

		case 2:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_2_MASK);
			break;

		case 4:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_4_MASK);
			break;

		case 8:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_8_MASK);
			break;

		case 16:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_16_MASK);
			break;

		case 64:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_64_MASK);
			break;

		case 128:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_128_MASK);
			break;

		case 256:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_256_MASK);
			break;

		case 512:
			RCC->CFGR = ((RCC->CFGR & AHB_CLEAR_MASK) | AHB_PRESCALER_512_MASK);
			break;
		default:
			LocalError = NOK;
			break;
		}
	} else {
		LocalError = NOK;
	}
	return LocalError;
}

