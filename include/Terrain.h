#pragma once

class Terrain {
public:
    static const int SIZE = 50;
    float heightMap[SIZE][SIZE];

    void Generate();
    void Draw() const;
};