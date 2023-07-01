#pragma once

//#include "..\Calculator\ICalculator.hpp"
//#include "PreCalculator.hpp"
//#include <memory>


namespace GUIApplication
{
    class CartesianSystem
    {
    public:
    
        /*static class Plot
        {
        public:

            //static void set(std::string_view expr);
            //static void draw(System::Drawing::Graphics^ gfx);

        private:

            //static std::string expr;
            //static System::Drawing::Point* draw_map; 
            //static std::shared_ptr<MathExprCalculator::ICalculator> const calculator;
        };*/

    public:

        static void set(System::Drawing::Size area);
        static void draw(System::Drawing::Graphics^ gfx);

    private:
        
        //friend void Plot::set(std::string_view);
        static constexpr int padding{ 10 };

        static constexpr int min_x{ -100 };
        static constexpr int max_x{ 100 };
        
        static constexpr int min_y{ -100 };
        static constexpr int max_y{ 100 };

        static constexpr int line_thickness{ 2 };
        
        static int pixels_in_unit_x;
        static int pixels_in_unit_y;
        static System::Drawing::Rectangle graph_area;

        static int x_zero;
        static int y_zero;
    };
}