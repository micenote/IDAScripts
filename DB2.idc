#include <ida.idc>

static main()
{
    auto curAddr, xref;

    // DB2Load
    curAddr = FindBinary(0, SEARCH_DOWN, "40 53 48 83 EC 50 48 89 51 08 48 8D 05 ? ? ? ? 48 89 01");

    if (curAddr == BADADDR)
    {
        Message("Can't find DB2Load, aborting...\n");
        return;
    }

    // time to loop through and find all cross references to the wow DB_Common_Load function we found above!
    for (xref = RfirstB(curAddr); xref != BADADDR; xref = RnextB(curAddr, xref))
    {
        auto prevFunc, nextFunc, disasm, disasmAddr, dbAddress, dbNameAddress;

        prevFunc = PrevFunction(xref);
        nextFunc = NextFunction(xref);
        disasmAddr = xref;

        disasmAddr = PrevHead(disasmAddr, prevFunc);
        //Message("GetOperandValue at 0x%X\n", disasmAddr);
        disasm = GetDisasm(disasmAddr);
        if (strstr(disasm, "lea") > -1 && strstr(disasm, "rcx") > -1)
        {
            dbAddress = GetOperandValue(disasmAddr, 1);
            if (dbAddress == BADADDR)
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        disasmAddr = PrevHead(disasmAddr, prevFunc);
        //Message("disasmAddr at 0x%X\n", disasmAddr);
        disasm = GetDisasm(disasmAddr);
        //Message("disasm at 0x%X\n", disasm);
        if (strstr(disasm, "lea") > -1 && strstr(disasm, "rdx") > -1)
        {
            dbNameAddress = GetOperandValue(disasmAddr, 1);
            //Message("dbNameAddress at 0x%X\n", dbNameAddress);
            if (dbNameAddress == BADADDR)
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        auto dbName;
        dbName = WoWDb_GetName(dbNameAddress);

        if (strlen(dbName) == 0)
        {
            break;
        }

        RenameFunc(dbAddress, form("%sDB", dbName));
        Message("%s = 0x%x\n", dbName, dbAddress);
    }
}

// 1 = Success, 0 = Failure
static RenameFunc(dwAddress, sFunction)
{
    auto dwRet;

    dwRet = MakeNameEx(dwAddress, sFunction, SN_NOWARN);

    if (dwRet == 0)
    {
        auto sTemp, i;
        for (i = 0; i < 32; i++)
        {
            sTemp = form("%s_%i", sFunction, i);

            if ((dwRet = MakeNameEx(dwAddress, sTemp, SN_NOWARN)) != 0)
            {
                Message("Info: Renamed to %s instead of %s\n", sTemp, sFunction);
                break;
            }
        }
    }
    return dwRet;
}

static WoWDb_GetName(dbBase)
{
    auto dbName;

    dbName = GetString(Dword(dbBase), -1, ASCSTR_C);

    return substr(dbName, strstr(dbName, "\\") + 1, 30);
}