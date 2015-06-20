/*
 * oneiroi/oneiroi.c
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

#define NYX_FILE               "/sys/nyx/nyx_data"
#define NYX_LOG                "/data/local/tmp/nyx_log"
#define NYX_SIZEOF_HEADER_BUF  2
#define NYX_SIZEOF_COORD       3
#define NYX_SIZEOF_CHARBUF     512

Point Origin = {0.0f, 0.0f};
std::vector<Point> Resample_newpoints;
std::vector<Point> RotateBy_newpoints;
std::vector<Point> ScaleTo_newpoints;
std::vector<Point> TranslateTo_newpoints;

std::vector<Unistroke> Unistrokes;

int oneiroi_init(int argc, char **argv) {
	char ch;
	/* char charbuf[(NYX_SIZEOF_COORD * NYX_SIZEOF_CHARBUF)]; */
	char charbuf[NYX_SIZEOF_COORD];
	unsigned i;
	//point Points[NYX_SIZEOF_COORDCHARBUF][2]
	std::vector<Point> Points;
	FILE *ifp;
	int debug = 2;
	unsigned nyx_count = 0;
	Result ret;

	printf("%s: oneiroi!\n", __func__);

	ifp = fopen(NYX_FILE, "r");
	if (ifp == NULL) {
		printf("%s: error opening file!\n", __func__);
		return -EIO;
	}

	ch = fgetc(ifp);
	nyx_count |= ((ch == 0xff) ? 0x00 : ((ch - '0') << 4));
	if (debug > 2) {
		printf("\t1: %d\n", ch);
	}

	ch = fgetc(ifp);
	nyx_count |= ch;
	if (debug > 2) {
		printf("\t2: %d\n", ch);
	}

	if (debug)
		printf("%s: nyx_count: %d\n", __func__, nyx_count);

	fclose(ifp);

	if (!nyx_count) {
		printf("%s: nyx_count zero! reutrn;\n", __func__);
		return -EINVAL;
	}

	ifp = fopen(NYX_FILE, "r");
	for (i = 0; i < NYX_SIZEOF_HEADER_BUF; i++)
		ch = fgetc(ifp);

	for (i = 0; i < nyx_count; i++) {
		int x, y;

		int j = 0;
		for (j = 0; j < NYX_SIZEOF_COORD; j++)
			charbuf[j] = fgetc(ifp);

		//fgets(charbuf, NYX_SIZEOF_COORD, ifp);
		//printf("%03i: %d, %d, %d\n", i, charbuf[0], charbuf[1], charbuf[2]);

		x &= 0x00;
		x |= (charbuf[0] << 4);
		if (debug > 2)
			printf("%i: x1: %d\n", i, x);
		x |= (charbuf[1] >> 4);
		if (debug > 2)
			printf("%i: x2: %d\n", i, x);


		y &= 0x00;
		y |= ((charbuf[1] & 0x0f) << 8);
		if (debug > 2)
			printf("%i: y1: %d\n", i, y);
		y |= charbuf[2];
		if (debug > 2)
			printf("%i: y2: %d\n", i, y);

		Points.insert(Points.begin(), {(float)x, (float)y});

		if (debug > 2)
			printf("%s: touch %03d: %i, %i\n", __func__, i, x, y);
	} // for

	ret =

	return 0;
}
