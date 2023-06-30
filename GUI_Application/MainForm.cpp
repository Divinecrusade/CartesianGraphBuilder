#include "MainForm.h"
#include "..\Calculator\Calculator.hpp"

#include <Windows.h>

using namespace GUIApplication;

char tmp[] {'x', 'e'};

std::pair<size_t, char const* const> const Validater::calculator_symbols = std::make_pair(std::size(MathExprCalculator::Calculator<MathExpression::Notation::RPN>::available_symbols), MathExprCalculator::Calculator<MathExpression::Notation::RPN>::available_symbols);
std::pair<size_t, char const* const> const Validater::preprocessor_symbols = std::make_pair(std::size(tmp), tmp);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MainForm);

    return EXIT_SUCCESS;
}