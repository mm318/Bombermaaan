// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
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
 *  \file CVideoSDL.cpp
 *  \brief SDL video on Linux
 */

#include <algorithm>
#include "StdAfx.h"
#include "BombermaaanAssets.h"

#include "CVideoSDL.h"
#include "hqx/HQ2x.hh"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
constexpr Uint32 rmask = 0x0000ff00;
constexpr Uint32 gmask = 0x00ff0000;
constexpr Uint32 bmask = 0xff000000;
constexpr Uint32 amask = 0x000000ff;
#else
constexpr Uint32 rmask = 0x00ff0000;
constexpr Uint32 gmask = 0x0000ff00;
constexpr Uint32 bmask = 0x000000ff;
constexpr Uint32 amask = 0xff000000;
#endif

static const char* GetSDLVideoError();

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CVideoSDL::CVideoSDL(void)
{
    m_hWnd = NULL;
    m_Width = 0;
    m_Height = 0;
    m_Depth = 0;
    m_pPrimary = NULL;
    m_PrimaryRect = SDL_Rect();
#ifdef BOMBERMAAAN_SCALE_2X
    m_pBackBuffer = NULL;
    m_BackBufferRect = SDL_Rect();
#endif
    m_OriginX = 0;
    m_OriginY = 0;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CVideoSDL::~CVideoSDL(void)
{
    // Nothing to do
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CVideoSDL::Create(int Width, int Height, int Depth)
{

    theLog.WriteLine("CVideoSDL       => rmask: 0x%x", rmask);
    theLog.WriteLine("CVideoSDL       => gmask: 0x%x", gmask);
    theLog.WriteLine("CVideoSDL       => bmask: 0x%x", bmask);
    theLog.WriteLine("CVideoSDL       => amask: 0x%x", amask);

    // Set the display properties
    m_Width = Width;
    m_Height = Height;
    m_Depth = Depth;

    m_pPrimary = NULL;
#ifdef BOMBERMAAAN_SCALE_2X
    m_pBackBuffer = NULL;
    constexpr int scale = 2;
#else
    constexpr int scale = 1;
#endif

    bool validMode = false; // is this video mode valid?

    // Enumerate all display modes (without taking refresh rates into account)
    SDL_Rect** modes = SDL12_ListModes(NULL, SDL_HWSURFACE | SDL_DOUBLEBUF);

    // some mode available?
    if (modes == (SDL_Rect **)0)
    {
        // Log failure
        theLog.WriteLine("SDLVideo        => !!! Could not find any video modes.");
        theLog.WriteLine("SDLVideo        => !!! SDLVideo error is : %s.", GetSDLVideoError());

        // Get out
        return false;
    }
    else if (modes == (SDL_Rect **)-1)
    {
        // Log success
        theLog.WriteLine("SDLVideo        => All modes available");

        // so this mode is possible
        validMode = true;
    }
    else
    {
        // enumerate modes and add certain
        for (int i = 0; modes[i]; ++i) {
            // is our requested mode possbile?
            if (modes[i]->w == m_Width && modes[i]->h == m_Height) {
                validMode = true;
            }
        }
    }

    if (!validMode) {
        // Log failure
        theLog.WriteLine("SDLVideo        => !!! Requested video mode %dx%d not found.", m_Width, m_Height);

        // Get out
        return false;
    }

    // Log that windowed mode is being initialized
    theLog.WriteLine("SDLVideo        => Initializing SDLVideo interface for windowed mode %dx%d.", m_Width, m_Height);

    // Get normal windowed mode
    m_pPrimary = SDL12_SetVideoMode(scale * m_Width, scale * m_Height, m_Depth, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (m_pPrimary == NULL) {
        theLog.WriteLine("SDLVideo        => !!! Requested video mode could not be set. (primary surface)");  // Log failure
        return false;   // Get out
    }
    // Get the rects of the viewport and screen bounds
    m_PrimaryRect.x = 0;
    m_PrimaryRect.y = 0;
    m_PrimaryRect.w = scale * m_Width;
    m_PrimaryRect.h = scale * m_Height;

#ifdef BOMBERMAAAN_SCALE_2X
    m_pBackBuffer = SDL12_CreateRGBSurface(SDL_HWSURFACE, m_Width, m_Height, 32, rmask, gmask, bmask, amask);
    if (m_pBackBuffer == NULL) {
        theLog.WriteLine("SDLVideo        => !!! Requested buffer could not be made. (back buffer)");  // Log failure
        return false;   // Get out
    }
    m_BackBufferRect.x = 0;
    m_BackBufferRect.y = 0;
    m_BackBufferRect.w = m_Width;
    m_BackBufferRect.h = m_Height;
#endif

    // show cursor depending on windowed/fullscreen mode
    SDL12_ShowCursor(true);

    SDL_RWops *rwIcon = SDL12_RWFromMem(const_cast<uint8_t*>(BombermaaanIconSmall), BombermaaanIconSmallSize);

    SDL_Surface *icon = SDL12_LoadBMP_RW(rwIcon, 0);

    if (icon != NULL)
    {
        if (SDL12_SetColorKey(icon, SDL_SRCCOLORKEY, SDL12_MapRGB(icon->format, 0x00, 0xff, 0x00)) == 0)
        {
            SDL12_WM_SetIcon(icon, NULL);
        }
    }
    else
    {
        printf("could not load icon.\n");
    }

    SDL12_FreeSurface(icon);
    SDL12_FreeRW(rwIcon);

    // Clear the back buffer surface
    Clear();

    // Reset origin
    m_OriginX = 0;
    m_OriginY = 0;

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Destroys the SDLVideo interface

void CVideoSDL::Destroy(void)
{
    // Free drawing requests, sprite tables, surfaces...
    FreeSprites();

#ifdef BOMBERMAAAN_SCALE_2X
    // If the back buffer surface exists
    if (m_pBackBuffer != NULL)
    {
        // Release it
        SDL12_FreeSurface(m_pBackBuffer);
        m_pBackBuffer = NULL;

        // Log release
        theLog.WriteLine("SDLVideo        => Backbuffer surface was released.");
    }
#endif

    // If the primary surface exists
    if (m_pPrimary != NULL)
    {
        // Release it
        SDL12_FreeSurface(m_pPrimary);
        m_pPrimary = NULL;

        // Log release
        theLog.WriteLine("SDLVideo        => Primary surface was released.");
    }

    // Log release
    theLog.WriteLine("SDLVideo        => SDLVideo objects were released.");
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Updates the display by blitting the back buffer
// surface on the primary surface.

void CVideoSDL::UpdateScreen(void)
{
    HRESULT hRet;

#ifdef BOMBERMAAAN_SCALE_2X
    HQ2x().resize(reinterpret_cast<uint32_t*>(m_pBackBuffer->pixels),
                  m_Width,
                  m_Height,
                  reinterpret_cast<uint32_t*>(m_pPrimary->pixels));
#endif

    while (true)
    {
        // Update the primary surface by flipping backbuffer and primary surface
        hRet = SDL12_Flip(m_pPrimary);
        SDL12_Delay(5);

        // If it worked fine
        if (hRet == 0)
        {
            // Get out
            break;
        }

        // Log failure
        if (hRet != 0) {
            theLog.WriteLine("SDLVideo        => !!! Updating failed (switching primary/backbuffer).");
            theLog.WriteLine("SDLVideo        => !!! SDLVideo error is : %s.", GetSDLVideoError());
        }
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Updates the object : this updates the drawing zones in case the window moves.

void CVideoSDL::OnWindowMove()
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CVideoSDL::DrawSprite(int PositionX,
                           int PositionY,
                           RECT *pZone,
                           RECT *pClip,
                           const void* SpriteTable,
                           int Sprite,
                           int SpriteLayer,
                           int PriorityInLayer)
{

    // Prepare a drawing request
    SDrawingRequest DrawingRequest;

    // Save the sprite pointer
    SSprite *pSprite = &m_SpriteTables[SpriteTable][Sprite];

    // If we have to take care of clipping
    if (pClip != NULL)
    {
        // Save the sprite size
        int SpriteSizeX = pSprite->ZoneX2 - pSprite->ZoneX1;
        int SpriteSizeY = pSprite->ZoneY2 - pSprite->ZoneY1;

        // If the sprite is completely out of the clip rect
        if (PositionX >= pClip->right ||
            PositionY >= pClip->bottom ||
            PositionX + SpriteSizeX < pClip->left ||
            PositionY + SpriteSizeY < pClip->top)
        {
            // Get out, don't even register the drawing request
            return;
        }

        // If the sprite has to be clipped on the left
        if (PositionX < pClip->left)
        {
            // Clip on the left
            DrawingRequest.PositionX = pClip->left;
            DrawingRequest.ZoneX1 = pSprite->ZoneX1 + pClip->left - PositionX;
        }
        // If no clip on the left is needed
        else
        {
            // Don't clip
            DrawingRequest.PositionX = PositionX;
            DrawingRequest.ZoneX1 = pSprite->ZoneX1;
        }

        // If the sprite has to be clipped on the top
        if (PositionY < pClip->top)
        {
            // Clip on the top
            DrawingRequest.PositionY = pClip->top;
            DrawingRequest.ZoneY1 = pSprite->ZoneY1 + pClip->top - PositionY;
        }
        // If no clip on the top is needed
        else
        {
            // Don't clip
            DrawingRequest.PositionY = PositionY;
            DrawingRequest.ZoneY1 = pSprite->ZoneY1;
        }

        // If the sprite has to be clipped on the right
        if (PositionX + SpriteSizeX >= pClip->right)
        {
            // Clip on the right
            DrawingRequest.ZoneX2 = pSprite->ZoneX1 + pClip->right - PositionX;
        }
        // If no clip on the right is needed
        else
        {
            // Don't clip
            DrawingRequest.ZoneX2 = pSprite->ZoneX2;
        }

        // If the sprite has to be clipped on the bottom
        if (PositionY + SpriteSizeY >= pClip->bottom)
        {
            // Clip on the bottom
            DrawingRequest.ZoneY2 = pSprite->ZoneY1 + pClip->bottom - PositionY;
        }
        // If no clip on the bottom is needed
        else
        {
            // Don't clip
            DrawingRequest.ZoneY2 = pSprite->ZoneY2;
        }
    }
    // If we don't have to care about clipping
    else
    {
        // Use the desired position
        DrawingRequest.PositionX = PositionX;
        DrawingRequest.PositionY = PositionY;

        // Use the zone of the sprite
        DrawingRequest.ZoneX1 = pSprite->ZoneX1;
        DrawingRequest.ZoneY1 = pSprite->ZoneY1;
        DrawingRequest.ZoneX2 = pSprite->ZoneX2;
        DrawingRequest.ZoneY2 = pSprite->ZoneY2;
    }

    // Finish preparing the drawing request
    DrawingRequest.PositionX += m_OriginX;
    DrawingRequest.PositionY += m_OriginY;
    DrawingRequest.SpriteTable = SpriteTable;
    DrawingRequest.Sprite = Sprite;
    DrawingRequest.SpriteLayer = SpriteLayer;
    DrawingRequest.PriorityInLayer = PriorityInLayer;

    // Store it (automatic sort)
    m_DrawingRequests.push_back(DrawingRequest);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CVideoSDL::DrawDebugRectangle(int PositionX,
    int PositionY,
    int w, int h,
    Uint8 r, Uint8 g, Uint8 b,
    int SpriteLayer,
    int PriorityInLayer)
{
    // Prepare a drawing request
    SDebugDrawingRequest DrawingRequest;

    // Use the desired position
    DrawingRequest.PositionX = PositionX;
    DrawingRequest.PositionY = PositionY;

    // Use the zone of the sprite
    DrawingRequest.ZoneX1 = 0;
    DrawingRequest.ZoneY1 = 0;
    DrawingRequest.ZoneX2 = w;
    DrawingRequest.ZoneY2 = h;

    // rectangle colour
    DrawingRequest.R = r;
    DrawingRequest.G = g;
    DrawingRequest.B = b;

    // Finish preparing the drawing request
    DrawingRequest.PositionX += m_OriginX;
    DrawingRequest.PositionY += m_OriginY;
    DrawingRequest.SpriteLayer = SpriteLayer;
    DrawingRequest.PriorityInLayer = PriorityInLayer;

    // Store it (automatic sort)
    m_DebugDrawingRequests.push_back(DrawingRequest);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CVideoSDL::RemoveAllDebugRectangles()
{
    m_DebugDrawingRequests.clear();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Makes the display black.

void CVideoSDL::Clear()
{
    SDL12_FillRect(m_pPrimary, &m_PrimaryRect, 0);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

WORD CVideoSDL::GetNumberOfBits(DWORD dwMask)
{
    WORD wBits = 0;
    while (dwMask)
    {
        dwMask = dwMask & (dwMask - 1);
        wBits++;
    }
    return wBits;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool CVideoSDL::LoadSprites(int SpriteTableWidth,
                            int SpriteTableHeight,
                            int SpriteWidth,
                            int SpriteHeight,
                            bool Transparent,
                            const uint8_t* BitmapData,
                            uint32_t BitmapSize)
{

    SSurface Surface;

    SDL_RWops *rwBitmap = SDL12_RWFromMem(const_cast<uint8_t*>(BitmapData), BitmapSize);

    // Create a SDLVideo surface for this bitmap
    SDL_Surface *ddsd = SDL12_LoadBMP_RW(rwBitmap, 0);

    SDL12_FreeRW(rwBitmap);

    // If it failed
    if (ddsd == NULL)
    {
        // Log failure
        theLog.WriteLine("SDLVideo        => !!! Could not create surface.");
        theLog.WriteLine("SDLVideo        => !!! SDLVideo error is : %s.", GetSDLVideoError());

        // Get out
        return false;
    }

    // Blit the bitmap onto the SDLVideo surface
    Surface.pSurface = ddsd;

    //----------------------------------------------
    // Set the surface transparency color if needed
    //----------------------------------------------

    // If the sprite table uses transparency
    if (Transparent)
    {
        // Apply the color key to the surface
        HRESULT hRet = SDL12_SetColorKey(ddsd, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL12_MapRGBA(ddsd->format, 0x00, 0xff, 0x00, 0xff));

        // If it failed
        if (hRet != 0)
        {
            // Log failure
            theLog.WriteLine("SDLVideo        => !!! Could not set colorkey.");
            theLog.WriteLine("SDLVideo        => !!! SDLVideo error is : %s.", GetSDLVideoError());

            // Get out
            return false;
        }
    }

    //-----------------------
    // Store the new surface
    //-----------------------

    // Add the surface to the surface container
    m_Surfaces.push_back(Surface);

    //---------------------------
    // Create the sprite table
    //---------------------------

    // Prepare a sprite table
    ::portable_stl::vector<SSprite> SpriteTable;

    // Variable rectangle coordinates that will be passed during sprite creations
    int ZoneX1 = 1;
    int ZoneY1 = 1;
    int ZoneX2 = 1 + SpriteWidth;
    int ZoneY2 = 1 + SpriteHeight;

    // Scan all the sprites in this surface
    for (int Y = 0; Y < SpriteTableHeight; Y++)
    {
        for (int X = 0; X < SpriteTableWidth; X++)
        {
            // Prepare a sprite
            SSprite Sprite;
            Sprite.SurfaceNumber = m_Surfaces.size() - 1;       // The surface we just added to the container
            Sprite.ZoneX1 = ZoneX1;
            Sprite.ZoneY1 = ZoneY1;
            Sprite.ZoneX2 = ZoneX2;
            Sprite.ZoneY2 = ZoneY2;

            // Advance the rectangle on the row
            ZoneX1 += SpriteWidth + 1;
            ZoneX2 += SpriteWidth + 1;

            // Add the sprite to the sprite table
            SpriteTable.push_back(Sprite);
        }

        // Back to beginning of row
        ZoneX1 = 1;
        ZoneX2 = 1 + SpriteWidth;

        // Make the rectangle go down
        ZoneY1 += SpriteHeight + 1;
        ZoneY2 += SpriteHeight + 1;
    }

    // Store the sprite table
    m_SpriteTables[BitmapData] = SpriteTable;

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CVideoSDL::FreeSprites(void)
{
    // Empty drawing requests queue
    m_DrawingRequests.clear();

    // Remove all sprite tables
    m_SpriteTables.clear();

    // Scan all the surfaces
    for (unsigned int i = 0; i < m_Surfaces.size(); i++)
    {
        // If the surface exists
        if (m_Surfaces[i].pSurface != NULL)
        {
            // Release it
            SDL12_FreeSurface(m_Surfaces[i].pSurface);
            m_Surfaces[i].pSurface = NULL;
        }
    }

    // Remove all surfaces
    m_Surfaces.clear();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CVideoSDL::UpdateAll(void)
{
    std::sort(m_DrawingRequests.begin().base(), m_DrawingRequests.end().base());
    // While all the drawing requests have not been executed
    for (::portable_stl::vector<SDrawingRequest>::iterator it = m_DrawingRequests.begin(); it != m_DrawingRequests.end(); ++it)
    {
        // Save the top drawing request
        const SDrawingRequest &DR = *it;

        // Save the sprite as specified by this drawing request
        const SSprite *pSprite = &m_SpriteTables[DR.SpriteTable][DR.Sprite];

        // Build a RECT structure containing the zone to draw
        SDL_Rect SourceRect;
        SourceRect.x = DR.ZoneX1;
        SourceRect.y = DR.ZoneY1;
        SourceRect.w = DR.ZoneX2 - DR.ZoneX1;
        SourceRect.h = DR.ZoneY2 - DR.ZoneY1;

        SDL_Rect DestRect;
        DestRect.x = DR.PositionX;
        DestRect.y = DR.PositionY;
        DestRect.w = 0;
        DestRect.h = 0;

        // Blit the surface zone on the back buffer
#ifdef BOMBERMAAAN_SCALE_2X
        if (SDL12_BlitSurface(m_Surfaces[pSprite->SurfaceNumber].pSurface, &SourceRect, m_pBackBuffer, &DestRect) < 0)
#else
        if (SDL12_BlitSurface(m_Surfaces[pSprite->SurfaceNumber].pSurface, &SourceRect, m_pPrimary, &DestRect) < 0)
#endif
        {
            // blitting failed
            theLog.WriteLine("SDLVideo        => !!! SDLVideo error is : %s.", GetSDLVideoError());
        }
    }
    m_DrawingRequests.clear();

    // Debug rectangles?
    for (::portable_stl::vector<SDebugDrawingRequest>::iterator it = m_DebugDrawingRequests.begin(); it != m_DebugDrawingRequests.end(); it++)
    {
        // Save the top drawing request
        const SDebugDrawingRequest &DR = *it;

        // Build a RECT structure containing the zone to draw
        SDL_Rect SourceRect;
        SourceRect.x = DR.ZoneX1;
        SourceRect.y = DR.ZoneY1;
        SourceRect.w = DR.ZoneX2 - DR.ZoneX1;
        SourceRect.h = DR.ZoneY2 - DR.ZoneY1;

        SDL_Rect DestRect;
        DestRect.x = DR.PositionX;
        DestRect.y = DR.PositionY;
        DestRect.w = 0;
        DestRect.h = 0;

        Uint8 r, g, b;
        r = DR.R;
        g = DR.G;
        b = DR.B;

        // create surface
        SDL_Surface *rectangle = SDL12_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,
                                                        SourceRect.w,
                                                        SourceRect.h,
                                                        32,
                                                        rmask,
                                                        gmask,
                                                        bmask,
                                                        amask);

        SDL_Surface *reals = NULL;

        SDL12_SetAlpha(rectangle, SDL_SRCALPHA | SDL_RLEACCEL, 128);

        // fill with rectangle
        if (rectangle != NULL && SDL12_FillRect(rectangle, NULL, SDL12_MapRGBA(rectangle->format, r, g, b, 128)) == 0)
        {
            reals = SDL12_DisplayFormatAlpha(rectangle);

            // Blit the surface zone on the back buffer
#ifdef BOMBERMAAAN_SCALE_2X
            if (reals != NULL && SDL12_BlitSurface(reals, &SourceRect, m_pBackBuffer, &DestRect) < 0)
#else
            if (reals != NULL && SDL12_BlitSurface(reals, &SourceRect, m_pPrimary, &DestRect) < 0)
#endif
            {
                // blitting failed
                theLog.WriteLine("SDLVideo        => !!! SDLVideo error is : %s.", GetSDLVideoError());
            }
        }

        SDL12_FreeSurface(rectangle);
        if (reals != NULL)
        {
            SDL12_FreeSurface(reals);
        }

        // do not Pop the drawing request (there is a separate function)
        //m_DebugDrawingRequests.pop();
    }

    UpdateScreen();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

static const char* GetSDLVideoError()
{
    return SDL12_GetError();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
 