/*
 * oneiroi/helpers.cpp
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

std::vector<Point>& Resample(std::vector<Point>& points, unsigned n)
{
	float I = PathLength(points) / (n - 1); // interval length
	float D = 0.0;
	Resample_newpoints.clear();
	Resample_newpoints.push_back(points[0]);
	unsigned i;

	for (i = 1; i < points.size(); i++)
	{
		float d = Distance(points[i - 1], points[i]);
		if ((D + d) >= I)
		{
			float qx = points[i - 1].X + ((I - D) / d) * (points[i].X - points[i - 1].X);
			float qy = points[i - 1].Y + ((I - D) / d) * (points[i].Y - points[i - 1].Y);
			Resample_newpoints.insert(Resample_newpoints.begin(), {qx, qy}); // append new point 'q'
			// this should do the same as points.splice(i, 0, q);
			points.insert(points.begin()+i, {qx, qy}); // insert 'q' at position i in points s.t. 'q' will be the next i
			D = 0.0;
		}
		else D += d;
	}
	if (Resample_newpoints.size() == n - 1) // somtimes we fall a rounding-error short of adding the last point, so add it if so
		Resample_newpoints.insert(Resample_newpoints.end(), {points[points.size() - 1].X, points[points.size() - 1].Y});
	return Resample_newpoints;
}

float IndicativeAngle(std::vector<Point>& points)
{
	Point c = Centroid(points);
	return atan2(c.Y - points[0].Y, c.X - points[0].X);
}

std::vector<Point>& RotateBy(std::vector<Point>& points, float radians) // rotates points around centroid
{
	Point c = Centroid(points);
	float _cos = cos(radians);
	float _sin = sin(radians);
	RotateBy_newpoints.clear();
	unsigned i;
	for (i = 0; i < points.size(); i++) {
		float qx = (points[i].X - c.X) * _cos - (points[i].Y - c.Y) * _sin + c.X;
		float qy = (points[i].X - c.X) * _sin + (points[i].Y - c.Y) * _cos + c.Y;
		RotateBy_newpoints.insert(RotateBy_newpoints.begin(), {qx, qy});
	}
	return RotateBy_newpoints;
}

std::vector<Point>& ScaleTo(std::vector<Point>& points, float size) // non-uniform scale; assumes 2D gestures (i.e., no lines)
{
	Rectangle B = BoundingBox(points);
	ScaleTo_newpoints.clear();
	unsigned i;
	for (i = 0; i < points.size(); i++) {
		float qx = points[i].X * (size / B.Width);
		float qy = points[i].Y * (size / B.Height);
		ScaleTo_newpoints.insert(ScaleTo_newpoints.begin(), {qx, qy});
	}
	return ScaleTo_newpoints;
}

std::vector<Point>& TranslateTo(std::vector<Point>& points, Point pt) // translates points' centroid
{
	unsigned i;
	Point c = Centroid(points);
	TranslateTo_newpoints.clear();

	for (i = 0; i < points.size(); i++) {
		float qx = points[i].X + pt.X - c.X;
		float qy = points[i].Y + pt.Y - c.Y;
		TranslateTo_newpoints.insert(TranslateTo_newpoints.begin(), {qx, qy});
	}
	return TranslateTo_newpoints;
}

float DistanceAtBestAngle(std::vector<Point>& points, std::vector<Point>& T, float a, float b, float threshold)
{
	float x1 = Phi * a + (1.0 - Phi) * b;
	float f1 = DistanceAtAngle(points, T, x1);
	float x2 = (1.0 - Phi) * a + Phi * b;
	float f2 = DistanceAtAngle(points, T, x2);
	while (abs(b - a) > threshold)
	{
		if (f1 < f2) {
			b = x2;
			x2 = x1;
			f2 = f1;
			x1 = Phi * a + (1.0 - Phi) * b;
			f1 = DistanceAtAngle(points, T, x1);
		} else {
			a = x1;
			x1 = x2;
			f1 = f2;
			x2 = (1.0 - Phi) * a + Phi * b;
			f2 = DistanceAtAngle(points, T, x2);
		}
	}
	return std::min(f1, f2);
}

float DistanceAtAngle(std::vector<Point>& points, std::vector<Point>& T, float radians)
{
	std::vector<Point> newpoints = RotateBy(points, radians);
	return PathDistance(newpoints, T);
}

Point Centroid(std::vector<Point>& points)
{
	float x = 0.0f, y = 0.0f;
	unsigned i;
	Point ret;
	for (i = 0; i < points.size(); i++) {
		x += points[i].X;
		y += points[i].Y;
	}
	x /= points.size();
	y /= points.size();
	ret.X = x;
	ret.Y = y;
	return ret;
}

Rectangle BoundingBox(std::vector<Point>& points)
{
	Rectangle ret;
	unsigned i;
	float minX = FLT_MAX, maxX = FLT_MIN, minY = FLT_MAX, maxY = FLT_MIN;
	for (i = 0; i < points.size(); i++) {
		minX = std::min(minX, points[i].X);
		minY = std::min(minY, points[i].Y);
		maxX = std::max(maxX, points[i].X);
		maxY = std::max(maxY, points[i].Y);
	}
	ret.X      = minX;
	ret.Y      = minY;
	ret.Width  = maxX - minX;
	ret.Height = maxY - minY;
	return ret;
}

float PathDistance(std::vector<Point>& pts1, std::vector<Point>& pts2)
{
	float d = 0.0;
	unsigned i;
	for (i = 0; i < pts1.size(); i++) // assumes pts1.length == pts2.length
		d += Distance(pts1[i], pts2[i]);
	return d / pts1.size();
}

float PathLength(std::vector<Point>& points)
{
	float d = 0.0;
	unsigned i;
	for (i = 1; i < points.size(); i++)
		d += Distance(points[i - 1], points[i]);
	return d;
}

float Distance(Point p1, Point p2)
{
	float dx = p2.X - p1.X;
	float dy = p2.Y - p1.Y;
	return sqrt(dx * dx + dy * dy);
}
