#ifndef MY_IMAGE_GRID_CELL_RENDERED_H
#define MY_IMAGE_GRID_CELL_RENDERED_H

#include <wx/wxprec.h>
#include <wx/grid.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class myImageGridCellRenderer : public wxGridCellStringRenderer {
    public:
        myImageGridCellRenderer(int);
        virtual void Draw(wxGrid&, wxGridCellAttr&, wxDC&, const wxRect&, int, int, bool);
    private:
        int n_images;
};

#endif
