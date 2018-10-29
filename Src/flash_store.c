/*
 * ----------------------------------------------------------------------------------
 * @file  		: flash_store.c
 * @brief 		: Flash reading/writing  library
 *
 * ----------------------------------------------------------------------------------
 *	 Copyright (c) 2016 Dmitry Skulkin <dmitry.skulkin@gmail.com>					*
 *																					*
 *	Permission is hereby granted, free of charge, to any person obtaining a copy	*
 *	of this software and associated documentation files (the "Software"), to deal	*
 *	in the Software without restriction, including without limitation the rights	*
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell		*
 *	copies of the Software, and to permit persons to whom the Software is			*
 *	furnished to do so, subject to the following conditions:						*
 *																					*
 *	The above copyright notice and this permission notice shall be included in all	*
 *	copies or substantial portions of the Software.									*
 *																					*
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR		*
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		*
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE		*
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER			*
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	*
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	*
 *	SOFTWARE.																		*
 * ----------------------------------------------------------------------------------
 * */

#include <flash_store.h>
#include <..\common_types\common_structs.h>
#include <periph_init.h>


extern struct pin_conf pins[USEDPINS];
//extern struct axis_conf axises[AXISES];
//extern uint8_t POV_config;
//volatile extern uint8_t USB_Product_String_Unique[10];
//volatile extern uint8_t USB_Serial_Number_Unique[13];
//volatile extern struct rot_conf Single_rotaries[USEDPINS];
volatile extern struct total_config_ config;




uint16_t * get_lastpage_addr(uint16_t * flash_size_reg_addr) {
	uint16_t flash_size;

	flash_size = *flash_size_reg_addr;

	return (uint16_t *)(FLASH_BASE + (flash_size-1)*1024);

}


void get_config(void) {
	uint16_t * curradr;

	curradr = get_lastpage_addr((uint16_t *)FLASHSIZEREG);

	for (uint8_t i=0; i<sizeof(config)/BUFFSIZE;i++){
		memcpy((&(config.packet_id1)+(BUFFSIZE*i)), curradr, BUFFSIZE);
		curradr += 32;
	}
}

void erase_flash(void) {
	 /* Authorize the FPEC Access */
	  FLASH->KEYR = FLASH_KEY1;
	  FLASH->KEYR = FLASH_KEY2;

	  /* Clear 2 page */
	  FLASH->CR |= FLASH_CR_PER; /* Page erase */
	  FLASH->AR = (uint32_t)get_lastpage_addr((uint16_t *)FLASHSIZEREG);
	  FLASH->CR|= FLASH_CR_STRT; /* Start erase */
	  while ((FLASH->SR & FLASH_SR_BSY) != 0 ) /* Wait end of erase */
	    ;
	  FLASH->CR &= ~FLASH_CR_PER; /* Page erase end */
	  FLASH->CR |= FLASH_CR_LOCK; /* Lock the flash back */
}

void write_flash(void) {
  uint16_t * currflashaddr;
  uint16_t * currstructaddr;

  /* Authorize the FPEC Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;


  currflashaddr = get_lastpage_addr((uint16_t *)FLASHSIZEREG);
  currstructaddr = (uint16_t *)&(config.packet_id1);

  FLASH->CR |= FLASH_CR_PG; /* Programm the flash */


  for (uint16_t i=0; i<sizeof(config)/2; ++i) {
	  while ((FLASH->SR & FLASH_SR_BSY) != 0 );
	  *currflashaddr++ = *currstructaddr++;
  }

  FLASH->CR &= ~FLASH_CR_PG; /* Reset the flag back !!!! */
  FLASH->CR |= FLASH_CR_LOCK; /* Lock the flash back */
}
