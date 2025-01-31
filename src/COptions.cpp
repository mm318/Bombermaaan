// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/************************************************************************************

    Copyright (C) 2000-2002, 2007 Thibaut Tollemer
    Copyright (C) 2007, 2008 Bernd Arnold
    Copyright (C) 2008 Jerome Bigot
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
 *  \file COptions.cpp
 *  \brief Handling game options, saving to and reading from file
 */

#include <sstream>
#include <vector>
#include <algorithm>

#include "StdAfx.h"
#include "BombermaaanAssets.h"

#include "COptions.h"
#include "CInput.h"
#include "CArena.h"

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

#define TIMESTART_MINUTES   1
#define TIMESTART_SECONDS   30

#define TIMEUP_MINUTES      0
#define TIMEUP_SECONDS      35

#define CONFIGURATION_KEYBOARD_1      0
#define CONFIGURATION_KEYBOARD_2      1
#define CONFIGURATION_KEYBOARD_3      2
#define CONFIGURATION_KEYBOARD_4      3
#define CONFIGURATION_KEYBOARD_5      4
#define CONFIGURATION_JOYSTICK_1      5

// This check ensures we've also set NUMBER_OF_KEYBOARD_CONFIGURATIONS in CInput.h appropriate
#if NUMBER_OF_KEYBOARD_CONFIGURATIONS != CONFIGURATION_JOYSTICK_1
#error "Mismatch between first joystick input and number of keyboard configurations"
#endif

struct SFileInfo
{
    std::string fileNameWithoutPath;
    std::string fileNameWithPath;
};

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

COptions::COptions (void)
{

    m_BattleMode = BATTLEMODE_SINGLE;

    m_TimeStartMinutes = 0;
    m_TimeStartSeconds = 0;
    m_TimeUpMinutes = 0;
    m_TimeUpSeconds = 0;
    m_PlayerCount = 0;
    m_BattleCount = 0;

    m_Level = 0;
    
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        m_BomberType[i] = BOMBERTYPE_OFF;
        m_BomberTeam[i] = BOMBERTEAM_A;
        m_PlayerInput[i] = CONFIGURATION_KEYBOARD_1 + i;
    }

    for (int i = 0; i < MAX_PLAYER_INPUT; i++)
        for (int j = 0; j < NUM_CONTROLS; j++)
            m_Control[i][j] = 0;

}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

COptions::COptions(const COptions& another)
{

    operator=(another);

}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

COptions::~COptions (void)
{
    Destroy();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

COptions& COptions::operator = (const COptions& Copy)
{
    m_TimeStartMinutes = Copy.m_TimeStartMinutes;
    m_TimeStartSeconds = Copy.m_TimeStartSeconds;
    m_TimeUpMinutes = Copy.m_TimeUpMinutes;
    m_TimeUpSeconds = Copy.m_TimeUpSeconds;

    int i, j;

    for (i = 0 ; i < MAX_PLAYERS ; i++)
    {
        m_BomberType[i] = Copy.m_BomberType[i];
        m_PlayerInput[i] = Copy.m_PlayerInput[i];
    }

    m_PlayerCount = Copy.m_PlayerCount;
    m_BattleCount = Copy.m_BattleCount;

    for (i = 0 ; i < MAX_PLAYER_INPUT ; i++)
        for (j = 0 ; j < NUM_CONTROLS ; j++)
            m_Control[i][j] = Copy.m_Control[i][j];
    
    m_Level = Copy.m_Level;

    // Copy all the level data files
    m_Levels = Copy.m_Levels;

    return *this;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::Create(const std::string& dynamicDataFolder, const std::string& pgmFolder)
{
    m_programFolder = pgmFolder;

    // Set the file name of the configuration file including full path
    m_configFileName = dynamicDataFolder;
    m_configFileName.append( "config.xml" );
    theLog.WriteLine( "Options         => Name of config file: '%s'.", m_configFileName.c_str() );

    // Set default configuration values before loading the configuration file and overwriting the default
    SetDefaultValues();

    // Load configuration file and overwrite the previously set defaults
    if (!LoadConfiguration())
    {
        return false;
    }

    if (!LoadLevel("L01", LEVEL_01) ||
        !LoadLevel("L02", LEVEL_02) ||
        !LoadLevel("L03", LEVEL_03) ||
        !LoadLevel("L04", LEVEL_04) ||
        !LoadLevel("L05", LEVEL_05) ||
        !LoadLevel("L06", LEVEL_06) ||
        !LoadLevel("L07", LEVEL_07) ||
        !LoadLevel("L08", LEVEL_08) ||
        !LoadLevel("L09", LEVEL_09) ||
        !LoadLevel("L10", LEVEL_10) ||
        !LoadLevel("L11", LEVEL_11) ||
        !LoadLevel("L12", LEVEL_12) ||
        !LoadLevel("L13", LEVEL_13) ||
        !LoadLevel("L14", LEVEL_14) ||
        !LoadLevel("L15", LEVEL_15) ||
        !LoadLevel("L16", LEVEL_16) ||
        !LoadLevel("L17", LEVEL_17) ||
        !LoadLevel("L18", LEVEL_18) ||
        !LoadLevel("L19", LEVEL_19) ||
        !LoadLevel("L20", LEVEL_20) ||
        !LoadLevel("L21", LEVEL_21) ||
        !LoadLevel("L22", LEVEL_22) ||
        !LoadLevel("L23", LEVEL_23) ||
        !LoadLevel("L24", LEVEL_24))
    {
        return false;
    }

    // Load game levels data and names
    if (!LoadLevelFiles(dynamicDataFolder, pgmFolder))
    {
        return false;
    }

    //---------------------
    // Check for a problem
    //---------------------

    // If there is no level
    if (m_Levels.size() == 0)
    {
        // Log failure
        theLog.WriteLine ("Options         => !!! There should be at least 1 level.");
        return false;
    }

    // If the level number we read in the cfg file is invalid compared to the number of existing levels
    if (m_Level >= (int) m_Levels.size()) // #3078839
    {
        // Select the first level
        m_Level = 0;
    }

    // Everything went ok.
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::Destroy (void)
{
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::SaveBeforeExit (void)
{
    // Write the values to the XML based configuration file
    WriteXMLData();
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::SetDefaultValues(void)
{
    // Time of a match (TimeStart) and when the arena closing begins (TimeUp)
    m_TimeUpMinutes = TIMEUP_MINUTES;
    m_TimeUpSeconds = TIMEUP_SECONDS;
    m_TimeStartMinutes = TIMESTART_MINUTES;
    m_TimeStartSeconds = TIMESTART_SECONDS;

    // Number of matches for a battle
    m_BattleCount = 3;

    // First level file (index=0) is selected
    m_Level = 0;

    // Set the bomber types
    m_BomberType[0] = BOMBERTYPE_MAN;
    m_BomberType[1] = BOMBERTYPE_COM;
    m_BomberType[2] = BOMBERTYPE_COM;
    m_BomberType[3] = BOMBERTYPE_COM;
    m_BomberType[4] = BOMBERTYPE_COM;

    // Set the bomber teams
    m_BomberTeam[0] = BOMBERTEAM_A;
    m_BomberTeam[1] = BOMBERTEAM_A;
    m_BomberTeam[2] = BOMBERTEAM_B;
    m_BomberTeam[3] = BOMBERTEAM_B;
    m_BomberTeam[4] = BOMBERTEAM_B;

    // Initialise player inputs
    for (int i = 0 ; i < MAX_PLAYERS ; i++)
    {
        m_PlayerInput[i] = CONFIGURATION_KEYBOARD_1 + i;
    }

    // Set default keyboard keys and joystick buttons
    m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_UP]      = KEYBOARD_T;
    m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_DOWN]    = KEYBOARD_G;
    m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_LEFT]    = KEYBOARD_F;
    m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_RIGHT]   = KEYBOARD_H;
    m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_ACTION1] = KEYBOARD_S;
    m_Control[CONFIGURATION_KEYBOARD_1][CONTROL_ACTION2] = KEYBOARD_A;

    m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_UP]      = KEYBOARD_NUMPAD8;
    m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_DOWN]    = KEYBOARD_NUMPAD5;
    m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_LEFT]    = KEYBOARD_NUMPAD4;
    m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_RIGHT]   = KEYBOARD_NUMPAD6;
    m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_ACTION1] = KEYBOARD_APOSTROPHE;
    m_Control[CONFIGURATION_KEYBOARD_2][CONTROL_ACTION2] = KEYBOARD_SEMICOLON;

    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_UP]      = KEYBOARD_I;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_DOWN]    = KEYBOARD_K;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_LEFT]    = KEYBOARD_J;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_RIGHT]   = KEYBOARD_L;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_ACTION1] = KEYBOARD_6;
    m_Control[CONFIGURATION_KEYBOARD_3][CONTROL_ACTION2] = KEYBOARD_5;

    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_UP]      = KEYBOARD_D;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_DOWN]    = KEYBOARD_C;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_LEFT]    = KEYBOARD_X;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_RIGHT]   = KEYBOARD_V;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_ACTION1] = KEYBOARD_Z;
    m_Control[CONFIGURATION_KEYBOARD_4][CONTROL_ACTION2] = KEYBOARD_LSHIFT;

    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_UP]      = KEYBOARD_3;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_DOWN]    = KEYBOARD_E;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_LEFT]    = KEYBOARD_W;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_RIGHT]   = KEYBOARD_R;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_ACTION1] = KEYBOARD_2;
    m_Control[CONFIGURATION_KEYBOARD_5][CONTROL_ACTION2] = KEYBOARD_1;

    for ( unsigned int j = CONFIGURATION_JOYSTICK_1 ; j < MAX_PLAYER_INPUT ; j++)
    {
        m_Control[j][CONTROL_UP]      = JOYSTICK_UP;
        m_Control[j][CONTROL_DOWN]    = JOYSTICK_DOWN;
        m_Control[j][CONTROL_LEFT]    = JOYSTICK_LEFT;
        m_Control[j][CONTROL_RIGHT]   = JOYSTICK_RIGHT;
        m_Control[j][CONTROL_ACTION1] = JOYSTICK_BUTTON(0);
        m_Control[j][CONTROL_ACTION2] = JOYSTICK_BUTTON(1);
    }
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

/**
 *  For migration purposes, the old configuration file is still read.
 *  So your settings should be seamlessly migrated to the new XML format.
 *  Once the XML file is written, the old configuration file could be
 *  deleted.
 *
 *  This feature will be removed in the future.
 */

bool COptions::LoadConfiguration (void)
{
    TiXmlDocument configDoc( m_configFileName );
    
    // Try to load XML file
    if ( configDoc.LoadFile() ) {

        // The file could be loaded successfully
        int tempRevision = 0;
        TiXmlHandle configHandle( &configDoc );
        TiXmlElement *confRevision = configHandle.FirstChild( "Bombermaaan" )
                                                 .FirstChild( "Configuration" )
                                                 .FirstChild( "ConfigRevision" )
                                                 .ToElement();
        if ( confRevision )
        {
            confRevision->QueryIntAttribute( "value", &tempRevision );
        }

        theLog.WriteLine( "Options         => Configuration file was successfully loaded and is at revision %d.", tempRevision );

        ReadIntFromXML( configDoc, "TimeUp", "minutes", &m_TimeUpMinutes );
        ReadIntFromXML( configDoc, "TimeUp", "seconds", &m_TimeUpSeconds );

        ReadIntFromXML( configDoc, "TimeStart", "minutes", &m_TimeStartMinutes );
        ReadIntFromXML( configDoc, "TimeStart", "seconds", &m_TimeStartSeconds );

        ReadIntFromXML( configDoc, "BattleMode", "value", (int*)&m_BattleMode );

        ReadIntFromXML( configDoc, "BattleCount", "value", &m_BattleCount );
        
        ReadIntFromXML( configDoc, "LevelFileNumber", "value", &m_Level );

        for ( int i = 0; i < MAX_PLAYERS; i++ ) {
            std::ostringstream oss;
            oss << "bomber" << i;
            std::string attributeName = oss.str();
            ReadIntFromXML( configDoc, "BomberTypes", attributeName, (int*) (&m_BomberType[i]) );
            ReadIntFromXML(configDoc, "BomberTeams", attributeName, (int*)(&m_BomberTeam[i]));
            ReadIntFromXML(configDoc, "PlayerInputs", attributeName, (int*)(&m_PlayerInput[i]));
        }

        //
        // Read the control settings
        // List of input devices (keyboard n, joystick n) -> Control (up, down, ..., action1, action2) -> Key/Button
        //

        // Create a handle to the XML document
        TiXmlHandle handle( &configDoc );

        // Fetch the element
        TiXmlElement *element = handle.FirstChild( "Bombermaaan" ).FirstChild( "Configuration" ).FirstChild( "ControlList" ).FirstChild( "Control" ).ToElement();

        // If the element exists, go on
        if ( element )
        {
            // Loop through all sub-elements of the ControlList node
            for ( ; element; element = element->NextSiblingElement() )
            {
                int id = -1;
                element->QueryIntAttribute( "id", &id );

                // The id must be between 0 and MAX_PLAYER_INPUT
                if ( id < 0 || id >= MAX_PLAYER_INPUT )
                    continue;

                // Read all control values (up, down, left, right, action1, action2)
                for ( unsigned int ctrl = 0; ctrl < NUM_CONTROLS; ctrl++ )
                {
                    int ctrldata = -1;

                    std::ostringstream oss;
                    oss << "control" << ctrl;
                    std::string attributeName = oss.str();

                    element->QueryIntAttribute( attributeName, &ctrldata);

                    // Verify we have read a valid number
                    if ( ctrldata >= 0 )
                    {
                        m_Control[id][ctrl] = ctrldata;
                    }
                }
            }
        }

    } else {

        // The configuration could not be loaded, maybe it doesn't exist
        theLog.WriteLine ("Options         => Configuration file could not be loaded." );

    }

    //! We always return true since it doesn't matter if the configuration file could not be loaded
    // Success
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

void COptions::WriteXMLData()
{
    // Create document
    TiXmlDocument newConfig;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
    newConfig.LinkEndChild( decl );

    // Root node
    TiXmlElement * root = new TiXmlElement( "Bombermaaan" );
    newConfig.LinkEndChild( root );

    // Comment
    TiXmlComment * comment = new TiXmlComment();
    comment->SetValue(" Configuration settings for the Bombermaaan game (http://bombermaaan.sf.net/) " );
    root->LinkEndChild( comment );

    // Configuration tree node - all options have this node as parent
    TiXmlElement * config = new TiXmlElement( "Configuration" );
    root->LinkEndChild( config );

    //! The revision number is currently 1
    TiXmlElement* configRev = new TiXmlElement( "ConfigRevision" );
    configRev->SetAttribute( "value", 1 );
    config->LinkEndChild( configRev );

    // TimeUp (when will arena close begin)
    TiXmlElement* configTimeUp = new TiXmlElement( "TimeUp" );
    configTimeUp->SetAttribute( "minutes", m_TimeUpMinutes );
    configTimeUp->SetAttribute( "seconds", m_TimeUpSeconds );
    config->LinkEndChild( configTimeUp );

    // TimeStart (the duration of a match)
    TiXmlElement* configTimeStart = new TiXmlElement( "TimeStart" );
    configTimeStart->SetAttribute( "minutes", m_TimeStartMinutes );
    configTimeStart->SetAttribute( "seconds", m_TimeStartSeconds );
    config->LinkEndChild( configTimeStart );

    // BattleMode
    TiXmlElement* configBattleMode = new TiXmlElement("BattleMode");
    configBattleMode->SetAttribute("value", m_BattleMode);
    config->LinkEndChild(configBattleMode);

    // BattleCount
    TiXmlElement* configBattleCount = new TiXmlElement( "BattleCount" );
    configBattleCount->SetAttribute( "value", m_BattleCount );
    config->LinkEndChild( configBattleCount );

    // LevelFileNumber
    TiXmlElement* configLevel = new TiXmlElement( "LevelFileNumber" );
    configLevel->SetAttribute( "value", m_Level );
    config->LinkEndChild( configLevel );

    int i;

    // BomberTypes
    TiXmlElement* configBomberTypes = new TiXmlElement( "BomberTypes" );
    for ( i = 0; i < MAX_PLAYERS; i++ ) {
        std::ostringstream oss;
        oss << "bomber" << i;
        std::string attributeName = oss.str();
        configBomberTypes->SetAttribute( attributeName, (int) m_BomberType[i] );
    }
    config->LinkEndChild( configBomberTypes );

    // BomberTeams
    TiXmlElement* configBomberTeams = new TiXmlElement("BomberTeams");
    for (i = 0; i < MAX_PLAYERS; i++) {
        std::ostringstream oss;
        oss << "bomber" << i;
        std::string attributeName = oss.str();
        configBomberTeams->SetAttribute(attributeName, (int)m_BomberTeam[i]);
    }
    config->LinkEndChild(configBomberTeams);

    // PlayerInputs
    TiXmlElement* configPlayerInputs = new TiXmlElement( "PlayerInputs" );
    for ( i = 0; i < MAX_PLAYERS; i++ ) {
        std::ostringstream oss;
        oss << "bomber" << i;
        std::string attributeName = oss.str();
        configPlayerInputs->SetAttribute( attributeName, (int) m_PlayerInput[i] );
    }
    config->LinkEndChild( configPlayerInputs );

    // ControlList
    TiXmlElement* configControlList = new TiXmlElement( "ControlList" );
    for ( unsigned int j = 0; j < MAX_PLAYER_INPUT; j++ )
    {
        TiXmlElement* configControl = new TiXmlElement( "Control" );
        configControl->SetAttribute( "id", j );
        for ( unsigned int ctrl = 0; ctrl < NUM_CONTROLS; ctrl++ )
        {
            std::ostringstream oss;
            oss << "control" << ctrl;
            std::string attributeName = oss.str();
            configControl->SetAttribute( attributeName, (int) m_Control[j][ctrl] );
        }
        configControlList->LinkEndChild( configControl );
    }
    config->LinkEndChild( configControlList );


    //
    // Save file
    //
    bool saveOkay = newConfig.SaveFile( m_configFileName );

    // Log a message
    theLog.WriteLine( "Options         => Configuration file was %s written.", ( saveOkay ? "successfully" : "not" ) );
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

/**
 *  \brief Read an integer from the XML document structure.
 *  This function reads an attribute of the node /Bombermaaan/Configuration/NAME, where NAME can be specified by configNode.
 *
 *  @param doc          The TinyXML document
 *  @param configNode   The name of the node below /Bombermaaan/Configuration/
 *  @param attrName     The name of the attribute to be read
 *  @param value        Value of the specified attribute
 *  @todo Set first three parameters to const if possible
 */

void COptions::ReadIntFromXML(TiXmlDocument &doc, std::string configNode, std::string attrName, int *value)
{
    // Create a handle to the XML document
    TiXmlHandle handle( &doc );

    // Fetch the element
    TiXmlElement *element = handle.FirstChild( "Bombermaaan" ).FirstChild( "Configuration" ).FirstChild( configNode ).ToElement();

    // If the element exists, read the int value from the specified attribute
    // The value variable stays unchanged if there's no int value
    if ( element )
        element->QueryIntAttribute( attrName, value );
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

bool COptions::LoadLevel(const std::string& levelName, const uint8_t* data)
{
    m_Levels.push_back(CLevel(levelName));  // Create a new CLevel element and add it to the level container
    std::istringstream in(reinterpret_cast<const char*>(data));
    return m_Levels.back().LoadFromStream(in);
}

bool COptions::LoadLevel(const std::string& levelName, std::istream& in)
{
    // Create a new CLevel element and add it to the level container
    m_Levels.push_back(CLevel(levelName));
    return m_Levels.back().LoadFromStream(in);
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************

std::vector<SFileInfo> FindLevels(const std::string& folder)
{
    long FindHandle;
    _finddata_t FindData = {};  // initialise OUR data structure

    //-------------------------------------------
    // Set the path where the level files are stored
    //-------------------------------------------
    
    std::string levelFilePath = folder;
    if (folder.length() >= 1)
    {
        char delim = folder.c_str()[folder.length()-1];
        if (delim != '\\' && delim != '/')
#ifdef WIN32
            levelFilePath.append("\\");
#else
            levelFilePath.append("/");
#endif
    }

#ifdef WIN32
    levelFilePath.append( "Levels\\" );
#else
    levelFilePath.append( "levels/" );
#endif

    std::string levelFilePathMask = levelFilePath + "*.TXT";

    //-------------------------------------------
    // Determine number of level files available
    //-------------------------------------------
    
    theLog.WriteLine( "Options         => Loading level files '%s'.", levelFilePathMask.c_str() );

    std::vector<SFileInfo> files;

    FindHandle = _findfirst(levelFilePathMask.c_str(), &FindData);

    if (FindHandle != -1)
    {
        do
        {
            SFileInfo file;

            file.fileNameWithoutPath = FindData.name;
            file.fileNameWithPath = levelFilePath;
            file.fileNameWithPath.append(FindData.name);

            files.push_back(file);

        }
        while (_findnext(FindHandle, &FindData) != -1);
    }

    _findclose(FindHandle);

    //---------------------
    // Sort
    //---------------------
#ifdef WIN32
    sort(files.begin(), files.end(), [&](const SFileInfo& a, const SFileInfo& b) {
        return (a.fileNameWithoutPath < b.fileNameWithoutPath);
    });
#endif

    return files;
}

bool COptions::LoadLevelFiles(const std::string& dynamicDataFolder, const std::string& pgmFolder)
{
    std::vector<SFileInfo> files = FindLevels(pgmFolder);

    // If a dynamic folder is set, load level files from there, too
    if ( dynamicDataFolder != "" ) {
        std::vector<SFileInfo> dynamicDataFolderFiles = FindLevels(dynamicDataFolder);
        files.insert(files.end(), dynamicDataFolderFiles.begin(), dynamicDataFolderFiles.end());
    }

    //------------------------------------------------------
    // Load all the level files detected earlier
    //------------------------------------------------------
    
    bool ErrorOccurred = false;    

    for (std::vector<SFileInfo>::iterator it = files.begin(); it != files.end(); ++it)
    {
        std::ifstream in(it->fileNameWithPath);
        if (!LoadLevel(it->fileNameWithoutPath, in))
        {
            ErrorOccurred = true;
            break;
        }
    }

    // If we had to stop then there is a problem.
    if (ErrorOccurred)
    {
        return false;
    }

    // Everything went right
    return true;
}

//******************************************************************************************************************************
//******************************************************************************************************************************
//******************************************************************************************************************************
