// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
    Copyright (C) 2007, 2008 Bernd Arnold
    Copyright (C) 2008 Jerome Bigot
    Copyright (C) 2008 Markus Drescher

    This file is part of Bombermaaan.

    Bombermaaan is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Bombermaaan is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Bombermaaan.  If not, see <http://www.gnu.org/licenses/>.

    ************************************************************************************/


/**
 *  \file CDisplay.cpp
 *  \brief Load and display sprites, change screen mode
 */

#include "StdAfx.h"
#include "CDisplay.h"

#include "BombermaaanAssets.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CDisplay::CDisplay(void)
{
    // Reset view origin
    m_ViewOriginX = 0;
    m_ViewOriginY = 0;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CDisplay::~CDisplay(void)
{
    // Nothing to do
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CDisplay::Create(int Width, int Height)
{
    constexpr int Depth = 32;

    // If no display mode has been set yet or the current display mode is not the right one
    if (!m_VideoSDL.IsModeSet(Width, Height, Depth))
    {
        // Destroy SDLVideo interface and the sprite tables
        Destroy();

        // If SDLVideo object creation failed
        if (!m_VideoSDL.Create(Width, Height, Depth))
        {
            // Get out
            return false;
        }

        if (!LoadSprites(1, 1, 82, 41, false, BMP_GREEN_BACKGROUND_SOLID, BMP_GREEN_BACKGROUND_SOLID_SIZE) ||
            !LoadSprites(1, 1, 82, 41, false, BMP_BLUE_BACKGROUND_SOLID, BMP_BLUE_BACKGROUND_SOLID_SIZE) ||
            !LoadSprites(1, 1, 82, 41, false, BMP_PURPLE_BACKGROUND_SOLID, BMP_PURPLE_BACKGROUND_SOLID_SIZE) ||
            !LoadSprites(1, 1, 82, 41, false, BMP_RED_BACKGROUND_SOLID, BMP_RED_BACKGROUND_SOLID_SIZE) ||
            !LoadSprites(1, 1, 82, 41, false, BMP_GREEN_BACKGROUND_BOMB, BMP_GREEN_BACKGROUND_BOMB_SIZE) ||
            !LoadSprites(1, 1, 82, 41, false, BMP_BLUE_BACKGROUND_BOMB, BMP_BLUE_BACKGROUND_BOMB_SIZE) ||
            !LoadSprites(1, 1, 82, 41, false, BMP_PURPLE_BACKGROUND_BOMB, BMP_PURPLE_BACKGROUND_BOMB_SIZE) ||
            !LoadSprites(1, 1, 82, 41, false, BMP_RED_BACKGROUND_BOMB, BMP_RED_BACKGROUND_BOMB_SIZE) ||
            !LoadSprites(2, 1, 32, 32, false, BMP_ARENA_FLOOR, BMP_ARENA_FLOOR_SIZE) ||
            !LoadSprites(7, 1, 32, 32, true, BMP_ARENA_WALL, BMP_ARENA_WALL_SIZE) ||
            !LoadSprites(28, 1, 32, 32, true, BMP_ARENA_FLAME, BMP_ARENA_FLAME_SIZE) ||
            !LoadSprites(20, 1, 32, 32, false, BMP_ARENA_ITEM, BMP_ARENA_ITEM_SIZE) ||
            !LoadSprites(3, 1, 32, 32, true, BMP_ARENA_BOMB, BMP_ARENA_BOMB_SIZE) ||
            !LoadSprites(12, 8, 42, 44, true, BMP_ARENA_BOMBER_WALK, BMP_ARENA_BOMBER_WALK_SIZE) ||
            !LoadSprites(7, 1, 52, 54, true, BMP_ARENA_FIRE, BMP_ARENA_FIRE_SIZE) ||
            !LoadSprites(12, 8, 42, 44, true, BMP_ARENA_BOMBER_WALK_HOLD, BMP_ARENA_BOMBER_WALK_HOLD_SIZE) ||
            !LoadSprites(4, 1, 32, 32, true, BMP_ARENA_FLY, BMP_ARENA_FLY_SIZE) ||
            !LoadSprites(1, 1, 480, 26, false, BMP_BOARD_BACKGROUND, BMP_BOARD_BACKGROUND_SIZE) ||
            !LoadSprites(12, 1, 7, 10, true, BMP_BOARD_TIME, BMP_BOARD_TIME_SIZE) ||
            !LoadSprites(2, 1, 15, 7, true, BMP_BOARD_CLOCK_TOP, BMP_BOARD_CLOCK_TOP_SIZE) ||
            !LoadSprites(8, 1, 15, 13, true, BMP_BOARD_CLOCK_BOTTOM, BMP_BOARD_CLOCK_BOTTOM_SIZE) ||
            !LoadSprites(6, 1, 6, 8, true, BMP_BOARD_SCORE, BMP_BOARD_SCORE_SIZE) ||
            !LoadSprites(5, 2, 14, 14, true, BMP_BOARD_HEADS, BMP_BOARD_HEADS_SIZE) ||
            !LoadSprites(1, 1, 480, 442, false, BMP_DRAWGAME_MAIN, BMP_DRAWGAME_MAIN_SIZE) ||
            !LoadSprites(2, 1, 68, 96, false, BMP_DRAWGAME_FLAG, BMP_DRAWGAME_FLAG_SIZE) ||
            !LoadSprites(4, 1, 20, 62, true, BMP_DRAWGAME_FUMES, BMP_DRAWGAME_FUMES_SIZE) ||
            !LoadSprites(4, 5, 24, 32, true, BMP_WINNER_BOMBER, BMP_WINNER_BOMBER_SIZE) ||
            !LoadSprites(16, 1, 22, 22, true, BMP_WINNER_COIN, BMP_WINNER_COIN_SIZE) ||
            !LoadSprites(4, 1, 6, 6, true, BMP_WINNER_LIGHTS, BMP_WINNER_LIGHTS_SIZE) ||
            !LoadSprites(4, 2, 16, 16, true, BMP_WINNER_SPARKS, BMP_WINNER_SPARKS_SIZE) ||
            !LoadSprites(1, 1, 158, 16, true, BMP_WINNER_TITLE, BMP_WINNER_TITLE_SIZE) ||
            !LoadSprites(1, 1, 32, 405, false, BMP_VICTORY_WALL, BMP_VICTORY_WALL_SIZE) ||
            !LoadSprites(9, 1, 14, 16, true, BMP_VICTORY_CROWD, BMP_VICTORY_CROWD_SIZE) ||
            !LoadSprites(14, 5, 36, 61, true, BMP_VICTORY_BOMBER, BMP_VICTORY_BOMBER_SIZE) ||
            !LoadSprites(1, 1, 192, 60, true, BMP_VICTORY_TITLE, BMP_VICTORY_TITLE_SIZE) ||
            !LoadSprites(46, 6, 10, 10, true, BMP_GLOBAL_FONT, BMP_GLOBAL_FONT_SIZE) ||
            !LoadSprites(5, 2, 21, 19, true, BMP_MENU_BOMBER, BMP_MENU_BOMBER_SIZE) ||
            !LoadSprites(1, 1, 420, 362, true, BMP_MENU_FRAME_1, BMP_MENU_FRAME_1_SIZE) ||
            !LoadSprites(2, 1, 15, 16, true, BMP_MENU_HAND, BMP_MENU_HAND_SIZE) ||
            !LoadSprites(5, 1, 23, 23, true, BMP_WINNER_CROSS, BMP_WINNER_CROSS_SIZE) ||
            !LoadSprites(5, 5, 14, 15, true, BMP_VICTORY_CONFETTIS_LARGE, BMP_VICTORY_CONFETTIS_LARGE_SIZE) ||
            !LoadSprites(5, 5, 13, 14, true, BMP_VICTORY_CONFETTIS_MEDIUM, BMP_VICTORY_CONFETTIS_MEDIUM_SIZE) ||
            !LoadSprites(5, 5, 10, 10, true, BMP_VICTORY_CONFETTIS_SMALL, BMP_VICTORY_CONFETTIS_SMALL_SIZE) ||
            !LoadSprites(1, 1, 200, 36, true, BMP_PAUSE, BMP_PAUSE_SIZE) ||
            !LoadSprites(1, 1, 200, 36, true, BMP_HURRY, BMP_HURRY_SIZE) ||
            !LoadSprites(1, 1, 154, 93, true, BMP_MENU_FRAME_2, BMP_MENU_FRAME_2_SIZE) ||
            !LoadSprites(3, 4, 32, 32, true, BMP_ARENA_FUMES, BMP_ARENA_FUMES_SIZE) ||
            !LoadSprites(1, 1, 14, 14, true, BMP_BOARD_DRAWGAME, BMP_BOARD_DRAWGAME_SIZE) ||
            !LoadSprites(1, 1, 480, 442, false, BMP_TITLE_BACKGROUND, BMP_TITLE_BACKGROUND_SIZE) ||
            !LoadSprites(1, 1, 480, 126, true, BMP_TITLE_BOMBERS, BMP_TITLE_BOMBERS_SIZE) ||
            !LoadSprites(1, 1, 298, 139, true, BMP_TITLE_TITLE, BMP_TITLE_TITLE_SIZE) ||
            !LoadSprites(2, 6, 128, 26, true, BMP_TITLE_MENU_ITEMS, BMP_TITLE_MENU_ITEMS_SIZE) ||
            !LoadSprites(1, 1, 138, 46, true, BMP_TITLE_CLOUD_1, BMP_TITLE_CLOUD_1_SIZE) ||
            !LoadSprites(1, 1, 106, 46, true, BMP_TITLE_CLOUD_2, BMP_TITLE_CLOUD_2_SIZE) ||
            !LoadSprites(1, 1, 66, 22, true, BMP_TITLE_CLOUD_3, BMP_TITLE_CLOUD_3_SIZE) ||
            !LoadSprites(18, 1, 16, 16, true, BMP_LEVEL_MINI_TILES, BMP_LEVEL_MINI_TILES_SIZE) ||
            !LoadSprites(5, 1, 24, 20, true, BMP_LEVEL_MINI_BOMBERS, BMP_LEVEL_MINI_BOMBERS_SIZE) ||
            !LoadSprites(7, 5, 42, 44, true, BMP_ARENA_BOMBER_DEATH, BMP_ARENA_BOMBER_DEATH_SIZE) ||
            !LoadSprites(12, 8, 42, 44, true, BMP_ARENA_BOMBER_LIFT, BMP_ARENA_BOMBER_LIFT_SIZE) ||
            !LoadSprites(20, 8, 42, 44, true, BMP_ARENA_BOMBER_THROW, BMP_ARENA_BOMBER_THROW_SIZE) ||
            !LoadSprites(8, 8, 42, 44, true, BMP_ARENA_BOMBER_PUNCH, BMP_ARENA_BOMBER_PUNCH_SIZE) ||
            !LoadSprites(4, 8, 42, 44, true, BMP_ARENA_BOMBER_STUNT, BMP_ARENA_BOMBER_STUNT_SIZE) ||
            !LoadSprites(4, 1, 32, 32, true, BMP_ARENA_ARROWS, BMP_ARENA_ARROWS_SIZE) ||
            !LoadSprites(1, 1, 30, 32, true, BMP_MENU_HAND_TITLE, BMP_MENU_HAND_TITLE_SIZE) ||
            !LoadSprites(3, 1, 32, 32, true, BMP_ARENA_REMOTE_BOMB, BMP_ARENA_REMOTE_BOMB_SIZE))
        {
            // Failure, get out (error is logged by the LoadSprites() method)
            return false;
        }

        // Save origin where to draw from
        m_ViewOriginX = (Width - VIEW_WIDTH) / 2;
        m_ViewOriginY = (Height - VIEW_HEIGHT) / 2;

        m_VideoSDL.SetOrigin(m_ViewOriginX, m_ViewOriginY);
    }

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CDisplay::Create()
{
    return Create(VIEW_WIDTH, VIEW_HEIGHT);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CDisplay::Destroy(void)
{
    // Destroy SDLVideo interface and the sprite tables
    m_VideoSDL.Destroy();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CDisplay::LoadSprites(int SpriteTableWidth,
                           int SpriteTableHeight,
                           int SpriteWidth,
                           int SpriteHeight,
                           bool Transparent,
                           const uint8_t* BitmapData,
                           uint32_t BitmapSize)
{
    if (!m_VideoSDL.LoadSprites(SpriteTableWidth,
                                SpriteTableHeight,
                                SpriteWidth,
                                SpriteHeight,
                                Transparent,
                                BitmapData,
                                BitmapSize))
    {
        // Get out, failure
        return false;
    }

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
