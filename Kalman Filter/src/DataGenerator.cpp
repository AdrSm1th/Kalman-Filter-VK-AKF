#include "DataGenerator.h"

#include <random>

double getTrueR(int step, const GeneratorConfig &config) {
	switch (config.scenario) {
	case NoiseType::Constant:
		return config.lowR;

	case NoiseType::Jump:
		if (step >= config.jumpStart &&
			step < config.jumpEnd) {
			return config.highR;
		}
		return config.lowR;

	case NoiseType::Sinusoidal: {
		constexpr double PI = 3.14159265358979323846;

		double amplitude = (config.highR - config.lowR) / 2.0;
		double mean = (config.highR + config.lowR) / 2.0;

		return mean + amplitude *
			std::sin(2.0 * PI * step / config.period);
	}
	}
}

std::vector<Sample> gen_samples(const GeneratorConfig &config) {
	std::vector<Sample> samples;
	samples.reserve(config.sampleCount);

	std::mt19937 gen(config.seed);

	std::normal_distribution<double> processNoise(
		0.0, std::sqrt(config.Q)
	);

	std::normal_distribution<double> measurementNoise(
		0.0, 1.0
	);

	double temperature = config.initialTemperature;
	Sample sample;
	sample.step = 0;
	sample.trueTemperature = temperature;
	sample.measurement = temperature + measurementNoise(gen) * std::sqrt(0.2);
	sample.trueR = 0.2;
	samples.push_back(sample);

	for (int i = 1; i < config.sampleCount; i++) {
		temperature += processNoise(gen);

		double R = getTrueR(i, config);

		double v = measurementNoise(gen) * std::sqrt(R);

		sample.step = i;
		sample.trueTemperature = temperature;
		sample.measurement = temperature + v;
		sample.trueR = R;

		samples.push_back(sample);
	}

	return samples;
}