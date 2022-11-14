/*
 * lsm6ds0.h
 *
 *  Created on: 17. 11. 2019
 *      Author: Stancoj
 */

#include "main.h"
#include "i2c.h"


#define 	LSM6DSL_DEVICE_ADDRESS_0				0xD5 	//adresa read 1 SLAVE
#define 	LSM6DSL_DEVICE_ADDRESS_1				0xD7 	//adresa read 2 SLAVE

#define 	LSM6DSL_WHO_AM_I_VALUE					0x6A
#define 	LSM6DSL_WHO_AM_I_ADDRESS				0x0F

#define 	LSM6DSL_ADDRESS_CTRL1					0x10	// kontrolny register, konfiguracia slave zariadenia

#define 	LSM6DSL_ADDRESS_ACCX					0x28	//adresa acc X
#define 	LSM6DSL_ADDRESS_ACCY					0x2A	//adresa acc Y
#define 	LSM6DSL_ADDRESS_ACCZ					0x2C	//adresa acc Z

#define 	LSM6DSL_ADDRESS_TEMP_L					0x20	// adresa teplota

uint8_t lsm6dsl_init(void);
void lsm6dsl_get_acc(float* x, float * y, float * z);
uint8_t lsm6dsl_read_byte(uint8_t reg_addr);
void lsm6dsl_write_byte(uint8_t reg_addr, uint8_t value);
