#include "XYChart.h"

XYChart::XYChart(wxWindow* parent, mpFXY* function, const wxPoint &pos, const wxSize &size, wxString const& xName,
				 wxString const& yName)
{
	m_pPlot = new mpWindow(parent, wxID_ANY, pos, size);

	auto xAxis = new mpScaleX(xName, mpALIGN_BOTTOM, true, mpX_NORMAL);

	auto yAxis = new mpScaleY(yName, mpALIGN_LEFT, true);

	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	xAxis->SetFont(graphFont);
	yAxis->SetFont(graphFont);
	xAxis->SetDrawOutsideMargins(false);
	yAxis->SetDrawOutsideMargins(false);

	m_pPlot->SetMargins(30, 30, 50, 100);

	m_pPlot->AddLayer(xAxis);
	m_pPlot->AddLayer(yAxis);

	m_pPlot->AddLayer(function);


	m_pPlot->EnableDoubleBuffer(true);
	m_pPlot->EnableMousePanZoom(true);
	m_pPlot->SetMPScrollbars(false);

	m_pPlot->Fit();

}

XYChart::~XYChart()
{
	wxDELETE(m_pPlot);
}

void XYChart::ChangeDataset(mpFXY* function)
{
	m_pPlot->AddLayer(function);
	m_pPlot->Fit();
	m_pPlot->Update();

}

void XYChart::Clear()
{
	for(int i = m_pPlot->CountAllLayers() - 1; i >= 2; --i)
	{
		m_pPlot->DelLayer(m_pPlot->GetLayer(i));
	}
}


void XYChart::SaveScreenshot(wxString const &fileName)
{
	m_pPlot->SaveScreenshot(fileName, wxBITMAP_TYPE_BMP, wxDefaultSize, true);
}

void XYChart::Show(bool shw)
{
	m_pPlot->Show(shw);
}

bool XYChart::IsShown() const
{
	return m_pPlot->IsShown();
}