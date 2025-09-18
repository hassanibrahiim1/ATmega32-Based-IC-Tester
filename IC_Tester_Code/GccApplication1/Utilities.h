/*
 * Utilities.h
 *
 * Created: 12/5/2023 9:35:26 PM
 *  Author: Omar Yasser
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_

/***************************************** Macro Section *************************************************/

// BIT_MINPULATION
#define SET_BIT(REG,PIN)    (REG = REG|(1<<PIN))
#define CLR_BIT(REG,PIN)    (REG = REG & (~(1<<PIN)))
#define READ_PIN(REG,PIN)   ((REG>>PIN) & 1)
#define TOGGLE_BIT(REG,PIN) (REG = REG ^ (1<<PIN))
#define TOGGLE_PORT(REG)    (REG = ~REG)



#endif /* UTILITIES_H_ */