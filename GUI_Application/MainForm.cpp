#include "MainForm.h"
#include "..\Calculator\Calculator.hpp"
#include "..\Calculator\ConverterRPN.hpp"
#include "..\Calculator\ExecuterRPN.hpp"

#include <Windows.h>

using namespace GUIApplication;

std::pair<size_t const, char const* const> const Validater::calculator_symbols = std::make_pair(std::size(MathExprCalculator::Calculator<MathExpression::Notation::RPN>::available_symbols), MathExprCalculator::Calculator<MathExpression::Notation::RPN>::available_symbols);
std::pair<size_t const, char const* const> const Validater::precalculator_symbols = std::make_pair(std::size(PreCalculator<'x'>::available_symbols), PreCalculator<'x'>::available_symbols);
std::shared_ptr<MathExprCalculator::ICalculator> const CartesianSystem::Plot::calculator = std::make_shared<MathExprCalculator::Calculator<MathExpression::Notation::RPN>>(std::make_shared<MathExprCalculator::ConverterRPN>(), std::make_shared<MathExprCalculator::ExecuterRPN>());

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MainForm);

    return EXIT_SUCCESS;
}