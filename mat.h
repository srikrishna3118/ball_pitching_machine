/*
 * mat.h
 *
 *  Created on: 01-May-2019
 *      Author: acharya
 */

#ifndef MAT_H_
#define MAT_H_

//int map(int x, int in_min, int in_max, int out_min, int out_max);
//int constrain(int value, int max, int min);

void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
float mapf(float x, float in_min, float in_max, float out_min, float out_max);
float constrain(float value, float max, float min);


#endif /* MAT_H_ */
