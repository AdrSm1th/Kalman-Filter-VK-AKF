#include "KalmanFilter.h"

KalmanFilter::KalmanFilter(double m0, double P0, double Q, double R)
	: m_(m0), P_(P0), Q_(Q), R_(R)
{

}

void KalmanFilter::update(double measurement)
{
	double P_pred = P_ + Q_;

	double K = P_pred / (P_pred + R_);

	m_ = m_ + K * (measurement - m_);
	P_ = (1.0 - K) * P_pred;
}

double KalmanFilter::getM() const noexcept { return m_; }
double KalmanFilter::getP() const noexcept { return P_; }