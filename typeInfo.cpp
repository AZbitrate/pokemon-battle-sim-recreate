// typeInfo.cpp
#include "typeInfo.h"
#include <algorithm>

// The matrix size must match your number of types (excluding None)
const int TYPE_COUNT = 18;
        // ONLY FULLY DONE NOR,FIRE,water,ELECTRIC,GRASS,ICE,FIGHTING,POSION,GROUND,FLYING,PSYCHIC,BUG,ROCK,GHOST,DRAGON,DARK
// Rows = Attacker, Columns = Defender
// Index order: Normal (0), Fire (1), Water (2), Electric(3), Grass (4), etc
const float typeChart[TYPE_COUNT][TYPE_COUNT] = {
    //            Nor   Fir   Wat   ELE   Gra   Ice   Fig   Poi   Gro   Fly   Psy   Bug   Roc   Gho   Dra   Dar   Ste   Fai
    /* Normal */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f,},
    /* Fire   */ {1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f,},
    /* Water  */ {1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f,},
    /* Elect  */ {1.0f, 1.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f,},
    /* Grass  */ {1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f,},
    /* Ice    */ {1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f,},
    /* Fight  */ {2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 2.0f, 2.0f, 0.5f,},
    /* Poison */ {1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 2.0f,},
    /* Ground */ {1.0f, 2.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 2.0f, 1.0f, 0.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f,},
    /* Flying */ {1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,},
    /* Psych  */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f,},
    /* Bug    */ {1.0f, 0.5f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.5f, 2.0f, 0.5f, 2.0f, 1.0f, 2.0f, 0.5f, 1.0f, 2.0f, 0.5f, 0.5f,},
    /* Rock   */ {1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f,},
    /* Ghost  */ {0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 1.0f,},
    /* Dragon */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.0f,},
    /* Dark   */ {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f,},
    /* Steel  */ {1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 2.0f,},
    /* Fairy  */ {1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f, 2.0f, 2.0f, 0.5f, 1.0f,},
};

float getEffectiveness(Type attack, Type defend) {
    if (attack == Type::None || defend == Type::None) return 1.0f;

    // Map your enum values to the 0-indexed matrix array
    int atkIdx = static_cast<int>(attack) - 1;
    int defIdx = static_cast<int>(defend) - 1;

    return typeChart[atkIdx][defIdx];
}

Type stringToType( std::string typeStr) {
    std::transform(typeStr.begin(), typeStr.end(), typeStr.begin(), ::tolower);
    if (typeStr == "normal")   return Type::Normal;
    if (typeStr == "fire")     return Type::Fire;
    if (typeStr == "water")    return Type::Water;
    if (typeStr == "electric") return Type::Electric;
    if (typeStr == "grass")    return Type::Grass;
    if (typeStr == "ice")      return Type::Ice;
    if (typeStr == "fighting") return Type::Fighting;
    if (typeStr == "poison")   return Type::Poison;
    if (typeStr == "ground")   return Type::Ground;
    if (typeStr == "flying")   return Type::Flying;
    if (typeStr == "psychic")  return Type::Psychic;
    if (typeStr == "bug")      return Type::Bug;
    if (typeStr == "rock")     return Type::Rock;
    if (typeStr == "ghost")    return Type::Ghost;
    if (typeStr == "dragon")   return Type::Dragon;
    if (typeStr == "dark")     return Type::Dark;
    if (typeStr == "steel")    return Type::Steel;
    if (typeStr == "fairy")    return Type::Fairy;

    return Type::None; // Default fallback for single-type Pokemon or invalid input
}