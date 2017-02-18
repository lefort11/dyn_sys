#include "Application.h"


wxBEGIN_EVENT_TABLE(Application, wxApp)
				EVT_BUTTON(ID_RECALCULATE, Application::OnCalculate)
				EVT_BUTTON(ID_CLEAR, Application::OnClear)
				EVT_TEXT(ID_E1_BOX, Application::OnE1TextChanged)
				EVT_TEXT(ID_R_BOX, Application::OnRTextChanged)
				EVT_TEXT(ID_E2_BOX, Application::OnE2TextChanged)
				EVT_TEXT(ID_V0_BOX, Application::OnV0TextChanged)
				EVT_TEXT(ID_C_BOX, Application::OnCTextChanged)
				EVT_TEXT(ID_EPS_BOX, Application::OnEpsTextChanged)
				EVT_TEXT(ID_TN_BOX, Application::OnTnTextChanged)
				EVT_TEXT(ID_TK_BOX, Application::OnTkTextChanged)
				EVT_TEXT(ID_N_BOX, Application::OnNTextChanged)
wxEND_EVENT_TABLE()


Application::Application(): m_E1(0), m_R(0), m_E2(0), m_V0(0), m_eps(0), m_Tn(0), m_Tk(0), m_N(0), m_C(0)
{}

Application::~Application()
{}


bool Application::OnInit()
{
	m_pFrame = new MainWindow( "Trophic Chain Model", wxPoint(50, 50), wxSize(800, 600) );
	m_pFrame->Show( true );
	m_pFrame->SetBackgroundColour(wxColour(220, 220, 220));

	return true;
}

void Application::OnCalculate(wxCommandEvent &event)
{
	if((m_E1 == 0) || (m_R == 0) || (m_E2 == 0) || (m_V0 == 0))
	{
		m_pFrame->ErrorDialog();
		return;
	}

	double y0_1 = m_E2 * m_R / (1 - m_E2);
	double y0_2 = (m_V0 * (m_C - y0_1) - m_E1) * (m_R + y0_1) / (m_V0 * (m_R + y0_1) + 1);

	TrophicChainModel* trophicChainModel = new TrophicChainModel(m_E1, m_E2, m_R, m_V0, m_C,
																 y0_1 + m_eps, y0_2 + m_eps);


	m_pFrame->SetStatPoint(y0_1, y0_2);

	auto rkMeth = new RungeKuttaMethod(m_N, m_Tn, m_Tk, trophicChainModel);

	std::vector<double> y1, y2;

	rkMeth->Solve(y1, y2);

	auto y1y2Func = new mpFXYVector();
	y1y2Func->SetData(y1, y2);
	y1y2Func->SetContinuity(true);
	wxPen vectorpen(*wxBLUE, 2, wxSOLID);
	y1y2Func->SetPen(vectorpen);
	y1y2Func->SetDrawOutsideMargins(false);

	m_pFrame->RedrawFirstChart(y1y2Func);

	std::vector<double> t(m_N + 1);
	for(int i = 0; i < m_N + 1; ++i)
	{
		t[i] = m_Tn + (m_Tk - m_Tn) / m_N * i;
	}
	auto y1tFunc = new mpFXYVector();
	y1tFunc->SetData(t, y1);
	y1tFunc->SetContinuity(true);
	y1tFunc->SetPen(vectorpen);
	y1tFunc->SetDrawOutsideMargins(false);
	m_pFrame->RedrawY1Chart(y1tFunc);

	auto y2tFunc = new mpFXYVector();
	y2tFunc->SetData(t, y2);
	y2tFunc->SetContinuity(true);
	y2tFunc->SetPen(vectorpen);
	y2tFunc->SetDrawOutsideMargins(false);
	m_pFrame->RedrawY2Chart(y2tFunc);


}

void Application::OnClear(wxCommandEvent &event)
{
	m_pFrame->ClearChart();
	if(!firstSolution.empty())
	{
		firstSolution.erase(firstSolution.begin(), firstSolution.end());
		secondSolution.erase(secondSolution.begin(), secondSolution.end());
	}
}

void Application::OnE1TextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_E1);
}

void Application::OnRTextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_R);
}

void Application::OnE2TextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_E2);
}

void Application::OnV0TextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_V0);
}

void Application::OnCTextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_C);
}

void Application::OnTkTextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_Tk);
}

void Application::OnTnTextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_Tn);
}

void Application::OnEpsTextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_eps);
}

void Application::OnNTextChanged(wxCommandEvent &event)
{
	m_N = static_cast<unsigned>(wxAtoi(event.GetString()));
}

