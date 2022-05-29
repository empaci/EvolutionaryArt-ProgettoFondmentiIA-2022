#include "myImageGridCellRenderer.h"
#include "Image.h"

myImageGridCellRenderer::myImageGridCellRenderer(int n_images, std::vector<Image> images) {
	this->n_images = n_images;
	this->images = images;
}

void myImageGridCellRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected){
	
	wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	//wxImage cellImage;
	//cellImage.AddHandler(new wxPNMHandler);
	int p = 0;

	p = col + row * 5;

	std::vector<std::vector<int>> img = this->images[p].getPhenotype();

	unsigned char* buffer = static_cast<unsigned char*>(malloc(200*200*3));
	unsigned char*ptr = buffer;

	for (int y = 0; y < 200; ++y)
		for (int x = 0; x < 200; ++x) {
			unsigned char c = (unsigned char)img[x][y];
			*(ptr++) = c;
			*(ptr++) = c;
			*(ptr++) = c;
		}
		//*(++ptr) = static_cast<unsigned char>(img[x][y]);

	wxImage* cellImage = new wxImage(200, 200, buffer, true);

	wxBitmap cellBitmap(*cellImage);
	dc.DrawBitmap(cellBitmap, rect.x, rect.y);

	//free(buffer);
	//delete(cellImage);
}