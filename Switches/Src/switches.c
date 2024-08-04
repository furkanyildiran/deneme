#include "switches.h"

Switch_State_t read_clock_pin(void);
Switch_State_t read_data_pin(void);
Switch_State_t read_button_pin(void);

uint8_t arr[2] = {0};
uint8_t complate_flag = 0, order = 0;
volatile uint8_t counter = 0;

void Switches_init(void){
	arr[0] = arr[1] = 0;
	complate_flag = 0;
	order = 0;
	counter = 0;
}

Switch_State_t read_clock_pin(void){
	return (Switch_State_t)HAL_GPIO_ReadPin(CLOCK_PORT, CLOCK_PIN);
}

Switch_State_t read_data_pin(void){
	return (Switch_State_t)HAL_GPIO_ReadPin(DATA_PORT, DATA_PIN);
}

Switch_State_t read_button_pin(void){
	return (Switch_State_t)HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN);
}

Switch_State_t Switches_getButton(void){
	return read_button_pin();
}

void Switches_calcEncoder(void){
	if (read_clock_pin() && (order == 0)) {
		arr[order++] = (uint8_t)read_data_pin();
		complate_flag = 0;
	}
	else if (!read_clock_pin() && order) {
		arr[order++] = (uint8_t)read_data_pin();
		complate_flag = 1;
	}
	if (complate_flag && (order == 2)) {
		order = 0;
		complate_flag = 0;
		if ((arr[0] == 1) && (arr[1] == 0)) {
			counter ++;
		}
		else if ((arr[0] == 0) && (arr[1] == 1)) {
			counter--;
		}
	}
}

uint8_t Switches_getCounter(void){
	return (uint8_t)counter;
}
