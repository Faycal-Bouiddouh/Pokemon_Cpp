#include <iostream>
#include "Pokemon.hpp"
#include "SetOfPokemon.hpp"
#include "Pokedex.hpp"

using namespace std;

int main(){
    Pokedex& pokedex = Pokedex::getInstance();
    Pokemon monPokemon = pokedex.getClone(3);
    Pokemon monPokemon2 = pokedex.getClone(1);
    monPokemon.displayInfo();
    monPokemon.Battle(monPokemon2);
    return 0;
}