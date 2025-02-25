/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* These headers are from sdl12-compat, and are intended to give just enough
functionality to let you build an SDL-1.2-based project without having the
real SDL-1.2 available to you. */

#ifndef _SDL_error_h
#define _SDL_error_h

#include "SDL_stdinc.h"

#include "begin_code.h"

typedef enum SDL_errorcode
{
    SDL_ENOMEM,
    SDL_EFREAD,
    SDL_EFWRITE,
    SDL_EFSEEK,
    SDL_UNSUPPORTED,
    SDL_LASTERROR
} SDL_errorcode;

extern DECLSPEC void SDLCALL SDL12_SetError(const char *fmt, ...);
extern DECLSPEC char * SDLCALL SDL12_GetError(void);
extern DECLSPEC void SDLCALL SDL12_ClearError(void);
extern DECLSPEC void SDLCALL SDL12_Error(SDL_errorcode code);

#define SDL_OutOfMemory() SDL_Error(SDL_ENOMEM)
#define SDL_Unsupported() SDL_Error(SDL_UNSUPPORTED)

#include "close_code.h"

#endif

