//
// Created by xiaozhuai on 2019/12/12.
//

#include "Log.h"
#include "MainFrame.h"

#include <wx/wx.h>
#include <OdourlessUtils.h>
#include <ProcessHelper.h>


class OdourlessApp : public wxApp {

public:
    OdourlessApp()
            : wxApp(),
              m_mainFrame(nullptr) {
        Log::init();
    }

    ~OdourlessApp() override {
        Log::destroy();
    }

    bool OnInit() override {
        if (OdourlessUtils::checkSIPEnabled()) {
            wxMessageBox("You must disable SIP to use this application", "SIP Check", wxOK | wxICON_ERROR);
            Exit();
            return false;
        }

#ifdef ODOURLESS_MUST_INSTALL_TO_APPLICATIONS
        if (ProcessHelper::getCurrentApplicationPath() != ODOURLESS_INSTALL_PATH) {
            std::string msg = tfm::format("You must install this application as %s, but not %s",
                                          ODOURLESS_INSTALL_PATH,
                                          ProcessHelper::getCurrentApplicationPath());
            wxMessageBox(msg, "Installation Check", wxOK | wxICON_ERROR);
            Exit();
            return false;
        }
#endif

        m_mainFrame = new MainFrame();
        m_mainFrame->Show(true);
        return true;
    }

private:
    MainFrame *m_mainFrame;
};

wxIMPLEMENT_APP(OdourlessApp);
