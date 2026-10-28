// ANDREW: Making a separate file to do management of this stuff...
// If you see a lot of comments, I am doing this for self documentation or self mumbling, not because i used AI. no ai code will be used in this mod.
// formatting will also attempt to copy the codebase, despite my personal preference


#include "../idlib/precompiled.h"
#include "game/Item.h"
#include "game/Player.h"
#include "game/gamesys/SysCmds.h"
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
	dict.SetInt( "health", 50 + gameLocal.GetRound() * 10 );

	// zombie monsters in this game come in "transfers". halfway stroggs. pretty cool!
	// however, monster_failed_transfer has a shotgun, which I would want to disable
	zombie = gameLocal.SpawnEntityDef("monster_slimy_transfer", &dict);
	zombie->fl.isZombie = true;
}

void idGameLocal::ProcessZombiesGM() {
	idPlayer* player;
	idPhysics_Player* physicsObj;

	// simple rounds calc
	maxRoundZombies = Min(2 + round, MAX_ZOMBIES);

	// process rounds
	if ( zombiesSpawned < maxRoundZombies && zmTimer <= gameLocal.time ) {
		SpawnZombie(75.f, 300.f);
		zmTimer = gameLocal.time + 1000;
		zombiesSpawned++;
	}
	else if ( zombiesSpawned >= maxRoundZombies ) {		// 
		bool zombiesAlive = false;
		for (int i = 0; i < MAX_GENTITIES; i++) {
			if ( entities[i] && entities[i]->fl.isZombie && !static_cast<idAI*>(entities[i])->aifl.dead ) {
				zombiesAlive = true;
			}
		}
		if ( !zombiesAlive ) {
			Printf("New Round!\n");
			zombiesSpawned = 0;
			zmTimer = gameLocal.time + 3000;
			round++;
			GetLocalPlayer()->UpdateZMHud();
		}
	}
}

void Cmd_TestSpawn( const idCmdArgs& args ) {
	SpawnZombie( atof(args.Argv(0)) , atof(args.Argv(1)) );
}

// buy a weapon, or refill it's ammo
void Cmd_BuyWeapon( const idCmdArgs &args ) {

	// forgive me father, but i will program this all manually. super duper fucking inefficient, use a def file, but im crunching
	idDict weapons_points;
	weapons_points.SetInt("shotgun", 450); // krm-262
	weapons_points.SetInt("machinegun", 640); // hvk-30
	weapons_points.SetInt("rocketlauncher", 1000); // xm-53
	weapons_points.SetInt("nailgun", 1300); // BRM
	weapons_points.SetInt("hyperblaster", 3000); // diy-11 rennovator
	// other 5 will not be accessed, maybe ill program them and do give all
	

	if (args.Argc() != 2) {
		gameLocal.Printf("Invalid args...\n");
		return;
	}
	if ( !weapons_points.FindKey(args.Argv(1)) ) {
		gameLocal.Printf("Not a purchasable weapon...");
		return;
	}
	else if ( gameLocal.GetLocalPlayer()->points < weapons_points.GetInt(args.Argv(1)) ) {
		gameLocal.Printf("You do not have enough points! That costs %i points\n", weapons_points.GetInt(args.Argv(1)));
		return;
	}

	// again, double
	cmdSystem->BufferCommandText(CMD_EXEC_NOW, va("give weapon_%s", args.Argv(1)));
	gameLocal.GetLocalPlayer()->points -= weapons_points.GetInt(args.Argv(1));
	gameLocal.Printf("Player now has %i points\n", gameLocal.GetLocalPlayer()->points);

	gameLocal.GetLocalPlayer()->UpdateZMHud();

	weapons_points.Clear();
}

// perky

// probably better to define it on top, no time to care
bool CheckPoints(int cost) {
	if (gameLocal.GetLocalPlayer()->points < cost) {
		gameLocal.Printf("Not enough points. That costs %i points\n", cost);
		return false;
	}
	
	gameLocal.GetLocalPlayer()->points -= cost;
	gameLocal.Printf("Player now has %i points\n", gameLocal.GetLocalPlayer()->points);

	gameLocal.GetLocalPlayer()->UpdateZMHud();

	return true;
}

void Cmd_BuyPerk( const idCmdArgs &args ) {

	// to easily change it later
	const int perk_points[] = {
		1000,
		1000,
		1500,
		3000,
		5000
	};

	idPlayer* player = gameLocal.GetLocalPlayer();

	if (args.Argc() != 2) {
		gameLocal.Printf("Not enough args...\n");
		return;
	}
	
	// again, forgive me
	if ( !strcmp( "speed", args.Argv(1) ) && CheckPoints(perk_points[0] ) ) {
		player->perkfl.speedCola = 1;
		player->UpdateZMHud();
		return;
	}
	else if ( !strcmp( "jump", args.Argv(1) ) && CheckPoints(perk_points[1] ) ) {
		player->perkfl.superJump = 1;
		player->UpdateZMHud();
		return;
	}
	else if ( !strcmp( "juggernaug", args.Argv(1) ) && CheckPoints(perk_points[2] ) ) {
		// extra boost
		player->inventory.maxHealth = 150;
		player->health = 150;

		player->perkfl.juggernaut = 1;

		// update hud
		player->UpdateZMHud();
		return;
	}
	else if ( !strcmp( "strength", args.Argv(1) ) && CheckPoints(perk_points[3] ) ) {
		player->perkfl.dmgBoost = 1;
		player->UpdateZMHud();
		return;
	}
	else if ( !strcmp( "secondlife", args.Argv(1) ) && CheckPoints(perk_points[4] ) ) {
		player->perkfl.secondLife = 1;
		player->UpdateZMHud();
		return;
	}

	gameLocal.Printf("Perk not found...\n");
	return;
}

// fuck it we ball
class Kaboom : public idItem {
public:
	CLASS_PROTOTYPE( Kaboom );

	Kaboom();

	bool			Pickup( idPlayer *player );
};

CLASS_DECLARATION( idItem, Kaboom )
END_CLASS

Kaboom::Kaboom() : idItem() {}

bool Kaboom::Pickup( idPlayer *player ) {

	for (int i = 0; i < MAX_GENTITIES; i++) {
		idEntity* et = gameLocal.entities[i];
		if ( et && et->fl.isZombie ) {
			et->PostEventMS( &EV_Remove, 0 );
		}
	}

	trigger->SetContents( 0 );
	PostEventMS( &EV_Remove, 0 );
	return 0;
}


// we pass a pointer to the entity for some info perhaps?
void idGameLocal::OnZombieKilled( idEntity* killedZombie ) {
	GetLocalPlayer()->points += 50 + round * 25; // CHANGE FOR DEMO
	Printf("You now have %i points\n", GetLocalPlayer()->points);

	// where we may drop something... we will do kaboom
	if ( random.RandomFloat() > .6 ) {
		idItem* drop;
		idDict spawnArgs;

		spawnArgs = *FindEntityDefDict("powerup_quad_damage");
		spawnArgs.Set("origin", killedZombie->GetPhysics()->GetOrigin().ToString());

		gameLocal.SpawnEntityType(Kaboom::GetClassType(), &spawnArgs);
	}
	GetLocalPlayer()->UpdateZMHud();
}

// where we will update things for our main hud
void idPlayer::UpdateZMHud() {

	idUserInterface* hud = uiManager->FindGuiByIndex(0);
	if (hud) {
		hud->SetStateString("zm_round", va( "Round: %i", gameLocal.GetRound() ) );
		hud->SetStateString("zm_points", va( "Points: %i", points ) );

		hud->SetStateString("zm_perk1", va( "%i", perkfl.speedCola ) );
		hud->SetStateString("zm_perk2", va( "%i", perkfl.superJump ) );
		hud->SetStateString("zm_perk3", va( "%i", perkfl.juggernaut ) );
		hud->SetStateString("zm_perk4", va( "%i", perkfl.dmgBoost ) );
		hud->SetStateString("zm_perk5", va( "%i", perkfl.secondLife ) );
	}

	UpdateHud();
}

void Cmd_BuyAll( const idCmdArgs &args ) {
	gameLocal.GetLocalPlayer()->points = 9999999;

	memset(&gameLocal.GetLocalPlayer()->perkfl, 0xFF, 1);
	gameLocal.GetLocalPlayer()->inventory.maxHealth = 150;
	gameLocal.GetLocalPlayer()->health = 150;

	cmdSystem->BufferCommandText(CMD_EXEC_NOW, "give weapon_shotgun");
	cmdSystem->BufferCommandText(CMD_EXEC_NOW, "give weapon_machinegun");
	cmdSystem->BufferCommandText(CMD_EXEC_NOW, "give weapon_rocketlauncher");
	cmdSystem->BufferCommandText(CMD_EXEC_NOW, "give weapon_nailgun");
	cmdSystem->BufferCommandText(CMD_EXEC_NOW, "give weapon_hyperblaster");

	gameLocal.GetLocalPlayer()->UpdateZMHud();
}

// Test ui stuff
void Cmd_TestUI( const idCmdArgs &args ) {
	gameLocal.GetLocalPlayer()->UpdateZMHud();
}
