#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Black_and_white_basic_genes.h"
#include <time.h>
#include "Controller.h"

#include <wx/wxprec.h>
#include "myImageGridCellRenderer.h"
#include "myColoredImageGridCellRenderer.h"
#include "mySlider.h"

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
    wxGrid* frozenGrid;
    std::vector<mySlider*> sliders;
    wxButton* evaluate;
    wxStaticText* TextGeneration;
    wxButton* unfreeze;
    wxStaticText* TextPopIndividual;
    wxTextCtrl*  popIndividual;
    wxStaticText* TextFrozenIndividual;
    wxTextCtrl* frozenIndividual;

    int generation;
    int population_size;

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnStart(wxCommandEvent& event);
    void OnEvaluate(wxCommandEvent& event);
    void OnUnfreeze(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1,
    START = 101,
    IN_POP_SIZE = 102,
    IN_DEPTH = 103,
    EVALUATE = 104,
    UNFREEZE = 105,
    IN_POP_IND = 106,
    IN_FR_IND = 107,
    COLOR_SELECTION = 108,
    IN_SLIDER = 109,
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
    this->TextCtrl1 = new wxTextCtrl(this, IN_POP_SIZE, _("20"), wxPoint(115, 25), wxSize(30, 20), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    this->Text2 = new wxStaticText(this, wxID_ANY, _("Individual depth: "), wxPoint(10, 60), wxSize(100, 30), 0, _T("ID_TEXT2"));
    this->TextCtrl2 = new wxTextCtrl(this, IN_DEPTH, _("2"), wxPoint(115, 55), wxSize(30, 20), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    this->CheckBox = new wxCheckBox(this, COLOR_SELECTION, _("Generate colored Images"), wxPoint(10, 90), wxSize(200, 30), 0, wxDefaultValidator, _T("ID_CHECKBOX"));

    new wxButton(this, START, _T("Start"), wxPoint(10, 120), wxSize(80, 30));

    Bind(wxEVT_MENU, &InitialFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &InitialFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &InitialFrame::OnStart, this, START);
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

    grid = new wxGrid(this, wxID_ANY, wxPoint(130, 130), wxSize(5*205, population_size / 5 * 205));


    if (this->CheckBox->IsChecked()) {
        grid->SetDefaultRenderer(new myColoredImageGridCellRenderer(population_size, images, 5));
    }
    else {
        grid->SetDefaultRenderer(new myImageGridCellRenderer(population_size, images, 5));
    }
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
    
    if (sliders.size() == population_size) {
        for (int i = 0; i < population_size; i++) {
            sliders[i]->setGrid(grid);
        }
    }
    else {

        for (int i = 0; i < population_size; i++) {
            new wxStaticText(this, wxID_ANY, _(std::to_string(i)), wxPoint(10, 155 + 30 * i), wxSize(20, 20), 0, _T("ID_TEXTI"));
            mySlider* slider = new mySlider(this, IN_SLIDER + i, 1, 1, 10, wxPoint(25, 150 + 30 * i), wxSize(100, 30), wxSL_HORIZONTAL, wxDefaultValidator, _T("ID_SLIDER"), grid, i);
            sliders.push_back(slider);
        }
    }
    

    evaluate = new wxButton(this, EVALUATE, _T("Evaluate"), wxPoint(10, 150+30*population_size), wxSize(80, 30));
    Bind(wxEVT_BUTTON, &InitialFrame::OnEvaluate, this, EVALUATE);

    new wxStaticText(this, wxID_ANY, _("Current\ngeneration: "), wxPoint(10, 200 + 30 * population_size), wxSize(60, 60), 0, _T("ID_TEXTGEN"));
    TextGeneration = new wxStaticText(this, wxID_ANY, _(std::to_string(generation)), wxPoint(100, 215 + 30 * population_size), wxSize(30, 20), 0, _T("ID_TEXTGEN"));

    //grid for frozen individuals

    frozenGrid = new wxGrid(this, wxID_ANY, wxPoint(200 + 5*205, 130), wxSize(2 * 205, 3 * 205));

    frozenGrid->CreateGrid(3,2);
    for (int i = 0; i < 2; i++) {
        frozenGrid->SetColSize(i, 205);
    }
    for (int i = 0; i < 3; i++) {
        frozenGrid->SetRowSize(i, 205);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            frozenGrid->SetReadOnly(j, i);
        }
    }

    frozenGrid->SetRowLabelSize(0);
    frozenGrid->SetColLabelSize(0);

    frozenGrid->DisableFocusFromKeyboard();
    frozenGrid->DisableDragCell();
    frozenGrid->DisableCellEditControl();
    frozenGrid->DisableDragGridSize();

    unfreeze = new wxButton(this, UNFREEZE, _T("Unfreeze"), wxPoint(100 + 5 * 205 + 102, 150 + 3 * 205), wxSize(80, 30));
    TextPopIndividual = new wxStaticText(this, wxID_ANY, _("Pop. ind."), wxPoint(100 + 5 * 205 + 102 + 100, 150 + 3 * 205), wxSize(60, 20), 0, _T("ID_TEXTPOPIND"));
    popIndividual = new wxTextCtrl(this, IN_POP_IND, _("0"), wxPoint(100 + 5 * 205 + 102 + 180, 150 + 3 * 205), wxSize(30, 20), 0, wxDefaultValidator, _T("ID_TEXTCTRLPOP"));
    TextFrozenIndividual = new wxStaticText(this, wxID_ANY, _("Frozen Ind."), wxPoint(100 + 5 * 205 + 102 + 100, 150 + 3 * 205 + 30), wxSize(60, 20), 0, _T("ID_TEXTFROZIND"));
    frozenIndividual = new wxTextCtrl(this, IN_FR_IND, _("0"), wxPoint(100 + 5 * 205 + 102 + 180, 150 + 3 * 205 + 30), wxSize(30, 20), 0, wxDefaultValidator, _T("ID_TEXTCTRLFR"));
    Bind(wxEVT_BUTTON, &InitialFrame::OnUnfreeze, this, UNFREEZE);
}

void InitialFrame::OnEvaluate(wxCommandEvent& event)
{
    std::vector<int> fitness_values;
    for (int i = 0; i < population_size; i++) {
        fitness_values.push_back(sliders[i]->GetValue());
        sliders[i]->SetValue(1);
    }
    if (this->CheckBox->IsChecked() && !controller.getColor()) {
        controller.changeGenes();
    }
    controller.evaluate(fitness_values);
    std::vector<Image> images = controller.generateImages();
    if (this->CheckBox->IsChecked()) {
        grid->SetDefaultRenderer(new myColoredImageGridCellRenderer(population_size, images, 5));
    }
    else {
        grid->SetDefaultRenderer(new myImageGridCellRenderer(population_size, images, 5));
    }
    grid->ForceRefresh();

    //only if a 10 was assigned refresh the frozen grid
    for (int i = 0; i < population_size; i++) {
        if (fitness_values[i] == 10) {
            std::vector<Image> frozen_images = controller.getFrozenImages();
            if (this->CheckBox->IsChecked()) {
                frozenGrid->SetDefaultRenderer(new myColoredImageGridCellRenderer(controller.getNFrozenImages(), frozen_images, 2));
            }
            else {
                frozenGrid->SetDefaultRenderer(new myImageGridCellRenderer(controller.getNFrozenImages(), frozen_images, 2));
            }
            frozenGrid->ForceRefresh();
            break;
        }
    }

    generation++;
    TextGeneration->SetLabel(std::to_string(generation));
    TextGeneration->Refresh();
}

void InitialFrame::OnUnfreeze(wxCommandEvent& event) {
    int pop = atoi(this->popIndividual->GetValue());
    int frozen = atoi(this->frozenIndividual->GetValue());
    controller.unfreeze(pop, frozen);
    //refresh grid
    std::vector<Image> images = controller.getTempImages();
    if (this->CheckBox->IsChecked()) {
        grid->SetDefaultRenderer(new myColoredImageGridCellRenderer(population_size, images, 5));
    }
    else {
        grid->SetDefaultRenderer(new myImageGridCellRenderer(population_size, images, 5));
    }
    grid->ForceRefresh();
}