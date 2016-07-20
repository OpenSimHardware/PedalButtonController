/*
 * rotary.c
 *
 *  Created on: Jul 4, 2016
 *      Author: John
 */
#include "rotary.h"


/*struct rotariesdef {
  uint8_t ccwCode;
  uint8_t cwCode;
  volatile uint8_t state;
};

struct rotariesdef rotaries[NUMROTARIES] = {
  {37,38,0},
  {39,40,0},
  {41,42,0},
  {43,44,0},
  {45,46,0},
  {47,48,0},
  {49,50,0},
  {51,52,0},
  {53,54,0},
  {55,56,0},
  {57,58,0},
};*/

//
//Encoders code from Ben Buxton
//More info: http://www.buxtronix.net/2011/10/rotary-encoders-done-properly.html
//

#define DIR_CCW 0x10
#define DIR_CW 0x20

#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT

const uint8_t ttable[7][4] = {
		{0x0,		0x5,	0x2,	0x0},
		{DIR_CW,	0x1,	0x1,	0x1},
		{0x0,		0x2,	0x2,	0x3},
		{0x0,		0x1,	0x3,	0x3},
		{0x0,		0x4,	0x6,	0x4},
		{0x0,		0x5,	0x5,	0x4},
		{DIR_CCW,	0x6,	0x6,	0x6},
};


volatile struct rots RotaryStore[NUMROTARIES];
volatile extern uint64_t millis;

/*
const uint8_t ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
*/

/* Read input pins and process for events. Call this either from a
 * loop or an interrupt (eg pin change or timer).
 *
 * Returns 0 on no event, otherwise 0x80 or 0x40 depending on the direction.
 */
uint8_t rotary_process(uint8_t _i) {

	GPIO_PinState rowstateA, rowstateB;
	uint8_t pinstate;

	rowstateA = HAL_GPIO_ReadPin(ROTARY_A_PORT, ROTARY_A_PIN);
	rowstateB = HAL_GPIO_ReadPin(ROTARY_B_PORT, ROTARY_B_PIN);

   pinstate = (uint8_t)(rowstateA << 1) | rowstateB;

   RotaryStore[_i].state = ttable[RotaryStore[_i].state & 0xf][pinstate];
  return (RotaryStore[_i].state & 0x30);
}


void CheckRotaries(void){
	uint8_t res;

	//Check 1st Rotary
	HAL_GPIO_WritePin(ROTARY_1_PORT, ROTARY_1_PIN, GPIO_PIN_SET);
	res = rotary_process(0);
	if (res == DIR_CW) {RotaryStore[0].pressed = 1; RotaryStore[0].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[0].pressed = 2; RotaryStore[0].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_1_PORT, ROTARY_1_PIN, GPIO_PIN_RESET);

	//Check 2nd Rotary
	HAL_GPIO_WritePin(ROTARY_2_PORT, ROTARY_2_PIN, GPIO_PIN_SET);
	res = rotary_process(1);
	if (res == DIR_CW) {RotaryStore[1].pressed = 1; RotaryStore[1].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[1].pressed = 2; RotaryStore[1].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_2_PORT, ROTARY_2_PIN, GPIO_PIN_RESET);

	//Check 3rd Rotary
	HAL_GPIO_WritePin(ROTARY_3_PORT, ROTARY_3_PIN, GPIO_PIN_SET);
	res = rotary_process(2);
	if (res == DIR_CW) {RotaryStore[2].pressed = 1; RotaryStore[2].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[2].pressed = 2; RotaryStore[2].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_3_PORT, ROTARY_3_PIN, GPIO_PIN_RESET);

	//Check 4th Rotary
	HAL_GPIO_WritePin(ROTARY_4_PORT, ROTARY_4_PIN, GPIO_PIN_SET);
	res = rotary_process(3);
	if (res == DIR_CW) {RotaryStore[3].pressed = 1; RotaryStore[3].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[3].pressed = 2; RotaryStore[3].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_4_PORT, ROTARY_4_PIN, GPIO_PIN_RESET);

	//Check 5th Rotary
	HAL_GPIO_WritePin(ROTARY_5_PORT, ROTARY_5_PIN, GPIO_PIN_SET);
	res = rotary_process(4);
	if (res == DIR_CW) {RotaryStore[4].pressed = 1; RotaryStore[4].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[4].pressed = 2; RotaryStore[4].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_5_PORT, ROTARY_5_PIN, GPIO_PIN_RESET);

	//Check 6th Rotary
	HAL_GPIO_WritePin(ROTARY_6_PORT, ROTARY_6_PIN, GPIO_PIN_SET);
	res = rotary_process(5);
	if (res == DIR_CW) {RotaryStore[5].pressed = 1; RotaryStore[5].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[5].pressed = 2; RotaryStore[5].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_6_PORT, ROTARY_6_PIN, GPIO_PIN_RESET);

	//Check 7th Rotary
	HAL_GPIO_WritePin(ROTARY_7_PORT, ROTARY_7_PIN, GPIO_PIN_SET);
	res = rotary_process(6);
	if (res == DIR_CW) {RotaryStore[6].pressed = 1; RotaryStore[6].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[6].pressed = 2; RotaryStore[6].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_7_PORT, ROTARY_7_PIN, GPIO_PIN_RESET);

	//Check 8th Rotary
	HAL_GPIO_WritePin(ROTARY_8_PORT, ROTARY_8_PIN, GPIO_PIN_SET);
	res = rotary_process(7);
	if (res == DIR_CW) {RotaryStore[7].pressed = 1; RotaryStore[7].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[7].pressed = 2; RotaryStore[7].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_8_PORT, ROTARY_8_PIN, GPIO_PIN_RESET);

	//Check 9th Rotary
	HAL_GPIO_WritePin(ROTARY_9_PORT, ROTARY_9_PIN, GPIO_PIN_SET);
	res = rotary_process(8);
	if (res == DIR_CW) {RotaryStore[8].pressed = 1; RotaryStore[8].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[8].pressed = 2; RotaryStore[8].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_9_PORT, ROTARY_9_PIN, GPIO_PIN_RESET);

	//Check 10th Rotary
	HAL_GPIO_WritePin(ROTARY_10_PORT, ROTARY_10_PIN, GPIO_PIN_SET);
	res = rotary_process(9);
	if (res == DIR_CW) {RotaryStore[9].pressed = 1; RotaryStore[9].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[9].pressed = 2; RotaryStore[9].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_10_PORT, ROTARY_10_PIN, GPIO_PIN_RESET);

	//Check 11th Rotary
	HAL_GPIO_WritePin(ROTARY_11_PORT, ROTARY_11_PIN, GPIO_PIN_SET);
	res = rotary_process(10);
	if (res == DIR_CW) {RotaryStore[10].pressed = 1; RotaryStore[10].time_pressed=millis;}
	if (res == DIR_CCW) {RotaryStore[10].pressed = 2; RotaryStore[10].time_pressed=millis;}
	HAL_GPIO_WritePin(ROTARY_11_PORT, ROTARY_11_PIN, GPIO_PIN_RESET);


}
