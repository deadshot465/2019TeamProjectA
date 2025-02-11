#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <stdexcept>
#include <string>
#include <optional>
#include <list>
#include <cstring>

constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 540;
constexpr float SCALE_SIZE = 1.0f;
constexpr int FLOOR_MOVE_SPEED = WINDOW_WIDTH / 10;
constexpr int FLOOR_BACK_SPEED = -FLOOR_MOVE_SPEED;
constexpr int FLOOR_STOP_SPEED = 0;
constexpr int PARRY_SCORE = 200;
constexpr int GUARD_SCORE = 100;
constexpr int BOSS_SCORE = 300;

struct RenderConfig {
	int xPos;
	int yPos;
	float scaleX;
	float scaleY;
};

enum class PlayerAnimation {
	Running,
	Guard,
	Parry,
	Injury,
	Beginning
};

enum class SoundList {
	Scream
};

enum class SceneName {
	Title,
	Game,
	GameClear
};

enum class PlayerStatus {
	Running,
	Guard,
	Parry,
	Injury
};

inline void ThrowIfFailed(int result, const std::string& message) {
	if (result < 0) {

		auto msg = std::string(message)
			+ "\nError Message: " + std::string(SDL_GetError());
		
		throw std::runtime_error(msg);
	}
}

template <typename T = std::mt19937, size_t N = T::state_size>
inline auto GetRandomSeededEngine() -> typename std::enable_if<!!N, T>::type {
	typename T::result_type data[N];
	std::random_device rd;
	std::generate(std::begin(data), std::end(data), std::ref(rd));
	std::seed_seq seeds(std::begin(data), std::end(data));
	T engine(seeds);
	return engine;
}

template <typename T = double>
inline T GetRandomFloatNumber(T lower, T upper) {
	auto engine = GetRandomSeededEngine();
	auto generator = std::uniform_real_distribution<>(lower, upper);
	return static_cast<T>(generator(engine));
}

template <typename T = int>
inline T GetRandomIntegerNumber(T lower, T upper) {
	auto engine = GetRandomSeededEngine();
	auto generator = std::uniform_int_distribution<T>(lower, upper);
	return generator(engine);
}
