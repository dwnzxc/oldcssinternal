//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//
#if !defined( PREDICTION_H )
#define PREDICTION_H
#ifdef _WIN32
#pragma once
#endif

#include "vector.h"
#include "iprediction.h"
#include "c_baseplayer.h"

class CMoveData;
class CUserCmd;

//-----------------------------------------------------------------------------
// Purpose: Implements prediction in the client .dll
//-----------------------------------------------------------------------------
class CPrediction : public IPrediction
{

};

extern ConVar	cl_predict;

extern CPrediction *prediction;

#endif // PREDICTION_H