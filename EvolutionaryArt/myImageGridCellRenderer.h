#ifndef MY_IMAGE_GRID_CELL_RENDERER_H
#define MY_IMAGE_GRID_CELL_RENDERER_H

#include <wx/wxprec.h>
#include <wx/grid.h>
#include "Image.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class myImageGridCellRenderer : public wxGridCellStringRenderer {
    public:
        myImageGridCellRenderer(int, std::vector<Image>, int);
        virtual void Draw(wxGrid&, wxGridCellAttr&, wxDC&, const wxRect&, int, int, bool);
        void setImages(std::vector<Image>);
        void setNumImages(int);
    private:
        int n_images;
        std::vector<Image> images;
        int col_size;
};

#endif
