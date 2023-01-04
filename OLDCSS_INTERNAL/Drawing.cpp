#include "Include.h"

vgui::HFont HFont_Tahoma;

void FontInit(void)
{
	HFont_Tahoma = m_pMatSurface->CreateFont();
	m_pMatSurface->SetFontGlyphSet(HFont_Tahoma, /*Tahoma*/XorStr<0x88, 7, 0x5ED02C00>("\xDC\xE8\xE2\xE4\xE1\xEC" + 0x5ED02C00).s, 13, 300, 0, 0, 0x200);
}

RECT GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	m_pEngine->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}

void Outline(int x, int y, int w, int h, Color color)
{
	m_pMatSurface->DrawSetColor(color);
	m_pMatSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void FillRGBA(int x, int y, int w, int h, Color dwColor)
{
	m_pMatSurface->DrawSetColor(dwColor);
	m_pMatSurface->DrawFilledRect(x, y, x + w, y + h);
}

void DrawLine(int x0, int y0, int x1, int y1, Color col)
{
	m_pSurface->DrawSetColor(col);
	m_pSurface->DrawLine(x0, y0, x1, y1);
}

void Border(int x, int y, int w, int h, Color dwColor)
{
	FillRGBA(x - 1, y - 1, w + 2, 1, dwColor);
	FillRGBA(x - 1, y, 1, h - 1, dwColor);
	FillRGBA(x + w, y, 1, h - 1, dwColor);
	FillRGBA(x - 1, y + h - 1, w + 2, 1, dwColor);
}

void DrawString(int x, int y, Color dwColor, const char *pszText, ...)
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t szString[1024] = { '\0' };

	va_start(va_alist, pszText);
	vsprintf(szBuffer, pszText, va_alist);
	va_end(va_alist);

	wsprintfW(szString, L"%S", szBuffer);

	m_pSurface->DrawSetTextPos(x, y);
	m_pSurface->DrawSetTextFont(HFont_Tahoma);
	m_pSurface->DrawSetTextColor(dwColor);
	m_pSurface->DrawPrintText(szString, wcslen(szString));
}

void DrawRect(int x, int y, int w, int h, Color dwColor)
{
	m_pSurface->DrawSetColor(dwColor);
	m_pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void GetWorldSpaceCenter(C_BaseEntity* pBaseEnt, Vector& vWorldSpaceCenter)
{
	if (pBaseEnt)
	{
		Vector vMin, vMax;
		pBaseEnt->GetRenderBounds(vMin, vMax);
		vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
		vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;
	}
}

bool WorldToScreen(const Vector &vOrigin, Vector &vScreen)
{
	const VMatrix& worldToScreen = m_pEngine->WorldToScreenMatrix();

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];

	vScreen.z = 0;

	if (w > 0.001)
	{
		int screensize[VECTOR2D];
		m_pEngine->GetScreenSize(screensize[X], screensize[Y]);

		vScreen.x = screensize[X] / 2 + ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * 1 / w / 2 * screensize[X] + 0.5);
		vScreen.y = screensize[Y] / 2 - ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * 1 / w / 2 * screensize[Y] + 0.5);
		return true;
	}

	return false;
}

__forceinline int GetFontIndexByDistance(const float& distance)
{
	float copy = max(min(distance, 1000.f), 1.f);

	return 5 * static_cast<int>(copy / 1000.f);
}

#include "menu.h"
#include "esp.h"

void __stdcall Hooked_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
	pPanelHook->Function<PaintTraverse_t>(PaintTraverse)(vguiPanel, forceRepaint, allowForce);

	static vgui::VPANEL targetPanel = 0;
	if (!targetPanel)
	{
		if (!strcmp(m_pPanel->GetName(vguiPanel), /*MatSystemTopPanel*/XorStr<0x17, 18, 0x8411553B>("\x5A\x79\x6D\x49\x62\x6F\x69\x7B\x72\x74\x4E\x52\x73\x45\x4B\x43\x4B" + 0x8411553B).s))
		{
			targetPanel = vguiPanel;
		}
	}
	else if (targetPanel == vguiPanel)
	{

	}

	const char* pszPanelName = m_pPanel->GetName(vguiPanel);
	bool isValidPanel = false;

	if (pszPanelName && pszPanelName[0] == 'F' && pszPanelName[1] == 'o' && pszPanelName[2] == 'c' && pszPanelName[3] == 'u' && pszPanelName[4] == 's' && pszPanelName[5] == 'O')
		isValidPanel = true;

	if (isValidPanel)
	{
		DO_ONCE
		(
			FontInit();
		);

		C_BaseEntity* pLocal = static_cast<C_BaseEntity*>(m_pEntList->GetClientEntity(m_pEngine->GetLocalPlayer()));

		if (!m_pEngine->IsTakingScreenshot())
		{
			RECT ViewPort = GetViewport();

			int Width = ViewPort.right / 2;
			int Height = ViewPort.bottom / 2;

			if (m_pEngine->IsInGame())
			{
				int index = m_pEngine->GetMaxClients();
				for (; index >= 1; index--)
				{
					if (index != m_pEngine->GetLocalPlayer())
					{
						IClientEntity* ClientEntity = m_pEntList->GetClientEntity(index);

						if (ClientEntity != nullptr)
						{
							C_BaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();

							if (!m_pEntity->IsDead(pBaseEntity) && pBaseEntity != nullptr && !pBaseEntity->IsDormant())
							{
								DrawESP(pBaseEntity, pLocal, index);
							}
						}
					}
				}
			}

			DrawMenu();

			DO_ONCE(
				pinterface.m_pMyCvars->InitCvars();
			);
		}
	}
}