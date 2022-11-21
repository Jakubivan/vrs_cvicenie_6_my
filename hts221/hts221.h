/*
 * hts221.h
 *
 *  Created on: Nov 14, 2022
 *      Author: jakub
 */

#ifndef HTS221_H_
#define HTS221_H_

#include "main.h"
#include "i2c.h"


#define 	HTS221_DEVICE_ADDRESS				0xBF 	//adresa read SLAVE

#define 	HTS221_WHO_AM_I_VALUE				0xBC
#define 	HTS221_WHO_AM_I_ADDRESS				0x0F

#define 	HTS221_ADDRESS_CTRL1				0x20	// kontrolny register, konfiguracia slave zariadenia

// temperature
#define 	HTS221_ADDRESS_TEMP_OUT_L			0x2A	// TEMP_OUT_L temperature data lsb
#define 	HTS221_ADDRESS_TEMP_OUT_H			0x2B	// TEMP_OUT_H temperature data MSB

#define 	HTS221_ADDRESS_T0_OUT_L				0x3C	// T0_OUT_L lsb
#define 	HTS221_ADDRESS_T0_OUT_H				0x3D	// T0_OUT_H MSB
#define 	HTS221_ADDRESS_T1_OUT_L				0x3E	// T1_OUT_L lsb
#define 	HTS221_ADDRESS_T1_OUT_H				0x3F	// T1_OUT_H MSB

#define 	HTS221_ADDRESS_T0_degC_x8			0x32	// T0_degC_x8
#define 	HTS221_ADDRESS_T1_degC_x8			0x33	// T1_degC_x8
#define 	HTS221_ADDRESS_T1_T0_msb			0x35	// T1_T0_msb

// humidity
#define 	HTS221_ADDRESS_HUMIDITY_OUT_L		0x28	// HUMIDITY_OUT_L lsb
#define 	HTS221_ADDRESS_HUMIDITY_OUT_H		0x29	// HUMIDITY_OUT_L MSB

#define 	HTS221_ADDRESS_H0_T0_OUT			0x36	// H0_T0_OUT
#define 	HTS221_ADDRESS_H1_T0_OUT			0x3A	// H1_TO_OUT

#define 	HTS221_ADDRESS_H0_rH_x2				0x30	// H0_rH_x2
#define 	HTS221_ADDRESS_H1_rH_x2				0x31	// H1_rH_x2





uint8_t hts221_init(void);
void hts221_get_temp(float* temp_out_deg);
void hts221_get_hum(int* hum_out_deg);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);
void do_linearization();





#endif /* HTS221_H_ */