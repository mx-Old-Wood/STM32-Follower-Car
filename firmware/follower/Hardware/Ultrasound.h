#ifndef __ULTRASOUND_H__
#define __ULTRASOUND_H__

extern unsigned short int Distance;

void Ultrasound_Init(void);
void Ultrasound_Fired(void);
unsigned short int Ultrasound_Get(void);

#endif
