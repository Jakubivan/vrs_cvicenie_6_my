/*
 * lsm6ds0.c
 *
 *  Created on: 17. 11. 2019
 *      Author: Stancoj
 */

#include "lsm6dsl.h"

uint8_t addres = LSM6DSL_DEVICE_ADDRESS_0;

uint8_t lsm6dsl_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres, 0));
						//  (uint8_t* buffer, uint8_t length, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}


void lsm6dsl_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres, 0);
				//  (uint8_t data, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}


void lsm6dsl_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres, 0);
				// (uint8_t* buffer, uint8_t length, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}

void lsm6dsl_get_acc(float* x, float* y, float* z)
{
	uint8_t data[6];
	int16_t xx, yy, zz;

	lsm6dsl_readArray(data, LSM6DSL_ADDRESS_ACCX, 6);

	xx = ((uint16_t)data[1]) << 8 | data[0];
	yy = ((uint16_t)data[3]) << 8 | data[2];
	zz = ((uint16_t)data[5]) << 8 | data[4];

	*x = (xx >> 4) / 1000.0f;
	*y = (yy >> 4) / 1000.0f;
	*z = (zz >> 4) / 1000.0f;
}

void lsm6dsl_get_gyro(float* roll, float* pitch, float* yaw)
{
	uint8_t data[6];
	int16_t xx, yy, zz;

	lsm6dsl_readArray(data, LSM6DSL_ADDRESS_GYROX, 6);

	xx = ((uint16_t)data[1]) << 8 | data[0];
	yy = ((uint16_t)data[3]) << 8 | data[2];
	zz = ((uint16_t)data[5]) << 8 | data[4];

	*roll = (xx >> 4) / 1000.0f;
	*pitch = (yy >> 4) / 1000.0f;
	*yaw = (zz >> 4) / 1000.0f;
}


uint8_t lsm6dsl_init(void)
{
	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = lsm6dsl_read_byte(LSM6DSL_WHO_AM_I_ADDRESS);

	if(val == LSM6DSL_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres = LSM6DSL_DEVICE_ADDRESS_1;
		val = lsm6dsl_read_byte(LSM6DSL_WHO_AM_I_ADDRESS);
		if(val == LSM6DSL_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
		}
	}

	//acc device config
	uint8_t ctrl1 = lsm6dsl_read_byte(LSM6DSL_ADDRESS_CTRL1);
	ctrl1 &= ~0xFC;
	ctrl1 |= 0x70;
	lsm6dsl_write_byte(LSM6DSL_ADDRESS_CTRL1, ctrl1);

	//gyro device config
	uint8_t ctrl2 = lsm6dsl_read_byte(LSM6DSL_ADDRESS_CTRL1);
	ctrl2 &= 0x70;
	lsm6dsl_write_byte(LSM6DSL_ADDRESS_CTRL2, ctrl2);
	return status;
}