/*
 * lps25hb.c
 *
 *  Created on: Nov 17, 2022
 *      Author: jakub
 */

//#define 	LPS25HB_DEVICE_ADDRESS1				0xB9 	//adresa1 read SLAVE
//#define 	LPS25HB_DEVICE_ADDRESS2				0xBB 	//adresa1 read SLAVE
//
//#define 	LPS25HB_WHO_AM_I_VALUE				0xBD
//#define 	LPS25HB_WHO_AM_I_ADDRESS			0x0F
//
//#define 	LPS25HB_ADDRESS_CTRL1				0x20	// kontrolny register, konfiguracia slave zariadenia
//
//
//#define 	LPS25HB_ADDRESS_PRESS_OUT_XL		0x28 // prvy register
//#define 	LPS25HB_ADDRESS_PRESS_OUT_L			0x29 // druhy register
//#define 	LPS25HB_ADDRESS_PRESS_OUT_H			0x2A // treti register
//
//#define 	LPS25HB_ADDRESS_TEMP_OUT_L			0x2B // prvy register
//#define 	LPS25HB_ADDRESS_TEMP_OUT_H			0x2C // druhy register

#include "lps25hb.h"

uint8_t addres_lsp25hb = LPS25HB_DEVICE_ADDRESS1;
float p0 = 1013.25;
float p_act;
float t_act;
float h0;
float p1;

uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_lsp25hb, 0));
						//  (uint8_t* buffer, uint8_t length, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}


void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_lsp25hb, 0);
				//  (uint8_t data, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}


void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_lsp25hb, 0);
				// (uint8_t* buffer, uint8_t length, uint8_t register_addr, uint8_t slave_addr, uint8_t read_flag)
}

void lps25hb_get_press(float* press_out)
{
	// PRESS_OUT
	uint8_t press_out_array[3];
	int32_t press_tmp;
	press_out_array[0] = lps25hb_read_byte(LPS25HB_ADDRESS_PRESS_OUT_XL);
	press_out_array[1] = lps25hb_read_byte(LPS25HB_ADDRESS_PRESS_OUT_L);
	press_out_array[2] = lps25hb_read_byte(LPS25HB_ADDRESS_PRESS_OUT_H);
	// vratenie hodnoty
	press_tmp = (press_out_array[2] << 16) | (press_out_array[1] << 8) | press_out_array[0];
	*press_out = (float)press_tmp/4096;
}

void lps25hb_get_temp(float* lps25hb_temp)
{
	uint8_t lps25hb_temp_array[2];
	lps25hb_temp_array[0] = lps25hb_read_byte(LPS25HB_ADDRESS_TEMP_OUT_L);
	lps25hb_temp_array[1] = lps25hb_read_byte(LPS25HB_ADDRESS_TEMP_OUT_H);
	*lps25hb_temp = (float)((lps25hb_temp_array[1] << 8) | lps25hb_temp_array[0])/100;
}

void lps25hb_get_rel_height(float* rel_height)
{
	float h_act;
	lps25hb_get_abs_height(&h_act);

	*rel_height = (float)(h_act - h0);
}
void lps25hb_get_abs_height(float* abs_height)
{

	lps25hb_get_press(&p_act);
	lps25hb_get_temp(&t_act);

	*abs_height = (float)( (pow((p0/p_act),(1/5.257)) - 1.0) * (t_act+273.15) )/0.0065;
}

uint8_t lps25hb_init(void)
{
	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRESS);

	if(val == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres_lsp25hb = LPS25HB_DEVICE_ADDRESS2;
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRESS);
		if(val == LPS25HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
		}
	}

	// device config
	uint8_t ctrl1 = lps25hb_read_byte(LPS25HB_ADDRESS_CTRL1);
	ctrl1 &= ~0xFF;
	ctrl1 |=  0x28; //10hz
	lps25hb_write_byte(LPS25HB_ADDRESS_CTRL1, ctrl1);

	// vypocet vysky od mora -> pri inicializacii
	lps25hb_get_abs_height(&h0);

	return status;
}

