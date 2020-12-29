//
// Created by xiaozhuai on 2019/12/12.
//

#ifndef ODOURLESS_ALL_MAINFRAME_H
#define ODOURLESS_ALL_MAINFRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/hyperlink.h>
#include <memory>
#include <sys/types.h>

class MainFrame : public wxFrame {

public:
    MainFrame();

private:
    std::shared_ptr<wxPanel> m_mainPanel;
    std::shared_ptr<wxNotebook> m_notebook;
    std::shared_ptr<wxWindow> m_generalWindow;
    std::shared_ptr<wxWindow> m_aboutWindow;

    // General Window
    std::shared_ptr<wxStaticText> m_daemonInstallationStatusTitle;
    std::shared_ptr<wxStaticText> m_daemonInstallationStatus;
    std::shared_ptr<wxButton> m_installUninstallButton;

    std::shared_ptr<wxStaticText> m_daemonRunningStatusTitle;
    std::shared_ptr<wxStaticText> m_daemonRunningStatus;
    std::shared_ptr<wxButton> m_startStopButton;
    std::shared_ptr<wxButton> m_restartDaemonButton;

    std::shared_ptr<wxButton> m_showDaemonLogButton;
    std::shared_ptr<wxButton> m_showInjectLogButton;

    // About Window
    std::shared_ptr<wxStaticText> m_aboutText;
    std::shared_ptr<wxHyperlinkCtrl> m_projectRepoLink;
    std::shared_ptr<wxButton> m_checkForUpdatesButton;

    // Timer
    std::shared_ptr<wxTimer> m_checkDaemonStatusTimer;

private:
    bool m_daemonInstalled = false;
    bool m_daemonRunning = false;

private:
    void InitTimer();

    void InitStatusBar();

    void InitTab();

    void InitGeneralWindow();

    void InitAboutWindow();

private:
    void UpdateDaemonInstallationStatus();

    void UpdateDaemonRunningStatus();

private:
    void OnCheckDaemonStatusTimer(wxTimerEvent &event);

    void OnInstallUninstallButtonClicked(wxCommandEvent &event);

    void OnStartStopDaemonButtonClicked(wxCommandEvent &event);

    void OnRestartDaemonButtonClicked(wxCommandEvent &event);

    void OnShowDaemonLogClicked(wxCommandEvent &event);

    void OnShowInjectLogClicked(wxCommandEvent &event);

    void OnCheckForUpdatesClicked(wxCommandEvent &event);

private:
    enum {
        ID_TIMER_CHECK_DAEMON_RUNNING = wxID_HIGHEST + 1,
        ID_BUTTON_INSTALL_UNINSTALL_DAEMON,
        ID_BUTTON_START_STOP_DAEMON,
        ID_BUTTON_RESTART_DAEMON,
        ID_BUTTON_SHOW_DAEMON_LOG,
        ID_BUTTON_SHOW_INJECT_LOG,
        ID_BUTTON_CHECK_FOR_UPDATES,
    };

    DECLARE_EVENT_TABLE();
};

#endif //ODOURLESS_ALL_MAINFRAME_H
