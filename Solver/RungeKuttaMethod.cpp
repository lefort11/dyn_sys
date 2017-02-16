#include "RungeKuttaMethod.h"

void RungeKuttaMethod::Solve(std::vector<double>& y1, std::vector<double>& y2) const
{
	std::vector<double> y1_n(m_N + 1);
	std::vector<double> y2_n(m_N + 1);

	double h = (m_Right - m_Left) / m_N;

	y1_n[0] = m_Y1_0;
	y2_n[0] = m_Y2_0;

	for(int i = 0; i < m_N; ++i)
	{
		auto t_i = m_Left + i*h;

		auto k1 = m_f1(t_i, y1_n[i], y2_n[i]);
		auto m1 = m_f2(t_i, y1_n[i], y2_n[i]);

		auto k2 = m_f1(t_i + h/2, y1_n[i] + h/2 * k1, y2_n[i] + h/2 * m1);
		auto m2 = m_f2(t_i + h/2, y1_n[i] + h/2 * k1, y2_n[i] + h/2 * m1);

		auto k3 = m_f1(t_i + h/2, y1_n[i] + h/2 * k2, y2_n[i] + h/2 * m2);
		auto m3 = m_f2(t_i + h/2, y1_n[i] + h/2 * k2, y2_n[i] + h/2 * m2);

		auto k4 = m_f1(t_i + h, y1_n[i] + h * k3, y2_n[i] + h * m3);
		auto m4 = m_f2(t_i + h, y1_n[i] + h * k3, y2_n[i] + h * m3);


		y1_n[i+1] = y1_n[i] + h/6 * (k1 + 2*k2 + 2*k3 + k4);
		y2_n[i+1] = y2_n[i] + h/6 * (m1 + 2*m2 + 2*m3 + m4);

	}

	y1 = y1_n;
	y2 = y2_n;
}