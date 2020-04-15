#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <softPwm.h>
#include <stdlib.h>
#define ObstaclePin 2

#define uchar unsigned char

#define LedPinRed    27
#define LedPinGreen  28
#define LedPinBlue   29

int colors[10][3]= {
    {0xff,0x00,0x00}, 
    {0x00,0xff,0x00},
    {0x00,0xff,0x00}, 
    {0x00,0x00,0xff}, 
    {0xff,0xff,0x00}, 
    {0xff,0x00,0xff},
    {0xc0,0xff,0x3e},
    {0x94,0x00,0xd3}, 
    {0x76,0xee,0x00}, 
    {0x00,0xc5,0xcd}
    };

void ledInit(void)
{
	softPwmCreate(LedPinRed,  0, 100);
	softPwmCreate(LedPinGreen,0, 100);
	softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(uchar r_val, uchar g_val, uchar b_val)
{
	softPwmWrite(LedPinRed,   r_val);
	softPwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}

void myISR(void)
{
        int randomnumber;
        randomnumber = rand() % 9;
        printf("Rajiv Detected - %d %d\n", randomnumber, time(NULL));
        ledInit();
        ledColorSet(colors[randomnumber][0],colors[randomnumber][1],colors[randomnumber][2]);
        delay(20);
}

int main(void)
{
        if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
                printf("setup wiringPi failed !\n");
                return 1;
        }

        
        if(wiringPiISR(ObstaclePin, INT_EDGE_BOTH, &myISR) < 0){
                printf("Unable to setup ISR !!!\n");
                return 1;
        }

        while(1){
                ledColorSet(0x00,0x00,0xff);
                ;
        }

        return 0;
}


