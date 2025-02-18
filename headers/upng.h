#pragma once

/**
 * uPNG -- derived from LodePNG version 20100808
 *
 * Copyright (c) 2005-2010 Lode Vandevenne
 * Copyright (c) 2010 Sean Middleditch
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *		1. The origin of this software must not be misrepresented; you must not
 *		claim that you wrote the original software. If you use this software
 *		in a product, an acknowledgment in the product documentation would be
 *		appreciated but is not required.
 *
 *		2. Altered source versions must be plainly marked as such, and must not be
 *		misrepresented as being the original software.
 *
 *		3. This notice may not be removed or altered from any source
 *		distribution.
 */

typedef enum upng_error
{
	UPNG_EOK            = 0, /* success (no error) */
	UPNG_ENOMEM         = 1, /* memory allocation failed */
	UPNG_ENOTFOUND      = 2, /* resource not found (file missing) */
	UPNG_ENOTPNG        = 3, /* image data does not have a PNG header */
	UPNG_EMALFORMED     = 4, /* image data is not a valid PNG image */
	UPNG_EUNSUPPORTED    = 5, /* critical PNG chunk type is not supported */
	UPNG_EUNINTERLACED  = 6, /* image interlacing is not supported */
	UPNG_EUNFORMAT      = 7, /* image color format is not supported */
	UPNG_EPARAM         = 8  /* invalid parameter to method call */
} upng_error;

typedef enum upng_format
{
	UPNG_BADFORMAT,
	UPNG_RGB8,
	UPNG_RGB16,
	UPNG_RGBA8,
	UPNG_RGBA16,
	UPNG_LUMINANCE1,
	UPNG_LUMINANCE2,
	UPNG_LUMINANCE4,
	UPNG_LUMINANCE8,
	UPNG_LUMINANCE_ALPHA1,
	UPNG_LUMINANCE_ALPHA2,
	UPNG_LUMINANCE_ALPHA4,
	UPNG_LUMINANCE_ALPHA8
} upng_format;

typedef struct upng_t upng_t;

/**
 * Create a new uPNG object from a byte buffer.
 * @param buffer Pointer to the PNG data.
 * @param size Size of the PNG data in bytes.
 * @return Pointer to the new uPNG object, or NULL on failure.
 */
upng_t *upng_new_from_bytes(const unsigned char *buffer, unsigned long size);

/**
 * Create a new uPNG object from a file.
 * @param path Path to the PNG file.
 * @return Pointer to the new uPNG object, or NULL on failure.
 */
upng_t *upng_new_from_file(const char *path);

/**
 * Free the uPNG object and its resources.
 * @param upng Pointer to the uPNG object to free.
 */
void upng_free(upng_t *upng);

/**
 * Read the header information from the uPNG object.
 * @param upng Pointer to the uPNG object.
 * @return Error code indicating the result of the operation.
 */
upng_error upng_header(upng_t *upng);

/**
 * Decode the PNG image data.
 * @param upng Pointer to the uPNG object.
 * @return Error code indicating the result of the operation.
 */
upng_error upng_decode(upng_t *upng);

/**
 * Get the last error code from the uPNG object.
 * @param upng Pointer to the uPNG object.
 * @return The last error code.
 */
upng_error upng_get_error(const upng_t *upng);

