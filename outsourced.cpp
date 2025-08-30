//========= Copyright © 2008-2024, Team Sandpit, All rights reserved. ============
//
// Purpose: Fake Source engine implementation
//
// $NoKeywords: $
//================================================================================

#include <cstdarg>
#include <ctime>

#include "outsourced.h"

namespace outsourced
{
	Engine gEngine;

	Engine::Engine() : isDedicatedServer(false), isInEditMode(false)
	{
	}

	Engine::~Engine() noexcept
	{
		for (edict_t *pEdict: gEngine.edicts)
		{
			delete pEdict;
		}
	}

	/// <summary>
	/// Clear everything back to a known good state. Ideally we'd just initialise a new Engine class per-test but the way this has
	/// all been architected is to have a global engine that a bunch of functions can call back to.
	/// </summary>
	void Engine::Initialise()
	{
		clientCommands.clear();
		serverCommands.clear();
		queryCvarCookies.clear();
		clientPrintf = "";

		for (edict_t *pEdict: gEngine.edicts)
		{
			delete pEdict;
		}

		edicts.clear();
	}

	edict_t *Engine::CreateEdict( int iForceEdictIndex )
	{
		edict_t *pEdict = new edict_t();

		gEngine.edicts.push_back( pEdict );

		return pEdict;
	}

	void Engine::ClientPrintf( edict_t *pEdict, const char *szMsg )
	{
		clientPrintf += szMsg;
	}

	void Engine::ClientCommand( edict_t *pEntity, const char *cmd )
	{
		gEngine.clientCommands.push_back( cmd );
	}

	void Engine::ServerCommand( const char *cmd )
	{
		gEngine.serverCommands.push_back( cmd );
	}

	QueryCvarCookie_t Engine::StartQueryCvarValue( edict_t *pEntity, const char *pName )
	{
		QueryCvarCookie_t queryCvarCookie = gEngine.queryCvarCookies.size();

		gEngine.queryCvarCookies.push_back( queryCvarCookie );

		return queryCvarCookie;
	}

	///////////////////////////////
	// Fake IVEngineServer below //
	///////////////////////////////

	edict_t *FakeVEngineServer::CreateEdict( int iForceEdictIndex )
	{
		return gEngine.CreateEdict( iForceEdictIndex );
	}

	void FakeVEngineServer::ServerCommand( const char *str )
	{
		gEngine.ServerCommand( str );
	}

	void FakeVEngineServer::ClientCommand( edict_t *pEdict, const char *szFmt, ... )
	{
		va_list argptr;
		char szCommand[1024];

		va_start( argptr, szFmt );
		vsprintf( szCommand, szFmt, argptr );
		va_end( argptr );

		gEngine.ClientCommand( pEdict, szCommand );
	}

	void FakeVEngineServer::ClientPrintf( edict_t *pEdict, const char *szMsg )
	{
		gEngine.ClientPrintf( pEdict, szMsg );
	}

	void FakeVEngineServer::Con_NPrintf( int pos, const char *fmt, ... )
	{
		va_list argptr;
		char szOutput[1024];

		va_start( argptr, fmt );
		vsprintf( szOutput, fmt, argptr );
		va_end( argptr );

		printf( "%s\n", szOutput );
	}

	void FakeVEngineServer::Con_NXPrintf( const struct con_nprint_s *info, const char *fmt, ... )
	{
		va_list argptr;
		char szOutput[1024];

		va_start( argptr, fmt );
		vsprintf( szOutput, fmt, argptr );
		va_end( argptr );

		printf( "%s\n", szOutput );
	}

	float FakeVEngineServer::Time( void )
	{
		return (float)time( nullptr );
	}

	void FakeVEngineServer::LogPrint( const char *msg )
	{
		printf( "%s\n", msg );
	}

	QueryCvarCookie_t FakeVEngineServer::StartQueryCvarValue( edict_t *pEntity, const char *pName )
	{
		return gEngine.StartQueryCvarValue( pEntity, pName );
	}

#if SOURCE_ENGINE == SE_HL2DM || SOURCE_ENGINE == SE_TF2
	float FakeVEngineServer::GetServerTime() const
	{
		return (float)time( nullptr );
	}
#endif

	/////////////////////////////////////
	// Fake IServerPluginHelpers below //
	/////////////////////////////////////

	void FakeServerPluginHelpers::CreateMessage( edict_t *pEntity, DIALOG_TYPE type, KeyValues *data, IServerPluginCallbacks *plugin )
	{
	}

	void FakeServerPluginHelpers::ClientCommand( edict_t *pEntity, const char *cmd )
	{
		gEngine.ClientCommand( pEntity, cmd );
	}

	QueryCvarCookie_t FakeServerPluginHelpers::StartQueryCvarValue( edict_t *pEntity, const char *pName )
	{
		return gEngine.StartQueryCvarValue( pEntity, pName );
	}
}