#ifndef DYN_SYS_CULTUREEVOLUTIONMODEL_H
#define DYN_SYS_CULTUREEVOLUTIONMODEL_H


#include <functional>

class Model
{
protected:

	std::function<double(double, double, double)> m_f1, m_f2;

	double m_Y1_0, m_Y2_0;


public:

	Model(double y1_0, double y2_0):
	m_f1(nullptr), m_f2(nullptr), m_Y1_0(y1_0), m_Y2_0(y2_0)
	{}

	Model(std::function<double(double, double, double)> f1, std::function<double(double, double, double)> f2,
		  double y1_0, double y2_0):
			m_f1(f1), m_f2(f2), m_Y1_0(y1_0), m_Y2_0(y2_0)
	{}

	virtual ~Model()
	{}

	virtual std::function<double(double, double, double)> GetF1() const
	{
		return m_f1;
	}

	virtual std::function<double(double, double, double)> GetF2() const
	{
		return m_f2;
	}

	virtual double GetY1_0() const
	{
		return m_Y1_0;
	}

	virtual double GetY2_0() const
	{
		return m_Y2_0;
	}

};

class TrophicChainModel: public Model
{
	double m_E1, m_R, m_E2, m_V0, m_C;


public:
	TrophicChainModel(double E1, double E2, double R, double V0, double C, double y1_0, double y2_0):
			Model(y1_0, y2_0),
			m_E1(E1), m_E2(E2), m_R(R), m_V0(V0), m_C(C)
	{
		m_f1 = [E1, V0, R, C](double t, double y1, double y2)
		{
			return y1 * (-E1 + V0 * (C - y1 - y2) - y2/(R+y1));
		};

		m_f2 = [E2, R](double t, double y1, double y2)
		{
			return y2 * (-E2 + y1/(R+y1));
		};
	}

	~TrophicChainModel()
	{}


};



#endif //DYN_SYS_CULTUREEVOLUTIONMODEL_H
