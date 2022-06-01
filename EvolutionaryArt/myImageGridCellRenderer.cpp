#include "myImageGridCellRenderer.h"
#include "Image.h"

myImageGridCellRenderer::myImageGridCellRenderer(int n_images, std::vector<Image> images, int col_size) {
	this->n_images = n_images;
	this->images = images;
	this->col_size = col_size;
}

void myImageGridCellRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected){
	
	wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	int dim = 600;
	int p = 0;

	p = col + row * col_size;

	if (p < n_images) {

		std::vector<std::vector<int>> img = this->images[p].getPhenotype();

		unsigned char* buffer = static_cast<unsigned char*>(malloc(dim * dim * 3));
		unsigned char* ptr = buffer;

		for (int y = 0; y < dim; ++y)
			for (int x = 0; x < dim; ++x) {
				unsigned char c = (unsigned char)img[y][x];
				*(ptr++) = c;
				*(ptr++) = c;
				*(ptr++) = c;
			}

		wxImage* cellImage = new wxImage(dim, dim, buffer, true);

		cellImage->Rescale(200, 200, wxIMAGE_QUALITY_NORMAL);

		wxBitmap cellBitmap(*cellImage);
		dc.DrawBitmap(cellBitmap, rect.x, rect.y);
	}
	//free(buffer);
	//delete(cellImage);
}