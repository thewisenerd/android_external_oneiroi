/*
 * oneiroi/include/oneiroi.h
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

#ifndef _ONEIROI_H
#define _ONEIROI_H

#include <vector>
#include <cmath>
#include <string>
#include <cfloat>

struct Point {
	float X;
	float Y;
};

struct Rectangle {
	float X;
	float Y;
	int   Width;
	int   Height;
};

struct Unistroke {
	std::string        Name;
	unsigned           Id;
	std::vector<Point> Points;
};

struct Result {
	std::string Name;
	float       Score;
};

#define Deg2Rad(d) ((d * M_PI) / 180.0f)

#define NumUnistrokes     16
#define NumPoints         64
#define SquareSize        250.0f
#define Diagonal          sqrt((SquareSize * SquareSize) + (SquareSize * SquareSize))
#define HalfDiagonal      (0.5 * Diagonal)
#define AngleRange        Deg2Rad(45.0)
#define AnglePrecision    Deg2Rad(2.0)
#define Phi               0.5 * (-1.0 + sqrt(5.0)) // Golden Ratio

extern Point Origin; // {0.0, 0.0}

extern std::vector<Point> Resample_newpoints;
extern std::vector<Point> RotateBy_newpoints;
extern std::vector<Point> ScaleTo_newpoints;
extern std::vector<Point> TranslateTo_newpoints;

extern std::vector<Unistroke> Unistrokes;

Unistroke           get_unistroke(std::string, std::vector<Point>&);
int                 init_unistrokes(void);

Result              Recognize(std::vector<Point>&);

std::vector<Point>& Resample(std::vector<Point>&, unsigned);
float               IndicativeAngle(std::vector<Point>&);
std::vector<Point>& RotateBy(std::vector<Point>&, float);
std::vector<Point>& ScaleTo(std::vector<Point>&, float);
std::vector<Point>& TranslateTo(std::vector<Point>&, Point);
float               DistanceAtBestAngle(std::vector<Point>&, std::vector<Point>&, float, float, float);
float               DistanceAtAngle(std::vector<Point>&, std::vector<Point>&, float);
Point               Centroid(std::vector<Point>&);
Rectangle           BoundingBox(std::vector<Point>&);
float               PathDistance(std::vector<Point>&, std::vector<Point>&);
float               PathLength(std::vector<Point>&);
float               Distance(Point, Point);

#define NYX_FILE               "/sys/nyx/nyx_data"
#define NYX_LOG_FILE           "/data/local/tmp/nyx_log"
#define NYX_GESTURES_FILE      "/data/local/tmp/gestures.txt"
#define NYX_SIZEOF_HEADER_BUF  2
#define NYX_SIZEOF_COORD       3
#define NYX_SIZEOF_CHARBUF     512

#endif // _ONEIROI_H
