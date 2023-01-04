#include "Include.h"

//===========================================================================
typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWCH Buffer;
} UNICODE_STRING;

typedef UNICODE_STRING* PUNICODE_STRING;

//===========================================================================
typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

//===========================================================================
typedef struct _LDR_MODULE
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

//===========================================================================

void UnlinkModule(char* szModule)
{
	DWORD dwPEB = 0, dwOffset = 0;
	PLIST_ENTRY pUserModuleHead, pUserModule;
	PPEB_LDR_DATA pLdrData;
	PLDR_MODULE pLdrModule = nullptr;
	PUNICODE_STRING lpModule = nullptr;
	char szModuleName[512];
	int i = 0, n = 0;
#ifndef _WIN64
	_asm
	{
		pushad
		mov eax, fs: [48]
		mov dwPEB, eax
		popad
	}

	pLdrData = reinterpret_cast<PPEB_LDR_DATA>(reinterpret_cast<PDWORD>(*reinterpret_cast<PDWORD>(dwPEB + 12)));
#else
	BYTE* _teb = (BYTE*)__readgsqword(0x30);
	pLdrData = (PPEB_LDR_DATA)(PULONGLONG)(*(PULONGLONG)((*(PULONGLONG)(_teb + 0x60)) + 0x18));
#endif

	for (; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			pUserModuleHead = pUserModule = static_cast<PLIST_ENTRY>(&pLdrData->InLoadOrderModuleList);
			dwOffset = 0;
			break;

		case 1:
			pUserModuleHead = pUserModule = static_cast<PLIST_ENTRY>(&pLdrData->InMemoryOrderModuleList);
#ifndef _WIN64
			dwOffset = 8;
#else
			dwOffset = 16;
#endif
			break;
		case 2:
			pUserModuleHead = pUserModule = static_cast<PLIST_ENTRY>(&(pLdrData->InInitializationOrderModuleList));
#ifndef _WIN64
			dwOffset = 16;
#else
			dwOffset = 32;
#endif
			break;
		}

		while (pUserModule->Flink != pUserModuleHead)
		{
			pUserModule = pUserModule->Flink;
#ifndef _WIN64
			lpModule = reinterpret_cast<PUNICODE_STRING>(reinterpret_cast<DWORD>(pUserModule) + (36 - dwOffset));
#else
			lpModule = (PUNICODE_STRING)(((LONGLONG)(pUserModule)) + (72 - dwOffset));
#endif

			for (n = 0; n < (lpModule->Length) / 2 && n < 512; n++)
				szModuleName[n] = static_cast<CHAR>(*((lpModule->Buffer) + (n)));

			szModuleName[n] = '\0';
			if (strstr(szModuleName, szModule))
			{
#ifndef _WIN64
				if (!pLdrModule)
					pLdrModule = reinterpret_cast<PLDR_MODULE>(reinterpret_cast<DWORD>(pUserModule) - dwOffset);
#else
				if (!pLdrModule)
					pLdrModule = (PLDR_MODULE)(((LONGLONG)(pUserModule)) - dwOffset);
#endif
				pUserModule->Blink->Flink = pUserModule->Flink;
				pUserModule->Flink->Blink = pUserModule->Blink;
			}
		}
	}

	// Unlink from LdrpHashTable
	if (pLdrModule)
	{
		pLdrModule->HashTableEntry.Blink->Flink = pLdrModule->HashTableEntry.Flink;
		pLdrModule->HashTableEntry.Flink->Blink = pLdrModule->HashTableEntry.Blink;
	}
}

//===========================================================================
void RemovePeHeader(HANDLE GetModuleBase)
{
	PIMAGE_DOS_HEADER pDosHeader = static_cast<PIMAGE_DOS_HEADER>(GetModuleBase);
	PIMAGE_NT_HEADERS pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<PBYTE>(pDosHeader) + static_cast<
		DWORD>(pDosHeader->e_lfanew));

	if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		return;

	if (pNTHeader->FileHeader.SizeOfOptionalHeader)
	{
		DWORD Protect;
		WORD Size = pNTHeader->FileHeader.SizeOfOptionalHeader;
		VirtualProtect(static_cast<PVOID>(GetModuleBase), Size, PAGE_EXECUTE_READWRITE, &Protect);
		RtlZeroMemory(static_cast<PVOID>(GetModuleBase), Size);
		VirtualProtect(static_cast<PVOID>(GetModuleBase), Size, Protect, &Protect);
	}
}

void CreateConsole()
{
	if (AllocConsole())
	{
		SetConsoleTitle(/* */XorStr<0xE7, 2, 0xD202036F>("\xC7" + 0xD202036F).s);
		freopen(/*CONOUT$*/XorStr<0x51, 8, 0x7BF8977B>("\x12\x1D\x1D\x1B\x00\x02\x73" + 0x7BF8977B).s, /*wt*/
		                   XorStr<0x4B, 3, 0x877E831D>("\x3C\x38" + 0x877E831D).s, stdout);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
}

//////////////////////
//Credits:
//TraitCore
//noop
//LayZ_Pz Coders
//////////////////////

int __stdcall DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (IsDebuggerPresent())
			exit(1);

		//CreateConsole();

		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartHooking), nullptr, 0, nullptr);

		CHAR PATCH[MAX_PATH];
		ULONG len = static_cast<ULONG>(strlen(PATCH));
		GetModuleFileNameA(hInstance, PATCH, MAX_PATH);
		RemovePeHeader(GetModuleHandleA(PATCH));
		UnlinkModule(PATCH);
		RtlZeroMemory(PATCH, len);
	}
	return true;
}
