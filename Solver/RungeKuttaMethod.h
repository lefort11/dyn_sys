#ifndef DYN_SYS_RUNGEKUTTAMETHOD_H
#define DYN_SYS_RUNGEKUTTAMETHOD_H


#include <functional>
#include <vector>
#include <array>

#include "TrophicChainModel.h"

class RungeKuttaMethod
{
	std::function<double(double, double, double)> m_f1;
	std::function<double(double, double, double)> m_f2;
	double m_Y1_0;
	double m_Y2_0;
	unsigned m_N;


	double m_Left;
	double m_Right;

public:
	RungeKuttaMethod(double y1_0, double y2_0, unsigned N, double left, double right,
					 std::function<double(double, double, double)> f1,
					 std::function<double(double, double, double)> f2):
			m_Y1_0(y1_0),
			m_Y2_0(y2_0),
			m_N(N),
			m_Left(left),
			m_Right(right),
			m_f1(f1),
			m_f2(f2)
	{}

	RungeKuttaMethod(unsigned N, double left, double right, Model* model):
			m_N(N),
			m_Left(left),
			m_Right(right),
			m_Y1_0(model->GetY1_0()),
			m_Y2_0(model->GetY2_0()),
			m_f1(model->GetF1()),
			m_f2(model->GetF2())
	{

	}

	~RungeKuttaMethod()
	{}


	void Solve(std::vector<double>& y1, std::vector<double>& y2) const;

};



#endif //DYN_SYS_RUNGEKUTTAMETHOD_H
