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

	std::vector<Point> triangle(begin(triangle_arr), end(triangle_arr));
	Unistrokes.push_back(get_unistroke("triangle", triangle));

	std::vector<Point> x(begin(x_arr), end(x_arr));
	Unistrokes.push_back(get_unistroke("x", x));

	std::vector<Point> rectangle(begin(rectangle_arr), end(rectangle_arr));
	Unistrokes.push_back(get_unistroke("rectangle", rectangle));

	std::vector<Point> circle(begin(circle_arr), end(circle_arr));
	Unistrokes.push_back(get_unistroke("circle", circle));

	std::vector<Point> check(begin(check_arr), end(check_arr));
	Unistrokes.push_back(get_unistroke("check", check));

	std::vector<Point> caret(begin(caret_arr), end(caret_arr));
	Unistrokes.push_back(get_unistroke("caret", caret));

	std::vector<Point> zigzag(begin(zigzag_arr), end(zigzag_arr));
	Unistrokes.push_back(get_unistroke("zigzag", zigzag));

	std::vector<Point> arrow(begin(arrow_arr), end(arrow_arr));
	Unistrokes.push_back(get_unistroke("arrow", arrow));

	std::vector<Point> left_square_bracket(begin(left_square_bracket_arr), end(left_square_bracket_arr));
	Unistrokes.push_back(get_unistroke("left_square_bracket", left_square_bracket));

	std::vector<Point> right_square_bracket(begin(right_square_bracket_arr), end(right_square_bracket_arr));
	Unistrokes.push_back(get_unistroke("right_square_bracket", right_square_bracket));

	std::vector<Point> v(begin(v_arr), end(v_arr));
	Unistrokes.push_back(get_unistroke("v", v));

	std::vector<Point> _delete(begin(delete_arr), end(delete_arr));
	Unistrokes.push_back(get_unistroke("delete", _delete));

	std::vector<Point> left_curly_brace(begin(left_curly_brace_arr), end(left_curly_brace_arr));
	Unistrokes.push_back(get_unistroke("left_curly_brace", left_curly_brace));

	std::vector<Point> right_curly_brace(begin(right_curly_brace_arr), end(right_curly_brace_arr));
	Unistrokes.push_back(get_unistroke("right_curly_brace", right_curly_brace));

	std::vector<Point> star(begin(star_arr), end(star_arr));
	Unistrokes.push_back(get_unistroke("star", star));

	std::vector<Point> pigtail(begin(pigtail_arr), end(pigtail_arr));
	Unistrokes.push_back(get_unistroke("pigtail", pigtail));

}
