#include "CartesianSystem.hpp"

#include <cmath>

namespace GUIApplication
{
    double CartesianSystem::pixels_in_unit_x;
    double CartesianSystem::pixels_in_unit_y;
    System::Drawing::Rectangle CartesianSystem::graph_area;

    int CartesianSystem::x_zero;
    int CartesianSystem::y_zero;

    System::Drawing::Point const CartesianSystem::INVALID( -1, -1 );

    void CartesianSystem::set(System::Drawing::Size area)
    {
        graph_area = System::Drawing::Rectangle(padding, padding, area.Width - 2 * padding, area.Height - 2 * padding);

        pixels_in_unit_x = double(graph_area.Width) / (std::abs(max_x - min_x));
        pixels_in_unit_y = double(graph_area.Height) / (std::abs(max_y - min_y));

        x_zero = graph_area.Width / 2 + padding;
        y_zero = graph_area.Height / 2 + padding;

        Plot::x_start = min_x;
        Plot::x_end = max_x;
        Plot::x_step = 1 / pixels_in_unit_x;
    }

    void CartesianSystem::draw(System::Drawing::Graphics^ gfx)
    {
        gfx->Clear(System::Drawing::Color::White);

        System::Drawing::Pen^ redPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
        redPen->Width = line_thickness;

        gfx->DrawLine(redPen, graph_area.Left, y_zero, graph_area.Right, y_zero);
        gfx->DrawLine(redPen, x_zero, graph_area.Top, x_zero, graph_area.Bottom);
    }

    System::Drawing::Point CartesianSystem::local_coordinates_to_global(double x, double y)
    {
        System::Drawing::Point global(x_zero + x * pixels_in_unit_x, y_zero - y * pixels_in_unit_y);
        return global.X > graph_area.Width + padding || global.X < 0 || global.Y > graph_area.Height + padding || global.Y < 0 ? INVALID : global;
    }


    std::string CartesianSystem::Plot::expr{};

    double CartesianSystem::Plot::x_start;
    double CartesianSystem::Plot::x_end;
    double CartesianSystem::Plot::x_step;


    void CartesianSystem::Plot::set(std::string_view expr)
    {
        Plot::expr = expr;
    }

    void CartesianSystem::Plot::draw(System::Drawing::Graphics^ gfx)
    {
        if (expr.length() > 0)
        {
            System::Drawing::Pen^ redPen = gcnew System::Drawing::Pen(System::Drawing::Color::Red);
            redPen->Width = 2;

            double x{ x_start };
            double y{ calculator->calculate(PreCalculator<'x'>::process_symbols(expr, x)) };
            System::Drawing::Point from{ CartesianSystem::local_coordinates_to_global(x, y) };
            x += x_step;
            for (; x < x_end; x += x_step)
            {
                y = calculator->calculate(PreCalculator<'x'>::process_symbols(expr, x));
                System::Drawing::Point to{ CartesianSystem::local_coordinates_to_global(x, y) };

                if (from != CartesianSystem::INVALID && to != CartesianSystem::INVALID)
                  gfx->DrawLine(redPen, from, to);
                from = to;
            }
            gfx->Flush();
        }
    }
}