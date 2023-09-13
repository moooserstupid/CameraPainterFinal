#include "camera_painter.hpp"
#include <iostream>

int main()
{
	std::vector<std::vector<int>> maskHSVs = camera_painter::GetMasks();

	camera_painter::ShowMasks(maskHSVs);

}