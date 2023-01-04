inline void DrawESP(C_BaseEntity* pBaseEntity, C_BaseEntity* pLocal, int index)
{
	Color cBaseColor = Color(255, 255, 255, 255);

	int iWidth, iHeight;

	player_info_t info;

	m_pEngine->GetScreenSize(iWidth, iHeight);

	iWidth *= 0.5f;
	iHeight *= 0.5f;

	cBaseColor = Color(255, 255, 70, 255);

	Vector origin;

	if (!WorldToScreen(pBaseEntity->GetAbsOrigin(), origin))
	{
		return;
	}

	Vector offset = (m_pEntity->GetFlags(pBaseEntity)& FL_DUCKING) ? Vector(0.f, 0.f, 53.5f) : Vector(0.f, 0.f, 72);
	Vector max = (pBaseEntity->GetAbsOrigin() + offset);

	Vector top;

	if (!WorldToScreen(max, top))
	{
		return;
	}

	float boxHeight = (origin.y - top.y);
	float boxHalfWidth = (boxHeight * .25f);

	if (m_pEntity->GetFlags(pBaseEntity) & FL_DUCKING)
	{
		boxHalfWidth *= 1.345794392523364f;
	}

	Vector box((top.x - boxHalfWidth), top.y, 0.f);

	//BoxESP
	{
		Outline((box.x - 1), (box.y - 1), ((boxHalfWidth * 2) + 2), (boxHeight + 2), Color(0, 0, 0, 255));
		Outline((box.x + 1), (box.y + 1), ((boxHalfWidth * 2) - 2), (boxHeight - 2), Color(0, 0, 0, 255));

		Outline(box.x, box.y, (boxHalfWidth * 2), boxHeight, cBaseColor);
	}

	//HealtBar
	{
		float fHealth = m_pEntity->GetHealth(pBaseEntity);

		if (fHealth > 0)
		{
			int r = 255 - (fHealth * 2.55);
			int g = fHealth * 2.55;

			Color patch(0, 0, 0, 255);

			if (fHealth > 100)
			{
				patch.SetColor(255, 255, 255, 255);
			}

			Outline(top.x - boxHalfWidth - 6, top.y - 1, 4, boxHeight + 2, Color(0, 0, 0, 255));

			Outline(top.x - boxHalfWidth - 5, top.y, 2, boxHeight, Color(r, g, 0, 255));

			Outline(top.x - boxHalfWidth - 5, top.y - 1, 2, (100 - fHealth) * (boxHeight / 100) + 1, Color(0, 0, 0, 255));
		}
	}

	//ArmorBar
	{
		float fArmor = min(m_pEntity->GetArmor(pBaseEntity), 100);

		if (fArmor > 0)
		{
			int iScale = (fArmor * 2.55f);

			Color patch(85, 85, 85, 255);

			if (m_pEntity->HasHelmet(pBaseEntity))
			{
				patch.SetColor(0, 0, 0, 255);
			}

			Outline(top.x - boxHalfWidth - (6 + 6), top.y - 1, 4, boxHeight + 2, patch);

			Outline(top.x - boxHalfWidth - (5 + 6), top.y, 2, boxHeight, Color(iScale, iScale, iScale, 255));

			Outline(top.x - boxHalfWidth - (5 + 6), top.y - 1, 2, (100 - fArmor) * (boxHeight / 100) + 1, patch);
		}
	}

	top.x += (boxHalfWidth + 5);
	top.y -= 4;

	static float fLength = 0.f;

	//Name ESP
	{
		if (m_pEngine->GetPlayerInfo(pBaseEntity->index, &info))
			DrawString(top.x, top.y, Color(255, 255, 255, 255), /*%s*/XorStr<0x92, 3, 0x3DD73B12>("\xB7\xE0" + 0x3DD73B12).s, info.name);
		else
			DrawString(top.x, top.y, Color(255, 255, 255, 255), /*NULLNAME*/XorStr<0x08, 9, 0x899EE6EC>("\x46\x5C\x46\x47\x42\x4C\x43\x4A" + 0x899EE6EC).s);

		top.y += ((12 - GetFontIndexByDistance(fLength)));
	}
}