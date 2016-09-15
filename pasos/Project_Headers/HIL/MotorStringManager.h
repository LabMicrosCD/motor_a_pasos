
/* ! **************
* @file: MotorStringManager.h
* @author(s): Daniela Becerra, Jesús Barroso
*
* @brief (User's Manual)
* This manager controls which bits in a String are
* on or off in order for a stepper motor to start working
*
* You can rotate ClockWise or Counter ClockWise
*
***************** */

#ifndef MOTOR_STRING_H_
#define MOTOR_STRING_H_

/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "types.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/

#define MOTOR_STRING_PORT				B	/* Specify the digital port where the LED string is connected */
#define MOTOR_STRING_PIN_START		0   /* Specify the starting pin on the digital port where teh LED String is connected */

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

/*!*-----------------------------------------------------------------------------------------------
* \name     MotorStringManager_Init
* \brief    Initalizes the GPIO pins used for the Motor String and it sets it to the initial condition
*           which is 0x08
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void MotorStringManager_Init(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     MotorStringManager_RotateClockwise
* \brief    Sets the appropriate sequence for the motor to rotate ClockWise
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void MotorStringManager_RotateClockwise(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     MotorStringManager_RotateCounterClockwise
* \brief    Sets the appropriate sequence for the motor to rotate Counter ClockWise
* \param    void
* \return   void
-------------------------------------------------------------------------------------------------*/
void MotorStringManager_RotateCounterClockwise(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     LedStringManager_RightEndReached
* \brief    Restarts the sequence from the start when the last index is reached
* \param    void.
* \return   void
-------------------------------------------------------------------------------------------------*/
bool MotorStringManager_RightEndReached(void);

/*!*-----------------------------------------------------------------------------------------------
* \name     LedStringManager_RightEndReached
* \brief    Restarts from the end the sequence when the first index is reached
* \param    void.
* \return   void
-------------------------------------------------------------------------------------------------*/
bool MotorStringManager_LeftEndReached(void);

#endif /* MOTOR_STRING_H_ */
