/*
 * mat.c
 *
 *  Created on: 01-May-2019
 *      Author: acharya
 */


#include <math.h>
#include "mat.h"

#include <stdio.h>

void reverse(char *str, int len){
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
int intToStr(int x, char str[], int d){
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int afterpoint){
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    char buf[20];
    //ftoa(x,buf,2);
    //printf("initial %s\n",buf);
    float value = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; // From Arduino source code: https://github.com/arduino/Arduino/blob/ide-1.5.x/hardware/arduino/avr/cores/arduino/WMath.cpp

    //ftoa(value,buf,2);
    //printf("final %s\n",buf);
    return value;

}

float constrain(float value, float max, float min)
{
    if(value>max) value = max;
    if(value<min) value = min;
    return value;
}


//int map(int x, int in_min, int in_max, int out_min, int out_max)
//{
//    int value = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; // From Arduino source code: https://github.com/arduino/Arduino/blob/ide-1.5.x/hardware/arduino/avr/cores/arduino/WMath.cpp
//    return value;
//}
//
//int constrain(int value, int max, int min)
//{
//    if(value>max) value = max;
//    if(value<min) value = min;
//    return value;
//}

