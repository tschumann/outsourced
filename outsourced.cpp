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

	Engine::Engine()
	{
	}

	Engine::~Engine() noexcept
	{
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