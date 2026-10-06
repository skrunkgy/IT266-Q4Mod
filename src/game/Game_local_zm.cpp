// ANDREW: Making a separate file to do management of this stuff...
// If you see a lot of comments, I am doing this for self documentation or self mumbling, not because i used AI. no ai code will be used in this mod.
// formatting will also attempt to copy the codebase, despite my 

#include "../idlib/precompiled.h"
#include "../idlib/CmdArgs.h"

#pragma hdrstop

#include "Game_local.h"

void idGameLocal::ProcessZombiesGM() {
	// Printf( "Processing ZM!\n" );
	return;
}

void Cmd_TestSpawn( const idCmdArgs& args ) {
	idPlayer*		player;
	idDict			dict;
	idEntity*		zombie;
	
	player = gameLocal.GetLocalPlayer();
	
	if ( !player || gameLocal.CheatsOk( false ) ) {
		gameLocal.Printf( "Ermmmm you can't do dat\n" );
		return;
	}
	
	dict.Set( "origin", player->GetPhysics()->GetOrigin().ToString() );

	zombie = gameLocal.SpawnEntityDef("monster_strogg_marine", &dict);

}
