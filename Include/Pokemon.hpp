
/**
 * Represents a Pokemon in the game.
 *
 * This class stores the statistics required for battles, type matchups, and
 * battle logic. It is the common data model used by the Pokedex, PC storage,
 * and the player's team.
 */

#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>

using std::string;

struct AttackResult {
    string attackerName;
    string defenderName;
    double typeEffectiveness = 1.0;
    double damage = 0.0;
    double remainingHitPoints = 0.0;
    bool hasNoEffect = false;
    bool defenderKnockedOut = false;
};

struct BattleResult {
    string fasterPokemonName;
    string slowerPokemonName;
    AttackResult attack;
};

class Pokemon {
private:
    int id;
    string name;
    string primaryType;
    string secondaryType;
    double totalStats;
    double hitPoints;
    double attackPower;
    double defensePower;
    double specialAttackPower;
    double specialDefensePower;
    double speed;
    int generation;
    bool legendary;
    static int pokemonCount;

public:
    // Creates a Pokemon with its base statistics and attributes.
    Pokemon(int id, string name, string primaryType, string secondaryType,
            double totalStats, double hitPoints, double attackPower,
            double defensePower, double specialAttackPower,
            double specialDefensePower, double speed, int generation, bool legendary);

    // Copies an existing Pokemon to create an independent instance in the Pokedex or PC.
    Pokemon(const Pokemon& anotherPokemon);

    // Returns the total number of Pokemon instances created during the program run.
    static int getNumberOfPokemon();

    // Accessors used to display Pokemon information and calculate battles.
    double getAttack() const;
    double getDefense() const;
    double getHitPoint() const;
    int getId() const;
    string getName() const;
    string getType1() const;
    string getType2() const;
    double getSpecialAttack() const;
    double getSpecialDefense() const;
    double getSpeed() const;
    int getGeneration() const;
    bool isLegendary() const;

    // Simulates an attack against an opponent and returns the attack details.
    AttackResult attack(Pokemon& target);

    // Determines attack order from speed, then executes the battle.
    BattleResult battle(Pokemon& target);

    // Destroys the instance and updates the global Pokemon counter.
    ~Pokemon();

private:
    // Calculates the effectiveness multiplier from the attacking and defending types.
    double getTypeEffectivenessAgainst(const Pokemon& target) const;

    // Removes hit points from this Pokemon after an attack.
    void takeDamage(double damage);
};

#endif