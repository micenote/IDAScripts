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
// Misses 2 Total Sets of labels because style i use to dump ToDo Fix This
//  C_WowTokenSecure
//  C_NewItems

static main()
{
    auto registerFunc, xRef;
    registerFunc = registerFunc = FindBinary(0, SEARCH_DOWN, "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B 1D ? ? ? ? 48 8B F9 8B F2 48 8B CB 49 8B D0 49 8B E8 E8 ? ? ? ? BA ? ? ? ?");

    Message("FrameScript__RegisterFunctionNamespaceWithCount at 0x%X\n", registerFunc);

    for (xRef = RfirstB(registerFunc); xRef != BADADDR; xRef = RnextB(registerFunc, xRef))
    {
        auto structBase;
        auto numFuncs, i, blahh, operandValue;

        blahh = (xRef - 0x7);
        operandValue = GetOperandValue(blahh, 0);
        if (operandValue == 0x1)
        {
            structBase = GetOperandValue(xRef - 0x7, 1);
            numFuncs = GetOperandValue(xRef - 0xC, 1);
        }
        else
        {
            structBase = GetOperandValue(xRef - 0xB, 1);
            numFuncs = GetOperandValue(xRef - 0x10, 1);
        }

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