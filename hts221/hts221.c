/*
 * hts221.c
 *
 *  Created on: Nov 14, 2022
 *      Author: jakub
 */


#include "hts221.h"

uint8_t addres_hts221 = HTS221_DEVICE_ADDRESS;

uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_hts221, 0));
						//  (uint8_t* buffer, uint8_t length, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}


void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_hts221, 0);
				//  (uint8_t data, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}


void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_hts221, 0);
				// (uint8_t* buffer, uint8_t length, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}

void hts221_get_temp(float* temp_result)
{

}


uint8_t hts221_init(void)
{

}
