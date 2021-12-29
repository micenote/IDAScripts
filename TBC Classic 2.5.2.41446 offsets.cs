using System.Reflection;


namespace LazyLib.Wow
{
    public class PublicPointers
    {
        /// <summary>
        /// Globals
        /// </summary>
        public enum Globals
        {
            PlayerName = 0x2DAACF8,
        }

        /// <summary>
        /// InGame
        /// </summary>
        public enum InGame
        {
            InGame = 0x30C2F24,//Reversed From Script_IsPlayerInWorld
            LoadingScreen = 0x2D94030,//Reversed From Script_CanLogIn to CGlueMgr__CanLogIn
            RealID = 0x31A56A8, /// Real ID / Name / # 
        }

     }

    internal class Pointers
    {
        /// <summary>
        /// ActionBar
        /// </summary>
        internal enum ActionBar
        {
            ActionBarFirstSlot = 0x3105A70,//Reversed From Script_GetActionTexture To CGActionBar__GetTexture
            ActionBarBonus =  ActionBarFirstSlot + 0x240,
            CurrentActionBar = 0x31060C4,
        }

        /// <summary>
        /// Battleground
        /// </summary>
        internal enum Battleground
        {
            BattlegroundStartTickcount = 0x30FE454,// GetBattlefieldInstanceRunTime
            Timestamp = 0x2E1A17C,////FrameTime__GetCurTimeMs
            IsBattlegroundFinished = 0x30FE6FC,//GetBattlefieldWinner
            BattlegroundWinner = 0x30FE700,// string GetBattlefieldWinner
            BattlegroundInfo = 0x2CB8840,
            UISelectedBattlegroundId = 0x3141CCB,
        }

        /// <summary>
        /// Corpse
        /// </summary>
        internal enum Corpse
        {
            X = 0x2CAEAB0,
            Y =  X + 0x4,
            Z =  X + 0x8,
        }

        /// <summary>
        /// Party
        /// </summary>
        internal enum Party
        {
            PartyOffset = 0x30F7EF0,// every pattern off by 2 idn why - 2 
            IsInGroupHome = 0x30F7EF0,// every pattern off by 2 idn why - 2 
            IsInGroupInstance = 0x30F7EF0,// every pattern off by 2 idn why - 2
            NumOfPlayers =  0x178,//Script_GetNumGroupMembers
            NumOfPlayersPattern = 0x178, // working 
            NumOfPlayers_SuBGroupPattern = 0x17C, // working 
            NumOfPlayers_SuBGroup =  0x17C,//// NumOFPlayers+4
            PlayerGuid =  0x10,
        }

        /// <summary>
        /// AutoLoot
        /// </summary>
        internal enum AutoLoot
        {
            Pointer = 0x30C2B88,//Reversed From CGGameUI__IsAutoLooting
            Offset =  0x5C,
        }

        /// <summary>
        /// ClickToMove
        /// </summary>
        internal enum ClickToMove
        {
            Pointer = 0x30C2B40,//Search String in ida Automatically stand when needed to CGGameUI__RegisterGameCVars then thats the offset
            Offset =  0x5C,
        }

        /// <summary>
        /// Reversed from CGUnit_C__GetCreatureRank 
        /// </summary>
        internal enum CgUnitCGetCreatureRank
        {
            Offset1 =  0x1800, //0x17B8 old,
            Offset2 =  0x34,
        }

        /// <summary>
        /// reversed from CGUnit_C__GetCreatureType 
        /// </summary>
        internal enum CgUnitCGetCreatureType
        {
            Offset1 =  0x1800, //0x17B8 old,
            Offset2 =  0x30,
        }

        /// <summary>
        /// reversed from CGWorldFrame__GetActiveCamera
        /// </summary>
        internal enum CgWorldFrameGetActiveCamera
        {
            CameraPointer = 0x31A4CA8,
            CameraOffset =  0x38E0,// good
            CameraOffsetPattern = 0x38E0, // working 
            CameraX =  0x10,
            CameraY =  0x14,
            CameraZ =  0x18,
            CameraMatrix =  0x1C,
        }

        /// <summary>
        /// Search for CGUnit_C::GetSkinnableType_Checked 
        /// </summary>
        internal enum Skinning
        {
            SkinnableFlags1 =  0x1800, // old 0x17B8,
            SkinnableFlags1Pattern = 0x1800, // working 
            SkinnableFlags2Pattern = 0xE8, // working 
            SkinnableFlags2 =  0xE8, // old todo test 0x0CC,
        }

        /// <summary>
        /// AuctionHouse
        /// </summary>
        internal enum AuctionHouse
        {
            AuctionListCount = 0x3140D78,
            AuctionList = AuctionListCount + 0x08 ,
            AuctionOwnerCount = 0x3140D98,
            AuctionOwnerList = AuctionOwnerCount + 0x08 ,
            AuctionBidderCount = 0x3140DB8,
            AuctionBidderList = AuctionBidderCount + 0x08 ,
        }

        /// <summary>
        /// reversed from CGActionBar__IsCurrentAction
        /// </summary>
        internal enum AutoAttack
        {
            IsAutoRepeatingSpell = 0x2E31C00,
            IsInMelee =  0xAF6C,
            IsInMelee1 =  0x18A8,
            AutoAttackFlag =  0xEE8,
            AutoAttackMask =  0xEEC,
            ///Address seems to show the GUID of the Auto Attack target
            AutoAttackGUID =  0xAF6C,
            ///Shows 0x06 when not wanding, 0x0C or 0x0E when wanding
            ///Wanding = 0xEF8
        }

        /// <summary>
        /// CastingInfo 
        /// </summary>
        internal enum CastingInfo
        {
            IsCasting2 =  0x19B0,// Script_UnitCastingInfo
            IsCasting =  0x19B0,// Script_UnitCastingInfo
            IsCastNotInterruptible =  0x1904,// Script_UnitCastingInfo
            ChanneledCasting2 =  0x1A08,// Script_UnitCastingInfo
            ChanneledCasting =  0x19C0,// Script_UnitChannelInfo//prb wrong 0x682 maybe
        }

        /// <summary>
        /// reversed from CGWorldFrame__GetActiveCamera
        /// </summary>
        internal enum Chat : uint
        {
            ChatStart = 0x30C3260,
            chatBufferPos = 0x30F2DA0,
            OffsetToNextMsg =  0xCB8,
            OffsetToNextMsgPattern = 0xCB8, // working 
            MsgSenderGuid =  0x00,
            MsgSenderName =  0x34,
            MsgFullMessage =  0xE6,
            MsgChatType =  0xCA0,
            MsgChannelNum =  0xCA4,
            MsgTimeStamp =  0xCB0,
            ChatQueueDepth =  0x3C,
        }

        /// <summary>
        /// BlueChat
        /// </summary>
        internal enum Messages
        {
            EventMessage = 0x30C1E20,//Reversed From CGGameUI__DisplayError
        }

        /// <summary>
        /// Container
        /// </summary>
        internal enum Container
        {
            EquippedBagGUID = 0x30FE320,// GetBagAtIndex 
        }

        /// <summary>
        /// Globals
        /// </summary>
        internal enum Globals
        {
            RedMessage = 0x30C1E20,//Reversed From CGGameUI__DisplayError
            MouseOverGUID = 0x30C2F48,// Reversed From Script_GetGUIDFromToken - MouseOver
            LootWindow = 0x30FF6A8,//Reversed From CGPlayer_C_OnLootClose
            ChatboxIsOpen = 0x2E41C44,//Reversed From CGPlayer_C_OnLootClose
            CursorType = 0x31953A0,// Reversed From CursorInitialize - Script_SetCursor To CursorSetMode
            CursorType2 = CursorType + 0x04 ,
            SelectedSpellId = 0x31133E8,// aka trainer 
            CGGameUI__m_cursorItem = 0x30C1CF0,
            CGGameUI__m_cursorSpell = 0x30C1D48,
            IsMouseButtonPressed = 0x2E1A1AC,
            Indoors = 0x2E1F825,
            IsBobbing = 0x14C ,
            ArchFacing = 0x198 ,
            ArchFacingOffset2 = 0x30 ,
        }

        /// <summary>
        /// KeyBinding // Reversed From Script_GetNumBindings
        /// </summary>
        internal enum KeyBinding
        {
            NumKeyBindings = 0x2DA94D0,
            First =  0x28,// 0x18 hardcoded 
            Next =  0x18,
            Key =  0x30,
            Command =  0x58,// or 0x50
        }

        /// <summary>
        /// Macros Todo Add Pattern for dumper not updated havent cared
        /// </summary>
        internal enum MacroManager
        {
            Next =  0x8,// currently not using anything besides 0x8 24 + 10 or 20 + 10
            Name =  0x38,
            Icon =  0x78,
            Body =  0x179,
            MacroFirst =  0x2CDC918,//40422 MacroBase  4 Below GetRunningMacroButton STring
            MacroNext  =  0x2CDC908,//40422 MacroBase  4 Below GetRunningMacroButton STring
            nbGeneralMacros = 0x311C068,// 40422 Found With GetNumMacros String
            nbSpecificMacros =  0x311C070,//40422 Found With GetNumMacros String
        }

        /// <summary>
        /// Quest
        /// </summary>
        internal enum Quest
        {
            m_quests = 0x3108490,
            m_numQuests = 0x31082D0,//Found With GetNumQuestLogEntries String
            m_currentQuest = 0x312FED4,//Found In GetQuestID String
            m_questTitle = 0x313B020,// Found With GetTitleText String pattern might not work
            m_gossipQuests = 0x30F8ED8,
            QuestsCompleted = 0x2E09FB8,
            GetNumQuestChoices = 0x313F4D0,//Found WithGetNumQuestChoices String // RewardChoiceItemIdCount
            GetQuestReward = 0x313F4D8,
            CGQuestInfo_Available__Quest = 0x313EB20,
            CGQuestInfo_Available__Num = 0x312FEEC,
            CGQuestInfo_Active__Num = 0x312FEF0,//Found With GetNumActiveQuests String
            CGQuestInfo_Active__Quest = 0x3135374,
        }

        /// <summary>
        /// ObjectManager
        /// </summary>
        internal enum ObjectManager
        {
            CurMgrPointer = 0x2ECF068,
            LocalPlayerGUID = 0x2DAACE0,
            TargetGUID = 0x2E20E20, // todo check this one
            PetGUID = 0x30FF584, // todo check this one
            StorageField = 0x10 ,
            ObjectType = 0x20 ,
            NextObject = 0x70 ,
            FirstObject = 0x18 ,
            LocalGUID = 0x58 ,
        }

        /// <summary>
        /// Script_UnitAffectingCombat 
        ///v4 = v2 && (*(_DWORD *)(*(_DWORD *)(v2 + 284) + 316) >> 19) & 1; 
        /// </summary>
        internal enum InCombat
        {
            Mask =  19,
            Offset2 =  0x158,
            Offset1 =  0x188,
            Offset2Pattern = 0x188,// working
            Offset1Pattern = 0x158,// working
        }

        /// <summary>
        /// Runes 
        /// </summary>
        internal enum Runes
        {
            RuneTypes =  0x0,
            RunesOffset =  0x0,
            //Offset is usually RuneTypes + 0x64
        }

        /// <summary>
        /// CGUnit_C__GetShapeshiftFormId 
        /// </summary>
        internal enum ShapeshiftForm
        {
            BaseAddressOffset1Pattern = 0x188,// working
            BaseAddressOffset2Pattern = 0x27B,// working
            BaseAddressOffset1 =  0x188,// good
            BaseAddressOffset2 =  0x27B,// good
        }

        /// <summary>
        /// SpellCooldown
        /// </summary>
        internal enum SpellCooldown : uint
        {
            CooldPown = 0x2E31A40,
        }

        /// <summary>
        /// Search for PowerTypePointer  
        /// </summary>
        internal enum PowerIndex
        {
            PowerIndexArrays = 0x2E8C7B0,
            Multiplicator =  13,// good
        }

        /// <summary>
        /// Swimming v5 = v3 && (*(*(v3 + 0x198) + 0x58i64) >> 20) & 1; 
        /// </summary>
        internal enum Swimming
        {
            Pointer =  0x198,
            Offset =  0x58,
            Mask =  0x100000,
        }

        /// <summary>
        /// IsFlying 
        /// </summary>
        internal enum IsFlying
        {
            Pointer =  0x198,
            Offset =  0x58,
            Mask =  0x1000000,
        }

        /// <summary>
        /// IsFalling v5 = v3 && (*(*(v3 + 0x198) + 0x58i64) >> 11) & 1 && !((*(*(v3 + 0x198) + 0x58i64) >> 10) & 1);
        /// </summary>
        internal enum IsFalling
        {
            Pointer =  0x198,
            Offset =  0x58,
            Mask =  0x1000000,
        }

        /// <summary>
        /// reversed from CGUnit_C__GetAura 
        /// </summary>
        internal enum UnitAuras : uint
        {
            AuraCount1Pattern = 0x1B20, // working 
            AuraCount2Pattern = 0x1B28, // working 
            AuraCount1 =  0x1B20,// fixed 40045
            AuraCount2 =  0x1B28,// fixed 40045
            AuraTable1 =  0x1B20,// fixed 40045
            AuraTable2 =  0x1B28,// fixed 40045
            AuraSize =  0xB0,
            AuraSpellId =  0x88,
            AuraStack =  0x39,
            TimeLeft =  0x40,
            OwnerGUID =  0x20,
            AuraTableOffset =  0x00,
            AuraFlags =  0x90,
            AuraLevel =  0x92,
        }

        /// <summary>
        /// UnitName 
        /// </summary>
        internal enum UnitName : uint
        {
            ObjectName1Pattern = 0x478,// working
            ObjectName2Pattern = 0xE0,// working
            ObjectName1 =  0x478,// good
            ObjectName2 =  0xE0,// good
            PlayerNameGUIDOffset =  0x20,// dont use atm
            PlayerNameStringOffset =  0x31,// dont use atm
            PlayerNameCacheNext =  0x0,// dont use atm
            PlayerNameCachePointer = 0x2A8A8A0,
            UnitName1 =  0x1800,  //old 0x17B8,
            UnitName2 =  0xF8, // good
            UnitName1Pattern = 0x1800,// working
            UnitName2Pattern = 0xF8,// working
        }

        /// <summary>
        /// UnitSpeed 
        /// </summary>
        internal enum UnitSpeed
        {
            Pointer1 =  0x198,
            Pointer2 =  0xA0,
        }

        /// <summary>
        /// WowObject 
        /// </summary>
        internal enum WowObject
        {
            X =  0x15F8,
            Y =  X + 0x4,
            Z =  X + 0x8,
            RotationOffset =  X + 0x10,
            Pitch =  X + 0x14,
            GameObjectX =  0x1B0,
            GameObjectY =  GameObjectX + 0x4,
            GameObjectZ =  GameObjectX + 0x8,
            GameObjectRotation =  GameObjectX + 0x10,
            TransportGUID =  0x15F0,
        }

        /// <summary>
        /// Zone 
        /// </summary>
        internal enum Zone : uint
        {
            ZoneText = 0x30C1CB8,//Script_GetZoneText
            ZoneID = 0x30C1E1C,//Reversed From Script_GetZonePVPInfo - Script_IsPlayerInMicroDungeon
            SubZoneText = 0x30C1CC0,//Reversed From Script_GetSubZoneText
            ContinentId = 0x2AA3B4C,
            GetContinentIDOffset =  0x00,
        }

        /// <summary>
        /// UiFrame 
        /// </summary>
        internal enum UiFrame
        {
            ScrWidth = 0x2A88E64,// Script_GetScreenWidth
            ScrHeight =  ScrWidth + 0x4,
            FrameBase = 0x2E1AE70,// Script_GetMouseMotionFocus
            CurrentFramePtr = 0x2E1AE70,// Script_GetMouseClickFocus
            CurrentFrameOffset =  0x290,
            FirstFrame =  0xF18,
            NextFrame =  0xF08,
            RegionsFirst =  0x2A0,
            RegionsNext =  0x290,
            Visible =  0x1CC,
            Visible1 =  1,
            Visible2 =  1,
            LabelText =  0x280,
            Name =  0x28,
            FrameBottom =  0x190,
            FrameLeft =  0x194,
            FrameTop =  0x198,
            FrameRight =  0x19C,
            EffectiveScale =  0x1C0,
            ParentFrame =  0x58,// 0xD0
            IconNumber =  0x12,
            ButtonEnabledPointer =  0x310,
            ButtonEnabledMask =  0xF,
            ButtonChecked =  0x360,
            EditBoxText =  0x330,
        }

    }

}
