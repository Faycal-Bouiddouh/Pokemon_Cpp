#include "PokemonApplication.hpp"

#include <algorithm>

namespace {
constexpr std::size_t draftRoundCount = 10;
constexpr std::size_t partySize = 6;
constexpr std::size_t visibleRows = 12;
}
// Adds the selected Pokemon to the PC and prepares the next selection round.
void PokemonApplication::chooseDraftPokemon(std::size_t index) {
    if (index >= draftChoices.size() || draftRound >= draftRoundCount) return;

    const Pokemon selectedPokemon = draftChoices[index];
    storage.addPokemon(selectedPokemon);
    ++draftRound;
    if (draftRound == draftRoundCount) {
        setState(View::Storage);
        storageSelection = 0;
        storageOffset = 0;
        statusMessage = "All 10 Pokemon are in the PC. Choose 6 for your team.";
        return;
    }

    std::vector<std::string> selectedNames;
    for (const Pokemon& pokemon : storage.getPokemonList()) {
        selectedNames.push_back(pokemon.getName());
    }
    draftChoices = pokedex.getRandomPokemon(3, selectedNames);
    statusMessage = selectedPokemon.getName() + " added to the PC (" + std::to_string(draftRound) + "/10).";
}

// Transfers the selected Pokemon from the PC to the team if a slot is available.
void PokemonApplication::addSelectedStoragePokemon() {
    const auto& pokemonList = storage.getPokemonList();
    if (storageSelection >= pokemonList.size()) {
        statusMessage = "The PC no longer contains any Pokemon to transfer.";
        return;
    }
    if (team.getPokemonList().size() >= partySize) {
        statusMessage = "Your team is full (6 Pokemon).";
        return;
    }

    const std::string name = pokemonList[storageSelection].getName();
    if (team.addPokemon(name)) {
        if (storageSelection >= storage.getPokemonList().size() && storageSelection > 0) {
            --storageSelection;
        }
        storageOffset = std::min(storageOffset, storageSelection);
        statusMessage = name + " transferred from the PC to the team (" +
                        std::to_string(team.getPokemonList().size()) + "/6).";
    }
}

// Returns a team Pokemon to the PC so it can be reassigned later.
void PokemonApplication::returnTeamPokemonToStorage(std::size_t index) {
    const auto& pokemonList = team.getPokemonList();
    if (index >= pokemonList.size()) return;

    const Pokemon pokemon = team.takePokemonByName(pokemonList[index].getName());
    storage.addPokemon(pokemon);
    storageSelection = storage.getPokemonList().size() - 1;
    statusMessage = pokemon.getName() + " returned to the PC.";
}

// Starts the battle if the team contains exactly six valid members.
void PokemonApplication::startBattle() {
    if (!battleTeam.empty()) {
        setState(View::Battle);
        return;
    }
    if (team.getPokemonList().size() != partySize) {
        statusMessage = "You must choose exactly 6 Pokemon in the PC.";
        return;
    }

    battleTeam = team.getPokemonList();
    std::vector<std::string> selectedNames;
    for (const Pokemon& pokemon : battleTeam) {
        selectedNames.push_back(pokemon.getName());
    }

    opponentTeam = pokedex.getRandomPokemon(6, selectedNames);
    opponentSelection = 0;
    teamSelection = 0;
    battleFinished = false;
    battleWon = false;
    rewardClaimed = false;
    rewardSelection = 0;
    lastRound.clear();
    setState(View::Battle);
    statusMessage = "Battle started against a random team of 6 Pokemon.";
}

// Generates a new random opponent team for another challenge.
void PokemonApplication::chooseRandomOpponent() {
    if (battleWon && !rewardClaimed) {
        statusMessage = "Recover a Pokemon from the defeated team first.";
        return;
    }

    std::vector<std::string> selectedNames;
    for (const Pokemon& pokemon : battleTeam) {
        selectedNames.push_back(pokemon.getName());
    }
    opponentTeam = pokedex.getRandomPokemon(6, selectedNames);
    opponentSelection = 0;
    lastRound.clear();
    battleFinished = false;
    battleWon = false;
    rewardClaimed = false;
    rewardSelection = 0;
    statusMessage = "New enemy team generated.";
}

// Adds a defeated Pokemon to the player's storage after a victory.
void PokemonApplication::claimOpponentPokemon() {
    if (!battleWon || rewardClaimed || rewardSelection >= opponentTeam.size()) return;

    const std::string selectedName = opponentTeam[rewardSelection].getName();
    storage.addPokemon(pokedex.findPokemonByName(selectedName));
    storageSelection = storage.getPokemonList().size() - 1;
    storageOffset = storageSelection >= visibleRows ? storageSelection - visibleRows + 1 : 0;
    rewardClaimed = true;
    statusMessage = selectedName + " recovered and placed in the PC.";
}

// Executes a battle turn, determining attack order from the Pokemon's speed.
void PokemonApplication::runBattle() {
    if (battleFinished) {
        statusMessage = "The battle is over.";
        return;
    }
    if (battleTeam.empty() || opponentTeam.empty()) {
        statusMessage = "One team is empty.";
        return;
    }

    if (opponentSelection >= opponentTeam.size()) {
        battleFinished = true;
        battleWon = true;
        rewardClaimed = false;
        rewardSelection = 0;
        statusMessage = "Victory! The enemy team has been defeated.";
        return;
    }

    Pokemon& activePokemon = battleTeam.at(teamSelection);
    Pokemon& enemyPokemon = opponentTeam.at(opponentSelection);
    if (activePokemon.getHitPoint() <= 0.0) {
        const bool hasHealthyPokemon = std::any_of(battleTeam.begin(), battleTeam.end(),
            [](const Pokemon& pokemon) { return pokemon.getHitPoint() > 0.0; });
        if (!hasHealthyPokemon) {
            battleFinished = true;
            statusMessage = "Defeat. Your entire team is K.O.";
        } else {
            statusMessage = "This Pokemon is K.O. Choose another team member.";
        }
        return;
    }

    lastRound.clear();
    auto attackIfStanding = [this](Pokemon& attacker, Pokemon& defender) {
        if (attacker.getHitPoint() > 0.0 && defender.getHitPoint() > 0.0) {
            lastRound.push_back(attacker.attack(defender));
        }
    };

    if (activePokemon.getSpeed() >= enemyPokemon.getSpeed()) {
        attackIfStanding(activePokemon, enemyPokemon);
        attackIfStanding(enemyPokemon, activePokemon);
    } else {
        attackIfStanding(enemyPokemon, activePokemon);
        attackIfStanding(activePokemon, enemyPokemon);
    }

    if (enemyPokemon.getHitPoint() <= 0.0) {
        ++opponentSelection;
        if (opponentSelection == opponentTeam.size()) {
            battleFinished = true;
            battleWon = true;
            rewardClaimed = false;
            rewardSelection = 0;
            statusMessage = "Victory! The enemy team has been defeated.";
        } else {
            statusMessage = enemyPokemon.getName() + " is K.O. The next Pokemon enters the battle.";
        }
    } else if (activePokemon.getHitPoint() <= 0.0) {
        const bool hasHealthyPokemon = std::any_of(battleTeam.begin(), battleTeam.end(),
            [](const Pokemon& pokemon) { return pokemon.getHitPoint() > 0.0; });
        if (!hasHealthyPokemon) {
            battleFinished = true;
            statusMessage = "Defeat. Your entire team is K.O.";
        } else {
            statusMessage = activePokemon.getName() + " is K.O. Choose another member.";
        }
    } else {
        statusMessage = "Turn complete. Choose an action or switch Pokemon.";
    }
}

// Changes the active Pokemon fighting for the player's team.
void PokemonApplication::switchActivePokemon(std::size_t index) {
    if (battleFinished) return;
    if (index >= battleTeam.size()) return;
    if (battleTeam[index].getHitPoint() <= 0.0) {
        statusMessage = "This Pokemon is K.O. Choose a healthy team member.";
        return;
    }
    if (index == teamSelection) return;
    teamSelection = index;
    statusMessage = battleTeam[index].getName() + " is now in battle.";
}
