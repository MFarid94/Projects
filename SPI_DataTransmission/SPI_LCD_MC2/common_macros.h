 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Comman_Macros.h
 *
 * Description: Commonly used macros.
 *
 * Author: Mohamed Farid
 *
 *******************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in register */
#define SET_BIT(REG,BIT) (REG |= (1<<BIT) )

/* Clear a certain bit in register */
#define CLEAR_BIT(REG,BIT) (REG &= (~(1<<BIT) ) )

/* Toggle a certain bit in register */
#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT) )

/* Rotate right the register value with specific number of bits, 8-bit mode */
#define ROR(REG,num) (REG = (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of bits, 8-bit mode */
#define ROL(REG,num) (REG = (REG<<num) | (REG>>(8-num)) )

/* Check if a certain bit in a register is set */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a certain bit is a register is cleared */
#define BIT_IS_CLEAR(REG,BIT) ( !( REG & (1<<BIT) ) )

#endif /* COMMON_MACROS_H_ */
