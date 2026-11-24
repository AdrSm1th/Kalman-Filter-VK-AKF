#pragma once

#include <vector>

struct Sample {
	int step = 0;
	double trueTemperature = 0;
	double measurement = 0;
	double trueR = 0;
};

enum class NoiseType {
   Constant,
   Jump,
   Sinusoidal
};

struct GeneratorConfig {
   int sampleCount = 300;

   double initialTemperature = 22.0;
   double Q = 0.01;

   double lowR = 0.2;
   double highR = 1.0;

   int jumpStart = 100;
   int jumpEnd = 200;

   int seed = 42;

   double period = 100.0;

   NoiseType scenario = NoiseType::Constant;
};

std::vector<Sample> gen_samples(const GeneratorConfig &config);