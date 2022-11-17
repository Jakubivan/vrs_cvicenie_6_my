/*
 * lps25hb.h
 *
 *  Created on: Nov 17, 2022
 *      Author: jakub
 */

#ifndef LPS22HB_H_
#define LPS22HB_H_

#include "main.h"
#include "i2c.h"
#include <math.h>


#define 	LPS22HB_DEVICE_ADDRESS1				0xB9 	//adresa1 read SLAVE
#define 	LPS22HB_DEVICE_ADDRESS2				0xBB 	//adresa2 read SLAVE

#define 	LPS22HB_WHO_AM_I_VALUE				0xB1
#define 	LPS22HB_WHO_AM_I_ADDRESS			0x0F

#define 	LPS22HB_ADDRESS_CTRL1				0x10	// kontrolny register, konfiguracia slave zariadenia


#define 	LPS22HB_ADDRESS_PRESS_OUT_XL		0x28 // prvy register
#define 	LPS22HB_ADDRESS_PRESS_OUT_L			0x29 // druhy register
#define 	LPS22HB_ADDRESS_PRESS_OUT_H			0x2A // treti register

#define 	LPS22HB_ADDRESS_TEMP_OUT_L			0x2B // prvy register
#define 	LPS22HB_ADDRESS_TEMP_OUT_H			0x2C // druhy register

uint8_t lps22hb_init(void);
void lps22hb_get_temp(float* lps25hb_temp);
void lps22hb_get_press(float* press_out);
void lps22hb_get_rel_height(float* rel_height);
void lps22hb_get_abs_height(float* abs_height);
uint8_t lps22hb_read_byte(uint8_t reg_addr);
void lps22hb_write_byte(uint8_t reg_addr, uint8_t value);




#endif /* LPS22HB_H_ */
