#pragma once
#include <iostream>
#include "raylib-cpp-utils.hpp"

class Counter {

    public:
        std::vector<int> ids;
        Counter() {
            this->ids.push_back(0);
            this->ids.push_back(0);
            this->ids.push_back(0);
            this->ids.push_back(0);
            this->ids.push_back(0);
            this->ids.push_back(0);
            this->ids.push_back(0);
            this->ids.push_back(0);
            this->ids.push_back(0);
        }

        void update(char tankID) {
            switch (tankID) {
                case 'b':
                    ids[0]++;
                    break;
                case 'g':
                    ids[1]++;
                    break;
                case 'r':
                    ids[2]++;
                    break;
                case 'y':
                    ids[3]++;
                    break;
                case 'p':
                    ids[4]++;
                    break;
                case 'w':
                    ids[5]++;
                    break;
                case 'P':
                    ids[6]++;
                    break;
                case 'l':
                    ids[7]++;
                    break;
                case 'B':
                    ids[8]++;
                    break;

                default:
                    break;
            }
        }
};