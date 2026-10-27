// ANDREW: Making a separate file to do management of this stuff...
// If you see a lot of comments, I am doing this for self documentation or self mumbling, not because i used AI. no ai code will be used in this mod.
// formatting will also attempt to copy the codebase, despite my personal preference


#include "../idlib/precompiled.h"
#include "game/Item.h"
#include "game/Player.h"
#include "game/gamesys/SysCvar.h"
#include "game/physics/Physics.h"
#include "idlib/math/Math.h"
#include "ui/UserInterface.h"

#pragma hdrstop

#include "Game_local.h"
#include "ai/AI.h"

void idGameLocal::InitZombiesGM() {
	zmTimer = gameLocal.time;
	round = 1;
	maxRoundZombies = 1;
	zombiesSpawned = 0;
}

// helper function that just spawns a zombie
void SpawnZombie(float a, float b) {
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
	zombie = gameLocal.SpawnEntityDef("monster_slimy_transfer", &dict);
	zombie->fl.isZombie = true;
}

void idGameLocal::ProcessZombiesGM() {
	idPlayer* player;
	idPhysics_Player* physicsObj;

	// simple rounds calc
	maxRoundZombies = Min(round, MAX_ZOMBIES);

	// process rounds
	if ( zombiesSpawned < maxRoundZombies && zmTimer <= gameLocal.time ) {
		SpawnZombie(100.f, 10.f);
		zmTimer = gameLocal.time + 1500;
		zombiesSpawned++;
	}
	else if ( zombiesSpawned >= maxRoundZombies ) {		// 
		bool zombiesAlive = false;
		for (int i = 0; i < MAX_GENTITIES; i++) {
			if ( entities[i] && entities[i]->fl.isZombie ) {
				zombiesAlive = true;
			}
		}
		if ( !zombiesAlive ) {
			Printf("New Round!\n");
			zombiesSpawned = 0;
			zmTimer = gameLocal.time;
			round++;
		}
	}

}

// make sure to do a random chance here too, but disable it for presentation
void idAI::DropPowerup() {
	idItemPowerup* item;

}

void Cmd_TestSpawn( const idCmdArgs& args ) {
	SpawnZombie( atof(args.Argv(0)) , atof(args.Argv(1)) );
}

// buy a weapon, or refill it's ammo
void Cmd_BuyWeapon( const idCmdArgs &args ) {

}

// perky
void Cmd_BuyPerk( const idCmdArgs &args ) {
	idPlayer* player = gameLocal.GetLocalPlayer();

	// extra boost
	player->inventory.maxHealth = 150;
	player->health = 150;

	// update hud
	player->UpdateHud();

	// set perk flags
	memset(&player->perkfl, 0xFF, 1);
}

// we pass a pointer to the entity for some info perhaps?
void idGameLocal::OnZombieKilled( idEntity* killedZombie ) {
	GetLocalPlayer()->points += 50 * round;
	Printf("You now have %i points\n", GetLocalPlayer()->points);
}

void Cmd_BuyAll( const idCmdArgs &args )
{

}

// Test ui stuff
void Cmd_TestUI( const idCmdArgs &args ) {
	idPlayer* player = gameLocal.GetLocalPlayer();
	idUserInterface* hud = player->GetHud();
}
