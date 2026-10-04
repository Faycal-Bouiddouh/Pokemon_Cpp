#include "Display.hpp"

#include <iostream>

namespace {
void displayBattleStart() {
    std::cout << "****** BATTLE ******" << std::endl;
}

void displaySpeedAdvantage(const std::string& fasterName, const std::string& slowerName) {
    std::cout << fasterName << " est plus rapide que " << slowerName << std::endl;
}

void displayAttack(const std::string& attackerName, const std::string& defenderName) {
    std::cout << attackerName << " attaque " << defenderName << std::endl;
}

void displayNoEffect() {
    std::cout << "L'attaque n'a aucun effet !" << std::endl;
}

void displayBlockedAttack(const std::string& defenderName) {
    std::cout << defenderName << " se protege et ne perd pas de points de vie" << std::endl;
}

void displayEffectiveness(double multiplier) {
    if (multiplier > 1.0) {
        std::cout << "C'est super efficace !" << std::endl;
    } else if (multiplier < 1.0) {
        std::cout << "Ce n'est pas tres efficace..." << std::endl;
    }
}

void displayDamage(const std::string& defenderName, double damage, double remainingHitPoints) {
    std::cout << defenderName << " perd " << damage << " points de vie" << std::endl;
    std::cout << defenderName << " a maintenant " << remainingHitPoints << " points de vie" << std::endl;
}

void displayKnockout(const std::string& pokemonName) {
    std::cout << pokemonName << " est KO" << std::endl;
}
}

void displayPokemonInfo(const Pokemon& pokemon) {
    std::cout << "****** " << pokemon.getName() << " ******" << std::endl;
    std::cout << "Id : " << pokemon.getId() << std::endl;
    std::cout << "Type 1 : " << pokemon.getType1() << std::endl;
    std::cout << "Type 2 : " << pokemon.getType2() << std::endl;
    std::cout << "HitPoint : " << pokemon.getHitPoint() << std::endl;
    std::cout << "Attack : " << pokemon.getAttack() << std::endl;
    std::cout << "Defense : " << pokemon.getDefense() << std::endl;
    std::cout << "Special Attack : " << pokemon.getSpecialAttack() << std::endl;
    std::cout << "Special Defense : " << pokemon.getSpecialDefense() << std::endl;
    std::cout << "Speed : " << pokemon.getSpeed() << std::endl;
    std::cout << "Generation : " << pokemon.getGeneration() << std::endl;
    std::cout << "Legendary : " << (pokemon.isLegendary() ? "Yes" : "No") << std::endl;
}

void displayPokemonCollection(const std::vector<Pokemon>& pokemonList) {
    for (const Pokemon& pokemon : pokemonList) {
        displayPokemonInfo(pokemon);
    }
}

void displayPokemonChoices(const std::vector<Pokemon>& pokemonChoices) {
    for (std::size_t index = 0; index < pokemonChoices.size(); ++index) {
        const Pokemon& pokemon = pokemonChoices[index];
        std::cout << index + 1 << ". " << pokemon.getName() << " (" << pokemon.getType1();
        if (!pokemon.getType2().empty()) {
            std::cout << ", " << pokemon.getType2();
        }
        std::cout << ")" << std::endl;
    }
}

void displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void displaySection(const std::string& title) {
    std::cout << "\n========== " << title << " ==========" << std::endl;
}

void displayBattleResult(const BattleResult& result) {
    displayBattleStart();
    displaySpeedAdvantage(result.fasterPokemonName, result.slowerPokemonName);
    displayAttack(result.attack.attackerName, result.attack.defenderName);

    if (result.attack.hasNoEffect) {
        displayNoEffect();
        return;
    }
    if (result.attack.damage == 0.0) {
        displayBlockedAttack(result.attack.defenderName);
        return;
    }

    displayEffectiveness(result.attack.typeEffectiveness);
    displayDamage(result.attack.defenderName, result.attack.damage, result.attack.remainingHitPoints);
    if (result.attack.defenderKnockedOut) {
        displayKnockout(result.attack.defenderName);
    }
}