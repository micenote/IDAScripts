#include <idc.idc>
static main()
{
    auto func, end, count, inst, operandValue, xRef, funcName, GetNameEffset, getname;

    // Put Mouse on DELETE_ITEM_CONFIRM function will dump all the events to window todo dump to file

    func = GetFunctionAttr(ScreenEA(), FUNCATTR_START);
    if (func != -1)
    {
        end = GetFunctionAttr(func, FUNCATTR_END);
        count = 0;
        inst = func;
        while (inst < end)
        {
            count++;
            inst = FindCode(inst, SEARCH_DOWN | SEARCH_NEXT);

            if (GetMnem(inst) == "lea")
            {
                //Message( "%s 0x%X\n" , getname,inst );
                operandValue = GetOperandValue(inst, 1);
                getname = GetString(operandValue, -1, ASCSTR_C);
                Message("%s\n", getname);
                //Message("FrameScript__RegisterFunction at 0x%X\n", inst);
            }
        }
        Warning("%s contains %d instructions \n", Name(func), count);
    }
    else
    {
        Warning("No function found at location %x ", ScreenEA());
    }
}