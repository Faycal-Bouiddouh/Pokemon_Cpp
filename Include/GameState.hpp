/**
 * State machine for the game engine.
 *
 * Each state represents a game screen: starter selection, Pokedex, team,
 * storage, or battle. This separates input handling and rendering for each view.
 */

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class PokemonApplication;

class GameState {
public:
    // Destroys a state without requiring additional cleanup.
    virtual ~GameState() = default;

    // Handles a mouse click in the current view.
    virtual bool handleClick(PokemonApplication& app, const sf::Vector2i& position) = 0;

    // Draws the screen associated with this state.
    virtual void render(PokemonApplication& app) const = 0;
};

class StarterSelectionState final : public GameState {
public:
    bool handleClick(PokemonApplication& app, const sf::Vector2i& position) override;
    void render(PokemonApplication& app) const override;
};

class PokedexState final : public GameState {
public:
    bool handleClick(PokemonApplication& app, const sf::Vector2i& position) override;
    void render(PokemonApplication& app) const override;
};

class TeamState final : public GameState {
public:
    bool handleClick(PokemonApplication& app, const sf::Vector2i& position) override;
    void render(PokemonApplication& app) const override;
};

class StorageState final : public GameState {
public:
    bool handleClick(PokemonApplication& app, const sf::Vector2i& position) override;
    void render(PokemonApplication& app) const override;
};

class BattleState final : public GameState {
public:
    bool handleClick(PokemonApplication& app, const sf::Vector2i& position) override;
    void render(PokemonApplication& app) const override;
};

#endif
