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
#define 	LPS25HB_DEVICE_ADDRESS2				0xBB 	//adresa2 read SLAVE

#define 	LPS25HB_WHO_AM_I_VALUE				0xB1
#define 	LPS25HB_WHO_AM_I_ADDRESS			0x0F

#define 	LPS25HB_ADDRESS_CTRL1				0x10	// kontrolny register, konfiguracia slave zariadenia


#define 	LPS25HB_ADDRESS_PRESS_OUT_XL		0x28 // prvy register
#define 	LPS25HB_ADDRESS_PRESS_OUT_L			0x29 // druhy register
#define 	LPS25HB_ADDRESS_PRESS_OUT_H			0x2A // treti register

#define 	LPS25HB_ADDRESS_TEMP_OUT_L			0x2B // prvy register
#define 	LPS25HB_ADDRESS_TEMP_OUT_H			0x2C // druhy register

uint8_t lps25hb_init(void);
void lps25hb_get_temp(float* lps25hb_temp);
void lps25hb_get_press(float* press_out);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);




#endif /* LPS25HB_H_ */
