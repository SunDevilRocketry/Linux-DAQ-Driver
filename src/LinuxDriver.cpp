/*******************************************************************************
*
* FILE: 
*       LinuxDriver.cpp
*
* DESCRIPTION: 
*       Contains base driver member methods.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <iostream>

/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "LinuxDriver.hpp"

/*------------------------------------------------------------------------------
Procedures
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		LinuxDriver::LinuxDriver                                               *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Constructor for the driver base class.                                 *
*                                                                              *
*******************************************************************************/
LinuxDriver::LinuxDriver
    (
    void
    )
{
// THIS METHOD IS A STUB. IT WILL DO NOTHING.

} /* LinuxDriver::LinuxDriver */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		LinuxDriver::~LinuxDriver                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Destructor for the driver base class.                                  *
*                                                                              *
*******************************************************************************/
LinuxDriver::~LinuxDriver
    (
    void
    )
{
// THIS METHOD IS A STUB. IT WILL DO NOTHING.

} /* LinuxDriver::LinuxDriver */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		LinuxDriver::ping                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Test method for the driver base class.                                 *
*                                                                              *
*******************************************************************************/
void LinuxDriver::ping
    (
    void
    )
{
std::cout << "Pong!\n";

} /* LinuxDriver::LinuxDriver */