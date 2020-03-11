#include <idc.idc>

/************************************************************************
   Desc:		Label each cvar variable with its appropriate name
   Author:  kynox
   Credit:	bobbysing for RenameFunc
   Website: http://www.gamedeception.net
*************************************************************************/
/*
This Is Some Really Ugly Code Just pre warning It Grabs All wow Op code Info Vtables / CliPutWithMsgId // Op Code Offsets
Its Not Perfect And idc Works for my needs I Have my version That Labels vtables 
/CliPutWithMsgId Based Of a Text File from dumping the names i marked 
/ copyed and guessed from prev versions i haven't fully tested it yet vs patches so i'm not releasing the naming part for time being
*/
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

// Gets Op Code Vtable
static ExtractCvarDest(xRef)
{
    auto head, blahhhhhhhhhhhhh;
    head = (xRef - 0x18);
    Message("Op Vtable OffSet at 0x%X\n", head);
    //
    //Grabs Names of Labled Vtables To Make A Text File TO prase / Name Them Future
    //
    //blahhhhhhhhhhhhh = get_name(head);
    //Message( "%s,\n", blahhhhhhhhhhhhh );
}

/// get op code CliPutWithMsgId // op code offset
static ExtractCvarName(xRef)
{
    auto head, Blahhhhh, operandValue, OPOffSet;
    head = PrevHead(xRef, 0); // opcode function
    Blahhhhh = Dfirst(head);
    OPOffSet = (Blahhhhh + 0x13); // 0x18  /// 0x1D
    if (GetMnem(OPOffSet) == "mov" && GetOpnd(OPOffSet, 0) == "edx")
        //
        //Grabs Names of Labled CliPutWithMsgId To Make A Text File TO prase / Name Them Future
        //
        //blahhhhhhhhhhhhh = get_name(head);
        //Message( "%s,\n", blahhhhhhhhhhhhh );
        operandValue = GetOperandValue(OPOffSet, 1);
    if (operandValue > 100)
    {
        Message("CliPutWithMsgId at 0x%X\n", head);
        Message("OPCode OFF Set at 0x%X\n", operandValue);
    }
    else
    {
        OPOffSet = (Blahhhhh + 0x18); // 0x18 // 0x1D
        operandValue = GetOperandValue(OPOffSet, 1);
        if (operandValue > 100)
        {
            Message("CliPutWithMsgId at 0x%X\n", head);
            Message("OPCode OFF Set at 0x%X\n", operandValue);
        }
        else
        {
            OPOffSet = (Blahhhhh + 0x1D); // 0x7 // 0x12 // 0x1F
            operandValue = GetOperandValue(OPOffSet, 1);
            if (operandValue > 100)
            {
                Message("CliPutWithMsgId at 0x%X\n", head);
                Message("OPCode OFF Set at 0x%X\n", operandValue);
            }
            else
            {
                // Message("not found ");
            }
        }
    }
}

static main()
{
    auto cvarRegister, xRef;

    cvarRegister = FindBinary(0, SEARCH_DOWN, "48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 08 48 89 42 10 48 8B C2 C3 ");
    if (cvarRegister == BADADDR)
    {
        Message("LabelCvars: Failed to locate cvarRegister\n");
        return;
    }

    for (xRef = DfirstB(cvarRegister); xRef != BADADDR; xRef = DnextB(cvarRegister, xRef))
    {
        auto cvarDest, cvarName;
        cvarName = ExtractCvarName(xRef);
        cvarDest = ExtractCvarDest(xRef);

        if (cvarDest)
        {
            //RenameFunc( cvarDest, form( "%sDB", cvarName ) );
            //     Message( "%s = 0x%x\n", cvarName, cvarDest );
            //RenameFunc( cvarDest, form( "s_Cvar_%s", cvarName ) );
        }
    }
}