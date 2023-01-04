#ifndef __NETVARS_H__
#define __NETVARS_H__

#include "Include.h"

class CNetVars
{
public:
	int GetOffset(const char *tableName, const char *propName)
	{
		int offset = GetProp(tableName, propName);

		if (!offset)
		{
			printf(/*ClientClass was not found\n*/XorStr<0x0D, 27, 0x711E96FF>("\x4E\x62\x66\x75\x7F\x66\x50\x78\x74\x65\x64\x38\x6E\x7B\x68\x3C\x73\x71\x6B\x00\x47\x4D\x56\x4A\x41\x2C" + 0x711E96FF).s);
			return 0;
		}

		return offset;
	}

	RecvVarProxyFn HookProp(const char* tableName, const char* propName, RecvVarProxyFn function)
	{
		RecvProp *recvProp = nullptr;

		if (!GetProp(tableName, propName, &recvProp))
		{
			printf(/*Failed to hook prop: %s from table: %s\n*/XorStr<0xE5, 40, 0x17F21852>("\xA3\x87\x8E\x84\x8C\x8E\xCB\x98\x82\xCE\x87\x9F\x9E\x99\xD3\x84\x87\x99\x87\xC2\xD9\xDF\x88\xDC\x9B\x8C\x90\x6D\x21\x76\x62\x66\x69\x63\x3D\x28\x2C\x79\x01" + 0x17F21852).s, propName, tableName);
			return nullptr;
		}


		RecvVarProxyFn old = recvProp->m_ProxyFn;
		recvProp->m_ProxyFn = function;

		return old;
	}

	int GetProp(const char* tableName, const char* propName, RecvProp** prop = 0)
	{
		RecvTable* recvTable = GetTable(tableName);

		if (!recvTable)
		{
			printf(/*Failed to find table: %s\n*/XorStr<0x2C, 26, 0x1A1D58BA>("\x6A\x4C\x47\x43\x55\x55\x12\x47\x5B\x15\x50\x5E\x56\x5D\x1A\x4F\x5D\x5F\x52\x5A\x7A\x61\x67\x30\x4E" + 0x1A1D58BA).s, tableName);
			return 0;
		}


		int offset = GetProp(recvTable, propName, prop);

		if (!offset)
		{
			printf(/*Failed to find offset for prop: %s from table: %s\n*/XorStr<0xC0, 51, 0x79EBD290>("\x86\xA0\xAB\xAF\xA1\xA1\xE6\xB3\xA7\xE9\xAC\xA2\xA2\xA9\xEE\xA0\xB6\xB7\xA1\xB6\xA0\xF5\xB0\xB8\xAA\xF9\xAA\xA9\xB3\xAD\xE4\xFF\xC5\x92\xC2\x85\x96\x8A\x8B\xC7\x9C\x88\x88\x87\x89\xD7\xCE\xCA\x83\xFB" + 0x79EBD290).s, propName, tableName);
			return 0;
		}


		return offset;
	}

	int GetProp(RecvTable* recvTable, const char* propName, RecvProp** prop = 0)
	{
		int extraOffset = 0;

		for (int i = 0; i < recvTable->m_nProps; ++i)
		{
			RecvProp* recvProp = &recvTable->m_pProps[i];


			RecvTable* child = recvProp->m_pDataTable;

			if (child
				&& (child->m_nProps > 0))
			{
				int tmp = GetProp(child, propName, prop);

				if (tmp)
				{
					extraOffset += (recvProp->m_Offset + tmp);
				}
			}

			if (stricmp(recvProp->m_pVarName, propName))
			{
				continue;
			}


			if (prop && !*prop)
			{
				*prop = recvProp;
			}

			return (recvProp->m_Offset + extraOffset);
		}

		return extraOffset;
	}


	RecvTable* GetTable(const char* tableName)
	{
		if (m_tables.empty())
		{
			printf(/*Failed to find table: %s (m_tables is empty)\n*/XorStr<0xB9, 46, 0xE518F0E2>("\xFF\xDB\xD2\xD0\xD8\xDA\x9F\xB4\xAE\xE2\xA5\xAD\xAB\xA2\xE7\xBC\xA8\xA8\xA7\xA9\xF7\xEE\xEA\xA3\xF1\xFA\xBE\x8B\xA1\xB7\xB5\xB4\xBC\xA9\xFB\xB5\xAE\xFE\xBA\x8D\x91\x96\x9A\xCD\xEF" + 0xE518F0E2).s, tableName);
			return nullptr;
		}

		for each (RecvTable* table in m_tables)
		{
			if (!table)
			{
				continue;
			}


			if (stricmp(table->m_pNetTableName, tableName) == 0)
			{
				return table;
			}
		}

		return nullptr;
	}

	void Init(void)
	{
		m_tables.clear();

		ClientClass *clientClass = m_pClient->GetAllClasses();

		if (!clientClass)
		{
			return;
		}

		while (clientClass)
		{
			RecvTable *recvTable = clientClass->m_pRecvTable;

			m_tables.push_back(recvTable);

			clientClass = clientClass->m_pNext;
		}
	}
private:
	vector<RecvTable*> m_tables;
};

#endif