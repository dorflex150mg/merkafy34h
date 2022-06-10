#include <math.h>
#include <stdio.h>

#define PI	3.141592

double get_angle_from_catets(double oposite, double adjacent) {
   double final_angle;
   double tan = oposite/adjacent;
   double angle = (atan(tan) * 180/PI) - 90; //fixes rotation
   return angle; // converts to degrees
}

double get_oposite_catet(double angle, double hypothenuse) {
   double rad = angle * PI/180 ;
   return sin(rad) * hypothenuse;
}

double get_adjacent_catet(double angle, double hypothenuse) {
   double rad = angle * PI/180 ;
   return cos(rad) * hypothenuse;
}
