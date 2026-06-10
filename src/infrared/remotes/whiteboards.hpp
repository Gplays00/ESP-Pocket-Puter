#pragma ocne

#include "../universal_remote.hpp"

const Remote WHITEBOARDS_REMOTES[] PROGMEM = {
    {
        "Promethean active panel",
        REMOTE_TYPE_WHITEBOARDS,
        {
            {"Power", REMOTE_PROTOCOL_NEC, "01 00 00 00", "18 00 00 00"},
            {"VOL+", REMOTE_PROTOCOL_NEC, "01 00 00 00", "14 00 00 00"},
            {"VOL-", REMOTE_PROTOCOL_NEC, "01 00 00 00", "10 00 00 00"},
            {"Blank", REMOTE_PROTOCOL_NEC, "01 00 00 00", "04 00 00 00"},
            {"Freeze", REMOTE_PROTOCOL_NEC, "01 00 00 00", "12 00 00 00"},
            {"Up", REMOTE_PROTOCOL_NEC, "01 00 00 00", "46 00 00 00"},
            {"Down", REMOTE_PROTOCOL_NEC, "01 00 00 00", "16 00 00 00"},
            {"Left", REMOTE_PROTOCOL_NEC, "01 00 00 00", "47 00 00 00"},
            {"Right", REMOTE_PROTOCOL_NEC, "01 00 00 00", "15 00 00 00"},
            {"Ok", REMOTE_PROTOCOL_NEC, "01 00 00 00", "55 00 00 00"},
            {"Menu", REMOTE_PROTOCOL_NEC, "01 00 00 00", "40 00 00 00"},
            {"Source", REMOTE_PROTOCOL_NEC, "01 00 00 00", "0D 00 00 00"},
            {"Settings", REMOTE_PROTOCOL_NEC, "01 00 00 00", "25 00 00 00"},

            
        }
    },
    { 
        "Promethean Digital Whiteboard",
        REMOTE_TYPE_WHITEBOARDS,
        {
            {"Power", REMOTE_PROTOCOL_NEC, "31 00 00 00", "81 00 00 00"},
            {"Freeze", REMOTE_PROTOCOL_NEC, "31 00 00 00", "8E 00 00 00"},
            {"Blank", REMOTE_PROTOCOL_NEC, "31 00 00 00", "8B 00 00 00"},
            {"Page up", REMOTE_PROTOCOL_NEC, "31 00 00 00", "CB 00 00 00"},
            {"Page down", REMOTE_PROTOCOL_NEC, "31 00 00 00", "CC 00 00 00"},
            {"UP", REMOTE_PROTOCOL_NEC, "31 00 00 00", "C1 00 00 00"},
            {"Down", REMOTE_PROTOCOL_NEC, "31 00 00 00", "C2 00 00 00"},
            {"Enter", REMOTE_PROTOCOL_NEC, "31 00 00 00", "C5 00 00 00"},
            {"Left", REMOTE_PROTOCOL_NEC, "31 00 00 00", "C3 00 00 00"},
            {"Right", REMOTE_PROTOCOL_NEC, "31 00 00 00", "C4 00 00 00"},
            {"Zoom-", REMOTE_PROTOCOL_NEC, "31 00 00 00", "8D 00 00 00"},
            {"Zoom+", REMOTE_PROTOCOL_NEC, "31 00 00 00", "8A 00 00 00"},
            {"Menu", REMOTE_PROTOCOL_NEC, "31 00 00 00", "87 00 00 00"},
            {"Source", REMOTE_PROTOCOL_NEC, "31 00 00 00", "83 00 00 00"},


            
        }
    },
    { 
        "Philips smartboard ID1",
        REMOTE_TYPE_WHITEBOARDS,
        {
        {"Power",      REMOTE_PROTOCOL_RC6, "00 00 00 00", "0C 00 00 00"},
        {"Home",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "F5 00 00 00"},
        {"Options",    REMOTE_PROTOCOL_RC6, "00 00 00 00", "40 00 00 00"},
        {"Info",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "5A 00 00 00"},
        {"Aspect Rat", REMOTE_PROTOCOL_RC6, "00 00 00 00", "0A 00 00 00"},
        {"Adjust",     REMOTE_PROTOCOL_RC6, "00 00 00 00", "59 00 00 00"},
        {"Vol+",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "10 00 00 00"},
        {"Mute",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "0D 00 00 00"},
        {"Vol-",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "11 00 00 00"},
        {"Play",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "2C 00 00 00"},
        {"Stop",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "31 00 00 00"},
        {"Pause",      REMOTE_PROTOCOL_RC6, "00 00 00 00", "30 00 00 00"},
        {"Next",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "28 00 00 00"},
        {"Prev",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "2B 00 00 00"},
        {"Up",         REMOTE_PROTOCOL_RC6, "00 00 00 00", "0F 00 00 00"},
        {"Ok",         REMOTE_PROTOCOL_RC6, "00 00 00 00", "5B 00 00 00"},
        {"Left",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "5C 00 00 00"},
        {"Right",      REMOTE_PROTOCOL_RC6, "00 00 00 00", "90 00 00 00"},
        {"Rev",        REMOTE_PROTOCOL_RC6, "00 00 00 00", "CC 00 00 00"},
        {"List",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "58 00 00 00"},
        {"Red",        REMOTE_PROTOCOL_RC6, "00 00 00 00", "6D 00 00 00"},
        {"Green",      REMOTE_PROTOCOL_RC6, "00 00 00 00", "6E 00 00 00"},
        {"Yellow",     REMOTE_PROTOCOL_RC6, "00 00 00 00", "6F 00 00 00"},
        {"Blue",       REMOTE_PROTOCOL_RC6, "00 00 00 00", "70 00 00 00"},
        {"0",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "00 00 00 00"},
        {"1",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "01 00 00 00"},
        {"2",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "02 00 00 00"},
        {"3",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "03 00 00 00"},
        {"4",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "04 00 00 00"},
        {"5",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "05 00 00 00"},
        {"6",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "06 00 00 00"},
        {"7",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "07 00 00 00"},
        {"8",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "08 00 00 00"},
        {"9",          REMOTE_PROTOCOL_RC6, "00 00 00 00", "09 00 00 00"},
        {"Source",     REMOTE_PROTOCOL_RC6, "00 00 00 00", "54 00 00 00"},
    }
},
{
    "Boxlight Smartboard",
    REMOTE_TYPE_WHITEBOARDS,
    {
        {"Power",         REMOTE_PROTOCOL_NEC, "20 00 00 00", "52 00 00 00"},
        {"Home",          REMOTE_PROTOCOL_NEC, "20 00 00 00", "48 00 00 00"},
        {"HDMI",          REMOTE_PROTOCOL_NEC, "20 00 00 00", "07 00 00 00"},
        {"Touchlock",     REMOTE_PROTOCOL_NEC, "20 00 00 00", "5C 00 00 00"},
        {"Display Off",   REMOTE_PROTOCOL_NEC, "20 00 00 00", "4E 00 00 00"},
        {"Screenshare",   REMOTE_PROTOCOL_NEC, "20 00 00 00", "0A 00 00 00"},
        {"Sound Controls",REMOTE_PROTOCOL_NEC, "20 00 00 00", "0D 00 00 00"},
        {"Vol+",          REMOTE_PROTOCOL_NEC, "20 00 00 00", "03 00 00 00"},
        {"Vol-",          REMOTE_PROTOCOL_NEC, "20 00 00 00", "41 00 00 00"},
        {"Mute",          REMOTE_PROTOCOL_NEC, "20 00 00 00", "53 00 00 00"},
        {"Up",            REMOTE_PROTOCOL_NEC, "20 00 00 00", "47 00 00 00"},
        {"Down",          REMOTE_PROTOCOL_NEC, "20 00 00 00", "4D 00 00 00"},
        {"Ok",            REMOTE_PROTOCOL_NEC, "20 00 00 00", "4A 00 00 00"},
        {"Left",          REMOTE_PROTOCOL_NEC, "20 00 00 00", "49 00 00 00"},
        {"Right",         REMOTE_PROTOCOL_NEC, "20 00 00 00", "4B 00 00 00"},

       
    }
},
};