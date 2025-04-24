#pragma once

class Character;

class Camera {
public:
    void SetupView(const Character& character) const;
};