//GIE                 ENABLE FOR ALL PERIPHERALS
//PIE                 ENABLE FOR EACH PERIPHERAL
//SELECT MODE
//BUILD FUNCTION ISR
//INT0
#include"EXT_INT0.h"


void EX_INT0VidInit(void)
{
	//for global int enable   SREG SET BIT NUM 7
	SET_BIT(SREG,7);
	//FOR int0 enable   GICR
	SET_BIT(GICR,6);
    // FOR MODE MCUCR  ANY CHANG is the best in switches case
    SET_BIT(MCUCR,0);
    CLR_BIT(MCUCR,1);



}


  //LAYERED ARCH RULES
//LIB &SERVICES ANY ONE COULD USE IT ANY WHERE


// MCAL CAN NOT INCLUDE ANY ONE ECEPT LIB & SERVICES
//HAL LIB & SERVICES & MCAL
//APP CAN INCLUDE EVERYTHING
