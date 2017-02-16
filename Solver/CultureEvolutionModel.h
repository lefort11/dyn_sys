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

class CultureEvolutionModel: public Model
{
	double m_A1, m_A2, m_B1, m_B2;


public:
	CultureEvolutionModel(double A1, double A2, double B1, double B2, double y1_0, double y2_0):
			Model(y1_0, y2_0),
			m_A1(A1), m_A2(A2), m_B1(B1), m_B2(B2)
	{
		m_f1 = [A1, B1](double t, double y1, double y2)
		{
			return y1 * (A1 * y2 - B1);
		};

		m_f2 = [A2, B2](double t, double y1, double y2)
		{
			return y2 * (A2 * y1 - B2);
		};
	}

	~CultureEvolutionModel()
	{}



};


#endif //DYN_SYS_CULTUREEVOLUTIONMODEL_H
