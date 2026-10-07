// ANDREW: Making a separate file to do management of this stuff...
// If you see a lot of comments, I am doing this for self documentation or self mumbling, not because i used AI. no ai code will be used in this mod.
// formatting will also attempt to copy the codebase, despite my 

#include "../idlib/precompiled.h"

#pragma hdrstop

#include "Game_local.h"

void idGameLocal::InitZombiesGM() {
	zombieSpawnTimer = 0;
	// player doesnt spawn yet, so we will have to do player init stuff some other place
}

void idGameLocal::ProcessZombiesGM() {
	// Printf( "Processing ZM!\n" );
	return;
}

void Cmd_TestSpawn( const idCmdArgs& args ) {
	idPlayer*		player;
	trace_t			tr;
	idDict			dict;
	idEntity*		zombie;
	idVec3			origin;

	player = gameLocal.GetLocalPlayer();
	
	if ( !player || !gameLocal.CheatsOk( false ) ) {
		gameLocal.Printf( "Ermmmm you can't do that\n" );
		return;
	}
	
	// begin getting a spawn radius

	// for a random position
	float a = gameLocal.random.RandomFloat() * idMath::TWO_PI;
	float b = gameLocal.random.RandomFloat() * 100.f;

	origin = player->GetPhysics()->GetOrigin();

	origin.x += idMath::Cos(a) * b;
	origin.y += idMath::Sin(a) * b;

	gameLocal.TracePoint(player, tr, origin + idVec3(0, 0, idMath::INFINITY), origin + idVec3(0, 0, -idMath::INFINITY), MASK_ALL, NULL);

	gameLocal.Printf("Spawned zombie at %s. \n", tr.endpos.ToString());
	gameLocal.Printf("player is at %s\n", player->GetPhysics()->GetOrigin().ToString());

	dict.Set( "origin", tr.endpos.ToString() );
	
	// zombie monsters in this game come in "transfers". halfway stroggs. pretty cool!
	// however, monster_failed_transfer has a shotgun, which I would want to disable
	zombie = gameLocal.SpawnEntityDef("monster_slimy_transfer", &dict);
	zombie->fl.isZombie = true; // NOTE: all flags by default are 0. check idEntity constructor for proof

	// NOTE: zombies are inserted into the entities list!

}
