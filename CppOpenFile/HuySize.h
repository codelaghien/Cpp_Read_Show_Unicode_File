#pragma once

class HuySize
{
    public:
        int width;
        int height;

        HuySize() : HuySize(0, 0) {
        }

        HuySize(int width, int height) {
            this->width = width;
            this->height = height;
        }
};

