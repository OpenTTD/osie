/* $Id$ */

/*
 * osie is a tool to extract metadata from OpenTTD's screenshots.
 * Copyright (C) 2010  Remko Bijker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/** @file osie.cpp Application for getting the saved information from OpenTTD screenshots */

#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "rev.hpp"


/**
 * Show the help to the user.
 * @param cmd the command line the user used
 */
void ShowHelp(const char *cmd)
{
	printf(
		"osie version %s - Copyright 2010 by Remko Bijker\n"
		"Usage:\n"
		"  %s <file>\n"
		"    Get the savegame information stored in the screenshot.\n"
		"\n"
		"<file> denotes the .png screenshot file you want to get the information from\n"
		"\n"
		"osie is Copyright 2010 by Remko Bijker\n"
		"You may copy and redistribute it under the terms of the GNU General Public\n"
		"License version 2, as stated in the file 'COPYING'\n",
		_osie_version, cmd
	);
}

/**
 * Oh hello, the user has found the way in :)
 * @param argc the number of arguments + 1
 * @param argv list with given arguments
 */
int main(int argc, char *argv[])
{
	if (argc != 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		ShowHelp(argv[0]);
		return 0;
	}

	png_structp png_ptr = NULL;
	png_infop info_ptr  = NULL;
	int ret = -1;
	png_byte header[8]; // 8 is the maximum size that can be checked

	png_textp text = NULL;
	int num = 0;

	/* Open file and test for it being a png */
	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "File %s could not be opened for reading\n", argv[1]);
		goto exit;
	}

	if (fread(header, 1, 8, fp) != 8 || png_sig_cmp(header, 0, 8) != 0) {
		fprintf(stderr, "File %s is not recognized as a PNG file\n", argv[1]);
		goto exit;
	}

	/* Initialize stuff */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fprintf(stderr, "png_create_read_struct failed\n");
		goto exit;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "png_create_info_struct failed\n");
		goto exit;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Couldn't set jmpbuf\n");
		goto exit;
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);

	png_get_text(png_ptr, info_ptr, &text, &num);

	if (num == 0) {
		fprintf(stderr, "The png does not seem to have metadata\n");
		goto exit;
	}

	for (int i = 0; i < num; i++) {
		printf("%s: %s\n", text[i].key, text[i].text);
	}
	ret = 0;

exit:
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	if (fp != NULL) fclose(fp);

	return ret;
}
