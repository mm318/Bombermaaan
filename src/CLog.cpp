// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
    Copyright (C) 2008-2010 Markus Drescher
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
 *  \file CLog.cpp
 *  \brief Handling the log
 *
 *  by Thibaut "Fury" Tollemer
 *
 *  Most of the code was taken in the
 *  Log.cpp/Log.h files of HaCKeR source,
 *  by Michael Schoonbrood :
 *      - MadButch@OneCoolDude.Com
 *      - http://play.as/madbutch
 */

#include "StdAfx.h"
#include "CLog.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! Display a dot on the console every X repeated messages
#define REPEATED_MESSAGES_LIMIT     300

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CLog::CLog()
{
    m_bOpen = false;    // Log file is not open yet
    m_toStdout = false;

    m_FilterRepeatedMessage = true; // Filter repeated messages by default
    m_NumberOfRepeatedMessages = 0; // No previous message
    m_LastMessage[0] = '\0';        // No previous message
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

CLog::~CLog()
{
    // Close the log file
    if( m_bOpen )
    {
        Close();
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Get an instance of CLog (singleton)
CLog& CLog::GetLog()
{
   static CLog sLog;
   return sLog;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Get an instance of CLog (singleton)
CLog& CLog::GetDebugLog()
{
   static CLog sDebugLog;
   return sDebugLog;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Open the Log
bool CLog::Open(const char *pFilename, const bool tee)
{
    // Check if there already is an opened file
    if( m_bOpen )
    {
        // Close it first
        Close();
    }

    // Make sure the file is NOT read-only
#ifdef WIN32
    SetFileAttributes( pFilename, FILE_ATTRIBUTE_NORMAL );
#endif

    // Open the Log
    m_theLog.open( pFilename );
    if( !m_theLog.fail() )
    {
        // Set indicator bOpen to true
        m_bOpen = true;

        // Get current time
#ifdef WIN32
        SYSTEMTIME LocalTime;
        GetLocalTime (&LocalTime);
#else
        struct tm *LocalTime;
        time_t curTime = time(NULL);
        LocalTime = localtime(&curTime);
#endif
        
        // Store first log entry
        char FirstLogEntry [128];
#ifdef WIN32
        sprintf( FirstLogEntry,                                              // String where to write
                 "==> Log started on %4d-%02d-%02d at %02d:%02d:%02d.\n\n",  // Format to use
                 LocalTime.wYear, LocalTime.wMonth, LocalTime.wDay,          // Time numbers to use
                 LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond );
#else
        sprintf( FirstLogEntry,                                                     // String where to write
                 "==> Log started on %4d-%02d-%02d at %02d:%02d:%02d.\n\n",         // Format to use
                 LocalTime->tm_year + 1900, LocalTime->tm_mon, LocalTime->tm_mday,  // Time numbers to use
                 LocalTime->tm_hour, LocalTime->tm_min, LocalTime->tm_sec );
#endif
        
        // Write first log entry
        m_theLog.write( FirstLogEntry, strlen( FirstLogEntry ) );
    }
    else
    {
        // Set indicator bOpen to false
        m_bOpen = false;
    }

    m_toStdout = tee;

    return m_bOpen;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Close the Log
bool CLog::Close()
{
    // Close the Log
    if( m_bOpen )
    {
        // Write a blank line
        m_theLog.write( "\n", 1 );
        
        // Get current time
#ifdef WIN32
        SYSTEMTIME LocalTime;
        GetLocalTime (&LocalTime);
#else
        struct tm *LocalTime;
        time_t curTime = time(NULL);
        LocalTime = localtime(&curTime);
#endif
        
        // Store last log entry
        char LastLogEntry [128];
#ifdef WIN32
        sprintf( LastLogEntry,                                             // String where to write
                 "==> Log ended on %4d-%02d-%02d at %02d:%02d:%02d.\n\n",  // Format to use
                 LocalTime.wYear, LocalTime.wMonth, LocalTime.wDay,        // Time numbers to use
                 LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond );
#else
        sprintf( LastLogEntry,                                                      // String where to write
                 "==> Log ended on %4d-%02d-%02d at %02d:%02d:%02d.\n\n",           // Format to use
                 LocalTime->tm_year + 1900, LocalTime->tm_mon, LocalTime->tm_mday,  // Time numbers to use
                 LocalTime->tm_hour, LocalTime->tm_min, LocalTime->tm_sec );
#endif
        
        // Write last log entry
        m_theLog.write( LastLogEntry, strlen( LastLogEntry ) );

        // Close the file
        m_theLog.close();
    }

    m_bOpen = false;

    return !m_bOpen;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//! Log the last error, which can be found by calling the WINAPI function GetLastError().
void CLog::LogLastError()
{
#ifdef WIN32
    // Declare variables
    LPVOID lpMsgBuf;

    FormatMessage(  FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    GetLastError(),
                    MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), // Default language
                    (char *) &lpMsgBuf,
                    0,
                    NULL );

    // Log the error
    WriteLine( (const char *) lpMsgBuf );

    // Free the buffer.
    LocalFree( lpMsgBuf );
#else
    WriteLine( (const char *) strerror( errno ) );
#endif
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

long CLog::Write( const char *pMessage, ...)
{
    va_list argList;
    va_start(argList, pMessage);
    long result = WriteImpl(pMessage, argList);
    va_end (argList);
    return result;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Write a line into the Log
long CLog::WriteLine( const char *pMessage, ... )
{
    char msgFmt[1024];
    sprintf(msgFmt, "%s\n", pMessage);

    va_list argList;
    va_start(argList, pMessage);
    long result = WriteImpl(msgFmt, argList);
    va_end (argList);

    return result;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

// Write a line into the Log
long CLog::WriteDebugMsg( EDebugSection section, const char *pMessage, ... )
{
    char msgFmt[1024];
    switch(section)
    {
        case DEBUGSECT_BOMBER:
            sprintf(msgFmt, "BOMBER:     %s\n", pMessage);  // #3078839
            break;
          
        case DEBUGSECT_BOMB:
            sprintf(msgFmt, "BOMB:       %s\n", pMessage);  // #3078839
            break;
          
        case DEBUGSECT_EXPLOSION:
            sprintf(msgFmt, "EXPLOSION:  %s\n", pMessage);  // #3078839
            break;

        default:
            sprintf(msgFmt, "UNKNOWN:    %s\n", pMessage);  // #3078839
            break;
    }

    va_list argList;
    va_start(argList, pMessage);
    long result = WriteImpl(msgFmt, argList);
    va_end (argList);

    return result;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

long CLog::WriteImpl(const char *pMessage, va_list args)
{
    // Format the given string using the given arguments ("..." parameter)
    char Message[2048];
    vsprintf(Message, pMessage, args);

    bool isRepeatMessage = false;

    // If we have to filter repeated messages
    if (m_FilterRepeatedMessage)
    {        
        // If the last message written to the console is not the same
        if (strcmp(Message, m_LastMessage) != 0)
        {
            // Save the message
            strcpy(m_LastMessage, Message);

            // Stop the chain of repeated messages (if there is one)
            m_NumberOfRepeatedMessages = 0;
        }
        // If the last message written to the console is the same
        else
        {
            // It's a repeated message
            m_NumberOfRepeatedMessages++;

            // Show that messages are being repeated, by writing a dot 
            // every REPEATED_MESSAGES_LIMIT repeated messages.
            if ((m_NumberOfRepeatedMessages % REPEATED_MESSAGES_LIMIT) == 0)
            {
                sprintf(Message, ".");
            }
            else
            {
                isRepeatMessage = true;
            }
        }
    }

    // If the log is open
    if(m_bOpen && !isRepeatMessage)
    {
        // Get current time
#ifdef WIN32
        SYSTEMTIME LocalTime;
        GetLocalTime (&LocalTime);
#else
        struct tm *LocalTime;
        time_t curTime = time(NULL);
        LocalTime = localtime(&curTime);
#endif

        // Store the time string
        char Time [64];
#ifdef WIN32
        sprintf ( Time,                 // String where to write
                  "%02d:%02d:%02d\n",   // Format (don't forget '\n' character!)
                  LocalTime.wHour,      // Time numbers to use
                  LocalTime.wMinute, 
                  LocalTime.wSecond );
#else
        sprintf ( Time,                 // String where to write
                  "%02d:%02d:%02d\n",   // Format (don't forget '\n' character!)
                  LocalTime->tm_hour,   // Time numbers to use
                  LocalTime->tm_min, 
                  LocalTime->tm_sec );
#endif
        
        // Write the time string
        m_theLog.write( Time, strlen( Time ) );

        // Write the space between time and message
        m_theLog.write( "  ", strlen( "  " ) );

        // Write the message
        m_theLog.write( Message, strlen( Message ) );

        m_theLog.flush();
    }

    if (m_toStdout && !isRepeatMessage)
    {
        std::cout.write(Message, strlen(Message));
    }

    return 1;
}
