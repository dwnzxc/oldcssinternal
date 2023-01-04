#ifndef __INCLUDE_H__
#define __INCLUDE_H__
#define CLIENT_DLL

#define WIN32_LEAN_AND_MEAN

#pragma optimize("gsy",on)

#pragma warning( disable : 4244 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4541 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4183 )
#pragma warning( disable : 4518 )
#pragma warning( disable : 4228 )
#pragma warning( disable : 4273 )
#pragma warning( disable : 4456 )
#pragma warning( disable : 4996 )

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <d3d9.h>
#include <memory>
#include <fcntl.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <io.h>
#include <Shlwapi.h>


using namespace std;

template <typename Fn>
__forceinline Fn CallVirtualFunction(PVOID pClassBase, int nFunctionIndex)
{
	return Fn(reinterpret_cast<PDWORD>((*static_cast<PDWORD*>(pClassBase))[nFunctionIndex]));
}

#define DO_ONCE( arg )				\
	static bool UnIqUe_ONC3 = false;\
	if( UnIqUe_ONC3 == false )\
{									\
	UnIqUe_ONC3 = true;				\
	arg								\
}

#define STATUS(x) bool x = false
#define STATUS_TRUE(x) bool x = true

#define _DT_BaseCombatCharacter /*DT_BaseCombatCharacter*/XorStr<0x88,23,0x5D40A4B0>("\xCC\xDD\xD5\xC9\xED\xFE\xEB\xCC\xFF\xFC\xF0\xF2\xE0\xD6\xFE\xF6\xEA\xF8\xF9\xEF\xF9\xEF"+0x5D40A4B0).s
#define _DT_BaseCombatWeapon /*DT_BaseCombatWeapon*/XorStr<0x71,20,0x7047197C>("\x35\x26\x2C\x36\x14\x05\x12\x3B\x16\x17\x19\x1D\x09\x29\x1A\xE1\xF1\xED\xED"+0x7047197C).s
#define _DT_BaseEntity /*DT_BaseEntity*/XorStr<0x0E,14,0xF296060F>("\x4A\x5B\x4F\x53\x73\x60\x71\x50\x78\x63\x71\x6D\x63"+0xF296060F).s
#define _DT_CSPLAYER /*DT_CSPLAYER*/XorStr<0xDA,12,0x43ACB773>("\x9E\x8F\x83\x9E\x8D\x8F\xAC\xA0\xBB\xA6\xB6"+0x43ACB773).s
#define _DT_BasePlayer /*DT_BasePlayer*/XorStr<0x8A,14,0xC35EA39A>("\xCE\xDF\xD3\xCF\xEF\xFC\xF5\xC1\xFE\xF2\xED\xF0\xE4"+0xC35EA39A).s

#include "XorString.h"

/*--------------------------------------------SDK------------------------------------------*/
#include "SDK/cdll_int.h"
#include "SDK/iprediction.h"
#include "SDK/mathlib.h"
#include "SDK/cl_dll/imessagechars.h"
#include "SDK/cl_dll/cdll_client_int.h"
#include "SDK/cl_dll/cbase.h"
#include "SDK/bone_setup.h"
#include "SDK/vgui/ILocalize.h"
#include "SDK/cl_dll/hud_chat.h"
#include "SDK/vgui_controls/Controls.h"
#include "SDK/cl_dll/c_baseanimating.h"
#include "SDK/cl_dll/c_basecombatcharacter.h"
#include "SDK/cl_dll/c_baseplayer.h"
#include "SDK/cl_dll/iviewport.h"
#include "SDK/cl_dll/iviewrender.h"
#include "SDK/icliententitylist.h"
#include "SDK/engine/ivmodelrender.h"
#include "SDK/engine/ivdebugoverlay.h"
#include "SDK/engine/ivmodelinfo.h"
#include "SDK/ienginevgui.h"
#include "SDK/vgui/IClientPanel.h"
#include "SDK/vgui/IPanel.h"
#include "SDK/vgui/ISurface.h"
#include "SDK/vgui_controls/Panel.h"
#include "SDK/engine/IEngineTrace.h"
#include "SDK/VGuiMatSurface/IMatSystemSurface.h"
#include "SDK/input.h"
#include "SDK/game_shared/basecombatweapon_shared.h"
#include "SDK/igameevents.h"
#include "SDK/materialsystem/IMaterialVar.h"
#include "SDK/engine/baseclient.h"
#include "SDK/tier0/vprof.h"
#include "SDK/tier1/utllinkedlist.h"
#include "SDK/cl_dll/game_controls/commandmenu.h"
#include "SDK/game_shared/ragdoll_shared.h"
#include "SDK/istudiorender.h"
#include "SDK/icvar.h"
#include "SDK/game_shared/usercmd.h"
#include "SDK/cl_dll/c_baseanimatingoverlay.h"
#include "SDK/inetchannel.h"
#include "SDK/dt_recv.h"
#include "SDK/con_nprint.h"
#include "SDK/GameUI/IGameConsole.h"
#include "SDK/tier1/checksum_md5.h"
#include "SDK/game_shared/util_shared.h"
#include "SDK/engine/ivmodelrender.h"
#include "SDK/filesystem.h"
#include "SDK/eiface.h"
#include "SDK/cl_dll/prediction.h"
#include "SDK/game_shared/igamesystem.h"
#include "SDK/client_class.h"
#include "SDK/engine/iserverplugin.h"
#include "SDK/dlls/iplayerinfo.h"
#include "SDK/tier0/dbg.h"
#include "SDK/game_shared/gamemovement.h"
#include "SDK/tier0/mem.h"
#include "SDK/tier1/convar.h"
/*--------------------------------------------END------------------------------------------*/

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "mathlib.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib") //remove if you using < 2015
#pragma comment(lib, "appframework.lib")
#pragma comment(lib, "nvtc.lib")
#pragma comment(lib, "nvtristrip.lib")
#pragma comment(lib, "shaderlib.lib")
#pragma comment(lib, "tier0.lib")
#pragma comment(lib, "vgui_controls.lib")
#pragma comment(lib, "vgui_surfacelib.lib")
#pragma comment(lib, "vmpi.lib")
#pragma comment(lib, "vstdlib.lib")
#pragma comment(lib, "vtf.lib")
#pragma comment(lib, "unitlib.lib")

enum Indexes
{
	PaintTraverse = 40
};

extern void StartHooking(void);

extern IGameConsole* m_pGameConsole;
extern IMatSystemSurface* m_pMatSurface;
extern ISurface* m_pSurface;
extern IVEngineClient* m_pEngine;
extern IPanel* m_pPanel;
extern ICvar* m_pCvar;
extern IBaseClientDLL* m_pClient;
extern IClientEntityList* m_pEntList;
extern IVModelInfoClient* m_pModelInfo;
extern CGlobalVarsBase* m_pGlobals;
extern CInput* m_pInput;
extern IEngineTrace* m_pEngineTrace;
extern CGameMovement* m_pGameMovement;
extern CPrediction* m_pPrediction;
extern IMaterialSystem* m_pMaterialSystem;
extern IVDebugOverlay* m_pDebugOverlay;
extern IVModelRender* m_pModelRender;
extern IVRenderView* m_pRender;
extern IGameEventManager2* m_pGameEventManager;
extern IPhysicsSurfaceProps* m_pPhysicsAPI;

//---------------------------------------------------------------------------

#include "cVars.h"
#include "cNetVars.h"

class _Interfaces
{
public:
	My_cVars* m_pMyCvars = new My_cVars();
	CNetVars* m_pNetVars = new CNetVars();

	bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return false;
		return (*szMask) == NULL;
	}

	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
			if (bDataCompare(reinterpret_cast<BYTE*>(dwAddress + i), bMask, szMask))
				return static_cast<DWORD>(dwAddress + i);

		return 0;
	}
};

extern _Interfaces pinterface;

#include "vtable.h"
#include "cEntity.h"

//User Class
extern CEntity* m_pEntity;
//---------------------------------------------------------------------------

typedef void (__stdcall*PaintTraverse_t)(VPANEL vguiPanel, bool forceRepaint, bool allowForce);
void __stdcall Hooked_PaintTraverse(VPANEL vguiPanel, bool forceRepaint, bool allowForce);

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)

#endif
