void DrawMainMenu(void)
{

}

void DrawMenu(void)
{
	if(GetAsyncKeyState(VK_INSERT) & 1)
	{
		pinterface.m_pMyCvars->MenuOpened = !pinterface.m_pMyCvars->MenuOpened;
	}

	static bool bReset;

	if(pinterface.m_pMyCvars->MenuOpened)
	{
		if (bReset == false)
		{
			bReset = true;
			m_pCvar->FindVar("cl_mouseenable")->SetValue(0);

			DrawMainMenu();
		}
	}
	else
	{
		if (bReset == true)
		{
			bReset = false;
			m_pCvar->FindVar("cl_mouseenable")->SetValue(1);
		}
	}
}