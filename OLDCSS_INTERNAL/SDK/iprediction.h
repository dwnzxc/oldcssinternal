//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#if !defined( IPREDICTION_H )
#define IPREDICTION_H
#ifdef _WIN32
#pragma once
#endif


#include "SDK\tier1\interface.h"
#include "vector.h" // Solely to get at define for QAngle

class C_BasePlayer;
class IMoveHelper;
class CMoveData;
class CUserCmd;

//-----------------------------------------------------------------------------
// Purpose: Engine interface into client side prediction system
//-----------------------------------------------------------------------------
class IPrediction
{
public:
	virtual void	function0();
	virtual void	function1();
	virtual void	function2();
	virtual void	Update(int startframe, bool validframe, int incoming_acknowledged, int outgoing_command);
	virtual void	function4();
	virtual void	function5();
	virtual void	function6();
	virtual void	function7();
	virtual bool	InPrediction(void) const;
	virtual void	function9();
	virtual void	function10();
	virtual void	function11();
	virtual void	function12();
	virtual void	function13();
	virtual void	function14();
	virtual void	GetViewAngles(QAngle& ang);
	virtual void	SetViewAngles(QAngle& ang);
	virtual void	GetLocalViewAngles(QAngle& ang);
	virtual void	SetLocalViewAngles(QAngle& ang);
	virtual void	RunCommand(C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* pHelper);
	virtual void	SetupMove(C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move);
	virtual void	FinishMove(C_BasePlayer *player, CUserCmd *ucmd, CMoveData *move);
#if 0
	virtual void	RunCommand(C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *moveHelper);
	virtual void	SetupMove(C_BasePlayer *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move);
	virtual void	FinishMove(C_BasePlayer *player, CUserCmd *ucmd, CMoveData *move);

	virtual			~IPrediction(void) {};

	virtual void	Init(void) = 0;
	virtual void	Shutdown(void) = 0;

	// Run prediction
	virtual void	Update
	(
		int startframe,				// World update ( un-modded ) most recently received
		bool validframe,			// Is frame data valid
		int incoming_acknowledged,	// Last command acknowledged to have been run by server (un-modded)
		int outgoing_command		// Last command (most recent) sent to server (un-modded)
	) = 0;

	// We are about to get a network update from the server.  We know the update #, so we can pull any
	//  data purely predicted on the client side and transfer it to the new from data state.
	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void	PostEntityPacketReceived(void) = 0;
	virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;

	virtual void	OnReceivedUncompressedPacket(void) = 0;

	// The engine needs to be able to access a few predicted values
	virtual int		GetWaterLevel(void) = 0;
	virtual void	GetViewOrigin(Vector& org) = 0;
	virtual void	SetViewOrigin(Vector& org) = 0;
	virtual void	GetViewAngles(QAngle& ang) = 0;
	virtual void	SetViewAngles(QAngle& ang) = 0;
	virtual void	GetLocalViewAngles(QAngle& ang) = 0;
	virtual void	SetLocalViewAngles(QAngle& ang) = 0;
#endif
};

extern IPrediction *g_pClientSidePrediction;

#define VCLIENT_PREDICTION_INTERFACE_VERSION	"VClientPrediction"

#endif // IPREDICTION_H