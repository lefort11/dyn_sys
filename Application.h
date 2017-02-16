#ifndef DYN_SYS_APPLICATION_H
#define DYN_SYS_APPLICATION_H

#include <wx/wx.h>
#include "GUI/Window.h"
#include "Solver/CultureEvolutionModel.h"
#include "Solver/RungeKuttaMethod.h"


class Application: public wxApp
{
	MainWindow* m_pFrame;

	std::vector<double> firstSolution, secondSolution;

	double m_A1, m_A2, m_B1, m_B2, m_eps, m_Tn, m_Tk;
	unsigned m_N;

public:
	Application();

	~Application();

	virtual bool OnInit();

	void OnCalculate(wxCommandEvent& event);

	void OnClear(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

private:

	void OnA1TextChanged(wxCommandEvent& event);
	void OnA2TextChanged(wxCommandEvent& event);
	void OnB1TextChanged(wxCommandEvent& event);
	void OnB2TextChanged(wxCommandEvent &event);
	void OnTnTextChanged(wxCommandEvent& event);
	void OnTkTextChanged(wxCommandEvent& event);
	void OnEpsTextChanged(wxCommandEvent& event);
	void OnNTextChanged(wxCommandEvent& event);
};



#endif //DYN_SYS_APPLICATION_H
