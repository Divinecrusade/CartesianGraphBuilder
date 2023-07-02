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
        
        static void set(System::Drawing::Size area, int scale);
        static void draw(System::Drawing::Graphics^ gfx);
        static System::Drawing::Point local_coordinates_to_global(double x, double y);

    private:
        
        static constexpr int padding{ 10 };

        static constexpr int base_min_x{ -4 };
        static constexpr int base_max_x{ 4 };
        
        static constexpr int base_min_y{ -4 };
        static constexpr int base_max_y{ 4 };

        static constexpr int line_thickness{ 2 };
        
        static int min_x;
        static int max_x;

        static int min_y;
        static int max_y;

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

            friend void CartesianSystem::set(System::Drawing::Size, int);

            static std::string expr;
            static std::shared_ptr<MathExprCalculator::ICalculator> const calculator;

            static double x_start;
            static double x_end;
            static double x_step;
        };
    };
}