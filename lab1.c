#include<stdio.h>
#include<math.h>
#define PI 3.14159

int main()
{
	double circumference;
	int radius;
	int i;
	
	printf("please enter the radius of a circle to calculate the circumference\n");
	scanf("%d", &radius);
	circumference = PI*2*radius;
	printf("circumference of circle = %lf", circumference);
	printf("this is a test comment\n");
	return 0;
};