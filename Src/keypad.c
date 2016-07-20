#include "keypad.h"

uint8_t Keypad_Buttons[NUMROWS][NUMCOLS][3];
/*= {
	{{1,0,0},  {2,0,0},  {3,0,0},  {4,0,0},  {5,0,0},  {6,0,0}},
	{{7,0,0},  {8,0,0},  {9,0,0},  {10,0,0}, {11,0,0}, {12,0,0}},
	{{13,0,0}, {14,0,0}, {15,0,0}, {16,0,0}, {17,0,0}, {18,0,0}},
	{{19,0,0}, {20,0,0}, {21,0,0}, {22,0,0}, {23,0,0}, {24,0,0}},
	{{25,0,0}, {26,0,0}, {27,0,0}, {28,0,0}, {29,0,0}, {30,0,0}},
	{{31,0,0}, {32,0,0}, {33,0,0}, {34,0,0}, {35,0,0}, {36,0,0}},
};*/

uint64_t KeyTimes[NUMROWS][NUMCOLS];

/*struct Keypad {
	uint8_t Code;
	uint8_t Row;
	uint8_t Col;
	uint8_t ShortPressed;
	uint8_t LongPressed;
	uint8_t State;
	uint64_t TimePressed;
};

struct Keypad Buttons[] = {
		{0x01, 1, 1, 0, 0, 0, 0},
		{0x02, 2, 1, 0, 0, 0, 0},
		{0x03, 3, 1, 0, 0, 0, 0},
		{0x04, 4, 1, 0, 0, 0, 0},
		{0x05, 5, 1, 0, 0, 0, 0},
		{0x06, 6, 6, 0, 0, 0, 0},
		{0x07, 2, 1, 0, 0, 0, 0},
		{0x08, 2, 2, 0, 0, 0, 0},
		{0x09, 2, 3, 0, 0, 0, 0},
		{0x0A, 2, 4, 0, 0, 0, 0},
		{0x0B, 2, 5, 0, 0, 0, 0},
		{0x0C, 2, 6, 0, 0, 0, 0},
		{0x0D, 3, 1, 0, 0, 0, 0},
		{0x0E, 3, 2, 0, 0, 0, 0},
		{0x0F, 3, 3, 0, 0, 0, 0},
		{0x10, 3, 4, 0, 0, 0, 0},
		{0x11, 3, 5, 0, 0, 0, 0},
		{0x12, 3, 6, 0, 0, 0, 0},
		{0x13, 4, 1, 0, 0, 0, 0},
		{0x14, 4, 2, 0, 0, 0, 0},
		{0x15, 4, 3, 0, 0, 0, 0},
		{0x16, 4, 4, 0, 0, 0, 0},
		{0x17, 4, 5, 0, 0, 0, 0},
		{0x18, 4, 6, 0, 0, 0, 0},
		{0x19, 5, 1, 0, 0, 0, 0},
		{0x1A, 5, 2, 0, 0, 0, 0},
		{0x1B, 5, 3, 0, 0, 0, 0},
		{0x1C, 5, 4, 0, 0, 0, 0},
		{0x1D, 5, 5, 0, 0, 0, 0},
		{0x1E, 5, 6, 0, 0, 0, 0},
		{0x1F, 6, 1, 0, 0, 0, 0},
		{0x20, 6, 2, 0, 0, 0, 0},
		{0x21, 6, 3, 0, 0, 0, 0},
		{0x22, 6, 4, 0, 0, 0, 0},
		{0x23, 6, 5, 0, 0, 0, 0},
		{0x24, 6, 6, 0, 0, 0, 0},
};*/

uint64_t millis;

void CheckButtons(void) {

	extern uint64_t millis;

	millis++;

//	static uint8_t tmp;
//	if (++tmp >5) tmp=0;

//	switch (tmp) {

//	case 0:
	// Check 1st column
	HAL_GPIO_WritePin(COL_1_PORT, COL_1_PIN, GPIO_PIN_SET);
	CheckRows(1);
	HAL_GPIO_WritePin(COL_1_PORT, COL_1_PIN, GPIO_PIN_RESET);
//	break;

//	case 1:
	// Check 2nd column
	HAL_GPIO_WritePin(COL_2_PORT, COL_2_PIN, GPIO_PIN_SET);
	CheckRows(2);
	HAL_GPIO_WritePin(COL_2_PORT, COL_2_PIN, GPIO_PIN_RESET);
//	break;

//	case 2:
	// Check 3rd column
	HAL_GPIO_WritePin(COL_3_PORT, COL_3_PIN, GPIO_PIN_SET);
	CheckRows(3);
	HAL_GPIO_WritePin(COL_3_PORT, COL_3_PIN, GPIO_PIN_RESET);
//	break;

//	case 3:
	// Check 4th column
	HAL_GPIO_WritePin(COL_4_PORT, COL_4_PIN, GPIO_PIN_SET);
	CheckRows(4);
	HAL_GPIO_WritePin(COL_4_PORT, COL_4_PIN, GPIO_PIN_RESET);
//	break;

//	case 4:
	// Check 5th column
	HAL_GPIO_WritePin(COL_5_PORT, COL_5_PIN, GPIO_PIN_SET);
	CheckRows(5);
	HAL_GPIO_WritePin(COL_5_PORT, COL_5_PIN, GPIO_PIN_RESET);
//	break;

//	case 5:
	// Check 6th column
	HAL_GPIO_WritePin(COL_6_PORT, COL_6_PIN, GPIO_PIN_SET);
	CheckRows(6);
	HAL_GPIO_WritePin(COL_6_PORT, COL_6_PIN, GPIO_PIN_RESET);
//	break;
//	}

}

void CheckRows(uint8_t column) {

	GPIO_PinState rowstate;
	uint8_t row;

	row = 1;
	rowstate = HAL_GPIO_ReadPin(ROW_1_PORT, ROW_1_PIN);
	SetButtonState(row,column,rowstate);

	row = 2;
	rowstate = HAL_GPIO_ReadPin(ROW_2_PORT, ROW_2_PIN);
	SetButtonState(row,column,rowstate);

	row = 3;
	rowstate = HAL_GPIO_ReadPin(ROW_3_PORT, ROW_3_PIN);
	SetButtonState(row,column,rowstate);

	row = 4;
	rowstate = HAL_GPIO_ReadPin(ROW_4_PORT, ROW_4_PIN);
	SetButtonState(row,column,rowstate);

	row = 5;
	rowstate = HAL_GPIO_ReadPin(ROW_5_PORT, ROW_5_PIN);
	SetButtonState(row,column,rowstate);

	row = 6;
	rowstate = HAL_GPIO_ReadPin(ROW_6_PORT, ROW_6_PIN);
	//if (rowstate) ITM_SendChar((char)'b');
	SetButtonState(row,column,rowstate);



/*	if (HAL_GPIO_ReadPin(ROW_2_PORT, ROW_2_PIN) == GPIO_PIN_SET) {
			Keypad_Buttons[1][column-1][1] = 1;
		}
	if (HAL_GPIO_ReadPin(ROW_3_PORT, ROW_3_PIN) == GPIO_PIN_SET) {
			Keypad_Buttons[2][column-1][1] = 1;
		}
	if (HAL_GPIO_ReadPin(ROW_4_PORT, ROW_4_PIN) == GPIO_PIN_SET) {
			Keypad_Buttons[3][column-1][1] = 1;
		}
	if (HAL_GPIO_ReadPin(ROW_5_PORT, ROW_5_PIN) == GPIO_PIN_SET) {
			Keypad_Buttons[4][column-1][1] = 1;
		}
	if (HAL_GPIO_ReadPin(ROW_6_PORT, ROW_6_PIN) == GPIO_PIN_SET) {
			Keypad_Buttons[5][column-1][1] = 1;
		}
		*/
}


void SetButtonState(uint8_t row, uint8_t column, GPIO_PinState rowstate) {

	extern uint64_t millis;

	//Keypad_Buttons[row][column][0] - press fact, 1 - pressed, 0 - non pressed
	//Keypad_Buttons[row][column][1] - current state, 1 - high, 0 - low
	//Keypad_Buttons[row][column][2] - previous state, 1 - high, 0 - low

	if (rowstate == GPIO_PIN_SET) {

		if (Keypad_Buttons[row-1][column-1][2] == 0) { //if previous state is 0, then just remember push time
			KeyTimes[row-1][column-1] = millis;
		}

		if ((Keypad_Buttons[row-1][column-1][0] == 1) &&  //if already pressed and longer then presstime
				 (millis - KeyTimes[row-1][column-1]  > PRESSTIME)) { //then reset
			Keypad_Buttons[row-1][column-1][0] = 0;
		//	KeyTimes[row-1][column-1] = millis;
		//	Keypad_Buttons[row-1][column-1][2] = 0;
		}

		if ((Keypad_Buttons[row-1][column-1][2] == 1) &&
				(!Keypad_Buttons[row-1][column-1][1]) && //if previous state is HIGH and time since 1st push is
			 (millis - KeyTimes[row-1][column-1]  > DEBOUNCETIME)) { //more than debounce time then button is
		//		ITM_SendChar((char)'s');							 //pressed
				Keypad_Buttons[row-1][column-1][0] = 1;
				Keypad_Buttons[row-1][column-1][1] = 1;
				KeyTimes[row-1][column-1] = millis;
		}

		Keypad_Buttons[row-1][column-1][2] = 1; //set previous state to 1
	}


	if (rowstate == GPIO_PIN_RESET) {

//		if (Keypad_Buttons[row-1][column-1][0]) {//if pin reset but was pressed then reset
//			Keypad_Buttons[row-1][column-1][1] = 0;
//			Keypad_Buttons[row-1][column-1][0] = 0;
//		}

		Keypad_Buttons[row-1][column-1][1] = 0;
		Keypad_Buttons[row-1][column-1][0] = 0;
		Keypad_Buttons[row-1][column-1][2] = 0; //set previous state to 0
	}
/*
	if (rowstate == GPIO_PIN_RESET) {

		if( Keypad_Buttons[row-1][column-1][2] == 1 ) { //if previous state is 1, then just remember push time
			KeyTimes[row-1][column-1] = millis;
		}

//		ITM_SendChar((char)'F');
		if ((Keypad_Buttons[row-1][column-1][2] == 0) &&  //if previous state is LOW and time since 1st release is
			 (millis - KeyTimes[row-1][column-1]  > DEBOUNCETIME)) { //more than debounce time then button is
		//		ITM_SendChar((char)'s');							 //released
				Keypad_Buttons[row-1][column-1][1] = 0;
				KeyTimes[row-1][column-1] = millis;
		}

		Keypad_Buttons[row-1][column-1][2] = 0; //set previous state to 0
	}
*/

//	if ((rowstate == GPIO_PIN_RESET && Keypad_Buttons[row-1][column-1][1] == 0) ||
//			(rowstate == GPIO_PIN_SET && Keypad_Buttons[row-1][column-1][1] == 1)) {
//		Keypad_Buttons[row-1][column-1][2] = 0;
//	}
}
