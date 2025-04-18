/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
    Copyright (C) 2008 Bernd Arnold

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
 *  \file CLog.h
 *  \brief Header file of the log
 *
 *  by Thibaut "Fury" Tollemer
 *
 *  Most of the code was taken in the
 *  Log.cpp/Log.h files of HaCKeR source,
 *  by Michael Schoonbrood :
 *      - MadButch@OneCoolDude.Com
 *      - http://play.as/madbutch
 */

#ifndef _LOG_H
#define _LOG_H

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#ifndef __EMSCRIPTEN__
#include <cstdio>
#endif

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define theLog      CLog::GetLog()
#define debugLog    CLog::GetDebugLog()

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

enum EDebugSection {
    DEBUGSECT_BOMBER,
    DEBUGSECT_BOMB,
    DEBUGSECT_EXPLOSION,
    DEBUGSECT_OTHER
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! Implements a log file where messages can be written to
class CLog
{
public:
                    CLog();
    virtual         ~CLog();
    static CLog&    GetLog();                                             //!< Get an instance of CLog (singleton)
    static CLog&    GetDebugLog();                                        //!< Get an instance of CLog (singleton) for debug messages
    bool            Open(const char *pFilename, const bool tee = false);  //!< Open the log
    bool            Close();                                              //!< Close the log
    void            LogLastError();                                       //!< Log the last occured error!
    long            Write( const char *pMessage, ... );
    long            WriteLine( const char *pMessage, ... );               //!< Write a line to the log
    long            WriteDebugMsg( EDebugSection section, const char *pMessage, ... ); //!< Write a line to the log

private:

    inline bool     IsOpen() const;                                       //!< Return whether the log is open or not
    long            WriteImpl(const char *pMessage, va_list args);

#ifndef __EMSCRIPTEN__
    FILE*           m_theLog;
#endif
    bool            m_toStdout;
    bool            m_FilterRepeatedMessage;    //!< Should we manage message repetition by not displaying all consecutive identical messages?
    int             m_NumberOfRepeatedMessages; //!< How many consecutive identical messages have been sent?
    char            m_LastMessage[2048];        //!< Last message written to the console
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Return whether the log is open or not
inline bool CLog::IsOpen() const
{
#ifndef __EMSCRIPTEN__
    return m_theLog != nullptr;
#else
    return false;
#endif
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#endif // _LOG_H
