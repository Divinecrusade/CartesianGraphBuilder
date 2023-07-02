#include "CartesianSystem.hpp"

#include <cmath>

namespace GUIApplication
{
    int CartesianSystem::min_x;
    int CartesianSystem::max_x;
    int CartesianSystem::min_y;
    int CartesianSystem::max_y;
    
    double CartesianSystem::pixels_in_unit_x;
    double CartesianSystem::pixels_in_unit_y;
    System::Drawing::Rectangle CartesianSystem::graph_area;

    int CartesianSystem::x_zero;
    int CartesianSystem::y_zero;

    System::Drawing::Point const CartesianSystem::INVALID( -1, -1 );

    void CartesianSystem::set(System::Drawing::Size area, int scale)
    {
        graph_area = System::Drawing::Rectangle(padding, padding, area.Width - 2 * padding, area.Height - 2 * padding);

        min_x = base_min_x * scale;
        max_x = base_max_x * scale;

        min_y = base_min_y * scale;
        max_y = base_max_y * scale;

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

        System::Drawing::Pen^ blackPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
        blackPen->Width = line_thickness;

        gfx->DrawLine(blackPen, graph_area.Left, y_zero, graph_area.Right, y_zero);
        gfx->DrawLine(blackPen, x_zero, graph_area.Top, x_zero, graph_area.Bottom);
        
        System::Drawing::FontFamily^ fntFamily = gcnew System::Drawing::FontFamily("Times New Roman");
        System::Drawing::Font^ fntWrite = gcnew System::Drawing::Font(fntFamily, 10.00F, System::Drawing::FontStyle::Regular);

        static constexpr int x_axis_x_margin{ -10 };
        static constexpr int x_axis_y_margin{ 3 };
        static constexpr int y_axis_x_margin{ 5 };
        static constexpr int y_axis_y_margin{ -5 };

        gfx->DrawString("x", fntWrite, System::Drawing::Brushes::Black, graph_area.Right + x_axis_x_margin, y_zero + x_axis_y_margin);
        gfx->DrawString("y", fntWrite, System::Drawing::Brushes::Black, x_zero + y_axis_x_margin, graph_area.Top + y_axis_y_margin);

        static constexpr int segment_halfwidth{ 4 };

        System::String^ s_zero{ "0" };
        gfx->DrawString(s_zero, fntWrite, System::Drawing::Brushes::Black, x_zero + y_axis_x_margin, y_zero + x_axis_y_margin);


        for (int x{ 1 }; x <= max_x - 1; ++x)
        {
            System::String^ str{ x.ToString() };
            gfx->DrawLine(blackPen, x_zero + x * pixels_in_unit_x, y_zero, x_zero + x * pixels_in_unit_x, y_zero - segment_halfwidth);
            gfx->DrawLine(blackPen, x_zero + x * pixels_in_unit_x, y_zero, x_zero + x * pixels_in_unit_x, y_zero + segment_halfwidth);
            gfx->DrawString(str, fntWrite, System::Drawing::Brushes::Black, x_zero + x * pixels_in_unit_x - y_axis_x_margin, y_zero + x_axis_y_margin);
        }
        for (int x{ -1 }; x >= min_x + 1; --x)
        {
            System::String^ str{ x.ToString() };
            gfx->DrawLine(blackPen, x_zero + x * pixels_in_unit_x, y_zero, x_zero + x * pixels_in_unit_x, y_zero - segment_halfwidth);
            gfx->DrawLine(blackPen, x_zero + x * pixels_in_unit_x, y_zero, x_zero + x * pixels_in_unit_x, y_zero + segment_halfwidth);
            gfx->DrawString(str, fntWrite, System::Drawing::Brushes::Black, x_zero + x * pixels_in_unit_x - y_axis_x_margin, y_zero + x_axis_y_margin);
        }

        for (int y{ 1 }; y <= max_y - 1; ++y)
        {
            System::String^ str{ y.ToString() };
            gfx->DrawLine(blackPen, x_zero, y_zero - y * pixels_in_unit_y, x_zero + segment_halfwidth, y_zero - y * pixels_in_unit_y);
            gfx->DrawLine(blackPen, x_zero, y_zero - y * pixels_in_unit_y, x_zero - segment_halfwidth, y_zero - y * pixels_in_unit_y);
            gfx->DrawString(str, fntWrite, System::Drawing::Brushes::Black, x_zero + y_axis_x_margin, y_zero - y * pixels_in_unit_y + x_axis_x_margin);
        }
        for (int y{ -1 }; y >= min_y + 1; --y)
        {
            System::String^ str{ y.ToString() };
            gfx->DrawLine(blackPen, x_zero, y_zero - y * pixels_in_unit_y, x_zero + segment_halfwidth, y_zero - y * pixels_in_unit_y);
            gfx->DrawLine(blackPen, x_zero, y_zero - y * pixels_in_unit_y, x_zero - segment_halfwidth, y_zero - y * pixels_in_unit_y);
            gfx->DrawString(str, fntWrite, System::Drawing::Brushes::Black, x_zero + y_axis_x_margin, y_zero - y * pixels_in_unit_y + x_axis_x_margin);
        }
    }

    System::Drawing::Point CartesianSystem::local_coordinates_to_global(double x, double y)
    {
        System::Drawing::Point global(x_zero + std::lround(x * pixels_in_unit_x), y_zero - std::lround(y * pixels_in_unit_y));
        
        return global.X > graph_area.Width + 2 * padding || global.X < 0 || global.Y > graph_area.Height + 2 * padding || global.Y < 0 ? INVALID : global;
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