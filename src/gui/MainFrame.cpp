//
// Created by xiaozhuai on 2019/12/12.
//

#include "OdourlessUtils.h"
#include "ProcessHelper.h"
#include "MainFrame.h"
#include "Log.h"

#include <wx/sstream.h>
#include <wx/protocol/http.h>

#define COLOR_SUC               wxColour("#228135")
#define COLOR_ERR               wxColour("#B22A2E")
#define ABOUT_TEXT              "Odourless is a tool for preventing .DS_Store creation.\n\n" \
                                "Version: " ODOURLESS_VERSION "\n\n" \
                                "Author: xiaozhuai\n\n" \
                                "Special Thanks: darwin && JK3Y\n"
#define REPO_URL                "https://github.com/xiaozhuai/odourless"
#define REPO_RELEASES_API_URL   "https://api.github.com/repos/xiaozhuai/odourless/releases"
#define REPO_LATEST_RELEASE_URL "https://github.com/xiaozhuai/odourless/releases/latest"

MainFrame::MainFrame()
        : wxFrame(nullptr, wxID_ANY, "Odourless", wxDefaultPosition, wxSize(400, 300), wxSYSTEM_MENU | wxCLOSE_BOX | wxCAPTION),
          m_daemonInstalled(false),
          m_daemonRunning(false) {

    InitTimer();
    InitStatusBar();
    InitTab();
    InitGeneralWindow();
    InitAboutWindow();
}

void MainFrame::InitStatusBar() {
    CreateStatusBar();
    SetStatusText("Ready to Odourless!");
}

void MainFrame::InitTab() {
    m_mainPanel = std::make_shared<wxPanel>(this, wxID_ANY);
    m_notebook = std::make_shared<wxNotebook>(m_mainPanel.get(), wxID_ANY, wxPoint(12, 12), wxSize(376, 240));
    m_generalWindow = std::make_shared<wxWindow>(m_notebook.get(), wxID_ANY);
    m_aboutWindow = std::make_shared<wxWindow>(m_notebook.get(), wxID_ANY);
    m_notebook->AddPage(m_generalWindow.get(), "General");
    m_notebook->AddPage(m_aboutWindow.get(), "About");
}

void MainFrame::InitGeneralWindow() {
    m_daemonInstallationStatusTitle = std::make_shared<wxStaticText>(m_generalWindow.get(), wxID_ANY, "Daemon Status:", wxPoint(16, 8));
    m_daemonInstallationStatus = std::make_shared<wxStaticText>(m_generalWindow.get(), wxID_ANY, "", wxPoint(122, 8));
    m_installUninstallButton = std::make_shared<wxButton>(m_generalWindow.get(), ID_BUTTON_INSTALL_UNINSTALL_DAEMON, "", wxPoint(210, 6));
    UpdateDaemonInstallationStatus();

    m_daemonRunningStatusTitle = std::make_shared<wxStaticText>(m_generalWindow.get(), wxID_ANY, "Daemon Running:", wxPoint(16, 40));
    m_daemonRunningStatus = std::make_shared<wxStaticText>(m_generalWindow.get(), wxID_ANY, "", wxPoint(132, 40));
    m_startStopButton = std::make_shared<wxButton>(m_generalWindow.get(), ID_BUTTON_START_STOP_DAEMON, "", wxPoint(164, 38));
    m_restartDaemonButton = std::make_shared<wxButton>(m_generalWindow.get(), ID_BUTTON_RESTART_DAEMON, "restart", wxPoint(256, 38));
    UpdateDaemonRunningStatus();

    m_checkForUpdatesButton = std::make_shared<wxButton>(m_generalWindow.get(), ID_BUTTON_CHECK_FOR_UPDATES, "Check for Updates...", wxPoint(16, 158));
}

void MainFrame::InitAboutWindow() {
    m_aboutText = std::make_shared<wxStaticText>(m_aboutWindow.get(), wxID_ANY, ABOUT_TEXT, wxPoint(16, 8));
    m_projectRepoLink = std::make_shared<wxHyperlinkCtrl>(m_aboutWindow.get(), wxID_ANY, REPO_URL, REPO_URL,
                                                          wxPoint(16, 170));
}

void MainFrame::InitTimer() {
    m_checkDaemonStatusTimer = std::make_shared<wxTimer>(this, ID_TIMER_CHECK_DAEMON_RUNNING);
    m_checkDaemonStatusTimer->Start(3000);
}

void MainFrame::UpdateDaemonInstallationStatus() {
    m_daemonInstalled = OdourlessUtils::daemonInstalled();
    m_daemonInstallationStatus->SetLabelText(m_daemonInstalled ? "Installed" : "Not Installed");
    m_daemonInstallationStatus->SetForegroundColour(m_daemonInstalled ? COLOR_SUC : COLOR_ERR);
    m_installUninstallButton->SetPosition(wxPoint(m_daemonInstalled ? 186 : 210, 6));
    m_installUninstallButton->SetLabelText(m_daemonInstalled ? "uninstall" : "install");
    if(m_startStopButton) m_startStopButton->Show(m_daemonInstalled);
    if(m_restartDaemonButton) m_restartDaemonButton->Show(m_daemonInstalled && m_daemonRunning);
}

void MainFrame::UpdateDaemonRunningStatus() {
    m_daemonRunning = OdourlessUtils::daemonRunning();
    m_daemonRunningStatus->SetLabelText(m_daemonRunning ? "Yes" : "No");
    m_daemonRunningStatus->SetForegroundColour(m_daemonRunning ? COLOR_SUC : COLOR_ERR);
    m_startStopButton->SetLabelText(m_daemonRunning ? "stop" : "start");
    m_startStopButton->Show(m_daemonInstalled);
    m_restartDaemonButton->Show(m_daemonInstalled && m_daemonRunning);
}

void MainFrame::OnCheckDaemonStatusTimer(wxTimerEvent &event) {
    UpdateDaemonInstallationStatus();
    UpdateDaemonRunningStatus();
}

void MainFrame::OnInstallUninstallButtonClicked(wxCommandEvent &event) {
    LOG("OnInstallUninstallButtonClicked");
    m_installUninstallButton->Disable();

    if (m_daemonInstalled) {
        SetStatusText("Uninstalling daemon...");
        auto res = OdourlessUtils::uninstallDaemon();
        if (res.suc) {
            SetStatusText("Suc uninstall daemon!");
        } else {
            SetStatusText("Failed uninstall daemon!");
            wxMessageBox(res.output.c_str(), "Failed uninstall daemon!", wxOK | wxICON_ERROR);
        }
    } else {
        SetStatusText("Installing daemon...");
        auto res = OdourlessUtils::installDaemon();
        if (res.suc) {
            SetStatusText("Suc install daemon!");
        } else {
            SetStatusText("Failed install daemon!");
            wxMessageBox(res.output.c_str(), "Failed install daemon!", wxOK | wxICON_ERROR);
        }
    }

    UpdateDaemonInstallationStatus();
    UpdateDaemonRunningStatus();

    m_installUninstallButton->Enable();
}

void MainFrame::OnStartStopDaemonButtonClicked(wxCommandEvent &event) {
    LOG("OnStartStopDaemonButtonClicked");
    m_startStopButton->Disable();
    m_restartDaemonButton->Disable();

    if (m_daemonRunning) {
        SetStatusText("Stopping daemon...");
        auto res = OdourlessUtils::stopDaemon();
        if (res.suc) {
            SetStatusText("Suc stop daemon!");
        } else {
            SetStatusText("Failed stop daemon!");
            wxMessageBox(res.output.c_str(), "Failed stop daemon!", wxOK | wxICON_ERROR);
        }
    } else {
        SetStatusText("Starting daemon...");
        auto res = OdourlessUtils::startDaemon();
        if (res.suc) {
            SetStatusText("Suc start daemon!");
        } else {
            SetStatusText("Failed start daemon!");
            wxMessageBox(res.output.c_str(), "Failed start daemon!", wxOK | wxICON_ERROR);
        }
    }

    UpdateDaemonRunningStatus();

    m_startStopButton->Enable();
    m_restartDaemonButton->Enable();
}

void MainFrame::OnRestartDaemonButtonClicked(wxCommandEvent &event) {
    LOG("OnRestartDaemonButtonClicked");
    m_startStopButton->Disable();
    m_restartDaemonButton->Disable();

    SetStatusText("Restarting daemon...");
    auto res = OdourlessUtils::restartDaemon();
    if (res.suc) {
        SetStatusText("Suc restart daemon!");
    } else {
        SetStatusText("Failed restart daemon!");
        wxMessageBox(res.output.c_str(), "Failed restart daemon!", wxOK | wxICON_ERROR);
    }

    m_startStopButton->Enable();
    m_restartDaemonButton->Enable();
}

void MainFrame::OnCheckForUpdatesClicked(wxCommandEvent &event) {
    LOG("OnCheckForUpdatesClicked");
    m_checkForUpdatesButton->Disable();
    // TODO should use REPO_RELEASES_API_URL for checking

    OdourlessUtils::shellExec("open \"" REPO_LATEST_RELEASE_URL "\"", false);

    m_checkForUpdatesButton->Enable();
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_TIMER(ID_TIMER_CHECK_DAEMON_RUNNING, MainFrame::OnCheckDaemonStatusTimer)
    EVT_BUTTON(ID_BUTTON_INSTALL_UNINSTALL_DAEMON, MainFrame::OnInstallUninstallButtonClicked)
    EVT_BUTTON(ID_BUTTON_START_STOP_DAEMON, MainFrame::OnStartStopDaemonButtonClicked)
    EVT_BUTTON(ID_BUTTON_RESTART_DAEMON, MainFrame::OnRestartDaemonButtonClicked)
    EVT_BUTTON(ID_BUTTON_CHECK_FOR_UPDATES, MainFrame::OnCheckForUpdatesClicked)
END_EVENT_TABLE()
