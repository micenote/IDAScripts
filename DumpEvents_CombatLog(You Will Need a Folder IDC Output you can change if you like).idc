#include <ida.idc>

static ExtractPath(sPath)
{
    auto dwIndex;
    for (dwIndex = strlen(sPath); strstr(substr(sPath, dwIndex, -1), "\\"); dwIndex--)
        ;
    return substr(sPath, 0, dwIndex + 1);
}

static GetTargetPath()
{
    return ExtractPath(GetIdbPath()) + "IDC\\Output\\";
}

static main()
{
    auto sPath, hFile, dwTable, sString, iIndex, iMax, iStop;

    sPath = GetTargetPath() + "Events_CombatLog_Enum.cpp";
    hFile = fopen(sPath, "w");
    if (hFile != -1)
    {
        fprintf(hFile, "#include \"CWoWX.h\"\n");
        fprintf(hFile, "const char * pszCombatLogEvents[][2] =\n{\n");
        /// .data:000000000217F790 off_217F790     dq offset aEnvironmentalD In Ida for offset or ENVIRONMENTAL_DAMAGE strings
        dwTable = 0x217F790;
        Message("dwTable %x\n", dwTable);

        if (dwTable != BADADDR)
        {
            dwTable = (dwTable);

            Message("Found event table at %x\n", dwTable);

            iIndex = 0;
            while (1)
            {
                sString = GetString(Dword(dwTable + iIndex * 8), -1, ASCSTR_C);

                if (strlen(sString) <= 0)
                    break;
                ///
                ///   TODO Add A Better End Stop
                if (strstr(sString, "CombatLogResetFilter") != -1)
                    break;

                iStop = strstr(sString, "_");

                fprintf(hFile, "\t{ \"%s\", \"%s\" }%s\n", substr(sString, 0, iStop), substr(sString, iStop + 1, -1), (iIndex != iMax - 1) ? "," : "");
                iIndex = iIndex + 1;
            }
        }
        fprintf(hFile, "};\n");
        fclose(hFile);

        Message("Successfully dumped %s.\n", sPath);
    }
    else
        Message("Failed to open file %s.\n", sPath);
    sPath = GetTargetPath() + "Events_CombatLog_Enum.h";
    hFile = fopen(sPath, "w");
    if (hFile != -1)
    {
        fprintf(hFile, "#ifndef __EVENTS_COMBATLOG_ENUM_H__\n#define __EVENTS_COMBATLOG_ENUM_H__\n");
        fprintf(hFile, "extern const char * pszCombatLogEvents[][2];\n\n");
        fprintf(hFile, "#endif //__EVENTS_COMBATLOG_ENUM_H__");
        fclose(hFile);
        Message("Successfully dumped %s.\n", sPath);
    }
    else
        Message("Failed to open file %s.\n", sPath);
    return 0;
}