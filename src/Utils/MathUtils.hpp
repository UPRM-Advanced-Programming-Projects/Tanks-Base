#pragma once
#include <iostream>
#include <cmath>
#include "HitBox.hpp"

class Math {
    public:
        static double atan3(double y, double x) {
            double result = (180/PI) * atan2(y, x);
            return (result < 0) ? result + 360 : result;
        }

        static double getAngleDif(double angle1, double angle2) {
            double dif = (angle1 - angle2) + 180.0;
            dif = (dif - floor(dif / 360.0) * 360.0) - 180.0;
            return dif;
        }

        static int sign(double x) { return (x > 0)? 1 : -1; }

        static double getDistance(CustomHitbox source, CustomHitbox target) {
            return sqrt(pow(source.box.x - target.box.x, 2) + 
                        pow(source.box.y - target.box.y, 2));
        }

        static std::pair<double, double> getPointOfIntersection(float pjcSpeed, std::pair<double, double> pjcPos, float pSpeed, std::pair<double, double> pPos, std::pair<double, double> pVel) {
            for (int i = 0; i < 360; i++) {
                int angle = i;

                double velX = pjcSpeed* cos(angle * PI/180);
                double velY = pjcSpeed* sin(angle * PI/180);
                double denominator = velX - pSpeed * pVel.first;
                double time = (denominator != 0) ? (pPos.first - pjcPos.first) / denominator : -1;
                
                if (time > 0) {
                    double newX = pPos.first + pSpeed * pVel.first * time;
                    double newY = pPos.second + pSpeed * pVel.second * time;
                    if (abs((pjcPos.second + velY * time) - (newY)) <= 32) {
                        return std::pair<double, double>({newX, newY});
                    }
                } 

                angle += 1;
            }

            return pPos;
        }
};