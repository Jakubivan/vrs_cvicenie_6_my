/*
 * lps25hb.h
 *
 *  Created on: Nov 17, 2022
 *      Author: jakub
 */

#ifndef LPS25HB_H_
#define LPS25HB_H_

#include "main.h"
#include "i2c.h"


#define 	LPS25HB_DEVICE_ADDRESS1				0xB9 	//adresa1 read SLAVE
#define 	LPS25HB_DEVICE_ADDRESS2				0xBB 	//adresa1 read SLAVE

#define 	LPS25HB_WHO_AM_I_VALUE				0xBD
#define 	LPS25HB_WHO_AM_I_ADDRESS			0x0F

#define 	LPS25HB_ADDRESS_CTRL1				0x20	// kontrolny register, konfiguracia slave zariadenia


#define 	LPS25HB_ADDRESS_PRESS_OUT_XL		0x28 // prvy register
#define 	LPS25HB_ADDRESS_PRESS_OUT_L			0x29 // druhy register
#define 	LPS25HB_ADDRESS_PRESS_OUT_H			0x2A // treti register

#define 	LPS25HB_ADDRESS_TEMP_OUT_L			0x2B // prvy register
#define 	LPS25HB_ADDRESS_TEMP_OUT_H			0x2C // druhy register




#endif /* LPS25HB_H_ */
