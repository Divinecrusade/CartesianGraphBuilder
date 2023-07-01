#pragma once

#include "..\Calculator\ICalculator.hpp"
#include "PreCalculator.hpp"
#include <memory>


namespace GUIApplication
{
    class CartesianSystem
    {
    public:

        static System::Drawing::Point const INVALID;
        
        static void set(System::Drawing::Size area);
        static void draw(System::Drawing::Graphics^ gfx);
        static System::Drawing::Point local_coordinates_to_global(double x, double y);

    private:
        
        static constexpr int padding{ 10 };

        static constexpr int min_x{ -10 };
        static constexpr int max_x{ 10 };
        
        static constexpr int min_y{ -10 };
        static constexpr int max_y{ 10 };

        static constexpr int line_thickness{ 2 };
        
        static double pixels_in_unit_x;
        static double pixels_in_unit_y;
        static System::Drawing::Rectangle graph_area;

        static int x_zero;
        static int y_zero;

    public:

        class Plot
        {
        public:

            static void set(std::string_view expr);
            static void draw(System::Drawing::Graphics^ gfx);

        private:

            friend void CartesianSystem::set(System::Drawing::Size);

            static std::string expr;
            static std::shared_ptr<MathExprCalculator::ICalculator> const calculator;

            static double x_start;
            static double x_end;
            static double x_step;
        };
    };
}