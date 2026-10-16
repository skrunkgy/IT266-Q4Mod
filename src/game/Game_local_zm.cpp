// ANDREW: Making a separate file to do management of this stuff...
// If you see a lot of comments, I am doing this for self documentation or self mumbling, not because i used AI. no ai code will be used in this mod.
// formatting will also attempt to copy the codebase, despite my 

#include "../idlib/precompiled.h"

#pragma hdrstop

#include "Game_local.h"

void idGameLocal::InitZombiesGM() {
	zombieSpawnTimer = 0;
	round = 1;
	// player doesnt spawn yet, so we will have to do player init stuff some other place
}

// helper function that just spawns a zombie
void SpawnZombie(float a, float b)
{
	idPlayer*		player;
	trace_t			tr;
	idDict			dict;
	idEntity*		zombie;
	idVec3			origin;

	player = gameLocal.GetLocalPlayer();

	// for a random position
	float c = gameLocal.random.RandomFloat() * idMath::TWO_PI;
	float d = gameLocal.random.RandomFloat() * a + b;

	origin = player->GetPhysics()->GetOrigin();

	origin.x += idMath::Cos(c) * d;
	origin.y += idMath::Sin(c) * d;

	gameLocal.TracePoint(player, tr, origin + idVec3(0, 0, 1000), origin + idVec3(0, 0, -1000), MASK_ALL, NULL);

	dict.Set( "origin", tr.endpos.ToString() );
	
	// zombie monsters in this game come in "transfers". halfway stroggs. pretty cool!
	// however, monster_failed_transfer has a shotgun, which I would want to disable
	zombie = gameLocal.SpawnEntityDef("monster_failed_transfer", &dict);
	zombie->fl.isZombie = true; // NOTE: all flags by default are 0. check idEntity constructor for proof
}

void idGameLocal::ProcessZombiesGM() {
	// Printf( "Processing ZM!\n" );
	return;
}

void Cmd_TestSpawn( const idCmdArgs& args ) {
	
	if ( !gameLocal.CheatsOk( true ) ) {
		gameLocal.Printf( "Ermmmm you can't do that\n" );
		return;
	}
	
	SpawnZombie( atof(args.Argv(0)) , atof(args.Argv(1)) );
}

// we pass a pointer to the entity for some info perhaps?
void idGameLocal::OnZombieKilled( idEntity* killedZombie )
{
	GetLocalPlayer()->points += 50 * round;
	Printf("You now have %i points\n", GetLocalPlayer()->points);
}
