#ifndef __ENCODER_H__
#define __ENCODER_H__

extern float Encoder_Count1, Encoder_Count2;

void Encoder1_Init(void);
void Encoder2_Init(void);
uint16_t EncoderSpeed1_Get(void);
uint16_t EncoderSpeed2_Get(void);

#endif
