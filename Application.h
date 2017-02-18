#ifndef DYN_SYS_APPLICATION_H
#define DYN_SYS_APPLICATION_H

#include <wx/wx.h>
#include "GUI/Window.h"
#include "Solver/TrophicChainModel.h"
#include "Solver/RungeKuttaMethod.h"


class Application: public wxApp
{
	MainWindow* m_pFrame;

	std::vector<double> firstSolution, secondSolution;

	double m_E1, m_R, m_E2, m_V0, m_eps, m_Tn, m_Tk, m_C;
	unsigned m_N;

	wxColour m_Color;

public:
	Application();

	~Application();

	virtual bool OnInit();


	wxDECLARE_EVENT_TABLE();

private:

	void OnE1TextChanged(wxCommandEvent &event);
	void OnRTextChanged(wxCommandEvent &event);
	void OnE2TextChanged(wxCommandEvent &event);
	void OnV0TextChanged(wxCommandEvent &event);
	void OnTnTextChanged(wxCommandEvent& event);
	void OnTkTextChanged(wxCommandEvent& event);
	void OnEpsTextChanged(wxCommandEvent& event);
	void OnCTextChanged(wxCommandEvent& event);
	void OnNTextChanged(wxCommandEvent& event);
	void OnColorChanged(wxCommandEvent& event);
	void OnCalculate(wxCommandEvent& event);
	void OnClear(wxCommandEvent& event);




};



#endif //DYN_SYS_APPLICATION_H
