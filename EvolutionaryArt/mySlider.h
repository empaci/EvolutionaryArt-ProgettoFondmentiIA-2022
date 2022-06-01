#ifndef MY_SLIDER_H
#define MY_SLIDER_H

#include <wx/wxprec.h>
#include <wx/slider.h>
#include <wx/Grid.h>
#include "Image.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class mySlider : public wxSlider {
public:
    mySlider(wxWindow*, wxWindowID, int, int, int, const wxPoint&, const wxSize&, long, const wxValidator&, const wxString&, wxGrid*, int);
    void setGrid(wxGrid*);

private:
    void OnMouseOver(wxMouseEvent&);
    void OnMouseOut(wxMouseEvent&);

    int i;
    wxGrid* grid;

    DECLARE_EVENT_TABLE()

};

#endif