#include "Include.h"

HMODULE hClient = nullptr;
HMODULE hEngine = nullptr;

IGameConsole* m_pGameConsole = nullptr;
IMatSystemSurface* m_pMatSurface = nullptr;
vgui::ISurface* m_pSurface = nullptr;
IVEngineClient* m_pEngine = nullptr;
vgui::IPanel* m_pPanel = nullptr;
ICvar* m_pCvar = nullptr;
IBaseClientDLL* m_pClient = nullptr;
IClientEntityList* m_pEntList = nullptr;
CEntity* m_pEntity = nullptr;
IVModelInfoClient* m_pModelInfo = nullptr;
CGlobalVarsBase* m_pGlobals = nullptr;
CInput* m_pInput = nullptr;
IEngineTrace* m_pEngineTrace = nullptr;
_Interfaces pinterface;
CGameMovement* m_pGameMovement = nullptr;
CPrediction* m_pPrediction = nullptr;
IMaterialSystem* m_pMaterialSystem = nullptr;
IVDebugOverlay* m_pDebugOverlay = nullptr;
IVModelRender* m_pModelRender = nullptr;
IVRenderView* m_pRender = nullptr;
IGameEventManager2* m_pGameEventManager = nullptr;
IPhysicsSurfaceProps* m_pPhysicsAPI = nullptr;

bool FindInterface(CreateInterfaceFn *factory, const string interfaceName, void** interfaceInstance)
{
	int version = -1;//Start from 0
	for (; version <= 255; version++/*Start brute*/)
	{
		ostringstream temp;
		temp << /*Go to interface name*/interfaceName << /*Fill non-set*/setfill('0') << setw(3)/*Width*/ << version /*Add brute-forced integer*/;

		*interfaceInstance = (*factory)(/*Set to our brute-forced interface name*/temp.str().c_str()/*To string*/, nullptr);

		if (*interfaceInstance)
		{
			return true;
		}
	}

	return false;
}

void Interfaces(void)
{
	CreateInterfaceFn gClient = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(
			/*client.dll*/XorStr<0x7C, 11, 0x028CF936>("\x1F\x11\x17\x1A\xEE\xF5\xAC\xE7\xE8\xE9" + 0x028CF936).s),
		/*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));
	CreateInterfaceFn gEngine = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(
			/*engine.dll*/XorStr<0x45, 11, 0xA63A89FB>("\x20\x28\x20\x21\x27\x2F\x65\x28\x21\x22" + 0xA63A89FB).s),
		/*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));
	CreateInterfaceFn gGameUI = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(
			/*gameui.dll*/XorStr<0x72, 11, 0xF7577311>("\x15\x12\x19\x10\x03\x1E\x56\x1D\x16\x17" + 0xF7577311).s),
		/*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));
	CreateInterfaceFn gVGUI2 = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(/*vgui2.dll*/XorStr<0x4B, 10, 0x2414524C>("\x3D\x2B\x38\x27\x7D\x7E\x35\x3E\x3F" + 0x2414524C).s),
		/*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));
	CreateInterfaceFn gSurface = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(/*vguimatsurface.dll*/XorStr<0x5B, 19, 0x04E29B30>(
			"\x2D\x3B\x28\x37\x32\x01\x15\x11\x16\x16\x03\x07\x04\x0D\x47\x0E\x07\x00" + 0x04E29B30).s), /*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));
	CreateInterfaceFn gVSTDLIB = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(
			/*vstdlib.dll*/XorStr<0x66, 12, 0x25E22677>("\x10\x14\x1C\x0D\x06\x02\x0E\x43\x0A\x03\x1C" + 0x25E22677).s),
		/*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));
	CreateInterfaceFn gMaterialSystem = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(/*materialsystem.dll*/XorStr<0x19, 19, 0x200DC3EC>(
			"\x74\x7B\x6F\x79\x6F\x77\x7E\x4C\x52\x5B\x50\x50\x40\x4B\x09\x4C\x45\x46" + 0x200DC3EC).s), /*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));
	CreateInterfaceFn gPhysics = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(
		GetModuleHandleA(/*vphysics.dll*/XorStr<0x21, 13, 0xC7A98BBD>("\x57\x52\x4B\x5D\x56\x4F\x44\x5B\x07\x4E\x47\x40" + 0xC7A98BBD).s), /*CreateInterface*/
		XorStr<0xBB, 16, 0xBA925500>("\xF8\xCE\xD8\xDF\xCB\xA5\x88\xAC\xB7\xA1\xB7\xA0\xA6\xAB\xAC" + 0xBA925500).s));

	FindInterface(&gGameUI, /*GameConsole*/XorStr<0xB6, 12, 0x03C2433A>("\xF1\xD6\xD5\xDC\xF9\xD4\xD2\xCE\xD1\xD3\xA5" + 0x03C2433A).s, reinterpret_cast<void**>(&m_pGameConsole));

	if (m_pGameConsole == nullptr)
		return;

	FindInterface(&gEngine, /*VEngineClient*/XorStr<0xC4, 14, 0xD65DC682>("\x92\x80\xA8\xA0\xA1\xA7\xAF\x88\xA0\xA4\xAB\xA1\xA4" + 0xD65DC682).s, reinterpret_cast<void**>(&m_pEngine));

	if (m_pEngine == nullptr)
		return;

	FindInterface(&gVGUI2, /*VGUI_Panel*/XorStr<0xB3, 11, 0x77627997>("\xE5\xF3\xE0\xFF\xE8\xE8\xD8\xD4\xDE\xD0" + 0x77627997).s, reinterpret_cast<void**>(&m_pPanel));

	if (m_pPanel == nullptr)
		return;

	FindInterface(&gSurface, /*VGUI_Surface*/XorStr<0x83, 13, 0x0690F34A>("\xD5\xC3\xD0\xCF\xD8\xDB\xFC\xF8\xED\xED\xEE\xEB" + 0x0690F34A).s, reinterpret_cast<void**>(&m_pSurface));

	if (m_pSurface == nullptr)
		return;

	FindInterface(&gSurface, /*VGUI_Surface*/XorStr<0x18, 13, 0x8996B6AB>("\x4E\x5E\x4F\x52\x43\x4E\x6B\x6D\x46\x40\x41\x46" + 0x8996B6AB).s, reinterpret_cast<void**>(&m_pMatSurface));

	if (m_pMatSurface == nullptr)
		return;

	FindInterface(&gEngine, /*VEngineCvar*/XorStr<0x3D, 12, 0xEA28710A>("\x6B\x7B\x51\x27\x28\x2C\x26\x07\x33\x27\x35" + 0xEA28710A).s, reinterpret_cast<void**>(&m_pCvar));

	if (m_pCvar == nullptr)
		return;

	FindInterface(&gClient, /*VClient*/XorStr<0x7A, 8, 0x827196D2>("\x2C\x38\x10\x14\x1B\x11\xF4" + 0x827196D2).s, reinterpret_cast<void**>(&m_pClient));

	if (m_pClient == nullptr)
		return;

	FindInterface(&gClient, /*VClientEntityList*/XorStr<0x6C, 18, 0xA3FDD097>("\x3A\x2E\x02\x06\x15\x1F\x06\x36\x1A\x01\x1F\x03\x01\x35\x13\x08\x08" + 0xA3FDD097).s, reinterpret_cast<void**>(&m_pEntList));

	if (m_pEntList == nullptr)
		return;

	FindInterface(&gEngine, /*VModelInfoClient*/XorStr<0x2C, 17, 0xBCDC1080>("\x7A\x60\x41\x4B\x55\x5D\x7B\x5D\x52\x5A\x75\x5B\x51\x5C\x54\x4F" + 0xBCDC1080).s, reinterpret_cast<void**>(&m_pModelInfo));

	if (m_pModelInfo == nullptr)
		return;

	m_pGlobals = *reinterpret_cast<CGlobalVarsBase**>(reinterpret_cast<DWORD>(hClient) + 0x392C8C);

	if (m_pGlobals == nullptr)
		return;

	m_pInput = *reinterpret_cast<CInput**>(reinterpret_cast<DWORD>(hClient) + 0x39D408);

	if (m_pInput == nullptr)
		return;

	FindInterface(&gEngine, /*EngineTraceClient*/XorStr<0x6D, 18, 0x6A03146E>("\x28\x00\x08\x19\x1F\x17\x27\x06\x14\x15\x12\x3B\x15\x13\x1E\x12\x09" + 0x6A03146E).s, reinterpret_cast<void**>(&m_pEngineTrace));

	if (m_pEngineTrace == nullptr)
		return;

	FindInterface(&gClient, /*GameMovement*/XorStr<0xD7, 13, 0x586F6A7E>("\x90\xB9\xB4\xBF\x96\xB3\xAB\xBB\xB2\x85\x8F\x96" + 0x586F6A7E).s, reinterpret_cast<void**>(&m_pGameMovement));

	if (m_pGameMovement == nullptr)
		return;

	FindInterface(&gClient, /*VClientPrediction*/XorStr<0x18, 18, 0xA8907853>("\x4E\x5A\x76\x72\x79\x73\x6A\x4F\x52\x44\x46\x4A\x47\x51\x4F\x48\x46" + 0xA8907853).s, reinterpret_cast<void**>(&m_pPrediction));

	if (m_pPrediction == nullptr)
		return;

	FindInterface(&gMaterialSystem, /*VMaterialSystem*/XorStr<0x37, 16, 0x91CBCEFB>("\x61\x75\x58\x4E\x5E\x4E\x54\x5F\x53\x13\x38\x31\x37\x21\x28" + 0x91CBCEFB).s, reinterpret_cast<void**>(&m_pMaterialSystem));

	if (m_pMaterialSystem == nullptr)
		return;

	FindInterface(&gEngine, /*VDebugOverlay*/XorStr<0x18, 14, 0x62D1BD53>("\x4E\x5D\x7F\x79\x69\x7A\x51\x69\x45\x53\x4E\x42\x5D" + 0x62D1BD53).s, reinterpret_cast<void**>(&m_pDebugOverlay));

	if (m_pDebugOverlay == nullptr)
		return;

	FindInterface(&gEngine, /*VEngineModel*/XorStr<0xDD, 13, 0xCF317604>("\x8B\x9B\xB1\x87\x88\x8C\x86\xA9\x8A\x82\x82\x84" + 0xCF317604).s, reinterpret_cast<void**>(&m_pModelRender));

	if (m_pModelRender == nullptr)
		return;

	FindInterface(&gEngine, /*VEngineRenderView*/XorStr<0x14, 18, 0x1BB888C1>("\x42\x50\x78\x70\x71\x77\x7F\x49\x79\x73\x7A\x7A\x52\x77\x4B\x46\x53" + 0x1BB888C1).s, reinterpret_cast<void**>(&m_pRender));

	if (m_pRender == nullptr)
		return;

	FindInterface(&gEngine, /*GAMEEVENTSMANAGER*/XorStr<0x4C, 18, 0x90B595E1>("\x0B\x0C\x03\x0A\x15\x07\x17\x1D\x00\x06\x1B\x16\x16\x18\x1D\x1E\x0E" + 0x90B595E1).s, reinterpret_cast<void**>(&m_pGameEventManager));

	if (m_pGameEventManager == nullptr)
		return;

	FindInterface(&gPhysics, /*VPhysicsSurfaceProps*/XorStr<0xC8, 21, 0x77AC2137>("\x9E\x99\xA2\xB2\xBF\xA4\xAD\xBC\x83\xA4\xA0\xB5\xB5\xB6\xB3\x87\xAA\xB6\xAA\xA8" + 0x77AC2137).s, reinterpret_cast<void**>(&m_pPhysicsAPI));

	if (m_pPhysicsAPI == nullptr)
		return;
}

void StartHooking(void)
{
	Beep(1000, 50);
	Beep(1000, 50);
	Beep(1000, 50);

	while (hClient == nullptr)
	{
		hClient = GetModuleHandleA(/*client.dll*/XorStr<0x7C, 11, 0x028CF936>("\x1F\x11\x17\x1A\xEE\xF5\xAC\xE7\xE8\xE9" + 0x028CF936).s);
	}
	//------------------------------------------------------------------------------------------------------------------------------------
	while (hEngine == nullptr)
	{
		hEngine = GetModuleHandleA(/*engine.dll*/XorStr<0x45, 11, 0xA63A89FB>("\x20\x28\x20\x21\x27\x2F\x65\x28\x21\x22" + 0xA63A89FB).s);
	}

	Interfaces();

	m_pGameConsole->Activate();
	m_pGameConsole->Clear();
	DWORD dwPanel = reinterpret_cast<DWORD>(m_pPanel);
	pPanelHook = new C_VMT(&dwPanel);

	pPanelHook->Hook(reinterpret_cast<DWORD>(Hooked_PaintTraverse), PaintTraverse);

	pinterface.m_pNetVars->Init();

	ExitThread(EXIT_SUCCESS);
}