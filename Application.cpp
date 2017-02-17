#include "Application.h"


wxBEGIN_EVENT_TABLE(Application, wxApp)
				EVT_BUTTON(ID_RECALCULATE, Application::OnCalculate)
				EVT_BUTTON(ID_CLEAR, Application::OnClear)
				EVT_TEXT(ID_A1_BOX, Application::OnA1TextChanged)
				EVT_TEXT(ID_A2_BOX, Application::OnA2TextChanged)
				EVT_TEXT(ID_B1_BOX, Application::OnB1TextChanged)
				EVT_TEXT(ID_B2_BOX, Application::OnB2TextChanged)
				EVT_TEXT(ID_EPS_BOX, Application::OnEpsTextChanged)
				EVT_TEXT(ID_TN_BOX, Application::OnTnTextChanged)
				EVT_TEXT(ID_TK_BOX, Application::OnTkTextChanged)
				EVT_TEXT(ID_N_BOX, Application::OnNTextChanged)
wxEND_EVENT_TABLE()


Application::Application(): m_A1(0), m_A2(0), m_B1(0), m_B2(0), m_eps(0), m_Tn(0), m_Tk(0), m_N(0)
{}

Application::~Application()
{}


bool Application::OnInit()
{
	m_pFrame = new MainWindow( "Culture Evolution Model", wxPoint(50, 50), wxSize(800, 600) );
	m_pFrame->Show( true );
	m_pFrame->SetBackgroundColour(wxColour(220, 220, 220));

	return true;
}

void Application::OnCalculate(wxCommandEvent &event)
{
	if((m_A1 == 0) || (m_A2 == 0) || (m_B1 == 0) || (m_B2 == 0))
	{
		m_pFrame->ErrorDialog();
		return;
	}

	CultureEvolutionModel* ceModel = new CultureEvolutionModel(m_A1, m_A2, m_B1, m_B2,
															   m_B2 / m_A2 + m_eps,
															   m_B1 / m_A1 + m_eps);


	m_pFrame->SetStatPoint(m_B2/m_A2, m_B1/m_A1);

	auto rkMeth = new RungeKuttaMethod(m_N, m_Tn, m_Tk, ceModel);

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

void Application::OnA1TextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_A1);
}

void Application::OnA2TextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_A2);
}

void Application::OnB1TextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_B1);
}

void Application::OnB2TextChanged(wxCommandEvent &event)
{
	event.GetString().ToDouble(&m_B2);
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

