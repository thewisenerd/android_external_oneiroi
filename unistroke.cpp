/*
 * oneiroi/unistroke.c
 *
 * Copyright (c) 2015, Vineeth Raj <thewisenerd@protonmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <oneiroi.h>

template <typename T, size_t N>
T* begin(T(&arr)[N]) { return &arr[0]; }
template <typename T, size_t N>
T* end(T(&arr)[N]) { return &arr[0]+N; }

Unistroke get_unistroke(std::string name, std::vector<Point>& points)
{
	Unistroke ret;
	ret.Name = name;
	ret.Points = Resample(points, NumPoints);
	float radians = IndicativeAngle(ret.Points);
	ret.Points = RotateBy(ret.Points, -radians);
	ret.Points = ScaleTo(ret.Points, SquareSize);
	ret.Points = TranslateTo(ret.Points, Origin);
	return ret;
}

void init_unistrokes(void)
{
#include <gestures.h>
	std::vector<Point> circle(begin(circle_arr), end(circle_arr));
	Unistrokes.push_back(get_unistroke("circle", circle));

	std::vector<Point> rectangle(begin(rectangle_arr), end(rectangle_arr));
	Unistrokes.push_back(get_unistroke("rectangle", rectangle));
}
