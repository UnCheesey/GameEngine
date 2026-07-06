#pragma once

#include <cstdlib>

namespace nu {

	inline int RandomInt() {
		return rand();
	}

	/// <summary>
	/// Get random integer value [0, max]
	/// </summary>
	/// <param name="max">exclusive</param>
	/// <returns>Random number 0 and max (exclusive)</returns>
	inline int RandomInt(int max) {
		return rand() % max;
	}

	/// <summary>
	/// Ger random integer value [min, max]
	/// </summary>
	/// <param name="min">inclusive</param>
	/// <param name="max">inclusive</param>
	/// <returns>Random number min and max inclusive</returns>
	inline int RandomInt(int min, int max) {
		return RandomInt((max - min) + 1) + min;
	}

	inline float RandomFloat() {

		// rand() = 0 <- RAND_MAX
		return rand() / (float)RAND_MAX;
	}

	inline float RandomFloat(float max) {

		// 0 <-> 1 * max
		return RandomFloat() * max;
	}

	inline float RandomFloat(float min, float max) {

		// (0 <-> 1) * (max - min) + min
		return RandomFloat() * (max + min) + min;
	}
}