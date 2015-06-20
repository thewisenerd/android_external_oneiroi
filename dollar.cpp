/*
 * oneiroi/dollar.c
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

Result Recognize(std::vector<Point>& points) {
	Result ret;
	float radians;
	float b, u, d;
	unsigned i;

	points  = Resample(points, NumPoints);
	radians = IndicativeAngle(points);
	points  = RotateBy(points, -radians);
	points  = ScaleTo(points, SquareSize);
	points  = TranslateTo(points, Origin);

	b = FLT_MAX;
	u = -1;
	for (i = 0; i < Unistrokes.size(); i++) // for each unistroke
	{
		// Golden Section Search (original $1)
		d = DistanceAtBestAngle(points, Unistrokes[i].Points, -AngleRange, +AngleRange, AnglePrecision);
		if (d < b) {
			b = d; // best (least) distance
			u = i; // unistroke
		}
	}

	if (u == -1) {
		ret.Name  = "No match.";
		ret.Score = 0.0;
	} else {
		ret.Name  = Unistrokes[u].Name;
		ret.Score = 1.0 - b / HalfDiagonal;
	}

	return ret;
}
