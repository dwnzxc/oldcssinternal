#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Include.h"

class CEntity
{
public:

	bool IsDead(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<char*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_lifeState*/
			XorStr<0xA6, 12, 0x7671B668>("\xCB\xF8\xC4\xC0\xCC\xCE\xFF\xD9\xCF\xDB\xD5" + 0x7671B668).s));
	}

	int GetTeamID(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_iTeamNum*/
			XorStr<0xFB, 11, 0x3542C47A>("\x96\xA3\x94\xAA\x9A\x61\x6C\x4C\x76\x69" + 0x3542C47A).s));
	}

	float GetNextPrimaryAttack(C_BaseCombatWeapon* m_pWeapon)
	{
		return *reinterpret_cast<float*>(reinterpret_cast<DWORD>(m_pWeapon) + pinterface.m_pNetVars->GetOffset(
			_DT_BaseCombatWeapon, /*m_flNextPrimaryAttack*/XorStr<0xF2, 22, 0x891278A2>(
				"\x9F\xAC\x92\x99\xB8\x92\x80\x8D\xAA\x89\x95\x90\x9F\x8D\x79\x40\x76\x77\x65\x66\x6D" + 0x891278A2).s));
	}

	float CEntity::GetNextAttack(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<float*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BaseCombatCharacter, /*m_flNextAttack*/
			XorStr<0x6D, 15, 0x68E032ED>("\x00\x31\x09\x1C\x3F\x17\x0B\x00\x34\x02\x03\x19\x1A\x11" + 0x68E032ED).s));
	}

	int GetTickBase(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_nTickBase*/
			XorStr<0x95, 12, 0xC4710100>("\xF8\xC9\xF9\xCC\xF0\xF9\xF0\xDE\xFC\xED\xFA" + 0xC4710100).s));
	}

	int GetFlags(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_fFlags*/XorStr<0x9B, 9, 0x4D67D100>("\xF6\xC3\xFB\xD8\xF3\xC1\xC6\xD1" + 0x4D67D100).s));
	}

	int GetHealth(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_iHealth*/XorStr<0x9D, 10, 0x5487FA1B>("\xF0\xC1\xF6\xE8\xC4\xC3\xCF\xD0\xCD" + 0x5487FA1B).s));
	}

	int GetShotsFired(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_CSPLAYER, /*m_iShotsFired*/
			XorStr<0x30, 14, 0x040AE2DF>("\x5D\x6E\x5B\x60\x5C\x5A\x42\x44\x7E\x50\x48\x5E\x58" + 0x040AE2DF).s));
	}

	Vector GetVecOrigin(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BaseEntity, /*m_vecOrigin*/
			XorStr<0xBE, 12, 0x5E125EB0>("\xD3\xE0\xB6\xA4\xA1\x8C\xB6\xAC\xA1\xAE\xA6" + 0x5E125EB0).s));
	}

	QAngle GetPunchAngle(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<QAngle*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_vecPunchAngle*/
			XorStr<0x24, 16, 0x05DC07F5>("\x49\x7A\x50\x42\x4B\x79\x5F\x45\x4F\x45\x6F\x41\x57\x5D\x57" + 0x05DC07F5).s));
	}

	MoveType_t GetMoveType(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<MoveType_t*>(reinterpret_cast<DWORD>(pBaseEntity) + 0x134);
	}

	Vector GetVelocity(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_vecVelocity[0]*/
			XorStr<0xF1, 17, 0x2B5DE7A2>("\x9C\xAD\x85\x91\x96\xA0\x92\x94\x96\x99\x92\x88\x84\xA5\xCF\x5D" + 0x2B5DE7A2).s));
	}

	Vector GetEyePos(C_BaseEntity* pBaseEntity)
	{
		Vector m_VecOrigin = *reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BaseEntity, /*m_vecOrigin*/
			XorStr<0xBE, 12, 0x5E125EB0>("\xD3\xE0\xB6\xA4\xA1\x8C\xB6\xAC\xA1\xAE\xA6" + 0x5E125EB0).s));

		Vector m_vecViewOffset = *reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BasePlayer, /*m_vecViewOffset[0]*/
			XorStr<0x04, 19, 0xD03806B5>("\x69\x5A\x70\x62\x6B\x5F\x63\x6E\x7B\x42\x68\x69\x63\x74\x66\x48\x24\x48" + 0xD03806B5).
			s));

		Vector EyePos = (Vector(m_VecOrigin.x, m_VecOrigin.y, m_VecOrigin.z) + m_vecViewOffset);

		return EyePos;
	}

	C_BaseCombatWeapon* GetWeapon(C_BaseEntity* pBaseEntity)
	{
		EHANDLE hHandle = static_cast<EHANDLE>(*reinterpret_cast<PDWORD>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_BaseCombatCharacter, /*m_hActiveWeapon*/
			XorStr<0x72, 16, 0xA2A827FD>("\x1F\x2C\x1C\x34\x15\x03\x11\x0F\x1F\x2C\x19\x1C\x0E\x10\xEE" + 0xA2A827FD).s)));

		C_BaseCombatWeapon* pWeapon = static_cast<C_BaseCombatWeapon*>(m_pEntList->GetClientEntityFromHandle(hHandle));

		if (!pWeapon)
			return nullptr;

		return pWeapon;
	}

	int CEntity::HasHelmet(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_CSPLAYER, /*m_bHasHelmet*/XorStr<0xA2, 13, 0x57915036>("\xCF\xFC\xC6\xED\xC7\xD4\xE0\xCC\xC6\xC6\xC9\xD9" + 0x57915036).s));
	}

	int CEntity::GetArmor(C_BaseEntity* pBaseEntity)
	{
		return *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pBaseEntity) + pinterface.m_pNetVars->GetOffset(
			_DT_CSPLAYER, /*m_ArmorValue*/
			XorStr<0x93, 13, 0x8A1EBCD8>("\xFE\xCB\xD4\xE4\xFA\xF7\xEB\xCC\xFA\xF0\xE8\xFB" + 0x8A1EBCD8).s));
	}

	bool CEntity::HasAmmo(C_BaseCombatWeapon* m_pWeapon)
	{
		int iAmmo = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(m_pWeapon) + pinterface.m_pNetVars->GetOffset(
			_DT_BaseCombatWeapon, /*m_iClip1*/XorStr<0x98, 9, 0x3DFFE6E7>("\xF5\xC6\xF3\xD8\xF0\xF4\xEE\xAE" + 0x3DFFE6E7).s));

		if (iAmmo == NULL)
			return false;

		return true;
	}
};

#endif