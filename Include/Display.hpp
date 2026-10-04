#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>
#include <vector>
#include "Pokemon.hpp"

void displayPokemonInfo(const Pokemon& pokemon);
void displayPokemonCollection(const std::vector<Pokemon>& pokemonList);
void displayPokemonChoices(const std::vector<Pokemon>& pokemonChoices);
void displayMessage(const std::string& message);
void displaySection(const std::string& title);
void displayBattleResult(const BattleResult& result);

#endif