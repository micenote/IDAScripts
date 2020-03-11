#include <idc.idc>

/************************************************************************
   Desc:		Label each lua function based on its appropriate name
   Author:  kynox
   Credit:	bobbysing for RenameFunc
   Website: http://www.gamedeception.net
*************************************************************************/

// 1 = Success, 0 = Failure
static RenameFunc(dwAddress, sFunction)
{
    auto dwRet;
    auto part = substr(GetFunctionName(dwAddress), 0, 7);

    if (part != "Script_")
    {
        auto oldName = GetFunctionName(dwAddress);

        dwRet = MakeNameEx(dwAddress, sFunction, SN_NOWARN);

        if (dwRet == 0)
        {
            auto sTemp, i;

            for (i = 1; i < 32; i++)
            {
                sTemp = form("%s_%i", sFunction, i);

                if ((dwRet = MakeNameEx(dwAddress, sTemp, SN_NOWARN)) != 0)
                {
                    // Message( "Info: Renamed to %s instead of %s\n", sTemp, sFunction );
                    break;
                }
            }

            if (i == 31)
                Message("-- Error --: Failed to rename %s -> %s\n", oldName, sFunction);
        }
        else
            Message("%s 0x%X\n", sFunction, dwAddress);
    }

    return dwRet;
}

static Luafunc_GetName(structAddr)
{
    return GetString(Qword(structAddr), -1, ASCSTR_C);
}

static Luafunc_GetFunc(structAddr)
{
    return Qword(structAddr + 8);
}

static HandleLuaFunc(structBase)
{
    auto funcName, funcAddr;

    funcName = Luafunc_GetName(structBase);
    funcAddr = Luafunc_GetFunc(structBase);
    RenameFunc(funcAddr, form("Script_%s", funcName));
}

// ToDo Add a check For These 2 Types
//
// UnitExists
// SetTaxiMap

static main()
{
    auto registerFunc, xRef;
    registerFunc = registerFunc = FindBinary(0, SEARCH_DOWN, "48 89 5C 24 ? 57 48 83 EC 20 48 8B 3D ? ? ? ? 48 8B D9 48 8B CF 45 33 C0 E8 ? ? ? ? 48 8B D3 48 8B CF E8 ? ? ? ? BA ? ? ? ? 48 8B CF");

    Message("FrameScript__RegisterFunction at 0x%X\n", registerFunc);

    for (xRef = RfirstB(registerFunc); xRef != BADADDR; xRef = RnextB(registerFunc, xRef))
    {
        auto structBase;
        auto numFuncs, i, blahh, operandValue;

        blahh = (xRef - 0xE);
        operandValue = GetOperandValue(blahh, 0);
        //Message("blahh at 0x%X\n", blahh);
        //Message("operandValue at 0x%X\n", operandValue);
        if (operandValue == 0x3)
        {
            structBase = GetOperandValue(xRef - 0xE, 1);
            numFuncs = GetOperandValue(xRef + 0xB, 1);
        }
        else
        {
            structBase = GetOperandValue(xRef - 0x14, 1);
            numFuncs = GetOperandValue(xRef + 0xB, 1);
        }
        //else if
        // {
        //structBase = GetOperandValue( xRef - 0x1D, 1 ); // works for last few start struct
        //numFuncs = GetOperandValue( xRef + 0x14, 1 );  // hail mary for size of struct since mia
        //}
        if (numFuncs < 1000 && numFuncs > 0)
        {
            //Message( "Found 0x%x, count: 0x%x\n", structBase, numFuncs);

            for (i = 0; i < numFuncs; i++)
            {
                HandleLuaFunc(structBase);
                structBase = structBase + 0x10;
            }
        }
    }
}