#include "myImageGridCellRendered.h"

myImageGridCellRenderer::myImageGridCellRenderer(int n_images) {
	this->n_images = n_images;
}

void myImageGridCellRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected){
	
	wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	wxImage cellImage;
	cellImage.AddHandler(new wxPNMHandler);
	
	if (cellImage.LoadFile(wxT("..\\Images\\test.ppm")))
	{
		wxBitmap cellBitmap(cellImage);
		dc.DrawBitmap(cellBitmap, rect.x, rect.y);
	}
	else
	{
		//wxLogError(_T("The myimage.jpg, in cell:\n row '%d', column '%d',\n didn't load, does it exist?"), row, col);
	}
}