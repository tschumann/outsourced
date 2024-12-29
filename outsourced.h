//========= Copyright © 2008-2024, Team Sandpit, All rights reserved. ============
//
// Purpose: Fake Source engine implementation
//
// $NoKeywords: $
//================================================================================

#ifndef _OUTSOURCED_H_
#define _OUTSOURCED_H_

#include <string>
#include <vector>

#include "interface.h"
#include "eiface.h"
#include "engine/iserverplugin.h"

using std::string;
using std::vector;

namespace outsourced
{
	class Engine
	{
	public:
		Engine();
		~Engine() noexcept;

		void Reset();

		edict_t *Engine::CreateEdict( int iForceEdictIndex = -1 );

		void ClientPrintf( edict_t *pEdict, const char *szMsg );

		void ClientCommand( edict_t *pEntity, const char *cmd );

		QueryCvarCookie_t StartQueryCvarValue( edict_t *pEntity, const char *pName );

		// TODO: should probably be private
		vector<string> clientCommands;

		// TODO: should probably be private
		vector<QueryCvarCookie_t> queryCvarCookies;

		// TODO: should probably be private
		string clientPrintf;
	private:
		bool isDedicatedServer;
		bool isInEditMode;

		vector<edict_t *> edicts;
	};

	extern Engine gEngine;

	class FakeVEngineServer : public IVEngineServer
	{
	public:
#if SOURCE_ENGINE == SE_EPISODEONE
		virtual void		ChangeLevel( const char *s1, const char *s2 ) {};

		virtual int			IsMapValid( const char *filename ) { return 0; };

		virtual bool		IsDedicatedServer( void ) { return false; };

		virtual int			IsInEditMode( void ) { return 0; };

		virtual int			PrecacheModel( const char *s, bool preload = false ) { return 0; };
		virtual int			PrecacheSentenceFile( const char *s, bool preload = false ) { return 0; };
		virtual int			PrecacheDecal( const char *name, bool preload = false ) { return 0; };
		virtual int			PrecacheGeneric( const char *s, bool preload = false ) { return 0; };

		virtual bool		IsModelPrecached( char const *s ) const { return false; };
		virtual bool		IsDecalPrecached( char const *s ) const { return false; };
		virtual bool		IsGenericPrecached( char const *s ) const { return false; };

		virtual int			GetClusterForOrigin( const Vector &org ) { return 0; };
		virtual int			GetPVSForCluster( int cluster, int outputpvslength, unsigned char *outputpvs ) { return 0; };
		virtual bool		CheckOriginInPVS( const Vector &org, const unsigned char *checkpvs, int checkpvssize ) { return false; };
		virtual bool		CheckBoxInPVS( const Vector &mins, const Vector &maxs, const unsigned char *checkpvs, int checkpvssize ) { return false; };

		virtual int			GetPlayerUserId( const edict_t *e ) { return 0; }; 
		virtual const char	*GetPlayerNetworkIDString( const edict_t *e ) { return NULL; };

		virtual int			GetEntityCount( void ) { return 0; };
		virtual int			IndexOfEdict( const edict_t *pEdict ) { return 0; };
		virtual edict_t		*PEntityOfEntIndex( int iEntIndex ) { return NULL; };

		virtual INetChannelInfo* GetPlayerNetInfo( int playerIndex ) { return NULL; };

		virtual edict_t		*CreateEdict( int iForceEdictIndex = -1 );
		virtual void		RemoveEdict( edict_t *e ) {};

		virtual void		*PvAllocEntPrivateData( long cb ) { return NULL; };
		virtual void		FreeEntPrivateData( void *pEntity ) {};

		virtual void		*SaveAllocMemory( size_t num, size_t size ) { return NULL; };
		virtual void		SaveFreeMemory( void *pSaveMem ) {};

		virtual void		EmitAmbientSound( int entindex, const Vector &pos, const char *samp, float vol, soundlevel_t soundlevel, int fFlags, int pitch, float delay = 0.0f ) {};

		virtual void        FadeClientVolume( const edict_t *pEdict, float fadePercent, float fadeOutSeconds, float holdTime, float fadeInSeconds ) {};

		virtual int			SentenceGroupPick( int groupIndex, char *name, int nameBufLen ) { return 0; };
		virtual int			SentenceGroupPickSequential( int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset ) { return 0; };
		virtual int			SentenceIndexFromName( const char *pSentenceName ) { return 0; };
		virtual const char *SentenceNameFromIndex( int sentenceIndex ) { return NULL; };
		virtual int			SentenceGroupIndexFromName( const char *pGroupName ) { return 0; };
		virtual const char *SentenceGroupNameFromIndex( int groupIndex ) { return NULL; };
		virtual float		SentenceLength( int sentenceIndex ) { return 0.0f; };

		virtual void		ServerCommand( const char *str ) {};
		virtual void		ServerExecute( void ) {};
		virtual void		ClientCommand( edict_t *pEdict, const char *szFmt, ... );

		virtual void		LightStyle( int style, const char *val ) {};

		virtual void		StaticDecal( const Vector &originInEntitySpace, int decalIndex, int entityIndex, int modelIndex, bool lowpriority ) {};

		virtual void		Message_DetermineMulticastRecipients( bool usepas, const Vector& origin, CBitVec< ABSOLUTE_PLAYER_LIMIT >& playerbits ) {};

		virtual bf_write	*EntityMessageBegin( int ent_index, ServerClass * ent_class, bool reliable ) { return NULL; };
		virtual bf_write	*UserMessageBegin( IRecipientFilter *filter, int msg_type ) { return NULL; };
		virtual void		MessageEnd( void ) {};

		virtual void		ClientPrintf( edict_t *pEdict, const char *szMsg );

		virtual void		Con_NPrintf( int pos, const char *fmt, ... ) {};
		virtual void		Con_NXPrintf( const struct con_nprint_s *info, const char *fmt, ... ) {};

		virtual const char	*Cmd_Args( void ) { return NULL; };		
		virtual int			Cmd_Argc( void ) { return 0; };		
		virtual char		*Cmd_Argv( int argc ) { return NULL; };	 

		virtual void		SetView( const edict_t *pClient, const edict_t *pViewent ) {};

		virtual float		Time( void ) { return 0.0f; };

		virtual void		CrosshairAngle( const edict_t *pClient, float pitch, float yaw ) {};

		virtual void        GetGameDir( char *szGetGameDir, int maxlength ) {};

		virtual int 		CompareFileTime( const char *filename1, const char *filename2, int *iCompare ) { return 0; };

		virtual bool		LockNetworkStringTables( bool lock ) { return false; };

		virtual edict_t		*CreateFakeClient( const char *netname ) { return NULL; };	

		virtual const char	*GetClientConVarValue( int clientIndex, const char *name ) { return NULL; };

		virtual const char	*ParseFile( const char *data, char *token, int maxlen ) { return NULL; };
		virtual bool		CopyFile( const char *source, const char *destination ) { return false; };

		virtual void		ResetPVS( byte *pvs, int pvssize ) {};
		virtual void		AddOriginToPVS( const Vector &origin ) {};

		virtual void		SetAreaPortalState( int portalNumber, int isOpen ) {};

		virtual void		PlaybackTempEntity( IRecipientFilter& filter, float delay, const void *pSender, const SendTable *pST, int classID  ) {};
		virtual int			CheckHeadnodeVisible( int nodenum, const byte *pvs, int vissize ) { return 0; };
		virtual int			CheckAreasConnected( int area1, int area2 ) { return 0; };
		virtual int			GetArea( const Vector &origin ) { return 0; };
		virtual void		GetAreaBits( int area, unsigned char *bits, int buflen ) {};
		virtual bool		GetAreaPortalPlane( Vector const &vViewOrigin, int portalKey, VPlane *pPlane ) { return false; };

		virtual void		ApplyTerrainMod( TerrainModType type, CTerrainModParams const &params ) {};

		virtual bool		LoadGameState( char const *pMapName, bool createPlayers ) { return false; };
		virtual void		LoadAdjacentEnts( const char *pOldLevel, const char *pLandmarkName ) {};
		virtual void		ClearSaveDir() {};

		virtual const char*	GetMapEntitiesString() { return NULL; };

		virtual client_textmessage_t *TextMessageGet( const char *pName ) { return NULL; };

		virtual void		LogPrint( const char *msg ) {};

		virtual void		BuildEntityClusterList( edict_t *pEdict, PVSInfo_t *pPVSInfo ) {};

		virtual void SolidMoved( edict_t *pSolidEnt, ICollideable *pSolidCollide, const Vector* pPrevAbsOrigin ) {};
		virtual void TriggerMoved( edict_t *pTriggerEnt ) {};

		virtual ISpatialPartition *CreateSpatialPartition( const Vector& worldmin, const Vector& worldmax ) { return NULL; };
		virtual void 		DestroySpatialPartition( ISpatialPartition * ) {};

		virtual void		DrawMapToScratchPad( IScratchPad3D *pPad, unsigned long iFlags ) {};

		virtual const CBitVec<MAX_EDICTS>* GetEntityTransmitBitsForClient( int iClientIndex ) { return NULL; };

		virtual bool IsPaused() { return false; };

		virtual void		ForceExactFile( const char *s ) {};
		virtual void		ForceModelBounds( const char *s, const Vector &mins, const Vector &maxs ) {};
		virtual void		ClearSaveDirAfterClientLoad() {};

		virtual void SetFakeClientConVarValue( edict_t *pEntity, const char *cvar, const char *value ) {};
		
		virtual void InsertServerCommand( const char *str ) {};

		virtual void		ForceSimpleMaterial( const char *s ) {};

		virtual int			IsInCommentaryMode( void ) { return 0; };

		virtual void		SetAreaPortalStates( const int *portalNumbers, const int *isOpen, int nPortals ) {};

		virtual void		NotifyEdictFlagsChange( int iEdict ) {};

		virtual const CCheckTransmitInfo* GetPrevCheckTransmitInfo( edict_t *pPlayerEdict ) { return NULL; };
		
		virtual CSharedEdictChangeInfo* GetSharedEdictChangeInfo() { return NULL; };

		virtual void			AllowImmediateEdictReuse( ) {};

		virtual bool		IsInternalBuild( void ) { return false; };

		virtual IChangeInfoAccessor *GetChangeAccessor( const edict_t *pEdict ) { return NULL; };

		virtual QueryCvarCookie_t StartQueryCvarValue( edict_t *pPlayerEntity, const char *pName );
#elif SOURCE_ENGINE == SE_HL2DM || SOURCE_ENGINE == SE_TF2
		virtual void		ChangeLevel( const char *s1, const char *s2 ) {};

		virtual int			IsMapValid( const char *filename ) { return 0; };

		virtual bool		IsDedicatedServer( void ) { return false; };

		virtual int			IsInEditMode( void ) { return 0; };

		virtual int			PrecacheModel( const char *s, bool preload = false ) { return 0; };
		virtual int			PrecacheSentenceFile( const char *s, bool preload = false ) { return 0; };
		virtual int			PrecacheDecal( const char *name, bool preload = false ) { return 0; };
		virtual int			PrecacheGeneric( const char *s, bool preload = false ) { return 0; };

		virtual bool		IsModelPrecached( char const *s ) const { return false; };
		virtual bool		IsDecalPrecached( char const *s ) const { return false; };
		virtual bool		IsGenericPrecached( char const *s ) const { return false; };

		virtual int			GetClusterForOrigin( const Vector &org ) { return 0; };
		virtual int			GetPVSForCluster( int cluster, int outputpvslength, unsigned char *outputpvs ) { return 0; };
		virtual bool		CheckOriginInPVS( const Vector &org, const unsigned char *checkpvs, int checkpvssize ) { return false; };
		virtual bool		CheckBoxInPVS( const Vector &mins, const Vector &maxs, const unsigned char *checkpvs, int checkpvssize ) { return false; };

		virtual int			GetPlayerUserId( const edict_t *e ) { return 0; }; 
		virtual const char	*GetPlayerNetworkIDString( const edict_t *e ) { return NULL; };

		virtual int			GetEntityCount( void ) { return 0; };
		virtual int			IndexOfEdict( const edict_t *pEdict ) { return 0; };
		virtual edict_t		*PEntityOfEntIndex( int iEntIndex ) { return NULL; };

		virtual INetChannelInfo* GetPlayerNetInfo( int playerIndex ) { return NULL; };

		virtual edict_t		*CreateEdict( int iForceEdictIndex = -1 );
		virtual void		RemoveEdict( edict_t *e ) {};

		virtual void		*PvAllocEntPrivateData( long cb ) { return NULL; };
		virtual void		FreeEntPrivateData( void *pEntity ) {};

		virtual void		*SaveAllocMemory( size_t num, size_t size ) { return NULL; };
		virtual void		SaveFreeMemory( void *pSaveMem ) {};

		virtual void		EmitAmbientSound( int entindex, const Vector &pos, const char *samp, float vol, soundlevel_t soundlevel, int fFlags, int pitch, float delay = 0.0f ) {};

		virtual void        FadeClientVolume( const edict_t *pEdict, float fadePercent, float fadeOutSeconds, float holdTime, float fadeInSeconds ) {};

		virtual int			SentenceGroupPick( int groupIndex, char *name, int nameBufLen ) { return 0; };
		virtual int			SentenceGroupPickSequential( int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset ) { return 0; };
		virtual int			SentenceIndexFromName( const char *pSentenceName ){ return 0; };
		virtual const char *SentenceNameFromIndex( int sentenceIndex ) { return NULL; };
		virtual int			SentenceGroupIndexFromName( const char *pGroupName ) { return 0; };
		virtual const char *SentenceGroupNameFromIndex( int groupIndex ) { return NULL; };
		virtual float		SentenceLength( int sentenceIndex ) { return 0.0f; };

		virtual void		ServerCommand( const char *str ) {};
		virtual void		ServerExecute( void ) {};
		virtual void		ClientCommand( edict_t *pEdict, const char *szFmt, ... );

		virtual void		LightStyle( int style, const char *val ) {};

		virtual void		StaticDecal( const Vector &originInEntitySpace, int decalIndex, int entityIndex, int modelIndex, bool lowpriority ) {};

		virtual void		Message_DetermineMulticastRecipients( bool usepas, const Vector& origin, CBitVec< ABSOLUTE_PLAYER_LIMIT >& playerbits ) {};

		virtual bf_write	*EntityMessageBegin( int ent_index, ServerClass * ent_class, bool reliable ) { return NULL; };
		virtual bf_write	*UserMessageBegin( IRecipientFilter *filter, int msg_type ) { return NULL; };
		virtual void		MessageEnd( void ) {};

		virtual void		ClientPrintf( edict_t *pEdict, const char *szMsg );

		virtual void		Con_NPrintf( int pos, const char *fmt, ... ) {};
		virtual void		Con_NXPrintf( const struct con_nprint_s *info, const char *fmt, ... ) {};

		virtual void		SetView( const edict_t *pClient, const edict_t *pViewent ) {};

		virtual float		Time( void ) { return 0.0f; };

		virtual void		CrosshairAngle( const edict_t *pClient, float pitch, float yaw ) {};

		virtual void        GetGameDir( char *szGetGameDir, int maxlength ) {};

		virtual int 		CompareFileTime( const char *filename1, const char *filename2, int *iCompare ) { return 0; };

		virtual bool		LockNetworkStringTables( bool lock ) { return false; };

		virtual edict_t		*CreateFakeClient( const char *netname ) { return NULL; };

		virtual const char	*GetClientConVarValue( int clientIndex, const char *name ) { return NULL; };

		virtual const char	*ParseFile( const char *data, char *token, int maxlen ) { return NULL; };
		virtual bool		CopyFile( const char *source, const char *destination ) { return false; };

		virtual void		ResetPVS( byte *pvs, int pvssize ) {};
		virtual void		AddOriginToPVS( const Vector &origin ) {};

		virtual void		SetAreaPortalState( int portalNumber, int isOpen ) {};

		virtual void		PlaybackTempEntity( IRecipientFilter& filter, float delay, const void *pSender, const SendTable *pST, int classID  ) {};
		virtual int			CheckHeadnodeVisible( int nodenum, const byte *pvs, int vissize ) { return 0; };
		virtual int			CheckAreasConnected( int area1, int area2 ) { return 0; };
		virtual int			GetArea( const Vector &origin ) { return 0; };
		virtual void		GetAreaBits( int area, unsigned char *bits, int buflen ) {};
		virtual bool		GetAreaPortalPlane( Vector const &vViewOrigin, int portalKey, VPlane *pPlane ) { return false; };

		virtual bool		LoadGameState( char const *pMapName, bool createPlayers ){ return false; };
		virtual void		LoadAdjacentEnts( const char *pOldLevel, const char *pLandmarkName ) {};
		virtual void		ClearSaveDir() {};

		virtual const char*	GetMapEntitiesString() { return NULL; };

		virtual client_textmessage_t *TextMessageGet( const char *pName ) { return NULL; };

		virtual void		LogPrint( const char *msg ) {};

		virtual void		BuildEntityClusterList( edict_t *pEdict, PVSInfo_t *pPVSInfo ) {};

		virtual void SolidMoved( edict_t *pSolidEnt, ICollideable *pSolidCollide, const Vector* pPrevAbsOrigin, bool testSurroundingBoundsOnly ) {};
		virtual void TriggerMoved( edict_t *pTriggerEnt, bool testSurroundingBoundsOnly ) {};

		virtual ISpatialPartition *CreateSpatialPartition( const Vector& worldmin, const Vector& worldmax ) { return NULL; };
		virtual void 		DestroySpatialPartition( ISpatialPartition * ) {};

		virtual void		DrawMapToScratchPad( IScratchPad3D *pPad, unsigned long iFlags ) {};

		virtual const CBitVec<MAX_EDICTS>* GetEntityTransmitBitsForClient( int iClientIndex ) { return NULL; };

		virtual bool		IsPaused() { return false; };

		virtual void		ForceExactFile( const char *s ) {};
		virtual void		ForceModelBounds( const char *s, const Vector &mins, const Vector &maxs ) {};
		virtual void		ClearSaveDirAfterClientLoad() {};

		virtual void		SetFakeClientConVarValue( edict_t *pEntity, const char *cvar, const char *value ) {};

		virtual void		ForceSimpleMaterial( const char *s ) {};

		virtual int			IsInCommentaryMode( void ) { return 0; };

		virtual void		SetAreaPortalStates( const int *portalNumbers, const int *isOpen, int nPortals ) {};

		virtual void		NotifyEdictFlagsChange( int iEdict ) {};

		virtual const CCheckTransmitInfo* GetPrevCheckTransmitInfo( edict_t *pPlayerEdict ) { return NULL; };
		
		virtual CSharedEdictChangeInfo* GetSharedEdictChangeInfo() { return NULL; };

		virtual void			AllowImmediateEdictReuse( ) {};

		virtual bool		IsInternalBuild( void ) { return false; };

		virtual IChangeInfoAccessor *GetChangeAccessor( const edict_t *pEdict ) { return NULL; };	

		virtual char const *GetMostRecentlyLoadedFileName() { return NULL; };
		virtual char const *GetSaveFileName() { return NULL; };

		virtual void MultiplayerEndGame() {};
		virtual void ChangeTeam( const char *pTeamName ) {};

		virtual void CleanUpEntityClusterList( PVSInfo_t *pPVSInfo ) {};

		virtual void SetAchievementMgr( IAchievementMgr *pAchievementMgr ) {};
		virtual IAchievementMgr *GetAchievementMgr() { return NULL; };

		virtual int	GetAppID() { return 0; };
		
		virtual bool IsLowViolence() { return false; };

		virtual QueryCvarCookie_t StartQueryCvarValue( edict_t *pPlayerEntity, const char *pName );

		virtual void InsertServerCommand( const char *str ) {};

		virtual bool GetPlayerInfo( int ent_num, player_info_t *pinfo ) { return false; };

		virtual bool IsClientFullyAuthenticated( edict_t *pEdict ) { return false; };

		virtual void SetDedicatedServerBenchmarkMode( bool bBenchmarkMode ) {};

		virtual void SetGamestatsData( CGamestatsData *pGamestatsData ) {};
		virtual CGamestatsData *GetGamestatsData() { return NULL; };

		virtual const CSteamID	*GetClientSteamID( edict_t *pPlayerEdict ) { return NULL; };

		virtual const CSteamID	*GetGameServerSteamID() { return NULL; };

		virtual void ClientCommandKeyValues( edict_t *pEdict, KeyValues *pCommand ) {};

		virtual const CSteamID	*GetClientSteamIDByPlayerIndex( int entnum ) { return NULL; };
		virtual int GetClusterCount() { return 0; };
		virtual int GetAllClusterBounds( bbox_t *pBBoxList, int maxBBox ) { return 0; };

		virtual edict_t		*CreateFakeClientEx( const char *netname, bool bReportFakeClient = true ) { return NULL; };

		virtual int GetServerVersion() const { return 0; };

		virtual float GetServerTime() const { return 0.0f; };

		virtual IServer *GetIServer() { return NULL; };

		virtual bool IsPlayerNameLocked( const edict_t *pEdict ) { return false; };
		virtual bool CanPlayerChangeName( const edict_t *pEdict ) { return false; };

		virtual eFindMapResult FindMap( char *pMapName, int nMapNameMax ) { return eFindMap_Found; };
		
		virtual IReplaySystem *GetReplay() { return NULL; };
#else
#error Unsupported engine version
#endif
	};

	class FakeServerPluginHelpers : public IServerPluginHelpers
	{
	public:
		virtual void CreateMessage( edict_t *pEntity, DIALOG_TYPE type, KeyValues *data, IServerPluginCallbacks *plugin );
		virtual void ClientCommand( edict_t *pEntity, const char *cmd );

		virtual QueryCvarCookie_t StartQueryCvarValue( edict_t *pEntity, const char *pName );
	};
}

#endif // _OUTSOURCED_H_