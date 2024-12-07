//========= Copyright © 2008-2024, Team Sandpit, All rights reserved. ============
//
// Purpose: Fake Source engine implementation
//
// $NoKeywords: $
//================================================================================

#include <cstdarg>

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

	void Engine::Reset()
	{
		clientPrintf = "";
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

	void FakeVEngineServer::ClientPrintf( edict_t *pEdict, const char *szMsg )
	{
		gEngine.ClientPrintf( pEdict, szMsg );
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

	QueryCvarCookie_t FakeVEngineServer::StartQueryCvarValue( edict_t *pEntity, const char *pName )
	{
		return gEngine.StartQueryCvarValue( pEntity, pName );
	}

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