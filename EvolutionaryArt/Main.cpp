#include <iostream>
#include "Individual.h"
#include "Genes.h"
#include "Black_and_white_basic_genes.h"
#include <time.h>
#include "Main.h"
#include "Controller.h"
#include "EvolutionFrame.h"

// wxWidgets "Hello World" Program
#include <wx/wxprec.h>

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

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnStart(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1,
    START = 101,
    IN_POP_SIZE = 102,
    IN_DEPTH = 103,
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
    this->TextCtrl1 = new wxTextCtrl(this, IN_POP_SIZE, _("1"), wxPoint(120, 30), wxSize(30, 30), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    this->Text2 = new wxStaticText(this, wxID_ANY, _("Individual depth: "), wxPoint(10, 60), wxSize(100, 30), 0, _T("ID_TEXT2"));
    this->TextCtrl2 = new wxTextCtrl(this, IN_DEPTH, _("1"), wxPoint(120, 60), wxSize(30, 30), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    
    new wxButton(this, START, _T("Start"), wxPoint(10, 90), wxSize(80, 30));

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
    int population_size = atoi(this->TextCtrl1->GetValue());
    int depth = atoi(this->TextCtrl2->GetValue());
    this->controller = Controller(population_size, depth);
    controller.generateImages();
    wxLogMessage("banana " + this->TextCtrl1->GetValue());
    //show other frame
    //EvolutionFrame* eframe = new EvolutionFrame();
    //eframe->Show(true);
}