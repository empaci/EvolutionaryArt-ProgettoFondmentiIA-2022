#include "myColoredImageGridCellRenderer.h"
#include "Image.h"

myColoredImageGridCellRenderer::myColoredImageGridCellRenderer(int n_images, std::vector<Image> images) {
	this->n_images = n_images;
	this->images = images;
}

void myColoredImageGridCellRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected) {

	wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	int dim = 200;
	int p = 0;

	p = col + row * 5;

	std::vector<std::vector<int>> img = this->images[p].getPhenotype();

	unsigned char* buffer = static_cast<unsigned char*>(malloc(dim * dim * 3));
	unsigned char* ptr = buffer;

	for (int y = 0; y < dim; ++y)
		for (int x = 0; x < dim*3; ++x) {
			unsigned char red = (unsigned char)img[y][x];
			unsigned char green = (unsigned char)img[y][++x];
			unsigned char blue = (unsigned char)img[y][++x];
			*(++ptr) = red;
			*(++ptr) = green;
			*(++ptr) = blue;
		}

	wxImage* cellImage = new wxImage(dim, dim, buffer, true);

	wxBitmap cellBitmap(*cellImage);
	dc.DrawBitmap(cellBitmap, rect.x, rect.y);

	//free(buffer);
	//delete(cellImage);
}