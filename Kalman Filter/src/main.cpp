#include "DataGenerator.h"

#include <vector>
#include <fstream>
#include <iostream>

int main() {
	GeneratorConfig config;

	std::vector<Sample> samples = gen_samples(config);

	std::ofstream data("samples.csv");
	if (!data.is_open()) {
		std::cerr << "Ошибка открытия файла\n";
		return 1;
	}

	for (int i = 0; i < samples.size(); i++) {
		data << samples[i].step << "," << samples[i].trueTemperature << "," << samples[i].measurement << "," << samples[i].trueR << "\n";
	}

	data.close();
}