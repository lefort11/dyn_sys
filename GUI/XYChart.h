//
// Created by Gleb Plaksin on 15.02.17.
//

#ifndef DYN_SYS_XYCHART_H
#define DYN_SYS_XYCHART_H

#include <mathplot.h>


class XYChart
{
	mpWindow* m_pPlot;

public:
	XYChart(wxWindow* parent, mpFXY* function, wxPoint const& pos = wxDefaultPosition,
			wxSize const& size = wxDefaultSize, wxString const& xName = wxEmptyString,
			wxString const& yName = wxEmptyString);

	~XYChart();


	void ChangeDataset(mpFXY* function);

	void Clear();

	void SaveScreenshot(wxString const& fileName);

	void Show(bool);

	bool IsShown() const;

};


#endif //DYN_SYS_XYCHART_H
