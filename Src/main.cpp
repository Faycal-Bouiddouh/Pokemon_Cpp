#include <iostream>
#include <vector>
#include <windows.h> 

#include "Pokedex.hpp"
#include "Pokeball.hpp"
#include "PokemonParty.hpp"
#include "Pokemon.hpp"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    cout << "========== PHASE 1 : CHARGEMENT DU POKEDEX ==========" << endl;
    Pokedex& pokedex = Pokedex::getInstance();


    cout << "\n========== PHASE 2 : REMPLISSAGE DU PC (POKEBALL) ==========" << endl;
    Pokeball monPC;
    
    monPC.addPokemon(pokedex.getClone(1));  
    monPC.addPokemon(pokedex.getClone(4));  
    monPC.addPokemon(pokedex.getClone(7)); 
    monPC.addPokemon(pokedex.getClone(25)); 

    cout << "Contenu initial du PC (4 Pokemon) :" << endl;
    monPC.displayAllPokemon();


    cout << "\n========== PHASE 3 : CREATION DE L'EQUIPE ==========" << endl;
    vector<int> mesFavoris = {1, 7};
    
    PokemonParty monEquipe(mesFavoris, monPC);

    cout << "\nContenu de mon Equipe (Doit contenir Bulbizarre et Carapuce) :" << endl;
    monEquipe.displayAllPokemon();


    cout << "\n========== PHASE 4 : VERIFICATION DU PC ==========" << endl;
    cout << "Contenu du PC apres transfert (Bulbizarre et Carapuce ont disparu) :" << endl;
    monPC.displayAllPokemon();

    return 0;
}