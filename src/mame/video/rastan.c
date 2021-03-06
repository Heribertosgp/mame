// license:???
// copyright-holders:???
/***************************************************************************
  Functions to emulate video hardware on these Taito games:

  - rastan

***************************************************************************/

#include "emu.h"
#include "includes/rastan.h"

/***************************************************************************/

WRITE16_MEMBER(rastan_state::rastan_spritectrl_w)
{
	/* bits 5-7 are the sprite palette bank */
	m_pc090oj->set_sprite_ctrl((data & 0xe0) >> 5);

	/* bit 4 unused */

	/* bits 0 and 1 are coin lockout */
	coin_lockout_w(machine(), 1, ~data & 0x01);
	coin_lockout_w(machine(), 0, ~data & 0x02);

	/* bits 2 and 3 are the coin counters */
	coin_counter_w(machine(), 1, data & 0x04);
	coin_counter_w(machine(), 0, data & 0x08);
}

/***************************************************************************/

UINT32 rastan_state::screen_update_rastan(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	int layer[2];

	m_pc080sn->tilemap_update();

	layer[0] = 0;
	layer[1] = 1;

	screen.priority().fill(0, cliprect);

	m_pc080sn->tilemap_draw(screen, bitmap, cliprect, layer[0], TILEMAP_DRAW_OPAQUE, 1);
	m_pc080sn->tilemap_draw(screen, bitmap, cliprect, layer[1], 0, 2);

	m_pc090oj->draw_sprites(bitmap, cliprect, screen.priority(), 0);
	return 0;
}
