#ifndef __ENCODER_H__
#define __ENCODER_H__

#ifdef __cplusplus
extern "C"{
#endif

#define _ST_DEVICES		0

#ifdef _ST_DEVICES
#include "main.h"
#endif

#define BUTTON_PIN		BUTTON_Pin
#define CLOCK_PIN		CLOCK_Pin
#define DATA_PIN		DATA_Pin

#define BUTTON_PORT		BUTTON_GPIO_Port
#define CLOCK_PORT		CLOCK_GPIO_Port
#define DATA_PORT	 	DATA_GPIO_Port

typedef enum{
	STATE_ON,
	STATE_OFF
}Switch_State_t;

void Switches_init(void);
uint8_t Switches_getCounter(void);
void Switches_setCounter(uint8_t counter_val);
Switch_State_t Switches_getButton(void);
void Switches_calcEncoder(void);


#ifdef __cplusplus
}
#endif

#endif //!__ENCODER_H__
