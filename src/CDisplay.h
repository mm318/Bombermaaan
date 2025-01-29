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
 *  \file CDisplay.h
 *  \brief Header file of the display
 */

#ifndef __CDISPLAY_H__
#define __CDISPLAY_H__

#include "CVideoSDL.h"
#include "COptions.h"


//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

class CDisplay
{
private:
    const COptions* m_pOptions;         //!< Options object to use to get information about what the user chose
    CVideoSDL       m_VideoSDL;         //!< Object used for display
    int             m_ViewOriginX;      //!< Top left corner of the game view
    int             m_ViewOriginY;

    bool            Create (int Width, int Height); //!< (Re)Create the SDLVideo interface and (re)load the sprite tables given the resolution
    const std::string& GetProgramFolder(void) const;
    bool            LoadSprites(int SpriteTableWidth,
                                int SpriteTableHeight,
                                int SpriteWidth,
                                int SpriteHeight,
                                bool Transparent,
                                const uint8_t* BitmapData,
                                uint32_t BitmapSize);  //!< Load a sprite table given its bitmap data and its properties.

public:
                    CDisplay(void);     //!< Initialize some members
                    ~CDisplay(void);    //!< Does nothing
    inline void     SetOptions(const COptions *pOptions);
    inline void     SetWindowHandle(HWND hWnd); //!< Set the handle of the window DirectDraw/SDLVideo has to work with
    bool            Create();           //!< (Re)Create the DirectDraw/SDLVideo interface and (re)load the sprite tables given the display mode
    void            Destroy (void);     //!< Destroy the DirectDraw/SDLVideo interface and the sprite tables
    inline void     OnWindowMove (void);//!< Has to be called when the window moves (WM_MOVE)
    inline void     OnPaint(void);      //!< Has to be called when the window has to be repainted (WM_PAINT)
    inline void     Clear(void);        //!< Make the window's client area black
    inline void     Update(void);       //!< Draw the sprites that DrawSprite recorded and update the window's client area
    inline void     SetOrigin(int OriginX, int OriginY); //!< Set the origin to draw from the game view origin
    inline void     DrawSprite(int PositionX,
                               int PositionY,
                               RECT *pZone,
                               RECT *pClip,
                               const void* SpriteTable,
                               int Sprite,
                               int SpriteLayer,
                               int PriorityInLayer); //!< Record a drawing request that will be executed on next call to Update
    inline void     DrawDebugRectangle(int PositionX,
                                       int PositionY,
                                       int w,
                                       int h,
                                       BYTE r,
                                       BYTE g,
                                       BYTE b,
                                       int SpriteLayer,
                                       int PriorityInLayer); //!< Record a drawing request for debug purposes
    inline void     RemoveAllDebugRectangles(void);
    inline CVideoSDL& GetSDLVideo(void);
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

inline void CDisplay::SetOptions(const COptions *pOptions)
{
    m_pOptions = pOptions;
}

inline void CDisplay::SetWindowHandle(HWND hWnd)
{
    m_VideoSDL.SetWindowHandle (hWnd);
}

inline void CDisplay::SetOrigin(int OriginX, int OriginY)
{
    m_VideoSDL.SetOrigin(m_ViewOriginX + OriginX, m_ViewOriginY + OriginY);
}

inline void CDisplay::Clear(void)
{
    m_VideoSDL.Clear();
}

inline void CDisplay::Update(void)
{
    m_VideoSDL.UpdateAll();
}

inline void CDisplay::OnWindowMove(void)
{
    m_VideoSDL.OnWindowMove();
}

inline void CDisplay::OnPaint(void)
{
    m_VideoSDL.UpdateScreen ();
}

inline void CDisplay::DrawSprite(int PositionX,
                                 int PositionY,
                                 RECT *pZone,
                                 RECT *pClip,
                                 const void* SpriteTable,
                                 int Sprite,
                                 int SpriteLayer,
                                 int PriorityInLayer)
{
    m_VideoSDL.DrawSprite(PositionX, PositionY, pZone, pClip, SpriteTable, Sprite, SpriteLayer, PriorityInLayer);
}

inline void CDisplay::DrawDebugRectangle(int PositionX, int PositionY, int w, int h, BYTE r, BYTE g, BYTE b, int SpriteLayer, int PriorityInLayer)
{
    m_VideoSDL.DrawDebugRectangle (PositionX, PositionY, w, h, r, g, b, SpriteLayer, PriorityInLayer);
}

inline void CDisplay::RemoveAllDebugRectangles(void)
{
    m_VideoSDL.RemoveAllDebugRectangles();
}

inline const std::string& CDisplay::GetProgramFolder(void) const {
    return m_pOptions->GetProgramFolder();
}

inline CVideoSDL& CDisplay::GetSDLVideo(void) {
    return m_VideoSDL;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif // __CDISPLAY_H__
