#ifndef DYN_SYS_WINDOW_H
#define DYN_SYS_WINDOW_H

#include "wx/wx.h"

#include "XYChart.h"




class MainWindow: public wxFrame
{
	XYChart* m_pFirstXYChart;
	XYChart* m_pY1_XYChart;
	XYChart* m_pY2_XYChart;

	wxStaticText* m_pStatPointText;



public:
	MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
	~MainWindow();
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSavePlot(wxCommandEvent& event);

	void OnShowY1Plot(wxCommandEvent& event);
	void OnShowY2Plot(wxCommandEvent& event);
	void OnShowY1Y2Plot(wxCommandEvent& event);


public:


	void RedrawFirstChart(mpFXY* function)
	{
		m_pFirstXYChart->ChangeDataset(function);
	}

	void RedrawY1Chart(mpFXY* function)
	{
		m_pY1_XYChart->ChangeDataset(function);
	}

	void RedrawY2Chart(mpFXY* function)
	{
		m_pY2_XYChart->ChangeDataset(function);
	}

	void ClearChart()
	{
		m_pFirstXYChart->Clear();
		m_pY2_XYChart->Clear();
		m_pY1_XYChart->Clear();
	}

	void SavePlotScreenshot(wxString const& filename)
	{
		if(m_pFirstXYChart->IsShown())
			m_pFirstXYChart->SaveScreenshot(filename);
		else if(m_pY1_XYChart->IsShown())
			m_pY1_XYChart->SaveScreenshot(filename);
		else
			m_pY2_XYChart->SaveScreenshot(filename);
	}

	void SetStatPoint(double y1, double y2)
	{
		wxString str = wxString::Format(wxT("Stationary point:\ny1 = %f\ny2 = %f"), y1, y2);
		m_pStatPointText->SetLabel(str);
	}


	void ErrorDialog()
	{
		wxMessageDialog errorDialog(this, "ERROR!", wxMessageBoxCaptionStr);
		errorDialog.ShowModal();
	}


	wxDECLARE_EVENT_TABLE();
};
enum ID
{
	ID_RECALCULATE,
	ID_E1_BOX,
	ID_E2_BOX,
	ID_R_BOX,
	ID_V0_BOX,
	ID_C_BOX,
	ID_EPS_BOX,
	ID_TN_BOX,
	ID_TK_BOX,
	ID_N_BOX,
	ID_CLEAR,
	ID_SCREENSHOT,
	ID_SHOW_Y1_PLOT,
	ID_SHOW_Y2_PLOT,
	ID_SHOW_Y1Y2_PLOT,
	ID_LIST_BOX
};





#endif //DYN_SYS_WINDOW_H
