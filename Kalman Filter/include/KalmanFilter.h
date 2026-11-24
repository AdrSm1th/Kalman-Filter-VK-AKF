#pragma once

class KalmanFilter
{
public:
	KalmanFilter(double m0, double P0, double Q, double R);
	void update(double measurement);

	double getM() const noexcept;
	double getP() const noexcept;

private:
	double m_;
	double P_;
	double Q_;
	double R_;
};