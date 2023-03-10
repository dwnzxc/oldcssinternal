#ifndef __VMTHOOK__ 
#define __VMTHOOK__ 
#include <Windows.h> 
#include "Include.h"

class C_VMT
{
	C_VMT(const C_VMT &other);
	//C_VMT &operator = (const C_VMT &other);

public:

	C_VMT(DWORD *Instance)
	{
		ppInstance = *reinterpret_cast<PDWORD**>(Instance);
		pOldVMT = *ppInstance;

		VMTSize = dwGetVMTCount(pOldVMT);

		if (VMTSize <= 0) return;

		pNewVMT = new DWORD[VMTSize];
		memcpy(pNewVMT, pOldVMT, sizeof(DWORD) * VMTSize);

		*ppInstance = (pNewVMT);

		Instance = pNewVMT;
	}

	void Hook(DWORD dwNewFunc, unsigned int iIndex)
	{
		if (pNewVMT && pOldVMT && iIndex <= VMTSize && iIndex >= 0)
		{
			pNewVMT[iIndex] = dwNewFunc;
		}
	}

	void Unhook(unsigned int iIndex)
	{
		if (pNewVMT && pOldVMT && iIndex <= VMTSize && iIndex >= 0)
		{
			pNewVMT[iIndex] = pOldVMT[iIndex];
		}
	}

	DWORD OldPointer(int iIndex)
	{
		return pOldVMT[iIndex];
	}

	DWORD NewPointer(int iIndex)
	{
		return pNewVMT[iIndex];
	}

	template<typename T> T Function(int Index)
	{
		return (T)(pOldVMT[Index]);
	}
private:

	DWORD dwGetVMTCount(PDWORD pdwVMT)
	{
		DWORD dwIndex = 0;

		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			dwIndex++;
		}

		return dwIndex;
	}

	DWORD** ppInstance;
	DWORD*  pNewVMT, *pOldVMT;
	DWORD   VMTSize;
};

extern C_VMT* pPanelHook;
extern C_VMT* pDeviceHook;

#endif