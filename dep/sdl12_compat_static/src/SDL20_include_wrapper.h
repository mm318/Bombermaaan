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

/*
 * This file #includes the proper SDL 2.0 headers, but #defines a whole
 *  bunch of stuff so we don't conflict with symbols we plan to offer with
 *  the 1.2 signatures. Ugly business.
 */

#ifndef _INCL_SDL20_INCLUDE_WRAPPER_H_
#define _INCL_SDL20_INCLUDE_WRAPPER_H_

#if defined(_WIN32) || defined(__OS2__)
/* *** HACK HACK HACK:
 * *** Avoid including SDL_thread.h: it defines SDL_CreateThread() as a macro */
#define _SDL_thread_h
#define SDL_thread_h_
#define SDL_PASSED_BEGINTHREAD_ENDTHREAD
#endif
#ifdef __OS2__
#define INCL_DOSMODULEMGR /* for Dos_LoadModule() & co. */
#define INCL_DOSPROCESS
#endif

#define __BUILDING_SDL12_COMPAT__ 1
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"  /* includes windows.h or os2.h */

/* Headers from SDL2 >= 2.0.7 needed for SDL_AudioStream. */
#if !SDL_VERSION_ATLEAST(2,0,7)
#error You need to compile against SDL >= 2.0.7 headers.
#endif

/* Missing SDL_thread.h stuff (see above) */
#if defined(_WIN32) || defined(__OS2__)
typedef struct SDL_Thread SDL_Thread;
typedef int (SDLCALL *SDL_ThreadFunction) (void*);
#endif
#ifdef __OS2__
typedef int (*pfnSDL_CurrentBeginThread) (void (*func)(void*), void*, unsigned, void*);
typedef void (*pfnSDL_CurrentEndThread) (void);
#endif
#ifdef _WIN32
typedef UINT_PTR (__cdecl *pfnSDL_CurrentBeginThread)
                   (void*, unsigned, unsigned (__stdcall *func)(void*), void*, unsigned, unsigned*);
typedef void (__cdecl *pfnSDL_CurrentEndThread) (unsigned);
/* the following macros from Win32 SDK headers are harmful here. */
#undef CreateWindow
#undef CreateThread
#undef CreateSemaphore
#undef CreateMutex
#endif /* _WIN32 */


#ifdef SDL_BlitSurface
#undef SDL_BlitSurface
#endif

#ifdef SDL_mutexP
#undef SDL_mutexP
#endif

#ifdef SDL_mutexV
#undef SDL_mutexV
#endif

#ifdef SDL_SetError
#undef SDL_SetError
#endif

#ifdef SDL_Log
#undef SDL_Log
#endif

#ifdef SDL_LogVerbose
#undef SDL_LogVerbose
#endif

#ifdef SDL_LogDebug
#undef SDL_LogDebug
#endif

#ifdef SDL_LogInfo
#undef SDL_LogInfo
#endif

#ifdef SDL_LogWarn
#undef SDL_LogWarn
#endif

#ifdef SDL_LogError
#undef SDL_LogError
#endif

#ifdef SDL_LogCritical
#undef SDL_LogCritical
#endif

#ifdef SDL_LogMessage
#undef SDL_LogMessage
#endif

#ifdef SDL_sscanf
#undef SDL_sscanf
#endif

#ifdef SDL_snprintf
#undef SDL_snprintf
#endif

#ifdef SDL_CreateThread
#undef SDL_CreateThread
#endif

#ifdef SDL_RWFromFP
#undef SDL_RWFromFP
#endif

#ifdef SDL_RegisterApp
#undef SDL_RegisterApp
#endif

#ifdef SDL_UnregisterApp
#undef SDL_UnregisterApp
#endif

#ifdef SDL_Direct3D9GetAdapterIndex
#undef SDL_Direct3D9GetAdapterIndex
#endif

#ifdef SDL_RenderGetD3D9Device
#undef SDL_RenderGetD3D9Device
#endif

#ifdef SDL_iPhoneSetAnimationCallback
#undef SDL_iPhoneSetAnimationCallback
#endif

#ifdef SDL_iPhoneSetEventPump
#undef SDL_iPhoneSetEventPump
#endif

#ifdef SDL_AndroidGetJNIEnv
#undef SDL_AndroidGetJNIEnv
#endif

#ifdef SDL_AndroidGetActivity
#undef SDL_AndroidGetActivity
#endif

#ifdef SDL_AndroidGetInternalStoragePath
#undef SDL_AndroidGetInternalStoragePath
#endif

#ifdef SDL_AndroidGetExternalStorageState
#undef SDL_AndroidGetExternalStorageState
#endif

#ifdef SDL_AndroidGetExternalStoragePath
#undef SDL_AndroidGetExternalStoragePath
#endif

#ifdef SDL_Init
#undef SDL_Init
#endif

#ifdef SDL_InitSubSystem
#undef SDL_InitSubSystem
#endif

#ifdef SDL_QuitSubSystem
#undef SDL_QuitSubSystem
#endif

#ifdef SDL_WasInit
#undef SDL_WasInit
#endif

#ifdef SDL_Quit
#undef SDL_Quit
#endif

#ifdef SDL_ReportAssertion
#undef SDL_ReportAssertion
#endif

#ifdef SDL_SetAssertionHandler
#undef SDL_SetAssertionHandler
#endif

#ifdef SDL_GetAssertionReport
#undef SDL_GetAssertionReport
#endif

#ifdef SDL_ResetAssertionReport
#undef SDL_ResetAssertionReport
#endif

#ifdef SDL_AtomicTryLock
#undef SDL_AtomicTryLock
#endif

#ifdef SDL_AtomicLock
#undef SDL_AtomicLock
#endif

#ifdef SDL_AtomicUnlock
#undef SDL_AtomicUnlock
#endif

#ifdef SDL_AtomicCAS
#undef SDL_AtomicCAS
#endif

#ifdef SDL_AtomicSet
#undef SDL_AtomicSet
#endif

#ifdef SDL_AtomicGet
#undef SDL_AtomicGet
#endif

#ifdef SDL_AtomicAdd
#undef SDL_AtomicAdd
#endif

#ifdef SDL_AtomicCASPtr
#undef SDL_AtomicCASPtr
#endif

#ifdef SDL_AtomicSetPtr
#undef SDL_AtomicSetPtr
#endif

#ifdef SDL_AtomicGetPtr
#undef SDL_AtomicGetPtr
#endif

#ifdef SDL_GetNumAudioDrivers
#undef SDL_GetNumAudioDrivers
#endif

#ifdef SDL_GetAudioDriver
#undef SDL_GetAudioDriver
#endif

#ifdef SDL_AudioInit
#undef SDL_AudioInit
#endif

#ifdef SDL_AudioQuit
#undef SDL_AudioQuit
#endif

#ifdef SDL_GetCurrentAudioDriver
#undef SDL_GetCurrentAudioDriver
#endif

#ifdef SDL_OpenAudio
#undef SDL_OpenAudio
#endif

#ifdef SDL_GetNumAudioDevices
#undef SDL_GetNumAudioDevices
#endif

#ifdef SDL_GetAudioDeviceName
#undef SDL_GetAudioDeviceName
#endif

#ifdef SDL_OpenAudioDevice
#undef SDL_OpenAudioDevice
#endif

#ifdef SDL_GetAudioStatus
#undef SDL_GetAudioStatus
#endif

#ifdef SDL_GetAudioDeviceStatus
#undef SDL_GetAudioDeviceStatus
#endif

#ifdef SDL_PauseAudio
#undef SDL_PauseAudio
#endif

#ifdef SDL_PauseAudioDevice
#undef SDL_PauseAudioDevice
#endif

#ifdef SDL_LoadWAV_RW
#undef SDL_LoadWAV_RW
#endif

#ifdef SDL_FreeWAV
#undef SDL_FreeWAV
#endif

#ifdef SDL_BuildAudioCVT
#undef SDL_BuildAudioCVT
#endif

#ifdef SDL_ConvertAudio
#undef SDL_ConvertAudio
#endif

#ifdef SDL_MixAudio
#undef SDL_MixAudio
#endif

#ifdef SDL_MixAudioFormat
#undef SDL_MixAudioFormat
#endif

#ifdef SDL_LockAudio
#undef SDL_LockAudio
#endif

#ifdef SDL_LockAudioDevice
#undef SDL_LockAudioDevice
#endif

#ifdef SDL_UnlockAudio
#undef SDL_UnlockAudio
#endif

#ifdef SDL_UnlockAudioDevice
#undef SDL_UnlockAudioDevice
#endif

#ifdef SDL_CloseAudio
#undef SDL_CloseAudio
#endif

#ifdef SDL_CloseAudioDevice
#undef SDL_CloseAudioDevice
#endif

#ifdef SDL_SetClipboardText
#undef SDL_SetClipboardText
#endif

#ifdef SDL_GetClipboardText
#undef SDL_GetClipboardText
#endif

#ifdef SDL_HasClipboardText
#undef SDL_HasClipboardText
#endif

#ifdef SDL_GetCPUCount
#undef SDL_GetCPUCount
#endif

#ifdef SDL_GetCPUCacheLineSize
#undef SDL_GetCPUCacheLineSize
#endif

#ifdef SDL_HasRDTSC
#undef SDL_HasRDTSC
#endif

#ifdef SDL_HasAltiVec
#undef SDL_HasAltiVec
#endif

#ifdef SDL_HasMMX
#undef SDL_HasMMX
#endif

#ifdef SDL_Has3DNow
#undef SDL_Has3DNow
#endif

#ifdef SDL_HasSSE
#undef SDL_HasSSE
#endif

#ifdef SDL_HasSSE2
#undef SDL_HasSSE2
#endif

#ifdef SDL_HasSSE3
#undef SDL_HasSSE3
#endif

#ifdef SDL_HasSSE41
#undef SDL_HasSSE41
#endif

#ifdef SDL_HasSSE42
#undef SDL_HasSSE42
#endif

#ifdef SDL_GetSystemRAM
#undef SDL_GetSystemRAM
#endif

#ifdef SDL_GetError
#undef SDL_GetError
#endif

#ifdef SDL_ClearError
#undef SDL_ClearError
#endif

#ifdef SDL_Error
#undef SDL_Error
#endif

#ifdef SDL_PumpEvents
#undef SDL_PumpEvents
#endif

#ifdef SDL_PeepEvents
#undef SDL_PeepEvents
#endif

#ifdef SDL_HasEvent
#undef SDL_HasEvent
#endif

#ifdef SDL_HasEvents
#undef SDL_HasEvents
#endif

#ifdef SDL_FlushEvent
#undef SDL_FlushEvent
#endif

#ifdef SDL_FlushEvents
#undef SDL_FlushEvents
#endif

#ifdef SDL_PollEvent
#undef SDL_PollEvent
#endif

#ifdef SDL_WaitEvent
#undef SDL_WaitEvent
#endif

#ifdef SDL_WaitEventTimeout
#undef SDL_WaitEventTimeout
#endif

#ifdef SDL_PushEvent
#undef SDL_PushEvent
#endif

#ifdef SDL_SetEventFilter
#undef SDL_SetEventFilter
#endif

#ifdef SDL_GetEventFilter
#undef SDL_GetEventFilter
#endif

#ifdef SDL_AddEventWatch
#undef SDL_AddEventWatch
#endif

#ifdef SDL_DelEventWatch
#undef SDL_DelEventWatch
#endif

#ifdef SDL_FilterEvents
#undef SDL_FilterEvents
#endif

#ifdef SDL_EventState
#undef SDL_EventState
#endif

#ifdef SDL_RegisterEvents
#undef SDL_RegisterEvents
#endif

#ifdef SDL_GetBasePath
#undef SDL_GetBasePath
#endif

#ifdef SDL_GetPrefPath
#undef SDL_GetPrefPath
#endif

#ifdef SDL_GameControllerAddMapping
#undef SDL_GameControllerAddMapping
#endif

#ifdef SDL_GameControllerMappingForGUID
#undef SDL_GameControllerMappingForGUID
#endif

#ifdef SDL_GameControllerMapping
#undef SDL_GameControllerMapping
#endif

#ifdef SDL_IsGameController
#undef SDL_IsGameController
#endif

#ifdef SDL_GameControllerNameForIndex
#undef SDL_GameControllerNameForIndex
#endif

#ifdef SDL_GameControllerOpen
#undef SDL_GameControllerOpen
#endif

#ifdef SDL_GameControllerName
#undef SDL_GameControllerName
#endif

#ifdef SDL_GameControllerGetAttached
#undef SDL_GameControllerGetAttached
#endif

#ifdef SDL_GameControllerGetJoystick
#undef SDL_GameControllerGetJoystick
#endif

#ifdef SDL_GameControllerEventState
#undef SDL_GameControllerEventState
#endif

#ifdef SDL_GameControllerUpdate
#undef SDL_GameControllerUpdate
#endif

#ifdef SDL_GameControllerGetAxisFromString
#undef SDL_GameControllerGetAxisFromString
#endif

#ifdef SDL_GameControllerGetStringForAxis
#undef SDL_GameControllerGetStringForAxis
#endif

#ifdef SDL_GameControllerGetBindForAxis
#undef SDL_GameControllerGetBindForAxis
#endif

#ifdef SDL_GameControllerGetAxis
#undef SDL_GameControllerGetAxis
#endif

#ifdef SDL_GameControllerGetButtonFromString
#undef SDL_GameControllerGetButtonFromString
#endif

#ifdef SDL_GameControllerGetStringForButton
#undef SDL_GameControllerGetStringForButton
#endif

#ifdef SDL_GameControllerGetBindForButton
#undef SDL_GameControllerGetBindForButton
#endif

#ifdef SDL_GameControllerGetButton
#undef SDL_GameControllerGetButton
#endif

#ifdef SDL_GameControllerClose
#undef SDL_GameControllerClose
#endif

#ifdef SDL_RecordGesture
#undef SDL_RecordGesture
#endif

#ifdef SDL_SaveAllDollarTemplates
#undef SDL_SaveAllDollarTemplates
#endif

#ifdef SDL_SaveDollarTemplate
#undef SDL_SaveDollarTemplate
#endif

#ifdef SDL_LoadDollarTemplates
#undef SDL_LoadDollarTemplates
#endif

#ifdef SDL_NumHaptics
#undef SDL_NumHaptics
#endif

#ifdef SDL_HapticName
#undef SDL_HapticName
#endif

#ifdef SDL_HapticOpen
#undef SDL_HapticOpen
#endif

#ifdef SDL_HapticOpened
#undef SDL_HapticOpened
#endif

#ifdef SDL_HapticIndex
#undef SDL_HapticIndex
#endif

#ifdef SDL_MouseIsHaptic
#undef SDL_MouseIsHaptic
#endif

#ifdef SDL_HapticOpenFromMouse
#undef SDL_HapticOpenFromMouse
#endif

#ifdef SDL_JoystickIsHaptic
#undef SDL_JoystickIsHaptic
#endif

#ifdef SDL_HapticOpenFromJoystick
#undef SDL_HapticOpenFromJoystick
#endif

#ifdef SDL_HapticClose
#undef SDL_HapticClose
#endif

#ifdef SDL_HapticNumEffects
#undef SDL_HapticNumEffects
#endif

#ifdef SDL_HapticNumEffectsPlaying
#undef SDL_HapticNumEffectsPlaying
#endif

#ifdef SDL_HapticQuery
#undef SDL_HapticQuery
#endif

#ifdef SDL_HapticNumAxes
#undef SDL_HapticNumAxes
#endif

#ifdef SDL_HapticEffectSupported
#undef SDL_HapticEffectSupported
#endif

#ifdef SDL_HapticNewEffect
#undef SDL_HapticNewEffect
#endif

#ifdef SDL_HapticUpdateEffect
#undef SDL_HapticUpdateEffect
#endif

#ifdef SDL_HapticRunEffect
#undef SDL_HapticRunEffect
#endif

#ifdef SDL_HapticStopEffect
#undef SDL_HapticStopEffect
#endif

#ifdef SDL_HapticDestroyEffect
#undef SDL_HapticDestroyEffect
#endif

#ifdef SDL_HapticGetEffectStatus
#undef SDL_HapticGetEffectStatus
#endif

#ifdef SDL_HapticSetGain
#undef SDL_HapticSetGain
#endif

#ifdef SDL_HapticSetAutocenter
#undef SDL_HapticSetAutocenter
#endif

#ifdef SDL_HapticPause
#undef SDL_HapticPause
#endif

#ifdef SDL_HapticUnpause
#undef SDL_HapticUnpause
#endif

#ifdef SDL_HapticStopAll
#undef SDL_HapticStopAll
#endif

#ifdef SDL_HapticRumbleSupported
#undef SDL_HapticRumbleSupported
#endif

#ifdef SDL_HapticRumbleInit
#undef SDL_HapticRumbleInit
#endif

#ifdef SDL_HapticRumblePlay
#undef SDL_HapticRumblePlay
#endif

#ifdef SDL_HapticRumbleStop
#undef SDL_HapticRumbleStop
#endif

#ifdef SDL_SetHintWithPriority
#undef SDL_SetHintWithPriority
#endif

#ifdef SDL_SetHint
#undef SDL_SetHint
#endif

#ifdef SDL_GetHint
#undef SDL_GetHint
#endif

#ifdef SDL_AddHintCallback
#undef SDL_AddHintCallback
#endif

#ifdef SDL_DelHintCallback
#undef SDL_DelHintCallback
#endif

#ifdef SDL_ClearHints
#undef SDL_ClearHints
#endif

#ifdef SDL_NumJoysticks
#undef SDL_NumJoysticks
#endif

#ifdef SDL_JoystickNameForIndex
#undef SDL_JoystickNameForIndex
#endif

#ifdef SDL_JoystickOpen
#undef SDL_JoystickOpen
#endif

#ifdef SDL_JoystickName
#undef SDL_JoystickName
#endif

#ifdef SDL_JoystickGetDeviceGUID
#undef SDL_JoystickGetDeviceGUID
#endif

#ifdef SDL_JoystickGetGUID
#undef SDL_JoystickGetGUID
#endif

#ifdef SDL_JoystickGetGUIDString
#undef SDL_JoystickGetGUIDString
#endif

#ifdef SDL_JoystickGetGUIDFromString
#undef SDL_JoystickGetGUIDFromString
#endif

#ifdef SDL_JoystickGetAttached
#undef SDL_JoystickGetAttached
#endif

#ifdef SDL_JoystickInstanceID
#undef SDL_JoystickInstanceID
#endif

#ifdef SDL_JoystickNumAxes
#undef SDL_JoystickNumAxes
#endif

#ifdef SDL_JoystickNumBalls
#undef SDL_JoystickNumBalls
#endif

#ifdef SDL_JoystickNumHats
#undef SDL_JoystickNumHats
#endif

#ifdef SDL_JoystickNumButtons
#undef SDL_JoystickNumButtons
#endif

#ifdef SDL_JoystickUpdate
#undef SDL_JoystickUpdate
#endif

#ifdef SDL_JoystickEventState
#undef SDL_JoystickEventState
#endif

#ifdef SDL_JoystickGetAxis
#undef SDL_JoystickGetAxis
#endif

#ifdef SDL_JoystickGetHat
#undef SDL_JoystickGetHat
#endif

#ifdef SDL_JoystickGetBall
#undef SDL_JoystickGetBall
#endif

#ifdef SDL_JoystickGetButton
#undef SDL_JoystickGetButton
#endif

#ifdef SDL_JoystickClose
#undef SDL_JoystickClose
#endif

#ifdef SDL_GetKeyboardFocus
#undef SDL_GetKeyboardFocus
#endif

#ifdef SDL_GetKeyboardState
#undef SDL_GetKeyboardState
#endif

#ifdef SDL_GetModState
#undef SDL_GetModState
#endif

#ifdef SDL_SetModState
#undef SDL_SetModState
#endif

#ifdef SDL_GetKeyFromScancode
#undef SDL_GetKeyFromScancode
#endif

#ifdef SDL_GetScancodeFromKey
#undef SDL_GetScancodeFromKey
#endif

#ifdef SDL_GetScancodeName
#undef SDL_GetScancodeName
#endif

#ifdef SDL_GetScancodeFromName
#undef SDL_GetScancodeFromName
#endif

#ifdef SDL_GetKeyName
#undef SDL_GetKeyName
#endif

#ifdef SDL_GetKeyFromName
#undef SDL_GetKeyFromName
#endif

#ifdef SDL_StartTextInput
#undef SDL_StartTextInput
#endif

#ifdef SDL_IsTextInputActive
#undef SDL_IsTextInputActive
#endif

#ifdef SDL_StopTextInput
#undef SDL_StopTextInput
#endif

#ifdef SDL_SetTextInputRect
#undef SDL_SetTextInputRect
#endif

#ifdef SDL_HasScreenKeyboardSupport
#undef SDL_HasScreenKeyboardSupport
#endif

#ifdef SDL_IsScreenKeyboardShown
#undef SDL_IsScreenKeyboardShown
#endif

#ifdef SDL_LoadObject
#undef SDL_LoadObject
#endif

#ifdef SDL_LoadFunction
#undef SDL_LoadFunction
#endif

#ifdef SDL_UnloadObject
#undef SDL_UnloadObject
#endif

#ifdef SDL_LogSetAllPriority
#undef SDL_LogSetAllPriority
#endif

#ifdef SDL_LogSetPriority
#undef SDL_LogSetPriority
#endif

#ifdef SDL_LogGetPriority
#undef SDL_LogGetPriority
#endif

#ifdef SDL_LogResetPriorities
#undef SDL_LogResetPriorities
#endif

#ifdef SDL_LogMessageV
#undef SDL_LogMessageV
#endif

#ifdef SDL_LogGetOutputFunction
#undef SDL_LogGetOutputFunction
#endif

#ifdef SDL_LogSetOutputFunction
#undef SDL_LogSetOutputFunction
#endif

#ifdef SDL_SetMainReady
#undef SDL_SetMainReady
#endif

#ifdef SDL_ShowMessageBox
#undef SDL_ShowMessageBox
#endif

#ifdef SDL_ShowSimpleMessageBox
#undef SDL_ShowSimpleMessageBox
#endif

#ifdef SDL_GetMouseFocus
#undef SDL_GetMouseFocus
#endif

#ifdef SDL_GetMouseState
#undef SDL_GetMouseState
#endif

#ifdef SDL_GetRelativeMouseState
#undef SDL_GetRelativeMouseState
#endif

#ifdef SDL_WarpMouseInWindow
#undef SDL_WarpMouseInWindow
#endif

#ifdef SDL_SetRelativeMouseMode
#undef SDL_SetRelativeMouseMode
#endif

#ifdef SDL_GetRelativeMouseMode
#undef SDL_GetRelativeMouseMode
#endif

#ifdef SDL_CreateCursor
#undef SDL_CreateCursor
#endif

#ifdef SDL_CreateColorCursor
#undef SDL_CreateColorCursor
#endif

#ifdef SDL_CreateSystemCursor
#undef SDL_CreateSystemCursor
#endif

#ifdef SDL_SetCursor
#undef SDL_SetCursor
#endif

#ifdef SDL_GetCursor
#undef SDL_GetCursor
#endif

#ifdef SDL_GetDefaultCursor
#undef SDL_GetDefaultCursor
#endif

#ifdef SDL_FreeCursor
#undef SDL_FreeCursor
#endif

#ifdef SDL_ShowCursor
#undef SDL_ShowCursor
#endif

#ifdef SDL_CreateMutex
#undef SDL_CreateMutex
#endif

#ifdef SDL_LockMutex
#undef SDL_LockMutex
#endif

#ifdef SDL_TryLockMutex
#undef SDL_TryLockMutex
#endif

#ifdef SDL_UnlockMutex
#undef SDL_UnlockMutex
#endif

#ifdef SDL_DestroyMutex
#undef SDL_DestroyMutex
#endif

#ifdef SDL_CreateSemaphore
#undef SDL_CreateSemaphore
#endif

#ifdef SDL_DestroySemaphore
#undef SDL_DestroySemaphore
#endif

#ifdef SDL_SemWait
#undef SDL_SemWait
#endif

#ifdef SDL_SemTryWait
#undef SDL_SemTryWait
#endif

#ifdef SDL_SemWaitTimeout
#undef SDL_SemWaitTimeout
#endif

#ifdef SDL_SemPost
#undef SDL_SemPost
#endif

#ifdef SDL_SemValue
#undef SDL_SemValue
#endif

#ifdef SDL_CreateCond
#undef SDL_CreateCond
#endif

#ifdef SDL_DestroyCond
#undef SDL_DestroyCond
#endif

#ifdef SDL_CondSignal
#undef SDL_CondSignal
#endif

#ifdef SDL_CondBroadcast
#undef SDL_CondBroadcast
#endif

#ifdef SDL_CondWait
#undef SDL_CondWait
#endif

#ifdef SDL_CondWaitTimeout
#undef SDL_CondWaitTimeout
#endif

#ifdef SDL_GetPixelFormatName
#undef SDL_GetPixelFormatName
#endif

#ifdef SDL_PixelFormatEnumToMasks
#undef SDL_PixelFormatEnumToMasks
#endif

#ifdef SDL_MasksToPixelFormatEnum
#undef SDL_MasksToPixelFormatEnum
#endif

#ifdef SDL_AllocFormat
#undef SDL_AllocFormat
#endif

#ifdef SDL_FreeFormat
#undef SDL_FreeFormat
#endif

#ifdef SDL_AllocPalette
#undef SDL_AllocPalette
#endif

#ifdef SDL_SetPixelFormatPalette
#undef SDL_SetPixelFormatPalette
#endif

#ifdef SDL_SetPaletteColors
#undef SDL_SetPaletteColors
#endif

#ifdef SDL_FreePalette
#undef SDL_FreePalette
#endif

#ifdef SDL_MapRGB
#undef SDL_MapRGB
#endif

#ifdef SDL_MapRGBA
#undef SDL_MapRGBA
#endif

#ifdef SDL_GetRGB
#undef SDL_GetRGB
#endif

#ifdef SDL_GetRGBA
#undef SDL_GetRGBA
#endif

#ifdef SDL_CalculateGammaRamp
#undef SDL_CalculateGammaRamp
#endif

#ifdef SDL_GetPlatform
#undef SDL_GetPlatform
#endif

#ifdef SDL_GetPowerInfo
#undef SDL_GetPowerInfo
#endif

#ifdef SDL_HasIntersection
#undef SDL_HasIntersection
#endif

#ifdef SDL_IntersectRect
#undef SDL_IntersectRect
#endif

#ifdef SDL_UnionRect
#undef SDL_UnionRect
#endif

#ifdef SDL_EnclosePoints
#undef SDL_EnclosePoints
#endif

#ifdef SDL_IntersectRectAndLine
#undef SDL_IntersectRectAndLine
#endif

#ifdef SDL_GetNumRenderDrivers
#undef SDL_GetNumRenderDrivers
#endif

#ifdef SDL_GetRenderDriverInfo
#undef SDL_GetRenderDriverInfo
#endif

#ifdef SDL_CreateWindowAndRenderer
#undef SDL_CreateWindowAndRenderer
#endif

#ifdef SDL_CreateRenderer
#undef SDL_CreateRenderer
#endif

#ifdef SDL_CreateSoftwareRenderer
#undef SDL_CreateSoftwareRenderer
#endif

#ifdef SDL_GetRenderer
#undef SDL_GetRenderer
#endif

#ifdef SDL_GetRendererInfo
#undef SDL_GetRendererInfo
#endif

#ifdef SDL_GetRendererOutputSize
#undef SDL_GetRendererOutputSize
#endif

#ifdef SDL_CreateTexture
#undef SDL_CreateTexture
#endif

#ifdef SDL_CreateTextureFromSurface
#undef SDL_CreateTextureFromSurface
#endif

#ifdef SDL_QueryTexture
#undef SDL_QueryTexture
#endif

#ifdef SDL_SetTextureColorMod
#undef SDL_SetTextureColorMod
#endif

#ifdef SDL_GetTextureColorMod
#undef SDL_GetTextureColorMod
#endif

#ifdef SDL_SetTextureAlphaMod
#undef SDL_SetTextureAlphaMod
#endif

#ifdef SDL_GetTextureAlphaMod
#undef SDL_GetTextureAlphaMod
#endif

#ifdef SDL_SetTextureBlendMode
#undef SDL_SetTextureBlendMode
#endif

#ifdef SDL_GetTextureBlendMode
#undef SDL_GetTextureBlendMode
#endif

#ifdef SDL_UpdateTexture
#undef SDL_UpdateTexture
#endif

#ifdef SDL_UpdateYUVTexture
#undef SDL_UpdateYUVTexture
#endif

#ifdef SDL_LockTexture
#undef SDL_LockTexture
#endif

#ifdef SDL_UnlockTexture
#undef SDL_UnlockTexture
#endif

#ifdef SDL_RenderTargetSupported
#undef SDL_RenderTargetSupported
#endif

#ifdef SDL_SetRenderTarget
#undef SDL_SetRenderTarget
#endif

#ifdef SDL_GetRenderTarget
#undef SDL_GetRenderTarget
#endif

#ifdef SDL_RenderSetLogicalSize
#undef SDL_RenderSetLogicalSize
#endif

#ifdef SDL_RenderGetLogicalSize
#undef SDL_RenderGetLogicalSize
#endif

#ifdef SDL_RenderSetViewport
#undef SDL_RenderSetViewport
#endif

#ifdef SDL_RenderGetViewport
#undef SDL_RenderGetViewport
#endif

#ifdef SDL_RenderSetClipRect
#undef SDL_RenderSetClipRect
#endif

#ifdef SDL_RenderGetClipRect
#undef SDL_RenderGetClipRect
#endif

#ifdef SDL_RenderSetScale
#undef SDL_RenderSetScale
#endif

#ifdef SDL_RenderGetScale
#undef SDL_RenderGetScale
#endif

#ifdef SDL_SetRenderDrawColor
#undef SDL_SetRenderDrawColor
#endif

#ifdef SDL_GetRenderDrawColor
#undef SDL_GetRenderDrawColor
#endif

#ifdef SDL_SetRenderDrawBlendMode
#undef SDL_SetRenderDrawBlendMode
#endif

#ifdef SDL_GetRenderDrawBlendMode
#undef SDL_GetRenderDrawBlendMode
#endif

#ifdef SDL_RenderClear
#undef SDL_RenderClear
#endif

#ifdef SDL_RenderDrawPoint
#undef SDL_RenderDrawPoint
#endif

#ifdef SDL_RenderDrawPoints
#undef SDL_RenderDrawPoints
#endif

#ifdef SDL_RenderDrawLine
#undef SDL_RenderDrawLine
#endif

#ifdef SDL_RenderDrawLines
#undef SDL_RenderDrawLines
#endif

#ifdef SDL_RenderDrawRect
#undef SDL_RenderDrawRect
#endif

#ifdef SDL_RenderDrawRects
#undef SDL_RenderDrawRects
#endif

#ifdef SDL_RenderFillRect
#undef SDL_RenderFillRect
#endif

#ifdef SDL_RenderFillRects
#undef SDL_RenderFillRects
#endif

#ifdef SDL_RenderCopy
#undef SDL_RenderCopy
#endif

#ifdef SDL_RenderCopyEx
#undef SDL_RenderCopyEx
#endif

#ifdef SDL_RenderReadPixels
#undef SDL_RenderReadPixels
#endif

#ifdef SDL_RenderPresent
#undef SDL_RenderPresent
#endif

#ifdef SDL_DestroyTexture
#undef SDL_DestroyTexture
#endif

#ifdef SDL_DestroyRenderer
#undef SDL_DestroyRenderer
#endif

#ifdef SDL_GL_BindTexture
#undef SDL_GL_BindTexture
#endif

#ifdef SDL_GL_UnbindTexture
#undef SDL_GL_UnbindTexture
#endif

#ifdef SDL_RWFromFile
#undef SDL_RWFromFile
#endif

#ifdef SDL_RWFromMem
#undef SDL_RWFromMem
#endif

#ifdef SDL_RWFromConstMem
#undef SDL_RWFromConstMem
#endif

#ifdef SDL_AllocRW
#undef SDL_AllocRW
#endif

#ifdef SDL_FreeRW
#undef SDL_FreeRW
#endif

#ifdef SDL_ReadU8
#undef SDL_ReadU8
#endif

#ifdef SDL_ReadLE16
#undef SDL_ReadLE16
#endif

#ifdef SDL_ReadBE16
#undef SDL_ReadBE16
#endif

#ifdef SDL_ReadLE32
#undef SDL_ReadLE32
#endif

#ifdef SDL_ReadBE32
#undef SDL_ReadBE32
#endif

#ifdef SDL_ReadLE64
#undef SDL_ReadLE64
#endif

#ifdef SDL_ReadBE64
#undef SDL_ReadBE64
#endif

#ifdef SDL_WriteU8
#undef SDL_WriteU8
#endif

#ifdef SDL_WriteLE16
#undef SDL_WriteLE16
#endif

#ifdef SDL_WriteBE16
#undef SDL_WriteBE16
#endif

#ifdef SDL_WriteLE32
#undef SDL_WriteLE32
#endif

#ifdef SDL_WriteBE32
#undef SDL_WriteBE32
#endif

#ifdef SDL_WriteLE64
#undef SDL_WriteLE64
#endif

#ifdef SDL_WriteBE64
#undef SDL_WriteBE64
#endif

#ifdef SDL_CreateShapedWindow
#undef SDL_CreateShapedWindow
#endif

#ifdef SDL_IsShapedWindow
#undef SDL_IsShapedWindow
#endif

#ifdef SDL_SetWindowShape
#undef SDL_SetWindowShape
#endif

#ifdef SDL_GetShapedWindowMode
#undef SDL_GetShapedWindowMode
#endif

#ifdef SDL_malloc
#undef SDL_malloc
#endif

#ifdef SDL_calloc
#undef SDL_calloc
#endif

#ifdef SDL_realloc
#undef SDL_realloc
#endif

#ifdef SDL_free
#undef SDL_free
#endif

#ifdef SDL_getenv
#undef SDL_getenv
#endif

#ifdef SDL_setenv
#undef SDL_setenv
#endif

#ifdef SDL_qsort
#undef SDL_qsort
#endif

#ifdef SDL_abs
#undef SDL_abs
#endif

#ifdef SDL_isdigit
#undef SDL_isdigit
#endif

#ifdef SDL_isspace
#undef SDL_isspace
#endif

#ifdef SDL_toupper
#undef SDL_toupper
#endif

#ifdef SDL_tolower
#undef SDL_tolower
#endif

#ifdef SDL_memset
#undef SDL_memset
#endif

#ifdef SDL_memcpy
#undef SDL_memcpy
#endif

#ifdef SDL_memmove
#undef SDL_memmove
#endif

#ifdef SDL_memcmp
#undef SDL_memcmp
#endif

#ifdef SDL_wcslen
#undef SDL_wcslen
#endif

#ifdef SDL_wcslcpy
#undef SDL_wcslcpy
#endif

#ifdef SDL_wcslcat
#undef SDL_wcslcat
#endif

#ifdef SDL_strlen
#undef SDL_strlen
#endif

#ifdef SDL_strlcpy
#undef SDL_strlcpy
#endif

#ifdef SDL_utf8strlcpy
#undef SDL_utf8strlcpy
#endif

#ifdef SDL_strlcat
#undef SDL_strlcat
#endif

#ifdef SDL_strdup
#undef SDL_strdup
#endif

#ifdef SDL_strrev
#undef SDL_strrev
#endif

#ifdef SDL_strupr
#undef SDL_strupr
#endif

#ifdef SDL_strlwr
#undef SDL_strlwr
#endif

#ifdef SDL_strchr
#undef SDL_strchr
#endif

#ifdef SDL_strrchr
#undef SDL_strrchr
#endif

#ifdef SDL_strstr
#undef SDL_strstr
#endif

#ifdef SDL_itoa
#undef SDL_itoa
#endif

#ifdef SDL_uitoa
#undef SDL_uitoa
#endif

#ifdef SDL_ltoa
#undef SDL_ltoa
#endif

#ifdef SDL_ultoa
#undef SDL_ultoa
#endif

#ifdef SDL_lltoa
#undef SDL_lltoa
#endif

#ifdef SDL_ulltoa
#undef SDL_ulltoa
#endif

#ifdef SDL_atoi
#undef SDL_atoi
#endif

#ifdef SDL_atof
#undef SDL_atof
#endif

#ifdef SDL_strtol
#undef SDL_strtol
#endif

#ifdef SDL_strtoul
#undef SDL_strtoul
#endif

#ifdef SDL_strtoll
#undef SDL_strtoll
#endif

#ifdef SDL_strtoull
#undef SDL_strtoull
#endif

#ifdef SDL_strtod
#undef SDL_strtod
#endif

#ifdef SDL_strcmp
#undef SDL_strcmp
#endif

#ifdef SDL_strncmp
#undef SDL_strncmp
#endif

#ifdef SDL_strcasecmp
#undef SDL_strcasecmp
#endif

#ifdef SDL_strncasecmp
#undef SDL_strncasecmp
#endif

#ifdef SDL_vsnprintf
#undef SDL_vsnprintf
#endif

#ifdef SDL_acos
#undef SDL_acos
#endif

#ifdef SDL_asin
#undef SDL_asin
#endif

#ifdef SDL_atan
#undef SDL_atan
#endif

#ifdef SDL_atan2
#undef SDL_atan2
#endif

#ifdef SDL_ceil
#undef SDL_ceil
#endif

#ifdef SDL_copysign
#undef SDL_copysign
#endif

#ifdef SDL_cos
#undef SDL_cos
#endif

#ifdef SDL_cosf
#undef SDL_cosf
#endif

#ifdef SDL_fabs
#undef SDL_fabs
#endif

#ifdef SDL_floor
#undef SDL_floor
#endif

#ifdef SDL_log
#undef SDL_log
#endif

#ifdef SDL_pow
#undef SDL_pow
#endif

#ifdef SDL_scalbn
#undef SDL_scalbn
#endif

#ifdef SDL_sin
#undef SDL_sin
#endif

#ifdef SDL_sinf
#undef SDL_sinf
#endif

#ifdef SDL_sqrt
#undef SDL_sqrt
#endif

#ifdef SDL_iconv_open
#undef SDL_iconv_open
#endif

#ifdef SDL_iconv_close
#undef SDL_iconv_close
#endif

#ifdef SDL_iconv
#undef SDL_iconv
#endif

#ifdef SDL_iconv_string
#undef SDL_iconv_string
#endif

#ifdef SDL_CreateRGBSurface
#undef SDL_CreateRGBSurface
#endif

#ifdef SDL_CreateRGBSurfaceFrom
#undef SDL_CreateRGBSurfaceFrom
#endif

#ifdef SDL_FreeSurface
#undef SDL_FreeSurface
#endif

#ifdef SDL_SetSurfacePalette
#undef SDL_SetSurfacePalette
#endif

#ifdef SDL_LockSurface
#undef SDL_LockSurface
#endif

#ifdef SDL_UnlockSurface
#undef SDL_UnlockSurface
#endif

#ifdef SDL_LoadBMP_RW
#undef SDL_LoadBMP_RW
#endif

#ifdef SDL_SaveBMP_RW
#undef SDL_SaveBMP_RW
#endif

#ifdef SDL_SetSurfaceRLE
#undef SDL_SetSurfaceRLE
#endif

#ifdef SDL_SetColorKey
#undef SDL_SetColorKey
#endif

#ifdef SDL_GetColorKey
#undef SDL_GetColorKey
#endif

#ifdef SDL_SetSurfaceColorMod
#undef SDL_SetSurfaceColorMod
#endif

#ifdef SDL_GetSurfaceColorMod
#undef SDL_GetSurfaceColorMod
#endif

#ifdef SDL_SetSurfaceAlphaMod
#undef SDL_SetSurfaceAlphaMod
#endif

#ifdef SDL_GetSurfaceAlphaMod
#undef SDL_GetSurfaceAlphaMod
#endif

#ifdef SDL_SetSurfaceBlendMode
#undef SDL_SetSurfaceBlendMode
#endif

#ifdef SDL_GetSurfaceBlendMode
#undef SDL_GetSurfaceBlendMode
#endif

#ifdef SDL_SetClipRect
#undef SDL_SetClipRect
#endif

#ifdef SDL_GetClipRect
#undef SDL_GetClipRect
#endif

#ifdef SDL_ConvertSurface
#undef SDL_ConvertSurface
#endif

#ifdef SDL_ConvertSurfaceFormat
#undef SDL_ConvertSurfaceFormat
#endif

#ifdef SDL_ConvertPixels
#undef SDL_ConvertPixels
#endif

#ifdef SDL_FillRect
#undef SDL_FillRect
#endif

#ifdef SDL_FillRects
#undef SDL_FillRects
#endif

#ifdef SDL_UpperBlit
#undef SDL_UpperBlit
#endif

#ifdef SDL_LowerBlit
#undef SDL_LowerBlit
#endif

#ifdef SDL_SoftStretch
#undef SDL_SoftStretch
#endif

#ifdef SDL_UpperBlitScaled
#undef SDL_UpperBlitScaled
#endif

#ifdef SDL_LowerBlitScaled
#undef SDL_LowerBlitScaled
#endif

#ifdef SDL_GetWindowWMInfo
#undef SDL_GetWindowWMInfo
#endif

#ifdef SDL_GetThreadName
#undef SDL_GetThreadName
#endif

#ifdef SDL_ThreadID
#undef SDL_ThreadID
#endif

#ifdef SDL_GetThreadID
#undef SDL_GetThreadID
#endif

#ifdef SDL_SetThreadPriority
#undef SDL_SetThreadPriority
#endif

#ifdef SDL_WaitThread
#undef SDL_WaitThread
#endif

#ifdef SDL_DetachThread
#undef SDL_DetachThread
#endif

#ifdef SDL_TLSCreate
#undef SDL_TLSCreate
#endif

#ifdef SDL_TLSGet
#undef SDL_TLSGet
#endif

#ifdef SDL_TLSSet
#undef SDL_TLSSet
#endif

#ifdef SDL_GetTicks
#undef SDL_GetTicks
#endif

#ifdef SDL_GetPerformanceCounter
#undef SDL_GetPerformanceCounter
#endif

#ifdef SDL_GetPerformanceFrequency
#undef SDL_GetPerformanceFrequency
#endif

#ifdef SDL_Delay
#undef SDL_Delay
#endif

#ifdef SDL_AddTimer
#undef SDL_AddTimer
#endif

#ifdef SDL_RemoveTimer
#undef SDL_RemoveTimer
#endif

#ifdef SDL_GetNumTouchDevices
#undef SDL_GetNumTouchDevices
#endif

#ifdef SDL_GetTouchDevice
#undef SDL_GetTouchDevice
#endif

#ifdef SDL_GetNumTouchFingers
#undef SDL_GetNumTouchFingers
#endif

#ifdef SDL_GetTouchFinger
#undef SDL_GetTouchFinger
#endif

#ifdef SDL_GetVersion
#undef SDL_GetVersion
#endif

#ifdef SDL_GetRevision
#undef SDL_GetRevision
#endif

#ifdef SDL_GetRevisionNumber
#undef SDL_GetRevisionNumber
#endif

#ifdef SDL_GetNumVideoDrivers
#undef SDL_GetNumVideoDrivers
#endif

#ifdef SDL_GetVideoDriver
#undef SDL_GetVideoDriver
#endif

#ifdef SDL_VideoInit
#undef SDL_VideoInit
#endif

#ifdef SDL_VideoQuit
#undef SDL_VideoQuit
#endif

#ifdef SDL_GetCurrentVideoDriver
#undef SDL_GetCurrentVideoDriver
#endif

#ifdef SDL_GetNumVideoDisplays
#undef SDL_GetNumVideoDisplays
#endif

#ifdef SDL_GetDisplayName
#undef SDL_GetDisplayName
#endif

#ifdef SDL_GetDisplayBounds
#undef SDL_GetDisplayBounds
#endif

#ifdef SDL_GetDisplayDPI
#undef SDL_GetDisplayDPI
#endif

#ifdef SDL_GetNumDisplayModes
#undef SDL_GetNumDisplayModes
#endif

#ifdef SDL_GetDisplayMode
#undef SDL_GetDisplayMode
#endif

#ifdef SDL_GetDesktopDisplayMode
#undef SDL_GetDesktopDisplayMode
#endif

#ifdef SDL_GetCurrentDisplayMode
#undef SDL_GetCurrentDisplayMode
#endif

#ifdef SDL_GetClosestDisplayMode
#undef SDL_GetClosestDisplayMode
#endif

#ifdef SDL_GetWindowDisplayIndex
#undef SDL_GetWindowDisplayIndex
#endif

#ifdef SDL_SetWindowDisplayMode
#undef SDL_SetWindowDisplayMode
#endif

#ifdef SDL_GetWindowDisplayMode
#undef SDL_GetWindowDisplayMode
#endif

#ifdef SDL_GetWindowPixelFormat
#undef SDL_GetWindowPixelFormat
#endif

#ifdef SDL_CreateWindow
#undef SDL_CreateWindow
#endif

#ifdef SDL_CreateWindowFrom
#undef SDL_CreateWindowFrom
#endif

#ifdef SDL_GetWindowID
#undef SDL_GetWindowID
#endif

#ifdef SDL_GetWindowFromID
#undef SDL_GetWindowFromID
#endif

#ifdef SDL_GetWindowFlags
#undef SDL_GetWindowFlags
#endif

#ifdef SDL_SetWindowTitle
#undef SDL_SetWindowTitle
#endif

#ifdef SDL_GetWindowTitle
#undef SDL_GetWindowTitle
#endif

#ifdef SDL_SetWindowIcon
#undef SDL_SetWindowIcon
#endif

#ifdef SDL_SetWindowData
#undef SDL_SetWindowData
#endif

#ifdef SDL_GetWindowData
#undef SDL_GetWindowData
#endif

#ifdef SDL_SetWindowPosition
#undef SDL_SetWindowPosition
#endif

#ifdef SDL_GetWindowPosition
#undef SDL_GetWindowPosition
#endif

#ifdef SDL_SetWindowSize
#undef SDL_SetWindowSize
#endif

#ifdef SDL_GetWindowSize
#undef SDL_GetWindowSize
#endif

#ifdef SDL_SetWindowMinimumSize
#undef SDL_SetWindowMinimumSize
#endif

#ifdef SDL_GetWindowMinimumSize
#undef SDL_GetWindowMinimumSize
#endif

#ifdef SDL_SetWindowMaximumSize
#undef SDL_SetWindowMaximumSize
#endif

#ifdef SDL_GetWindowMaximumSize
#undef SDL_GetWindowMaximumSize
#endif

#ifdef SDL_SetWindowBordered
#undef SDL_SetWindowBordered
#endif

#ifdef SDL_ShowWindow
#undef SDL_ShowWindow
#endif

#ifdef SDL_HideWindow
#undef SDL_HideWindow
#endif

#ifdef SDL_RaiseWindow
#undef SDL_RaiseWindow
#endif

#ifdef SDL_MaximizeWindow
#undef SDL_MaximizeWindow
#endif

#ifdef SDL_MinimizeWindow
#undef SDL_MinimizeWindow
#endif

#ifdef SDL_RestoreWindow
#undef SDL_RestoreWindow
#endif

#ifdef SDL_SetWindowFullscreen
#undef SDL_SetWindowFullscreen
#endif

#ifdef SDL_GetWindowSurface
#undef SDL_GetWindowSurface
#endif

#ifdef SDL_UpdateWindowSurface
#undef SDL_UpdateWindowSurface
#endif

#ifdef SDL_UpdateWindowSurfaceRects
#undef SDL_UpdateWindowSurfaceRects
#endif

#ifdef SDL_SetWindowGrab
#undef SDL_SetWindowGrab
#endif

#ifdef SDL_GetWindowGrab
#undef SDL_GetWindowGrab
#endif

#ifdef SDL_SetWindowBrightness
#undef SDL_SetWindowBrightness
#endif

#ifdef SDL_GetWindowBrightness
#undef SDL_GetWindowBrightness
#endif

#ifdef SDL_SetWindowGammaRamp
#undef SDL_SetWindowGammaRamp
#endif

#ifdef SDL_GetWindowGammaRamp
#undef SDL_GetWindowGammaRamp
#endif

#ifdef SDL_DestroyWindow
#undef SDL_DestroyWindow
#endif

#ifdef SDL_IsScreenSaverEnabled
#undef SDL_IsScreenSaverEnabled
#endif

#ifdef SDL_EnableScreenSaver
#undef SDL_EnableScreenSaver
#endif

#ifdef SDL_DisableScreenSaver
#undef SDL_DisableScreenSaver
#endif

#ifdef SDL_GL_LoadLibrary
#undef SDL_GL_LoadLibrary
#endif

#ifdef SDL_GL_GetProcAddress
#undef SDL_GL_GetProcAddress
#endif

#ifdef SDL_GL_UnloadLibrary
#undef SDL_GL_UnloadLibrary
#endif

#ifdef SDL_GL_ExtensionSupported
#undef SDL_GL_ExtensionSupported
#endif

#ifdef SDL_GL_SetAttribute
#undef SDL_GL_SetAttribute
#endif

#ifdef SDL_GL_GetAttribute
#undef SDL_GL_GetAttribute
#endif

#ifdef SDL_GL_CreateContext
#undef SDL_GL_CreateContext
#endif

#ifdef SDL_GL_MakeCurrent
#undef SDL_GL_MakeCurrent
#endif

#ifdef SDL_GL_GetCurrentWindow
#undef SDL_GL_GetCurrentWindow
#endif

#ifdef SDL_GL_GetCurrentContext
#undef SDL_GL_GetCurrentContext
#endif

#ifdef SDL_GL_GetDrawableSize
#undef SDL_GL_GetDrawableSize
#endif

#ifdef SDL_GL_SetSwapInterval
#undef SDL_GL_SetSwapInterval
#endif

#ifdef SDL_GL_GetSwapInterval
#undef SDL_GL_GetSwapInterval
#endif

#ifdef SDL_GL_SwapWindow
#undef SDL_GL_SwapWindow
#endif

#ifdef SDL_GL_DeleteContext
#undef SDL_GL_DeleteContext
#endif

#ifdef SDL_vsscanf
#undef SDL_vsscanf
#endif

#ifdef SDL_GameControllerAddMappingsFromRW
#undef SDL_GameControllerAddMappingsFromRW
#endif

#ifdef SDL_GL_ResetAttributes
#undef SDL_GL_ResetAttributes
#endif

#ifdef SDL_HasAVX
#undef SDL_HasAVX
#endif

#ifdef SDL_GetDefaultAssertionHandler
#undef SDL_GetDefaultAssertionHandler
#endif

#ifdef SDL_GetAssertionHandler
#undef SDL_GetAssertionHandler
#endif

#ifdef SDL_DXGIGetOutputInfo
#undef SDL_DXGIGetOutputInfo
#endif

#ifdef SDL_RenderIsClipEnabled
#undef SDL_RenderIsClipEnabled
#endif

#ifdef SDL_WinRTRunApp
#undef SDL_WinRTRunApp
#endif

#ifdef SDL_WarpMouseGlobal
#undef SDL_WarpMouseGlobal
#endif

#ifdef SDL_WinRTGetFSPathUNICODE
#undef SDL_WinRTGetFSPathUNICODE
#endif

#ifdef SDL_WinRTGetFSPathUTF8
#undef SDL_WinRTGetFSPathUTF8
#endif

#ifdef SDL_sqrtf
#undef SDL_sqrtf
#endif

#ifdef SDL_tan
#undef SDL_tan
#endif

#ifdef SDL_tanf
#undef SDL_tanf
#endif

#ifdef SDL_CaptureMouse
#undef SDL_CaptureMouse
#endif

#ifdef SDL_SetWindowHitTest
#undef SDL_SetWindowHitTest
#endif

#ifdef SDL_GetGlobalMouseState
#undef SDL_GetGlobalMouseState
#endif

#ifdef SDL_HasAVX2
#undef SDL_HasAVX2
#endif

#ifdef SDL_QueueAudio
#undef SDL_QueueAudio
#endif

#ifdef SDL_GetQueuedAudioSize
#undef SDL_GetQueuedAudioSize
#endif

#ifdef SDL_ClearQueuedAudio
#undef SDL_ClearQueuedAudio
#endif

#ifdef SDL_GetGrabbedWindow
#undef SDL_GetGrabbedWindow
#endif

#ifdef SDL_SetWindowsMessageHook
#undef SDL_SetWindowsMessageHook
#endif

#ifdef SDL_JoystickCurrentPowerLevel
#undef SDL_JoystickCurrentPowerLevel
#endif

#ifdef SDL_GameControllerFromInstanceID
#undef SDL_GameControllerFromInstanceID
#endif

#ifdef SDL_JoystickFromInstanceID
#undef SDL_JoystickFromInstanceID
#endif

#ifdef SDL_GetDisplayUsableBounds
#undef SDL_GetDisplayUsableBounds
#endif

#ifdef SDL_GetWindowBordersSize
#undef SDL_GetWindowBordersSize
#endif

#ifdef SDL_SetWindowOpacity
#undef SDL_SetWindowOpacity
#endif

#ifdef SDL_GetWindowOpacity
#undef SDL_GetWindowOpacity
#endif

#ifdef SDL_SetWindowInputFocus
#undef SDL_SetWindowInputFocus
#endif

#ifdef SDL_SetWindowModalFor
#undef SDL_SetWindowModalFor
#endif

#ifdef SDL_RenderSetIntegerScale
#undef SDL_RenderSetIntegerScale
#endif

#ifdef SDL_RenderGetIntegerScale
#undef SDL_RenderGetIntegerScale
#endif

#ifdef SDL_DequeueAudio
#undef SDL_DequeueAudio
#endif

#ifdef SDL_SetWindowResizable
#undef SDL_SetWindowResizable
#endif

#ifdef SDL_CreateRGBSurfaceWithFormat
#undef SDL_CreateRGBSurfaceWithFormat
#endif

#ifdef SDL_CreateRGBSurfaceWithFormatFrom
#undef SDL_CreateRGBSurfaceWithFormatFrom
#endif

#ifdef SDL_GetHintBoolean
#undef SDL_GetHintBoolean
#endif

#ifdef SDL_JoystickGetDeviceVendor
#undef SDL_JoystickGetDeviceVendor
#endif

#ifdef SDL_JoystickGetDeviceProduct
#undef SDL_JoystickGetDeviceProduct
#endif

#ifdef SDL_JoystickGetDeviceProductVersion
#undef SDL_JoystickGetDeviceProductVersion
#endif

#ifdef SDL_JoystickGetVendor
#undef SDL_JoystickGetVendor
#endif

#ifdef SDL_JoystickGetProduct
#undef SDL_JoystickGetProduct
#endif

#ifdef SDL_JoystickGetProductVersion
#undef SDL_JoystickGetProductVersion
#endif

#ifdef SDL_GameControllerGetVendor
#undef SDL_GameControllerGetVendor
#endif

#ifdef SDL_GameControllerGetProduct
#undef SDL_GameControllerGetProduct
#endif

#ifdef SDL_GameControllerGetProductVersion
#undef SDL_GameControllerGetProductVersion
#endif

#ifdef SDL_HasNEON
#undef SDL_HasNEON
#endif

#ifdef SDL_GameControllerNumMappings
#undef SDL_GameControllerNumMappings
#endif

#ifdef SDL_GameControllerMappingForIndex
#undef SDL_GameControllerMappingForIndex
#endif

#ifdef SDL_JoystickGetAxisInitialState
#undef SDL_JoystickGetAxisInitialState
#endif

#ifdef SDL_JoystickGetDeviceType
#undef SDL_JoystickGetDeviceType
#endif

#ifdef SDL_JoystickGetType
#undef SDL_JoystickGetType
#endif

#ifdef SDL_MemoryBarrierReleaseFunction
#undef SDL_MemoryBarrierReleaseFunction
#endif

#ifdef SDL_MemoryBarrierAcquireFunction
#undef SDL_MemoryBarrierAcquireFunction
#endif

#ifdef SDL_JoystickGetDeviceInstanceID
#undef SDL_JoystickGetDeviceInstanceID
#endif

#ifdef SDL_utf8strlen
#undef SDL_utf8strlen
#endif

#ifdef SDL_LoadFile_RW
#undef SDL_LoadFile_RW
#endif

#ifdef SDL_wcscmp
#undef SDL_wcscmp
#endif

#ifdef SDL_ComposeCustomBlendMode
#undef SDL_ComposeCustomBlendMode
#endif

#ifdef SDL_DuplicateSurface
#undef SDL_DuplicateSurface
#endif

#ifdef SDL_Vulkan_LoadLibrary
#undef SDL_Vulkan_LoadLibrary
#endif

#ifdef SDL_Vulkan_GetVkGetInstanceProcAddr
#undef SDL_Vulkan_GetVkGetInstanceProcAddr
#endif

#ifdef SDL_Vulkan_UnloadLibrary
#undef SDL_Vulkan_UnloadLibrary
#endif

#ifdef SDL_Vulkan_GetInstanceExtensions
#undef SDL_Vulkan_GetInstanceExtensions
#endif

#ifdef SDL_Vulkan_CreateSurface
#undef SDL_Vulkan_CreateSurface
#endif

#ifdef SDL_Vulkan_GetDrawableSize
#undef SDL_Vulkan_GetDrawableSize
#endif

#ifdef SDL_LockJoysticks
#undef SDL_LockJoysticks
#endif

#ifdef SDL_UnlockJoysticks
#undef SDL_UnlockJoysticks
#endif

#ifdef SDL_GetMemoryFunctions
#undef SDL_GetMemoryFunctions
#endif

#ifdef SDL_SetMemoryFunctions
#undef SDL_SetMemoryFunctions
#endif

#ifdef SDL_GetNumAllocations
#undef SDL_GetNumAllocations
#endif

#ifdef SDL_NewAudioStream
#undef SDL_NewAudioStream
#endif

#ifdef SDL_AudioStreamPut
#undef SDL_AudioStreamPut
#endif

#ifdef SDL_AudioStreamGet
#undef SDL_AudioStreamGet
#endif

#ifdef SDL_AudioStreamClear
#undef SDL_AudioStreamClear
#endif

#ifdef SDL_AudioStreamAvailable
#undef SDL_AudioStreamAvailable
#endif

#ifdef SDL_FreeAudioStream
#undef SDL_FreeAudioStream
#endif

#ifdef SDL_AudioStreamFlush
#undef SDL_AudioStreamFlush
#endif

#ifdef SDL_acosf
#undef SDL_acosf
#endif

#ifdef SDL_asinf
#undef SDL_asinf
#endif

#ifdef SDL_atanf
#undef SDL_atanf
#endif

#ifdef SDL_atan2f
#undef SDL_atan2f
#endif

#ifdef SDL_ceilf
#undef SDL_ceilf
#endif

#ifdef SDL_copysignf
#undef SDL_copysignf
#endif

#ifdef SDL_fabsf
#undef SDL_fabsf
#endif

#ifdef SDL_floorf
#undef SDL_floorf
#endif

#ifdef SDL_logf
#undef SDL_logf
#endif

#ifdef SDL_powf
#undef SDL_powf
#endif

#ifdef SDL_scalbnf
#undef SDL_scalbnf
#endif

#ifdef SDL_fmod
#undef SDL_fmod
#endif

#ifdef SDL_fmodf
#undef SDL_fmodf
#endif

#ifdef SDL_SetYUVConversionMode
#undef SDL_SetYUVConversionMode
#endif

#ifdef SDL_GetYUVConversionMode
#undef SDL_GetYUVConversionMode
#endif

#ifdef SDL_GetYUVConversionModeForResolution
#undef SDL_GetYUVConversionModeForResolution
#endif

#ifdef SDL_RenderGetMetalLayer
#undef SDL_RenderGetMetalLayer
#endif

#ifdef SDL_RenderGetMetalCommandEncoder
#undef SDL_RenderGetMetalCommandEncoder
#endif

#ifdef SDL_IsAndroidTV
#undef SDL_IsAndroidTV
#endif

#ifdef SDL_WinRTGetDeviceFamily
#undef SDL_WinRTGetDeviceFamily
#endif

#ifdef SDL_log10
#undef SDL_log10
#endif

#ifdef SDL_log10f
#undef SDL_log10f
#endif

#ifdef SDL_GameControllerMappingForDeviceIndex
#undef SDL_GameControllerMappingForDeviceIndex
#endif

#ifdef SDL_LinuxSetThreadPriority
#undef SDL_LinuxSetThreadPriority
#endif

#ifdef SDL_HasAVX512F
#undef SDL_HasAVX512F
#endif

#ifdef SDL_IsChromebook
#undef SDL_IsChromebook
#endif

#ifdef SDL_IsDeXMode
#undef SDL_IsDeXMode
#endif

#ifdef SDL_AndroidBackButton
#undef SDL_AndroidBackButton
#endif

#ifdef SDL_exp
#undef SDL_exp
#endif

#ifdef SDL_expf
#undef SDL_expf
#endif

#ifdef SDL_wcsdup
#undef SDL_wcsdup
#endif

#ifdef SDL_GameControllerRumble
#undef SDL_GameControllerRumble
#endif

#ifdef SDL_JoystickRumble
#undef SDL_JoystickRumble
#endif

#ifdef SDL_NumSensors
#undef SDL_NumSensors
#endif

#ifdef SDL_SensorGetDeviceName
#undef SDL_SensorGetDeviceName
#endif

#ifdef SDL_SensorGetDeviceType
#undef SDL_SensorGetDeviceType
#endif

#ifdef SDL_SensorGetDeviceNonPortableType
#undef SDL_SensorGetDeviceNonPortableType
#endif

#ifdef SDL_SensorGetDeviceInstanceID
#undef SDL_SensorGetDeviceInstanceID
#endif

#ifdef SDL_SensorOpen
#undef SDL_SensorOpen
#endif

#ifdef SDL_SensorFromInstanceID
#undef SDL_SensorFromInstanceID
#endif

#ifdef SDL_SensorGetName
#undef SDL_SensorGetName
#endif

#ifdef SDL_SensorGetType
#undef SDL_SensorGetType
#endif

#ifdef SDL_SensorGetNonPortableType
#undef SDL_SensorGetNonPortableType
#endif

#ifdef SDL_SensorGetInstanceID
#undef SDL_SensorGetInstanceID
#endif

#ifdef SDL_SensorGetData
#undef SDL_SensorGetData
#endif

#ifdef SDL_SensorClose
#undef SDL_SensorClose
#endif

#ifdef SDL_SensorUpdate
#undef SDL_SensorUpdate
#endif

#ifdef SDL_IsTablet
#undef SDL_IsTablet
#endif

#ifdef SDL_GetDisplayOrientation
#undef SDL_GetDisplayOrientation
#endif

#ifdef SDL_HasColorKey
#undef SDL_HasColorKey
#endif

#ifdef SDL_CreateThreadWithStackSize
#undef SDL_CreateThreadWithStackSize
#endif

#ifdef SDL_JoystickGetDevicePlayerIndex
#undef SDL_JoystickGetDevicePlayerIndex
#endif

#ifdef SDL_JoystickGetPlayerIndex
#undef SDL_JoystickGetPlayerIndex
#endif

#ifdef SDL_GameControllerGetPlayerIndex
#undef SDL_GameControllerGetPlayerIndex
#endif

#ifdef SDL_RenderFlush
#undef SDL_RenderFlush
#endif

#ifdef SDL_RenderDrawPointF
#undef SDL_RenderDrawPointF
#endif

#ifdef SDL_RenderDrawPointsF
#undef SDL_RenderDrawPointsF
#endif

#ifdef SDL_RenderDrawLineF
#undef SDL_RenderDrawLineF
#endif

#ifdef SDL_RenderDrawLinesF
#undef SDL_RenderDrawLinesF
#endif

#ifdef SDL_RenderDrawRectF
#undef SDL_RenderDrawRectF
#endif

#ifdef SDL_RenderDrawRectsF
#undef SDL_RenderDrawRectsF
#endif

#ifdef SDL_RenderFillRectF
#undef SDL_RenderFillRectF
#endif

#ifdef SDL_RenderFillRectsF
#undef SDL_RenderFillRectsF
#endif

#ifdef SDL_RenderCopyF
#undef SDL_RenderCopyF
#endif

#ifdef SDL_RenderCopyExF
#undef SDL_RenderCopyExF
#endif

#ifdef SDL_GetTouchDeviceType
#undef SDL_GetTouchDeviceType
#endif

#ifdef SDL_UIKitRunApp
#undef SDL_UIKitRunApp
#endif

#ifdef SDL_SIMDGetAlignment
#undef SDL_SIMDGetAlignment
#endif

#ifdef SDL_SIMDAlloc
#undef SDL_SIMDAlloc
#endif

#ifdef SDL_SIMDFree
#undef SDL_SIMDFree
#endif

#ifdef SDL_RWsize
#undef SDL_RWsize
#endif

#ifdef SDL_RWseek
#undef SDL_RWseek
#endif

#ifdef SDL_RWtell
#undef SDL_RWtell
#endif

#ifdef SDL_RWread
#undef SDL_RWread
#endif

#ifdef SDL_RWwrite
#undef SDL_RWwrite
#endif

#ifdef SDL_RWclose
#undef SDL_RWclose
#endif

#ifdef SDL_LoadFile
#undef SDL_LoadFile
#endif

#ifdef SDL_Metal_CreateView
#undef SDL_Metal_CreateView
#endif

#ifdef SDL_Metal_DestroyView
#undef SDL_Metal_DestroyView
#endif

#ifdef SDL_LockTextureToSurface
#undef SDL_LockTextureToSurface
#endif

#ifdef SDL_HasARMSIMD
#undef SDL_HasARMSIMD
#endif

#ifdef SDL_strtokr
#undef SDL_strtokr
#endif

#ifdef SDL_wcsstr
#undef SDL_wcsstr
#endif

#ifdef SDL_wcsncmp
#undef SDL_wcsncmp
#endif

#ifdef SDL_GameControllerTypeForIndex
#undef SDL_GameControllerTypeForIndex
#endif

#ifdef SDL_GameControllerGetType
#undef SDL_GameControllerGetType
#endif

#ifdef SDL_GameControllerFromPlayerIndex
#undef SDL_GameControllerFromPlayerIndex
#endif

#ifdef SDL_GameControllerSetPlayerIndex
#undef SDL_GameControllerSetPlayerIndex
#endif

#ifdef SDL_JoystickFromPlayerIndex
#undef SDL_JoystickFromPlayerIndex
#endif

#ifdef SDL_JoystickSetPlayerIndex
#undef SDL_JoystickSetPlayerIndex
#endif

#ifdef SDL_SetTextureScaleMode
#undef SDL_SetTextureScaleMode
#endif

#ifdef SDL_GetTextureScaleMode
#undef SDL_GetTextureScaleMode
#endif

#ifdef SDL_OnApplicationWillTerminate
#undef SDL_OnApplicationWillTerminate
#endif

#ifdef SDL_OnApplicationDidReceiveMemoryWarning
#undef SDL_OnApplicationDidReceiveMemoryWarning
#endif

#ifdef SDL_OnApplicationWillResignActive
#undef SDL_OnApplicationWillResignActive
#endif

#ifdef SDL_OnApplicationDidEnterBackground
#undef SDL_OnApplicationDidEnterBackground
#endif

#ifdef SDL_OnApplicationWillEnterForeground
#undef SDL_OnApplicationWillEnterForeground
#endif

#ifdef SDL_OnApplicationDidBecomeActive
#undef SDL_OnApplicationDidBecomeActive
#endif

#ifdef SDL_OnApplicationDidChangeStatusBarOrientation
#undef SDL_OnApplicationDidChangeStatusBarOrientation
#endif

#ifdef SDL_GetAndroidSDKVersion
#undef SDL_GetAndroidSDKVersion
#endif

#ifdef SDL_isupper
#undef SDL_isupper
#endif

#ifdef SDL_islower
#undef SDL_islower
#endif

#ifdef SDL_JoystickAttachVirtual
#undef SDL_JoystickAttachVirtual
#endif

#ifdef SDL_JoystickDetachVirtual
#undef SDL_JoystickDetachVirtual
#endif

#ifdef SDL_JoystickIsVirtual
#undef SDL_JoystickIsVirtual
#endif

#ifdef SDL_JoystickSetVirtualAxis
#undef SDL_JoystickSetVirtualAxis
#endif

#ifdef SDL_JoystickSetVirtualButton
#undef SDL_JoystickSetVirtualButton
#endif

#ifdef SDL_JoystickSetVirtualHat
#undef SDL_JoystickSetVirtualHat
#endif

#ifdef SDL_GetErrorMsg
#undef SDL_GetErrorMsg
#endif

#ifdef SDL_LockSensors
#undef SDL_LockSensors
#endif

#ifdef SDL_UnlockSensors
#undef SDL_UnlockSensors
#endif

#ifdef SDL_Metal_GetLayer
#undef SDL_Metal_GetLayer
#endif

#ifdef SDL_Metal_GetDrawableSize
#undef SDL_Metal_GetDrawableSize
#endif

#ifdef SDL_trunc
#undef SDL_trunc
#endif

#ifdef SDL_truncf
#undef SDL_truncf
#endif

#ifdef SDL_GetPreferredLocales
#undef SDL_GetPreferredLocales
#endif

#ifdef SDL_SIMDRealloc
#undef SDL_SIMDRealloc
#endif

#ifdef SDL_AndroidRequestPermission
#undef SDL_AndroidRequestPermission
#endif

#ifdef SDL_OpenURL
#undef SDL_OpenURL
#endif

#ifdef SDL_HasSurfaceRLE
#undef SDL_HasSurfaceRLE
#endif

#ifdef SDL_GameControllerHasLED
#undef SDL_GameControllerHasLED
#endif

#ifdef SDL_GameControllerSetLED
#undef SDL_GameControllerSetLED
#endif

#ifdef SDL_JoystickHasLED
#undef SDL_JoystickHasLED
#endif

#ifdef SDL_JoystickSetLED
#undef SDL_JoystickSetLED
#endif

#ifdef SDL_GameControllerRumbleTriggers
#undef SDL_GameControllerRumbleTriggers
#endif

#ifdef SDL_JoystickRumbleTriggers
#undef SDL_JoystickRumbleTriggers
#endif

#ifdef SDL_GameControllerHasAxis
#undef SDL_GameControllerHasAxis
#endif

#ifdef SDL_GameControllerHasButton
#undef SDL_GameControllerHasButton
#endif

#ifdef SDL_GameControllerGetNumTouchpads
#undef SDL_GameControllerGetNumTouchpads
#endif

#ifdef SDL_GameControllerGetNumTouchpadFingers
#undef SDL_GameControllerGetNumTouchpadFingers
#endif

#ifdef SDL_GameControllerGetTouchpadFinger
#undef SDL_GameControllerGetTouchpadFinger
#endif

#ifdef SDL_crc32
#undef SDL_crc32
#endif

#ifdef SDL_GameControllerGetSerial
#undef SDL_GameControllerGetSerial
#endif

#ifdef SDL_JoystickGetSerial
#undef SDL_JoystickGetSerial
#endif

#ifdef SDL_GameControllerHasSensor
#undef SDL_GameControllerHasSensor
#endif

#ifdef SDL_GameControllerSetSensorEnabled
#undef SDL_GameControllerSetSensorEnabled
#endif

#ifdef SDL_GameControllerIsSensorEnabled
#undef SDL_GameControllerIsSensorEnabled
#endif

#ifdef SDL_GameControllerGetSensorData
#undef SDL_GameControllerGetSensorData
#endif

#ifdef SDL_wcscasecmp
#undef SDL_wcscasecmp
#endif

#ifdef SDL_wcsncasecmp
#undef SDL_wcsncasecmp
#endif

#ifdef SDL_round
#undef SDL_round
#endif

#ifdef SDL_roundf
#undef SDL_roundf
#endif

#ifdef SDL_lround
#undef SDL_lround
#endif

#ifdef SDL_lroundf
#undef SDL_lroundf
#endif

#ifdef SDL_SoftStretchLinear
#undef SDL_SoftStretchLinear
#endif

#ifdef SDL_RenderGetD3D11Device
#undef SDL_RenderGetD3D11Device
#endif

#ifdef SDL_UpdateNVTexture
#undef SDL_UpdateNVTexture
#endif

#ifdef SDL_SetWindowKeyboardGrab
#undef SDL_SetWindowKeyboardGrab
#endif

#ifdef SDL_SetWindowMouseGrab
#undef SDL_SetWindowMouseGrab
#endif

#ifdef SDL_GetWindowKeyboardGrab
#undef SDL_GetWindowKeyboardGrab
#endif

#ifdef SDL_GetWindowMouseGrab
#undef SDL_GetWindowMouseGrab
#endif

#ifdef SDL_isalpha
#undef SDL_isalpha
#endif

#ifdef SDL_isalnum
#undef SDL_isalnum
#endif

#ifdef SDL_isblank
#undef SDL_isblank
#endif

#ifdef SDL_iscntrl
#undef SDL_iscntrl
#endif

#ifdef SDL_isxdigit
#undef SDL_isxdigit
#endif

#ifdef SDL_ispunct
#undef SDL_ispunct
#endif

#ifdef SDL_isprint
#undef SDL_isprint
#endif

#ifdef SDL_isgraph
#undef SDL_isgraph
#endif

#ifdef SDL_AndroidShowToast
#undef SDL_AndroidShowToast
#endif

#ifdef SDL_GetAudioDeviceSpec
#undef SDL_GetAudioDeviceSpec
#endif

#ifdef SDL_TLSCleanup
#undef SDL_TLSCleanup
#endif

#ifdef SDL_SetWindowAlwaysOnTop
#undef SDL_SetWindowAlwaysOnTop
#endif

#ifdef SDL_FlashWindow
#undef SDL_FlashWindow
#endif

#ifdef SDL_GameControllerSendEffect
#undef SDL_GameControllerSendEffect
#endif

#ifdef SDL_JoystickSendEffect
#undef SDL_JoystickSendEffect
#endif

#ifdef SDL_GameControllerGetSensorDataRate
#undef SDL_GameControllerGetSensorDataRate
#endif

#ifdef SDL_SetTextureUserData
#undef SDL_SetTextureUserData
#endif

#ifdef SDL_GetTextureUserData
#undef SDL_GetTextureUserData
#endif

#ifdef SDL_RenderGeometry
#undef SDL_RenderGeometry
#endif

#ifdef SDL_RenderGeometryRaw
#undef SDL_RenderGeometryRaw
#endif

#ifdef SDL_RenderSetVSync
#undef SDL_RenderSetVSync
#endif

#ifdef SDL_asprintf
#undef SDL_asprintf
#endif

#ifdef SDL_vasprintf
#undef SDL_vasprintf
#endif

#ifdef SDL_GetWindowICCProfile
#undef SDL_GetWindowICCProfile
#endif

#ifdef SDL_GetTicks64
#undef SDL_GetTicks64
#endif

#ifdef SDL_LinuxSetThreadPriorityAndPolicy
#undef SDL_LinuxSetThreadPriorityAndPolicy
#endif

#ifdef SDL_GameControllerGetAppleSFSymbolsNameForButton
#undef SDL_GameControllerGetAppleSFSymbolsNameForButton
#endif

#ifdef SDL_GameControllerGetAppleSFSymbolsNameForAxis
#undef SDL_GameControllerGetAppleSFSymbolsNameForAxis
#endif

#ifdef SDL_hid_init
#undef SDL_hid_init
#endif

#ifdef SDL_hid_exit
#undef SDL_hid_exit
#endif

#ifdef SDL_hid_device_change_count
#undef SDL_hid_device_change_count
#endif

#ifdef SDL_hid_enumerate
#undef SDL_hid_enumerate
#endif

#ifdef SDL_hid_free_enumeration
#undef SDL_hid_free_enumeration
#endif

#ifdef SDL_hid_open
#undef SDL_hid_open
#endif

#ifdef SDL_hid_open_path
#undef SDL_hid_open_path
#endif

#ifdef SDL_hid_write
#undef SDL_hid_write
#endif

#ifdef SDL_hid_read_timeout
#undef SDL_hid_read_timeout
#endif

#ifdef SDL_hid_read
#undef SDL_hid_read
#endif

#ifdef SDL_hid_set_nonblocking
#undef SDL_hid_set_nonblocking
#endif

#ifdef SDL_hid_send_feature_report
#undef SDL_hid_send_feature_report
#endif

#ifdef SDL_hid_get_feature_report
#undef SDL_hid_get_feature_report
#endif

#ifdef SDL_hid_close
#undef SDL_hid_close
#endif

#ifdef SDL_hid_get_manufacturer_string
#undef SDL_hid_get_manufacturer_string
#endif

#ifdef SDL_hid_get_product_string
#undef SDL_hid_get_product_string
#endif

#ifdef SDL_hid_get_serial_number_string
#undef SDL_hid_get_serial_number_string
#endif

#ifdef SDL_hid_get_indexed_string
#undef SDL_hid_get_indexed_string
#endif

#ifdef SDL_SetWindowMouseRect
#undef SDL_SetWindowMouseRect
#endif

#ifdef SDL_GetWindowMouseRect
#undef SDL_GetWindowMouseRect
#endif

#ifdef SDL_RenderWindowToLogical
#undef SDL_RenderWindowToLogical
#endif

#ifdef SDL_RenderLogicalToWindow
#undef SDL_RenderLogicalToWindow
#endif

#ifdef SDL_JoystickHasRumble
#undef SDL_JoystickHasRumble
#endif

#ifdef SDL_JoystickHasRumbleTriggers
#undef SDL_JoystickHasRumbleTriggers
#endif

#ifdef SDL_GameControllerHasRumble
#undef SDL_GameControllerHasRumble
#endif

#ifdef SDL_GameControllerHasRumbleTriggers
#undef SDL_GameControllerHasRumbleTriggers
#endif

#ifdef SDL_hid_ble_scan
#undef SDL_hid_ble_scan
#endif

#ifdef SDL_PremultiplyAlpha
#undef SDL_PremultiplyAlpha
#endif

#ifdef SDL_AndroidSendMessage
#undef SDL_AndroidSendMessage
#endif

#ifdef SDL_GetTouchName
#undef SDL_GetTouchName
#endif

#ifdef SDL_ClearComposition
#undef SDL_ClearComposition
#endif

#ifdef SDL_IsTextInputShown
#undef SDL_IsTextInputShown
#endif

#ifdef SDL_HasIntersectionF
#undef SDL_HasIntersectionF
#endif

#ifdef SDL_IntersectFRect
#undef SDL_IntersectFRect
#endif

#ifdef SDL_UnionFRect
#undef SDL_UnionFRect
#endif

#ifdef SDL_EncloseFPoints
#undef SDL_EncloseFPoints
#endif

#ifdef SDL_IntersectFRectAndLine
#undef SDL_IntersectFRectAndLine
#endif

#ifdef SDL_RenderGetWindow
#undef SDL_RenderGetWindow
#endif

#ifdef SDL_bsearch
#undef SDL_bsearch
#endif

#ifdef SDL_GameControllerPathForIndex
#undef SDL_GameControllerPathForIndex
#endif

#ifdef SDL_GameControllerPath
#undef SDL_GameControllerPath
#endif

#ifdef SDL_JoystickPathForIndex
#undef SDL_JoystickPathForIndex
#endif

#ifdef SDL_JoystickPath
#undef SDL_JoystickPath
#endif

#ifdef SDL_JoystickAttachVirtualEx
#undef SDL_JoystickAttachVirtualEx
#endif

#ifdef SDL_GameControllerGetFirmwareVersion
#undef SDL_GameControllerGetFirmwareVersion
#endif

#ifdef SDL_JoystickGetFirmwareVersion
#undef SDL_JoystickGetFirmwareVersion
#endif

#ifdef SDL_GUIDToString
#undef SDL_GUIDToString
#endif

#ifdef SDL_GUIDFromString
#undef SDL_GUIDFromString
#endif

#ifdef SDL_HasLSX
#undef SDL_HasLSX
#endif

#ifdef SDL_HasLASX
#undef SDL_HasLASX
#endif

#ifdef SDL_RenderGetD3D12Device
#undef SDL_RenderGetD3D12Device
#endif

#ifdef SDL_utf8strnlen
#undef SDL_utf8strnlen
#endif

#ifdef SDL_GDKGetTaskQueue
#undef SDL_GDKGetTaskQueue
#endif

#ifdef SDL_GDKRunApp
#undef SDL_GDKRunApp
#endif

#ifdef SDL_GetOriginalMemoryFunctions
#undef SDL_GetOriginalMemoryFunctions
#endif

#ifdef SDL_ResetKeyboard
#undef SDL_ResetKeyboard
#endif

#ifdef SDL_GetDefaultAudioInfo
#undef SDL_GetDefaultAudioInfo
#endif

#ifdef SDL_GetPointDisplayIndex
#undef SDL_GetPointDisplayIndex
#endif

#ifdef SDL_GetRectDisplayIndex
#undef SDL_GetRectDisplayIndex
#endif

#ifdef SDL_ResetHint
#undef SDL_ResetHint
#endif

#ifdef SDL_crc16
#undef SDL_crc16
#endif

#ifdef SDL_GetWindowSizeInPixels
#undef SDL_GetWindowSizeInPixels
#endif

#ifdef SDL_GetJoystickGUIDInfo
#undef SDL_GetJoystickGUIDInfo
#endif

#ifdef SDL_SetPrimarySelectionText
#undef SDL_SetPrimarySelectionText
#endif

#ifdef SDL_GetPrimarySelectionText
#undef SDL_GetPrimarySelectionText
#endif

#ifdef SDL_HasPrimarySelectionText
#undef SDL_HasPrimarySelectionText
#endif

#ifdef SDL_GameControllerGetSensorDataWithTimestamp
#undef SDL_GameControllerGetSensorDataWithTimestamp
#endif

#ifdef SDL_SensorGetDataWithTimestamp
#undef SDL_SensorGetDataWithTimestamp
#endif

#ifdef SDL_ResetHints
#undef SDL_ResetHints
#endif

#ifdef SDL_strcasestr
#undef SDL_strcasestr
#endif

#ifdef SDL_GDKSuspendComplete
#undef SDL_GDKSuspendComplete
#endif

#ifdef SDL_HasWindowSurface
#undef SDL_HasWindowSurface
#endif

#ifdef SDL_DestroyWindowSurface
#undef SDL_DestroyWindowSurface
#endif

#ifdef SDL_GDKGetDefaultUser
#undef SDL_GDKGetDefaultUser
#endif

/* undefine these macros too: */
/* redefine using SDL2_xxx, if needed. */

#ifdef SDL_enabled_assert
#undef SDL_enabled_assert
#endif

#ifdef SDL_OutOfMemory
#undef SDL_OutOfMemory
#endif

#ifdef SDL_Unsupported
#undef SDL_Unsupported
#endif

#ifdef SDL_InvalidParamError
#undef SDL_InvalidParamError
#endif

#ifdef AtomicIncRef
#undef AtomicIncRef
#endif

#ifdef SDL_AtomicDecRef
#undef SDL_AtomicDecRef
#endif

#ifdef SDL_copyp
#undef SDL_copyp
#endif

#ifdef SDL_zero
#undef SDL_zero
#endif

#ifdef SDL_zeroa
#undef SDL_zeroa
#endif

#ifdef SDL_zerop
#undef SDL_zerop
#endif

#ifdef SDL_stack_alloc
#undef SDL_stack_alloc
#endif

#ifdef SDL_stack_free
#undef SDL_stack_free
#endif

#ifdef SDL_iconv_utf8_locale
#undef SDL_iconv_utf8_locale
#endif

#ifdef SDL_iconv_utf8_ucs2
#undef SDL_iconv_utf8_ucs2
#endif

#ifdef SDL_iconv_utf8_ucs4
#undef SDL_iconv_utf8_ucs4
#endif

#ifdef SDL_iconv_wchar_utf8
#undef SDL_iconv_wchar_utf8
#endif

#ifdef SDL_LoadWAV
#undef SDL_LoadWAV
#endif

#ifdef SDL_LoadBMP
#undef SDL_LoadBMP
#endif

#ifdef SDL_SaveBMP
#undef SDL_SaveBMP
#endif

#ifdef SDL_GameControllerAddMappingsFromFile
#undef SDL_GameControllerAddMappingsFromFile
#endif

#ifdef SDL_iOSSetAnimationCallback
#undef SDL_iOSSetAnimationCallback
#endif

#ifdef SDL_iOSSetEventPump
#undef SDL_iOSSetEventPump
#endif

#endif

/* vi: set ts=4 sw=4 expandtab: */
