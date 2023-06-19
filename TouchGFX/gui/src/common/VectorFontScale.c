#ifndef SIMULATOR
#include <stdint.h>
#include <string.h>

#include <nema_cmdlist.h>
#include <nema_blender.h>
#include <nema_graphics.h>

#include "nema_vg.h"
#include "nema_vg_context.h"
#include "nema_vg_font.h"
#include "malgunbd_ttf_kern.hpp"
#include <stm32u5xx_hal.h>

#define VECTOR_FONT malgunbd_ttf_kern

static NEMA_VG_PAINT_HANDLE fontPaint;
static uint32_t rgbaBlack;

// to be replaced by UART coming text
static const uint16_t koreanText1AsUnicode16[] = {
	0xC0BC, 0xC131, 0x0020, 0xC0DD, 0xD65C, 0x0020, 0xAC00, 0xC804, 0x0}; // 삼성 생활 가전

static const uint16_t koreanText2AsUnicode16[] = {
	0xd55c, 0xad6d, 0xc5b4, 0x0}; // korean in korean

static const uint16_t koreanText3AsUnicode16[] = {
	0xc548, 0xb155, 0xd558, 0xc138, 0xc694, 0x0}; // 안녕하세요. Not in the attached malgunbd_ttf_kern.c. Create it or a new one with more characters using NeochromSDK

static uint8_t koreanTextAsUTF8[256] = {0};

uint16_t toUTF8(const uint16_t *unicode, uint8_t *utf8, uint16_t maxbytes)
{
	uint16_t bytes = 0;
	while (bytes < maxbytes)
	{
		if (*unicode <= 0x7F) // always true "&& bytes < maxbytes"
		{
			// U+0000-U+007F: 0xxxxxxx
			*utf8++ = (uint8_t)(*unicode);
			bytes++;
		}
		else if (*unicode <= 0x7FF && bytes + 1 < maxbytes)
		{
			// U+0080-U+07FF: 110xxxxx 10xxxxxx
			*utf8++ = (*unicode >> 6) | 0xC0;
			*utf8++ = (*unicode & 0x3F) | 0x80;
			bytes += 2;
		}
		else if (bytes + 2 < maxbytes) // always true: "&& *unicode <= 0x7FFF"
		{
			// U+0800-U+7FFF: 1110xxxx 10xxxxxx 10xxxxxx
			*utf8++ = (*unicode >> 12) | 0xE0;
			*utf8++ = ((*unicode >> 6) & 0x3F) | 0x80;
			*utf8++ = (*unicode & 0x3F) | 0x80;
			bytes += 3;
		}
		else
		{
			// No room to decode character, abort!
			break;
		}
		if (*unicode++ == 0)
		{
			break;
		}
	}
	return bytes;
}

void fpga_demo_setup_font()
{
	fontPaint = nema_vg_paint_create();
	uint32_t rgba8888 = nema_rgba(255, 255, 255, 255);
	nema_vg_paint_set_type(fontPaint, rgba8888);

	nema_vg_bind_font(&VECTOR_FONT);
	rgbaBlack = nema_rgba(0x00, 0x00, 0x00, 255);
}

void fpga_demo_release_font()
{
	nema_vg_paint_destroy(fontPaint);
}

uint32_t FONT_COLOR = 0xe6b43cff;
extern const unsigned char image_tile_bg[];

// Used by Screen 1 and vector font size change
void fpga_demo_draw_font(uint16_t *const fb, const int32_t x, const int32_t y, const uint32_t w, const uint32_t h, const float scale, bool state)
{
	// Convert text string to UTF-8 encoding.
	if (state)
	{
		toUTF8(koreanText1AsUnicode16, koreanTextAsUTF8, 256);
	}
	else
	{
		toUTF8(koreanText2AsUnicode16, koreanTextAsUTF8, 256);
	}

	nema_bind_dst_tex((uint32_t)fb, 480, 480, NEMA_BGR24, -1); // 480 = fb.w and fb.h
	nema_vg_set_font_size(20.0f * scale);					   // change the size of the vector font size
	nema_set_clip(x, y, w, h);

	// overwrite the zone with a white box to clean the zone
	nema_clear(nema_rgba(255, 255, 255, 0xff));

	// Draw letters
	nema_set_blend_fill(NEMA_BL_SIMPLE);
	nema_vg_paint_set_paint_color(fontPaint, rgbaBlack);

	nema_matrix3x3_t mat;
	nema_mat3x3_load_identity(mat);

	nema_vg_print(fontPaint, (const char *)koreanTextAsUTF8, x, y, w, h, NEMA_VG_ALIGNX_LEFT, mat);

	// Make sure the command list is processed before returning.
	nema_cmdlist_t *cmd = nema_cl_get_bound();
	nema_cl_submit(cmd);
	nema_cl_wait(cmd);
}

// Used by Screen 3 and vector font scaling
void fpga_demo_draw_font_scale(uint16_t *const fb, const int32_t x, const int32_t y, const uint32_t w, const uint32_t h, const float scale, const int offset, bool state)
{
	// Convert text string to UTF-8 encoding.
	if (state)
	{
		toUTF8(koreanText1AsUnicode16, koreanTextAsUTF8, 256);
	}
	else
	{
		toUTF8(koreanText3AsUnicode16, koreanTextAsUTF8, 256);
	}

	nema_bind_dst_tex((uint32_t)fb, 480, 480, NEMA_BGR24, -1); // 480 = fb.w and fb.h
	nema_vg_set_font_size(20.0f);
	nema_set_clip(x, y, w, h);

	// overwrite the zone with a white box
	nema_clear(nema_rgba(255, 255, 255, 0xff));

	// Draw letters
	nema_set_blend_fill(NEMA_BL_SIMPLE);
	nema_vg_paint_set_paint_color(fontPaint, rgbaBlack);

	nema_matrix3x3_t mat;
	nema_mat3x3_load_identity(mat);
	nema_mat3x3_scale(mat, scale, scale);
	// nema_mat3x3_translate(mat, -offset, -offset);

	nema_vg_print(fontPaint, (const char *)koreanTextAsUTF8, x - offset, y - offset, w, h, NEMA_VG_ALIGNX_LEFT, mat);

	// Make sure the command list is processed before returning.
	nema_cmdlist_t *cmd = nema_cl_get_bound();
	nema_cl_submit(cmd);
	nema_cl_wait(cmd);
}

#endif