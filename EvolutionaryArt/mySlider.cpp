#include "mySlider.h"

mySlider::mySlider(wxWindow* parent, wxWindowID id, int value, int minValue, int maxValue, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name, wxGrid* grid, int i) {
	this->Create(parent, id, value, minValue, maxValue, pos, size, style, validator, name);
	this->grid = grid;
	this->i = i;
}

void mySlider::OnMouseOver(wxMouseEvent& event) {
	this->grid->SetCellBackgroundColour(i / 5, i % 5, *wxRED);
	this->grid->ForceRefresh();
}

void mySlider::OnMouseOut(wxMouseEvent& event) {
	this->grid->SetCellBackgroundColour(i / 5, i % 5, *wxWHITE);
	this->grid->ForceRefresh();
}

BEGIN_EVENT_TABLE(mySlider, wxSlider)
	EVT_ENTER_WINDOW(mySlider::OnMouseOver)
	EVT_LEAVE_WINDOW(mySlider::OnMouseOut)
END_EVENT_TABLE()