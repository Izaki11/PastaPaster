#pragma once
#include "wx/wx.h"
#include "wx/listctrl.h"
#include "wx/aboutdlg.h"
#include "wx/file.h"
#include <iostream>
#include <fstream>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	struct Entry
	{
		std::string title;
		std::string body;
	};

	std::vector<Entry> listEntry;
	Entry* newEntry;

public:
	wxMenuBar* m_menuBar = nullptr;
	wxMenu* m_menuFile = nullptr;
	wxMenu* m_menuHelp = nullptr;
	wxButton* m_newBtn = nullptr;
	wxButton* m_cpyBtn = nullptr;
	wxButton* m_delBtn = nullptr;
	wxListBox* m_entryList = nullptr;
	wxButton* m_savBtn = nullptr;
	wxButton* m_renameBtn = nullptr;
	wxButton* m_copyToClipBtn = nullptr;
	wxButton* m_undoBtn = nullptr;
	wxTextCtrl* m_bodyText = nullptr;
	wxTextCtrl* m_searchBar = nullptr;

	void MenuInit();
	void OnNewButtonClicked(wxCommandEvent& evt);
	void OnCopyButtonClicked(wxCommandEvent& evt);
	void OnDeleteButtonClicked(wxCommandEvent& evt);
	void OnSaveButtonClicked(wxCommandEvent& evt);
	void OnEntryReselection(wxCommandEvent& evt);
	void OnRenameButtonClicked(wxCommandEvent& evt);
	void OnCopyToClipboardButtonClicked(wxCommandEvent& evt);
	void OnUndoButtonClicked(wxCommandEvent& evt);
	void OnSearchBarTyped(wxCommandEvent& evt);
	void OnAboutMenuClicked(wxCommandEvent& evt);
	void OnExitMenuClicked(wxCommandEvent& evt);
	void ValidateButtons();
	void AppSave(wxCommandEvent& evt);
	void AppLoad();
	void OnClose(wxCloseEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

