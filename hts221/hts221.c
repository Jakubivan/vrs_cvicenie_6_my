/*
 * hts221.c
 *
 *  Created on: Nov 14, 2022
 *      Author: jakub
 */


#include "hts221.h"

uint8_t addres_hts221 = HTS221_DEVICE_ADDRESS;
float k_hts221;
float q_hts221;

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

void hts221_get_temp(float* temp_out_deg)
{
	// T_OUT
	uint8_t temp_out_array[2];
	uint16_t temp_out;
	temp_out_array[0] = hts221_read_byte(HTS221_ADDRESS_TEMP_OUT_L);
	temp_out_array[1] = hts221_read_byte(HTS221_ADDRESS_TEMP_OUT_H);
	temp_out = (temp_out_array[1] << 8) | temp_out_array[0];

	// vratenie hodnoty
	*temp_out_deg = (k_hts221*temp_out + q_hts221) /8.0; //TODO - vypocet asi OK zapis zly
}

void do_linearization()
{
		// T0_OUT
		uint8_t t0_out_array[2];
		uint16_t t0_out;
		t0_out_array[0] = hts221_read_byte(HTS221_ADDRESS_T0_OUT_L);
		t0_out_array[1] = hts221_read_byte(HTS221_ADDRESS_T0_OUT_H);
		t0_out = (t0_out_array[1] << 8) | t0_out_array[0];

		// T1_OUT
		uint8_t t1_out_array[2];
		uint16_t t1_out;
		t1_out_array[0] = hts221_read_byte(HTS221_ADDRESS_T1_OUT_L);
		t1_out_array[1] = hts221_read_byte(HTS221_ADDRESS_T1_OUT_H);
		t1_out = (t1_out_array[1] << 8) | t1_out_array[0];

		// T0_degC_x8
		uint8_t t0t1_deg_8b = hts221_read_byte(HTS221_ADDRESS_T1_T0_msb);
		uint8_t t0_deg_8b = hts221_read_byte(HTS221_ADDRESS_T0_degC_x8);
		uint8_t t0_deg_2b = t0t1_deg_8b & 0x03; //& 00000011
		uint16_t t0_deg_10b = (t0_deg_2b << 8) | t0_deg_8b;

		// T1_degC_x8
		uint8_t t1_deg_8b = hts221_read_byte(HTS221_ADDRESS_T1_degC_x8);
		uint8_t t1_deg_2b = (t0t1_deg_8b >> 2) & 0x03; //& 00000011
		uint16_t t1_deg_10b = (t1_deg_2b << 8) | t1_deg_8b;

		// vypocet smernice k a posunutia q linearizovanej char.
		k_hts221 = (float)(t1_deg_10b - t0_deg_10b)/(t1_out - t0_out);
		q_hts221 = (float)(t0_deg_10b - k_hts221*t0_out);
}

uint8_t hts221_init(void)
{
	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I_ADDRESS);

	if(val == HTS221_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else
	{
		status = 0;
		return status;
	}

	//hts221 device config
	uint8_t ctrl1hts221 = hts221_read_byte(HTS221_ADDRESS_CTRL1);
	ctrl1hts221 &= 0x85; // 10000101 - PD=1 (on), BDU=1 (not continuously updated), ODR01=01 (1Hz)
	hts221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1hts221);

	// vypocitanie linearizacie char.
	do_linearization();

	return status;
}
