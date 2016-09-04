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

struct pin_conf {
		uint8_t pin_type;
		uint32_t * conf_reg_addr;
		uint32_t * bsrr_reg_addr;
		uint32_t * idr_reg_addr;
		uint8_t pin_number;
	};



extern struct pin_conf pins[USEDPINS];


uint16_t * get_lastpage_addr(uint16_t * flash_size_reg_addr) {
	uint16_t flash_size;

	flash_size = *flash_size_reg_addr;

	return (uint16_t *)(FLASH_BASE + (flash_size-1)*1024);

}


void get_config(void) {
	uint16_t * curradr;

	curradr = get_lastpage_addr((uint16_t *)FLASHSIZEREG);

	for (uint8_t i=0;i<USEDPINS;i++) {
		pins[i].pin_type = (uint8_t)*curradr;
		curradr++;
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
	  while ((FLASH->SR & FLASH_SR_BSY) != 0 ) /* Wait end of eraze */
	    ;
	  FLASH->CR &= ~FLASH_CR_PER; /* Page erase end */
	  FLASH->CR |= FLASH_CR_LOCK; /* Lock the flash back */
}

void write_flash(void) {
  uint16_t * curradr;

  /* Authorize the FPEC Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;


  curradr = get_lastpage_addr((uint16_t *)FLASHSIZEREG);

  FLASH->CR |= FLASH_CR_PG; /* Programm the flash */

  for (uint8_t i=0;i<USEDPINS;i++) {
    *curradr = pins[i].pin_type;
     while ((FLASH->SR & FLASH_SR_BSY) != 0 )
      ;
     curradr++;
   }


  FLASH->CR &= ~FLASH_CR_PG; /* Reset the flag back !!!! */
  FLASH->CR |= FLASH_CR_LOCK; /* Lock the flash back */
}
