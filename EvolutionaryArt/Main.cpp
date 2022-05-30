#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Black_and_white_basic_genes.h"
#include <time.h>
#include "Main.h"
#include "Controller.h"

#include <wx/wxprec.h>
#include "myImageGridCellRenderer.h"
#include "myColoredImageGridCellRenderer.h"

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
    wxCheckBox* CheckBox;
    wxGrid* grid;
    std::vector<wxSlider*> sliders;
    wxButton* evaluate;
    wxStaticText* TextGeneration;

    int generation;
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
    COLOR_SELECTION = 105,
    IN_SLIDER = 106,
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
    this->TextCtrl2 = new wxTextCtrl(this, IN_DEPTH, _("2"), wxPoint(120, 60), wxSize(30, 30), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    this->CheckBox = new wxCheckBox(this, COLOR_SELECTION, _("Generate colored Images"), wxPoint(10, 90), wxSize(200, 30), 0, wxDefaultValidator, _T("ID_CHECKBOX"));

    new wxButton(this, START, _T("Start"), wxPoint(10, 120), wxSize(80, 30));

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
    generation = 0;
    population_size = atoi(this->TextCtrl1->GetValue());
    int depth = atoi(this->TextCtrl2->GetValue());
    this->controller = Controller(population_size, depth, this->CheckBox->IsChecked());
    std::vector<Image> images = controller.generateImages();

    grid = new wxGrid(this, wxID_ANY, wxPoint(130, 130), wxSize(1000, 800));


    if (this->CheckBox->IsChecked()) {
        grid->SetDefaultRenderer(new myColoredImageGridCellRenderer(population_size, images));
    }
    else {
        grid->SetDefaultRenderer(new myImageGridCellRenderer(population_size, images));
    }
    //grid->SetCellRenderer(0, 0, new myImageGridCellRenderer);
    grid->SetRowLabelSize(0);
    grid->SetColLabelSize(0);

    grid->DisableFocusFromKeyboard();
    grid->DisableDragCell();
    grid->DisableCellEditControl();
    grid->DisableDragGridSize();

    grid->CreateGrid(population_size/5, 5); 
    for (int i = 0; i < 5; i++) {
        grid->SetColSize(i, 205);
    }
    for (int i = 0; i < population_size / 5; i++) {
        grid->SetRowSize(i, 205);
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < population_size / 5; j++) {
            grid->SetReadOnly(j, i);
        }
    }
    /*
    int img_size = 200;
    for (int i = 0; i < 5; i++) { //col
        for (int j = 0; j < population_size / 5; j++) { //row
            wxSlider* slider = new wxSlider(this, IN_SLIDER + i, 5, 1, 10, wxPoint((j+1)*img_size + 10, (10+img_size)*i), wxSize(100, 30), wxSL_HORIZONTAL, wxDefaultValidator, _T("ID_SLIDER"));
            sliders.push_back(slider);
        }
    }
    */
    
    for (int i = 0; i < population_size; i++) {
        new wxStaticText(this, wxID_ANY, _(std::to_string(i)), wxPoint(10, 155+30*i), wxSize(20, 20), 0, _T("ID_TEXTI"));
        wxSlider* slider = new wxSlider(this, IN_SLIDER+i, 5, 1, 10, wxPoint(25, 150+30*i), wxSize(100, 30), wxSL_HORIZONTAL, wxDefaultValidator, _T("ID_SLIDER"));
        sliders.push_back(slider);
    }
    

    evaluate = new wxButton(this, EVALUATE, _T("Evaluate"), wxPoint(10, 150+30*population_size), wxSize(80, 30));
    Bind(wxEVT_BUTTON, &InitialFrame::OnEvaluate, this, EVALUATE);

    new wxStaticText(this, wxID_ANY, _("Current\ngeneration: "), wxPoint(10, 200 + 30 * population_size), wxSize(60, 60), 0, _T("ID_TEXTGEN"));
    TextGeneration = new wxStaticText(this, wxID_ANY, _(std::to_string(generation)), wxPoint(100, 215 + 30 * population_size), wxSize(30, 20), 0, _T("ID_TEXTGEN"));
}

void InitialFrame::OnEvaluate(wxCommandEvent& event)
{
    std::vector<int> fitness_values;
    for (int i = 0; i < population_size; i++) {
        fitness_values.push_back(sliders[i]->GetValue());
        sliders[i]->SetValue(5);
    }
    if (this->CheckBox->IsChecked() && !controller.getColor()) {
        controller.changeGenes();
    }
    controller.evaluate(fitness_values);
    std::vector<Image> images = controller.generateImages();
    if (this->CheckBox->IsChecked()) {
        grid->SetDefaultRenderer(new myColoredImageGridCellRenderer(population_size, images));
    }
    else {
        grid->SetDefaultRenderer(new myImageGridCellRenderer(population_size, images));
    }
    grid->ForceRefresh();

    generation++;
    TextGeneration->SetLabel(std::to_string(generation));
    TextGeneration->Refresh();
}