#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Black_and_white_basic_genes.h"
#include <time.h>
#include "Main.h"
#include "Controller.h"

#include <wx/wxprec.h>
#include "myImageGridCellRendered.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
private:
};

class InitialFrame : public wxFrame
{
public:
    InitialFrame();

protected:
    Controller controller;
    wxStaticText* Text1;
    wxTextCtrl* TextCtrl1;
    wxStaticText* Text2;
    wxTextCtrl* TextCtrl2;
    wxGrid* grid;
    std::vector<wxSlider*> sliders;
    wxButton* evaluate;

    int population_size;

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnStart(wxCommandEvent& event);
    void OnEvaluate(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1,
    START = 101,
    IN_POP_SIZE = 102,
    IN_DEPTH = 103,
    EVALUATE = 104,
    IN_SLIDER = 105,
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    InitialFrame* frame = new InitialFrame();
    frame->Show(true);
    return true;
}

InitialFrame::InitialFrame()
    : wxFrame(NULL, wxID_ANY, "Evolution Art")
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    this->Text1 = new wxStaticText(this, wxID_ANY, _("Population size: "), wxPoint(10, 30), wxSize(100, 30), 0, _T("ID_TEXT1"));
    this->TextCtrl1 = new wxTextCtrl(this, IN_POP_SIZE, _("20"), wxPoint(120, 30), wxSize(30, 30), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    this->Text2 = new wxStaticText(this, wxID_ANY, _("Individual depth: "), wxPoint(10, 60), wxSize(100, 30), 0, _T("ID_TEXT2"));
    this->TextCtrl2 = new wxTextCtrl(this, IN_DEPTH, _("4"), wxPoint(120, 60), wxSize(30, 30), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    
    new wxButton(this, START, _T("Start"), wxPoint(10, 90), wxSize(80, 30));

    Bind(wxEVT_MENU, &InitialFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &InitialFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &InitialFrame::OnStart, this, START);

    //grid = new wxGrid(this, wxID_ANY, wxPoint(10, 140), wxSize(800, 600));
    //grid->Fit(); // Set the parent frame client size to fit the grid 
    //this->SetClientSize(grid->GetSize());
}

void InitialFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void InitialFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a Evolutionary Art program",
        "About Evolutionary Art", wxOK | wxICON_INFORMATION);
}

void InitialFrame::OnStart(wxCommandEvent& event)
{
    population_size = atoi(this->TextCtrl1->GetValue());
    int depth = atoi(this->TextCtrl2->GetValue());
    this->controller = Controller(population_size, depth);
    controller.generateImages();
    //wxLogMessage("banana " + this->TextCtrl1->GetValue());

    //grid->SetDefaultRenderer(new myImageGridCellRenderer(population_size));
    //grid->SetCellRenderer(0, 0, new myImageGridCellRenderer);
    /*
    grid->CreateGrid(population_size/5, 5); 
    for (int i = 0; i < 5; i++) {
        grid->SetColSize(i, 320);
    }
    for (int i = 0; i < population_size / 5; i++) {
        grid->SetRowSize(i, 320);
    }
    */
    // We can specify that some cells are read-only 
    //grid->SetCellValue(0, 3, wxT("This is read-only")); grid->SetReadOnly(0, 3);

    for (int i = 0; i < population_size; i++) {
        wxSlider* slider = new wxSlider(this, IN_SLIDER+i, 5, 1, 10, wxPoint(10, 120+30*i), wxSize(100, 30), wxSL_HORIZONTAL, wxDefaultValidator, _T("ID_SLIDER"));
        sliders.push_back(slider);
    }

    evaluate = new wxButton(this, EVALUATE, _T("Evaluate"), wxPoint(10, 120+30*population_size), wxSize(80, 30));
    Bind(wxEVT_BUTTON, &InitialFrame::OnEvaluate, this, EVALUATE);
}

void InitialFrame::OnEvaluate(wxCommandEvent& event)
{
    std::vector<int> fitness_values;
    for (int i = 0; i < population_size; i++) {
        fitness_values.push_back(sliders[i]->GetValue());
        sliders[i]->SetValue(5);
    }
    controller.evaluate(fitness_values);
    controller.generateImages();
}