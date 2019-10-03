#pragma once
#include <algorithm>
#include <iostream>
#include <random>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <cstring>

constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 540;
constexpr float SCALE_SIZE = 1.0f;

struct RenderConfig {
	int xPos;
	int yPos;
	float scaleX;
	float scaleY;
};

struct EnemySpriteSet {
	int spriteIndex;
	int projectileIndex;
};

enum class CollisionResult {
	None,
	Guard,
	Parry
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