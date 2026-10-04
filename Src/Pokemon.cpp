/**
 * Purpose: Implements the Pokemon class logic.
 * 
 * Features:
 * - Defines the constructors used to initialize Pokemon attributes.
 * - Implements battle rules and data accessors.
 */

#include <algorithm>
#include <string>
#include <utility>
#include "Pokemon.hpp"
#include "TypeChart.hpp"

int Pokemon::pokemonCount = 0;

// Creates a Pokemon with its base statistics and increments the global counter.
Pokemon::Pokemon(int id, std::string name, std::string primaryType, std::string secondaryType,
                 double totalStats, double hitPoints, double attackPower,
                 double defensePower, double specialAttackPower,
                 double specialDefensePower, double speed, int generation, bool legendary)
    : id(id), name(std::move(name)), primaryType(std::move(primaryType)),
      secondaryType(std::move(secondaryType)), totalStats(totalStats),
      hitPoints(hitPoints), attackPower(attackPower), defensePower(defensePower),
      specialAttackPower(specialAttackPower), specialDefensePower(specialDefensePower),
      speed(speed), generation(generation), legendary(legendary) {
    ++pokemonCount;
}

// Copies another Pokemon's attributes to create a distinct instance.
Pokemon::Pokemon(const Pokemon& anotherPokemon)
    : id(anotherPokemon.id), name(anotherPokemon.name), primaryType(anotherPokemon.primaryType),
      secondaryType(anotherPokemon.secondaryType), totalStats(anotherPokemon.totalStats),
      hitPoints(anotherPokemon.hitPoints), attackPower(anotherPokemon.attackPower),
      defensePower(anotherPokemon.defensePower), specialAttackPower(anotherPokemon.specialAttackPower),
      specialDefensePower(anotherPokemon.specialDefensePower), speed(anotherPokemon.speed),
      generation(anotherPokemon.generation), legendary(anotherPokemon.legendary) {
    ++pokemonCount;
}

// Returns the total number of Pokemon created during the game session.
int Pokemon::getNumberOfPokemon() {
    return pokemonCount;
}

// Returns the Pokemon's attack power used to calculate damage.
double Pokemon::getAttack() const {
    return attackPower;
}

// Returns the Pokemon's physical defense used to reduce incoming damage.
double Pokemon::getDefense() const {
    return defensePower;
}

// Returns the Pokemon's current hit points.
double Pokemon::getHitPoint() const {
    return hitPoints;
}

// Returns the Pokemon's unique database ID.
int Pokemon::getId() const {
    return id;
}

// Returns the Pokemon's name.
std::string Pokemon::getName() const {
    return name;
}

std::string Pokemon::getType1() const {
    return primaryType;
}

std::string Pokemon::getType2() const {
    return secondaryType;
}

double Pokemon::getSpecialAttack() const {
    return specialAttackPower;
}

double Pokemon::getSpecialDefense() const {
    return specialDefensePower;
}

double Pokemon::getSpeed() const {
    return speed;
}

int Pokemon::getGeneration() const {
    return generation;
}

bool Pokemon::isLegendary() const {
    return legendary;
}

// Calculates the type effectiveness multiplier against the target Pokemon.
double Pokemon::getTypeEffectivenessAgainst(const Pokemon& target) const {
    double effectiveness = calculateTypeEffectiveness(primaryType, target.primaryType);
    if (!target.secondaryType.empty()) {
        effectiveness *= calculateTypeEffectiveness(primaryType, target.secondaryType);
    }
    return effectiveness;
}

// Reduces the target Pokemon's hit points without going below zero.
void Pokemon::takeDamage(double damage) {
    hitPoints = std::max(0.0, hitPoints - damage);
}

// Simulates one attack and returns a detailed result.
AttackResult Pokemon::attack(Pokemon& target) {
    AttackResult result{name, target.name, getTypeEffectivenessAgainst(target), 0.0, target.hitPoints, false, false};
    if (result.typeEffectiveness == 0.0) {
        result.hasNoEffect = true;
        return result;
    }

    result.damage = std::max(0.0, attackPower - target.defensePower) * result.typeEffectiveness;
    if (result.damage == 0.0) {
        return result;
    }

    target.takeDamage(result.damage);
    result.remainingHitPoints = target.hitPoints;
    result.defenderKnockedOut = target.hitPoints == 0.0;
    return result;
}

// Determines attack order from speed before exchanging attacks.
BattleResult Pokemon::battle(Pokemon& target) {
    BattleResult result;
    if (speed > target.speed) {
        result.fasterPokemonName = name;
        result.slowerPokemonName = target.name;
        result.attack = attack(target);
    } else {
        result.fasterPokemonName = target.name;
        result.slowerPokemonName = name;
        result.attack = target.attack(*this);
    }
    return result;
}

// Decrements the global counter when the object is destroyed.
Pokemon::~Pokemon() {
    --pokemonCount;
}