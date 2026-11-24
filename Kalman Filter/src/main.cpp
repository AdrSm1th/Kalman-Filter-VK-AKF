#include "DataGenerator.h"
#include "KalmanFilter.h"

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

	double m0 = config.initialTemperature;
	double P0 = 1.0;
	double Q = config.Q;
	double R = samples[0].trueR;

	std::vector<double> kf_m, kf_P;
	kf_m.reserve(config.sampleCount);
	kf_P.reserve(config.sampleCount);

	KalmanFilter KF(m0, P0, Q, R);
	

	std::ofstream data_kf("kf.csv");
	if (!data_kf.is_open()) {
		std::cerr << "Ошибка открытия файла\n";
		return 1;
	}

	for (const Sample& sample : samples)
	{
		KF.update(sample.measurement);
		data_kf << KF.getM() << "," << KF.getP() << "\n";

	}

	data_kf.close();

}