/*	
	PastaPaster v1.0
	A text-based application for storing all of your favorite quotes/conversation pieces
	Built using the cross-platform-friendly wxWidgets framework (v3.1.3)
	You may modify or distribute this application and its source as necessary
*/
#include "cMain.h"
#include <cstring>
#define PP_SAVEFILE "Pasta.txt"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnNewButtonClicked)
	EVT_BUTTON(10002, OnCopyButtonClicked)
	EVT_BUTTON(10003, OnDeleteButtonClicked)
	EVT_BUTTON(10003, OnEntryReselection)
	EVT_BUTTON(20001, OnSaveButtonClicked)
	EVT_BUTTON(20011, OnRenameButtonClicked)
	EVT_BUTTON(20012, OnCopyToClipboardButtonClicked)
	EVT_BUTTON(20013, OnUndoButtonClicked)
	EVT_LISTBOX(10011, OnEntryReselection)
	EVT_TEXT(10012, OnSearchBarTyped)
	EVT_MENU(wxID_ABOUT, OnAboutMenuClicked)
	EVT_MENU(wxID_EXIT, OnExitMenuClicked)
	EVT_MENU(wxID_SAVE, AppSave)
	EVT_CLOSE(OnClose)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "PastaPaster", wxPoint(30, 30), wxSize(1000, 640), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	MenuInit();
	m_newBtn = new wxButton(this, 10001, "New", wxPoint(220, 50), wxSize(100, 30));
	m_cpyBtn = new wxButton(this, 10002, "Copy", wxPoint(220, 90), wxSize(100, 30));
	m_delBtn = new wxButton(this, 10003, "Delete", wxPoint(220, 130), wxSize(100, 30));
	m_entryList = new wxListBox(this, 10011, wxPoint(10, 50), wxSize(200, 500));
	m_savBtn = new wxButton(this, 20001, "Save Body", wxPoint(220, 250), wxSize(100, 30));
	m_renameBtn = new wxButton(this, 20011, "Rename", wxPoint(220, 210), wxSize(100, 30));
	m_undoBtn = new wxButton(this, 20013, "Undo Body", wxPoint(220, 290), wxSize(100, 30));
	m_copyToClipBtn = new wxButton(this, 20012, "Copy Clipboard", wxPoint(220, 290), wxSize(100, 30));
	m_bodyText = new wxTextCtrl(this, 20000, "", wxPoint(330, 10), wxSize(640, 540), wxTE_MULTILINE);
	m_searchBar = new wxTextCtrl(this, 10012, "", wxPoint(10, 10), wxSize(200, 30));

	ValidateButtons();
}

cMain::~cMain()
{
	delete[] newEntry;
}

void cMain::MenuInit()
{
	m_menuBar = new wxMenuBar;
	m_menuFile = new wxMenu;
	m_menuFile->Append(wxID_SAVE, "Save", "Save all changes");
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_EXIT);
	m_menuHelp = new wxMenu;
	m_menuHelp->Append(wxID_ABOUT, "About", "About this program");
	m_menuBar->Append(m_menuFile, "File");
	m_menuBar->Append(m_menuHelp, "Help");
	SetMenuBar(m_menuBar);
	CreateStatusBar();
}

void cMain::OnNewButtonClicked(wxCommandEvent& evt)
{
	Entry e{"New Entry", ""};
	listEntry.push_back(e);
	m_entryList->AppendString(e.title);
	evt.Skip();
}

void cMain::OnCopyButtonClicked(wxCommandEvent& evt)
{
	if (m_entryList->GetSelection() != wxNOT_FOUND)
	{
		Entry copyEntry;
		copyEntry.title = listEntry.at(m_entryList->GetSelection()).title;
		copyEntry.body = listEntry.at(m_entryList->GetSelection()).body;
		listEntry.push_back(copyEntry);
		m_entryList->AppendString(copyEntry.title);
		evt.Skip();
	}
}

void cMain::OnDeleteButtonClicked(wxCommandEvent& evt)
{
	if (m_entryList->GetSelection() != wxNOT_FOUND)
	{
		listEntry.erase(listEntry.begin() + m_entryList->GetSelection());
		m_entryList->Delete(m_entryList->GetSelection());
		evt.Skip();
	}
}

void cMain::OnSaveButtonClicked(wxCommandEvent& evt)
{
	if(m_entryList->GetSelection() != wxNOT_FOUND)
		listEntry.at(m_entryList->GetSelection()).body = m_bodyText->GetValue();
	evt.Skip();
}

void cMain::OnEntryReselection(wxCommandEvent& evt)
{
	ValidateButtons();
	m_bodyText->Clear();
	if (m_entryList->GetSelection() != wxNOT_FOUND)
	{
		m_bodyText->AppendText(listEntry.at(m_entryList->GetSelection()).body);
	}
	evt.Skip();
}

void cMain::OnRenameButtonClicked(wxCommandEvent& evt)
{
	wxString newName = wxGetTextFromUser("Enter new name", "Rename", "", this);
	if (newName != "")
	{
		listEntry.at(m_entryList->GetSelection()).title = newName;
		m_entryList->SetString(m_entryList->GetSelection(), newName);
	}
	evt.Skip();
}

void cMain::OnCopyToClipboardButtonClicked(wxCommandEvent& evt)
{
	if (m_bodyText->IsEmpty() != true)
	{
		m_bodyText->SelectAll();
		m_bodyText->Copy();
	}
	evt.Skip();
}

void cMain::OnUndoButtonClicked(wxCommandEvent& evt)
{
	if (m_entryList->GetSelection() != wxNOT_FOUND)
	{
		m_bodyText->Clear();
		m_bodyText->AppendText(listEntry.at(m_entryList->GetSelection()).body);
	}
	evt.Skip();
}

void cMain::OnSearchBarTyped(wxCommandEvent& evt)
{
	m_bodyText->Clear();
	if (m_searchBar->GetValue() != "" && !m_entryList->IsEmpty())
	{
		m_entryList->SetSelection(m_entryList->FindString(m_searchBar->GetValue()));
		m_bodyText->AppendText(listEntry.at(m_entryList->GetSelection()).body);
	}
	evt.Skip();
}

void cMain::OnAboutMenuClicked(wxCommandEvent& evt)
{
	wxAboutDialogInfo aboutInfo;
	aboutInfo.SetName("PastaPaster");
	aboutInfo.SetVersion("1.0");
	aboutInfo.AddDeveloper("Isaac Hasher");
	aboutInfo.SetDescription("Built using wxWidgets v3.1.3");
	wxAboutBox(aboutInfo);
	evt.Skip();
}

void cMain::OnExitMenuClicked(wxCommandEvent& evt)
{
	this->Close();
	evt.Skip();
}

void cMain::ValidateButtons()
{
	if (m_entryList->GetSelection() != wxNOT_FOUND)
	{
		m_cpyBtn->Enable();
		m_delBtn->Enable();
		m_renameBtn->Enable();
		m_copyToClipBtn->Enable();
		m_savBtn->Enable();
		m_undoBtn->Enable();
	}
	else
	{
		m_cpyBtn->Disable();
		m_delBtn->Disable();
		m_renameBtn->Disable();
		m_copyToClipBtn->Disable();
		m_savBtn->Disable();
		m_undoBtn->Disable();
	}
}

void cMain::AppSave(wxCommandEvent& evt)
{
	std::fstream saveFile(PP_SAVEFILE, std::ios::out | std::ios::trunc);

	if (!saveFile.is_open())
	{
		wxLogWarning("Error saving file");
		return;
	}
	else
	{
		Entry tempEntry;

		for (unsigned int i = 0; i < listEntry.size(); i++)
		{
			tempEntry = listEntry.at(i);
			saveFile << tempEntry.title + '|';
			saveFile << tempEntry.body + '|';
		}
	}

	saveFile.close();
	evt.Skip();
}

void cMain::AppLoad()
{
	std::fstream loadFile(PP_SAVEFILE, std::ios::in);

	if(!loadFile.is_open())
	{
		wxLogWarning("No valid save file found!");
		return;
	}
	else
	{
		listEntry.clear();
		m_entryList->Clear();
		Entry tempEntry;

		while (loadFile.good())
		{
			std::getline(loadFile, tempEntry.title, '|');
			std::getline(loadFile, tempEntry.body, '|');
			if (!loadFile.eof())
			{
				listEntry.push_back(tempEntry);
				m_entryList->AppendString(tempEntry.title);
			}
		}
		
	}
	loadFile.close();
}

void cMain::OnClose(wxCloseEvent& evt)
{
	listEntry.clear();
	m_entryList->Clear();
	evt.Skip();
}
