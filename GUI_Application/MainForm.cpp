#include "MainForm.h"

#include <Windows.h>

using namespace GUIApplication;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MainForm);

    return EXIT_SUCCESS;
}