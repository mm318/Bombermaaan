/*
  SDL_mixer:  An audio mixer library based on the SDL library
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

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

/* misc helper routines */
#ifndef UTILS_H_
#define UTILS_H_

#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_version.h"

extern char *_MIX_strtokr(char *s1, const char *s2, char **saveptr);

/* Parse time string of the form HH:MM:SS.mmm and return equivalent sample
 * position */
extern Sint64 _Mix_ParseTime(char *time, long samplerate_hz);

extern SDL_bool _Mix_IsLoopTag(const char *tag);

#endif /* UTILS_H_ */

