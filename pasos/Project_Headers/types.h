/*! **********************************************************************************************
* 2014  ITESM Campus Guadalajara. Laboratorio de Microcontroladores
*
*
* @file:      types.h
* @author(s): Mauricio Capistr�n Garza Jirash
*
* @brief (User's Manual)
* 	Defines platform-independent datatypes
*
**************************************************************************************************/

#ifndef TYPES_H_
#define TYPES_H_


typedef char 			u8;
typedef signed char 	i8;
typedef char 			bool;
typedef signed short	i16;
typedef unsigned short	u16;
typedef signed long		i32;
typedef unsigned long	u32;

typedef void (*ISR_callback)(void); /*ISR function data type */
typedef void (*pFunc_t)(void);      /* generic function pointer data type */

#endif /* TYPES_H_ */
