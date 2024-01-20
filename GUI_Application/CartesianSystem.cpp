#include "CartesianSystem.hpp"

#include <cmath>

namespace GUIApplication
{
    int CartesianSystem::pixels_in_unit_x;
    int CartesianSystem::pixels_in_unit_y;
    System::Drawing::Rectangle CartesianSystem::graph_area;

    int CartesianSystem::x_zero;
    int CartesianSystem::y_zero;


    void CartesianSystem::set(System::Drawing::Size area)
    {
        graph_area = System::Drawing::Rectangle(padding, padding, area.Width - 2 * padding, area.Height - 2 * padding);

        pixels_in_unit_x = graph_area.Width / (std::abs(max_x - min_x));
        pixels_in_unit_y = graph_area.Height / (std::abs(max_y - min_y));

        x_zero = graph_area.Width / 2;
        y_zero = graph_area.Height / 2;
    }

    void CartesianSystem::draw(System::Drawing::Graphics^ gfx)
    {
        gfx->Clear(System::Drawing::Color::White);

        System::Drawing::Pen^ redPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
        redPen->Width = line_thickness;

        gfx->DrawLine(redPen, graph_area.Left, y_zero, graph_area.Right, y_zero);
        gfx->DrawLine(redPen, x_zero, graph_area.Top, x_zero, graph_area.Bottom);
    }
}