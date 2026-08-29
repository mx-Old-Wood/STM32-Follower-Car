#ifndef __MODE_H__
#define __MODE_H__

#define DISTANCE_MIN        20
#define DISTANCE_MAX        400
#define DISTANCE_AIM        200
#define BASE_SPEED          40
#define MIN_SPEED           32
#define MAX_SPEED           45
#define OVERTAKE_SPEED      45
#define YIELD_SPEED         35
#define DISTANCE_KP         0.07

extern unsigned short int Dis, Modes, Stop;
extern unsigned char Set1, Set2;

void Display(void);
uint8_t Detection(void);
void Mode(uint8_t Choose, int set1, int set2);

#endif
