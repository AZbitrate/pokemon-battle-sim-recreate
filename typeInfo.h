// typeInfo.h
#pragma once
#include <string>

enum class Type {
    None, // default value before assigning type
    Normal,
    Fire,
    Water,
    Electric,
    Grass,
    Ice,
    Fighting,
    Poison,
    Ground,
    Flying,
    Psychic,
    Bug,
    Rock,
    Ghost,
    Dragon,
    Dark,
    Steel,
    Fairy
};

// Add this declaration to typeInfo.h:
Type stringToType(std::string typeStr);
float getEffectiveness(Type attack, Type defend);
