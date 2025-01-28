// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
    Copyright (C) 2010 Markus Drescher

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
 *  \file CArenaSnapshot.cpp
 *  \brief Arena snapshot for network exchange
 */

#include "StdAfx.h"
#include "CArenaSnapshot.h"

#include <string.h>

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

//#define _DEBUG

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::Create (void)
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::Destroy (void)
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::Begin (void)
{
    m_Position = 0;

#ifdef BOMBERMAAAN_DEBUG
    debugLog.WriteDebugMsg(DEBUGSECT_OTHER, "BEGIN SNAPSHOT\n");
#endif
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

template<typename T>
void CArenaSnapshot::ReadData(T* pValue)
{
    ASSERT(m_Position + sizeof(T) < ARENA_SNAPSHOT_SIZE);

    memcpy(pValue, &m_Buffer[m_Position], sizeof(T)); // #3078839

#ifdef BOMBERMAAAN_DEBUG
    debugLog.WriteDebugMsg(DEBUGSECT_OTHER, "READ %s %d FROM POS %d\n", typeid(T).name(), *pValue, m_Position);
#endif

    m_Position += sizeof(T);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

template<typename T>
void CArenaSnapshot::WriteData(const T& Value)
{
    ASSERT(m_Position + sizeof(T) < ARENA_SNAPSHOT_SIZE);
    
    memcpy(&m_Buffer[m_Position], &Value, sizeof(T)); // #3078839

#ifdef BOMBERMAAAN_DEBUG
    debugLog.WriteDebugMsg(DEBUGSECT_OTHER, "WRITE %s %d TO POS %d\n", typeid(T).name(), Value, m_Position);
#endif

    m_Position += sizeof(T);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::ReadInteger(int* pValue)
{
    ReadData(pValue);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::ReadFloat(float* pValue)
{
    ReadData(pValue);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::ReadBoolean(bool* pValue)
{
    ReadData(pValue);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::ReadPointer(const void** pValue)
{
    ReadData(pValue);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::WriteInteger(int Value)
{
    WriteData(Value);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::WriteFloat(float Value)
{
    WriteData(Value);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::WriteBoolean(bool Value)
{
    WriteData(Value);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void CArenaSnapshot::WritePointer(const void* Value)
{
    WriteData(Value);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
