#include "Window.h"
#include <wx/wfstream.h>



wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
				EVT_MENU(wxID_EXIT,  MainWindow::OnExit)
				EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
				EVT_BUTTON(wxID_EXIT, MainWindow::OnExit)
				EVT_BUTTON(ID_SCREENSHOT, MainWindow::OnSavePlot)
				EVT_BUTTON(ID_SHOW_Y1_PLOT, MainWindow::OnShowY1Plot)
				EVT_BUTTON(ID_SHOW_Y2_PLOT, MainWindow::OnShowY2Plot)
				EVT_BUTTON(ID_SHOW_Y1Y2_PLOT, MainWindow::OnShowY1Y2Plot)
wxEND_EVENT_TABLE()




MainWindow::MainWindow(wxString const& title, wxPoint const& pos, wxSize const& size)
		: wxFrame(nullptr, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),
		  m_pFirstXYChart(nullptr), m_pStatPointText(nullptr),
		  m_pY1_XYChart(nullptr), m_pY2_XYChart(nullptr)

{

#define X(a) size.x * a / 800
#define Y(a) size.y * a / 600

	auto pInputPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(size.x/3, size.y));
	pInputPanel->Show(true);

	auto pMenuBar = new wxMenuBar;
	SetMenuBar( pMenuBar );


	auto inputText = new wxStaticText(pInputPanel, wxID_ANY, wxT("Input"), wxPoint(X(90), Y(10)),
									  wxSize(X(30), Y(30)));
	inputText->Show(true);

	auto a1Text = new wxStaticText(pInputPanel, wxID_ANY, wxT("A1"), wxPoint(X(50), Y(60)),
								   wxSize(X(30), Y(30)));
	a1Text->Show(true);

	auto b1Text = new wxStaticText(pInputPanel, wxID_ANY, wxT("B1"), wxPoint(X(130), Y(60)),
								   wxSize(X(30), Y(30)));
	b1Text->Show(true);

	auto a2Text = new wxStaticText(pInputPanel, wxID_ANY, wxT("A2"), wxPoint(X(50), Y(130)),
								   wxSize(X(30), Y(30)));
	a2Text->Show(true);

	auto b2Text = new wxStaticText(pInputPanel, wxID_ANY, wxT("B2"), wxPoint(X(130), Y(130)),
								   wxSize(X(30), Y(30)));
	b2Text->Show(true);


	auto a1Box = new wxTextCtrl(pInputPanel, ID_A1_BOX, "0", wxPoint(X(40), Y(80)),
								wxSize(X(60), Y(20)));
	a1Box->Show(true);

	auto b1Box = new wxTextCtrl(pInputPanel, ID_B1_BOX, "0", wxPoint(X(120), Y(80)), wxSize(X(60), Y(20)));
	b1Box->Show(true);

	auto a2Box = new wxTextCtrl(pInputPanel, ID_A2_BOX, "0", wxPoint(X(40), Y(150)), wxSize(X(60), Y(20)));
	a2Box->Show(true);

	auto b2Box = new wxTextCtrl(pInputPanel, ID_B2_BOX, "0", wxPoint(X(120), Y(150)), wxSize(X(60), Y(20)));
	b2Box->Show(true);

	auto epsText = new wxStaticText(pInputPanel, wxID_ANY, wxT("Eps"), wxPoint(X(95), Y(200)), wxSize(X(30), Y(30)));
	epsText->Show(true);

	auto epsBox = new wxTextCtrl(pInputPanel, ID_EPS_BOX, "0", wxPoint(X(80), Y(220)), wxSize(X(60), Y(20)));
	epsBox->Show(true);

	auto tnText = new wxStaticText(pInputPanel, wxID_ANY, wxT("Tn"), wxPoint(X(50), Y(270)), wxSize(X(30), Y(30)));
	tnText->Show(true);
	auto tkText = new wxStaticText(pInputPanel, wxID_ANY, wxT("Tk"), wxPoint(X(130), Y(270)), wxSize(X(30), Y(30)));
	tkText->Show(true);
	auto tnBox = new wxTextCtrl(pInputPanel, ID_TN_BOX, "0", wxPoint(X(40), Y(290)), wxSize(X(60), Y(20)));
	tnBox->Show(true);
	tnBox->Enable(false);

	auto tkBox = new wxTextCtrl(pInputPanel, ID_TK_BOX, "0", wxPoint(X(120), Y(290)), wxSize(X(60), Y(20)));
	tkBox->Show(true);

	auto NText = new wxStaticText(pInputPanel, wxID_ANY, wxT("N"), wxPoint(X(95), Y(340)), wxSize(X(60), Y(30)));
	NText->Show(true);
	auto NBox = new wxTextCtrl(pInputPanel, ID_N_BOX, "0", wxPoint(80, 360), wxSize(60, 20));
	NBox->Show(true);

	auto calcButton = new wxButton(this, ID_RECALCULATE, wxT("Calculate"), wxPoint(X(40), Y(500)), wxSize(X(140),Y(30)));
	calcButton->Show(true);

	auto clearButton = new wxButton(this, ID_CLEAR, wxT("Clear"), wxPoint(X(40), Y(520)), wxSize(X(140),Y(30)));
	clearButton->Show(true);

	auto pExitButton = new wxButton(this, wxID_EXIT, "Exit", wxPoint(X(40), Y(540)),
									wxSize(X(140), Y(30)));
	pExitButton->Show(true);

	auto screenshotButton = new wxButton(this, ID_SCREENSHOT, wxT("Save plot"), wxPoint(X(500), Y(500)),
																						wxSize(X(100), Y(30)));
	screenshotButton->Show(true);

	auto showY1Plot = new wxButton(this, ID_SHOW_Y1_PLOT, wxT("y1(t) plot"), wxPoint(X(350), Y(520)),
								   wxSize(X(100), Y(30)));
	showY1Plot->Show(true);

	auto showY2Plot = new wxButton(this, ID_SHOW_Y2_PLOT, wxT("y2(t) plot"), wxPoint(X(500), Y(520)),
								   wxSize(X(100), Y(30)));
	showY2Plot->Show(true);

	auto showY1Y2Plot = new wxButton(this, ID_SHOW_Y1Y2_PLOT, wxT("y1, y2 plot"), wxPoint(X(650), Y(520)),
								   wxSize(X(100), Y(30)));
	showY1Y2Plot->Show(true);


	m_pStatPointText = new wxStaticText(this, wxID_ANY, wxT("Stationary Point:\ny1 = undefined\ny2 = undefined"),
										wxPoint(X(45), Y(390)));


	m_pFirstXYChart = new XYChart(this, nullptr, wxPoint(X(300), Y(0)), wxSize(X(500), X(500)), "y1", "y2");
	m_pY1_XYChart = new XYChart(this, nullptr, wxPoint(X(300), Y(0)), wxSize(X(500), X(500)), "t", "y1");
	m_pY2_XYChart = new XYChart(this, nullptr, wxPoint(X(300), Y(0)), wxSize(X(500), X(500)), "t", "y2");
	m_pY1_XYChart->Show(false);
	m_pY2_XYChart->Show(false);



	Centre();

}

MainWindow::~MainWindow()
{}

void MainWindow::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Close( true );
}
void MainWindow::OnAbout(wxCommandEvent& event)
{
	wxMessageBox( wxEmptyString,
				  wxEmptyString, wxOK | wxICON_INFORMATION );
}

void MainWindow::OnSavePlot(wxCommandEvent& event)
{
	wxFileDialog saveDialog(this, wxT("Choose save path"), "Documents", "Plot",
									  "BMP files (*.bmp)|*.bmp", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if(saveDialog.ShowModal() == wxID_CANCEL)
		return;
	saveDialog.Show(true);

	wxFileOutputStream outputStream(saveDialog.GetPath());
	if(!outputStream.IsOk())
	{
		wxLogError("Cannot save current contents in file '%s'.", saveDialog.GetPath());
		return;
	}

	SavePlotScreenshot(saveDialog.GetPath());
}

void MainWindow::OnShowY1Plot(wxCommandEvent &event)
{
	m_pFirstXYChart->Show(false);
	m_pY2_XYChart->Show(false);
	m_pY1_XYChart->Show(true);
}

void MainWindow::OnShowY2Plot(wxCommandEvent &event)
{
	m_pFirstXYChart->Show(false);
	m_pY1_XYChart->Show(false);
	m_pY2_XYChart->Show(true);
}
void MainWindow::OnShowY1Y2Plot(wxCommandEvent &event)
{
	m_pY2_XYChart->Show(false);
	m_pY1_XYChart->Show(false);
	m_pFirstXYChart->Show(true);

}

