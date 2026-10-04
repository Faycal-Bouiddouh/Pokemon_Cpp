#include "GameState.hpp"

#include "PokemonApplication.hpp"

// Selects the Pokemon clicked on the initial selection card.
bool StarterSelectionState::handleClick(PokemonApplication& app, const sf::Vector2i& position) {
    constexpr float cardStartX = 75.0f;
    constexpr float cardWidth = 350.0f;
    constexpr float cardGap = 40.0f;
    for (std::size_t index = 0; index < app.draftChoices.size(); ++index) {
        const sf::FloatRect card({cardStartX + index * (cardWidth + cardGap), 240.0f}, {cardWidth, 430.0f});
        if (app.contains(card, position)) {
            app.chooseDraftPokemon(index);
            return true;
        }
    }
    return false;
}

// Renders the initial Pokemon selection screen.
void StarterSelectionState::render(PokemonApplication& app) const {
    app.drawStarterSelection();
}

// Selects a Pokedex entry when its row is clicked.
bool PokedexState::handleClick(PokemonApplication& app, const sf::Vector2i& position) {
    constexpr float listTop = 170.0f;
    constexpr float rowHeight = 45.0f;
    if (app.contains({{28.0f, listTop}, {365.0f, 570.0f}}, position)) {
        const std::size_t row = static_cast<std::size_t>((position.y - static_cast<int>(listTop)) / rowHeight);
        if (row < 12 && app.dexOffset + row < app.pokedex.getPokemonList().size()) {
            app.dexSelection = app.dexOffset + row;
            return true;
        }
    }
    return false;
}

// Renders the Pokedex view and details of the selected Pokemon.
void PokedexState::render(PokemonApplication& app) const {
    app.drawPokedex();
}

// Returns a team member to the PC when its card is clicked.
bool TeamState::handleClick(PokemonApplication& app, const sf::Vector2i& position) {
    if (app.contains({{720.0f, 715.0f}, {500.0f, 44.0f}}, position)) {
        app.startBattle();
        return true;
    }
    if (!app.battleTeam.empty()) return false;

    const auto& pokemonList = app.team.getPokemonList();
    for (std::size_t index = 0; index < pokemonList.size(); ++index) {
        const sf::FloatRect card({35.0f + static_cast<float>(index % 2) * 410.0f,
                                  160.0f + static_cast<float>(index / 2) * 190.0f},
                                 {390.0f, 165.0f});
        if (app.contains(card, position)) {
            app.returnTeamPokemonToStorage(index);
            return true;
        }
    }
    return false;
}

// Renders the active team and its available slots.
void TeamState::render(PokemonApplication& app) const {
    app.drawTeam();
}

// Selects a Pokemon in the PC or transfers it to the team.
bool StorageState::handleClick(PokemonApplication& app, const sf::Vector2i& position) {
    if (app.contains({{785.0f, 660.0f}, {330.0f, 52.0f}}, position)) {
        app.addSelectedStoragePokemon();
        return true;
    }
    constexpr float listTop = 170.0f;
    constexpr float rowHeight = 45.0f;
    if (app.contains({{28.0f, listTop}, {365.0f, 570.0f}}, position)) {
        const std::size_t row = static_cast<std::size_t>((position.y - static_cast<int>(listTop)) / rowHeight);
        if (row < 12 && app.storageOffset + row < app.storage.getPokemonList().size()) {
            app.storageSelection = app.storageOffset + row;
            return true;
        }
    }
    return false;
}

// Renders the PC contents and allows Pokemon to be selected for transfer.
void StorageState::render(PokemonApplication& app) const {
    app.drawStorage();
}

// Selects a team Pokemon for battle when its card is clicked.
bool BattleState::handleClick(PokemonApplication& app, const sf::Vector2i& position) {
    if (app.contains({{590.0f, 666.0f}, {300.0f, 60.0f}}, position)) {
        if (app.battleWon && !app.rewardClaimed) {
            app.claimOpponentPokemon();
        } else {
            app.runBattle();
        }
        return true;
    }
    if (app.contains({{920.0f, 666.0f}, {300.0f, 60.0f}}, position)) {
        app.chooseRandomOpponent();
        return true;
    }

    constexpr float rosterTop = 194.0f;
    constexpr float rosterRowHeight = 74.0f;
    for (std::size_t index = 0; index < app.battleTeam.size(); ++index) {
        const float y = rosterTop + static_cast<float>(index) * rosterRowHeight;
        const sf::FloatRect card({34.0f, y}, {286.0f, 68.0f});
        if (app.contains(card, position)) {
            app.switchActivePokemon(index);
            return true;
        }
    }

    if (app.battleWon && !app.rewardClaimed) {
        for (std::size_t index = 0; index < app.opponentTeam.size(); ++index) {
            const float y = rosterTop + static_cast<float>(index) * rosterRowHeight;
            if (app.contains({{968.0f, y}, {278.0f, 68.0f}}, position)) {
                app.rewardSelection = index;
                app.statusMessage = app.opponentTeam[index].getName() +
                                    " selected. Click Claim at PC.";
                return true;
            }
        }
    }
    return false;
}

// Renders the battle arena and information about the current battle.
void BattleState::render(PokemonApplication& app) const {
    app.drawBattle();
}
