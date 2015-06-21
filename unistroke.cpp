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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>

#include <oneiroi.h>

Unistroke get_unistroke(std::string name, unsigned id, std::vector<Point>& points)
{
	Unistroke ret;
	ret.Name = name;
	ret.Id   = id;
	ret.Points = Resample(points, NumPoints);
	float radians = IndicativeAngle(ret.Points);
	ret.Points = RotateBy(ret.Points, -radians);
	ret.Points = ScaleTo(ret.Points, SquareSize);
	ret.Points = TranslateTo(ret.Points, Origin);
	return ret;
}

int init_unistrokes(void)
{
	FILE *fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int count = 0;
	std::vector<Point> Points;

	std::string name;
	std::string linebuf;
	std::string tmp_coord;
	unsigned id;
	std::string::size_type i = -1, j = -1;;
	//unsigned i, j, k, l;
	int qx = 0, qy = 0;

	fp = fopen(NYX_GESTURES_FILE, "r");
	if (fp == NULL) {
		printf("%s: error opening file!\n", __func__);
		return -EIO;
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		if (read == 1) {
			continue;
		}
		switch(++count) {
			case 1:
				// name
				name.assign(line, (line+read - 1));
				break;
			case 2:
				// id
				line[strlen(line) - 1] = '\0'; // fixup last newline for null
				sscanf(line, "%03d", &id);
				break;
			case 3:
				// line
				linebuf.assign(line, (line+read - 1));

				i = -1;
				j = -1;


				while (
				std::string::npos != (i = linebuf.find("{", i+1)) &&
				std::string::npos != (j = linebuf.find("}", j+1))
				) {
					tmp_coord = linebuf.substr(i+1, ((j - i) - 1));
					qx = atof(tmp_coord.substr(0, tmp_coord.find(",")).c_str());
					qy = atof(tmp_coord.substr(tmp_coord.find(",")+1).c_str());
					Points.push_back({qx, qy});
				}

				Unistrokes.push_back(get_unistroke(name, id, Points));
				Points.clear();
				count = 0;
				break;
			default:
				; // nothing?
		}
	}

	fclose(fp);

	if (line)
		free(line);

	return 0;
}
