#include "PokemonApplication.hpp"

#include <array>
#include <filesystem>

namespace {
constexpr unsigned int windowWidth = 1280;
constexpr unsigned int windowHeight = 800;
constexpr std::size_t visibleRows = 12;
constexpr std::size_t partySize = 6;

std::filesystem::path findResource(const std::string& relativePath) {
    const std::array<std::filesystem::path, 3> candidates = {
        std::filesystem::current_path() / relativePath,
        std::filesystem::current_path() / ".." / relativePath,
        std::filesystem::current_path() / ".." / ".." / relativePath
    };

    for (const auto& candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }
    return {};
}

}

// Creates the application and initializes the initial Pokemon selection screen.
PokemonApplication::PokemonApplication()
    : pokedex(Pokedex::getInstance()),
      window(sf::VideoMode({windowWidth, windowHeight}), "Pokemon | Pokedex"),
      draftChoices(pokedex.getRandomPokemon(3)),
      team(std::vector<int>{}, storage) {
    state = std::make_unique<StarterSelectionState>();
    window.setFramerateLimit(60);
    loadFont();
}

void PokemonApplication::loadFont() {
    const std::array<std::filesystem::path, 6> fontPaths = {
        std::filesystem::path("C:/Windows/Fonts/segoeui.ttf"),
        std::filesystem::path("C:/Windows/Fonts/segoeuisl.ttf"),
        std::filesystem::path("C:/Windows/Fonts/seguisym.ttf"),
        std::filesystem::path("C:/Windows/Fonts/arial.ttf"),
        std::filesystem::path("C:/Windows/Fonts/arialuni.ttf"),
        findResource("ressources/fonts/segoeui.ttf")
    };

    for (const auto& path : fontPaths) {
        if (!path.empty() && std::filesystem::exists(path) && font.openFromFile(path)) {
            return;
        }
    }
    throw std::runtime_error("Police introuvable. Installe SFML et verifie les polices Windows.");
}

int PokemonApplication::run() {
    while (window.isOpen()) {
        processEvents();
        draw();
    }
    return 0;
}

// Changes the current view and replaces the active state with the matching state object.
void PokemonApplication::setState(View nextView) {
    currentView = nextView;
    switch (nextView) {
        case View::StarterSelection: state = std::make_unique<StarterSelectionState>(); break;
        case View::Pokedex: state = std::make_unique<PokedexState>(); break;
        case View::Team: state = std::make_unique<TeamState>(); break;
        case View::Storage: state = std::make_unique<StorageState>(); break;
        case View::Battle: state = std::make_unique<BattleState>(); break;
    }
}

// Reads and processes queued SFML events to update the game.
void PokemonApplication::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        processEvent(*event);
    }
}

// Identifies the event type and routes it to the appropriate game logic.
void PokemonApplication::processEvent(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
        return;
    }

    if (const auto* mouseMove = event.getIf<sf::Event::MouseMoved>()) {
        mousePosition = mouseMove->position;
    } else if (const auto* mouseClick = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseClick->button == sf::Mouse::Button::Left) {
            processClick(mouseClick->position);
        }
    } else if (const auto* mouseWheel = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (currentView == View::Pokedex) {
            const std::size_t pokemonCount = pokedex.getPokemonList().size();
            if (mouseWheel->delta < 0.0f && dexSelection + 1 < pokemonCount) {
                ++dexSelection;
                if (dexSelection >= dexOffset + visibleRows) ++dexOffset;
            } else if (mouseWheel->delta > 0.0f && dexSelection > 0) {
                --dexSelection;
                if (dexSelection < dexOffset) --dexOffset;
            }
        } else if (currentView == View::Storage) {
            const std::size_t pokemonCount = storage.getPokemonList().size();
            if (mouseWheel->delta < 0.0f && storageSelection + 1 < pokemonCount) {
                ++storageSelection;
                if (storageSelection >= storageOffset + visibleRows) ++storageOffset;
            } else if (mouseWheel->delta > 0.0f && storageSelection > 0) {
                --storageSelection;
                if (storageSelection < storageOffset) --storageOffset;
            }
        }
    }
}

// Handles mouse clicks to select, transfer, or command Pokemon.
void PokemonApplication::processClick(sf::Vector2i position) {
    if (currentView != View::StarterSelection) {
        constexpr std::array<float, 4> navX = {590.0f, 715.0f, 830.0f, 930.0f};
        constexpr std::array<View, 4> navViews = {View::Pokedex, View::Team, View::Storage, View::Battle};
        for (std::size_t index = 0; index < navX.size(); ++index) {
            if (!contains({{navX[index], 26.0f}, {112.0f, 48.0f}}, position)) continue;
            if (navViews[index] == View::Battle) {
                startBattle();
            } else {
                setState(navViews[index]);
            }
            return;
        }
    }

    if (state) state->handleClick(*this, position);
}
