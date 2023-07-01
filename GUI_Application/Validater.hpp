#pragma once

#include "..\Calculator\Operator.hpp"
#include <string>
#include <utility>

namespace GUIApplication
{
    static class Validater
    {        
    private:

       static std::pair<size_t const, char const* const> const calculator_symbols;
       static std::pair<size_t const, char const* const> const preprocessor_symbols;

       enum TokenType
       {
           nan, invalid, number, math_operator, preprocessor
       };

    private:

        static TokenType check_char(char c);

    public:

       static bool validate(std::string const& expr);
       static bool validate(int key_code);
    
    };
}