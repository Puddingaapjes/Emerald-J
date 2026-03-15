OldaleTown_PlayerHouse_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, OldaleTown_PlayerHouse_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PlayerHouse_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OldaleTown_PlayerHouse_OnFrame
	.byte 0

OldaleTown_PlayerHouse_OnLoad:
	call_if_lt VAR_OLDALE_TOWN_STATE, 1, OldaleTown_PlayerHouse_EventScript_SetMovingBoxes
	end

OldaleTown_PlayerHouse_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return


OldaleTown_PlayerHouse_OnTransition:
	call_if_eq VAR_OLDALE_TOWN_STATE, 1, OldaleTown_PlayerHouse_EventScript_MoveMomToDoor
	call_if_eq VAR_OLDALE_TOWN_STATE, 2, OldaleTown_PlayerHouse_EventScript_MoveMomToTable
	call_if_eq VAR_OLDALE_TOWN_STATE, 3, OldaleTown_PlayerHouse_EventScript_MoveDadToDoor
	end

OldaleTown_PlayerHouse_EventScript_MoveDadToDoor::
	setobjectxyperm LOCALID_DAD, 8, 8
	setobjectmovementtype LOCALID_DAD, MOVEMENT_TYPE_FACE_UP
	return

OldaleTown_PlayerHouse_EventScript_MoveMomToTable::
	setobjectxyperm LOCALID_MOM, 2, 6
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_RIGHT
	return

OldaleTown_PlayerHouse_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_MOM, 9, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

OldaleTown_PlayerHouse_OnFrame:
	map_script_2 VAR_OLDALE_TOWN_STATE, 1, OldaleTown_PlayerHouse_EventScript_EnterHouseMovingIn
	map_script_2 VAR_OLDALE_TOWN_STATE, 3, OldaleTown_PlayerHouse_EventScript_GetStarter
	.2byte 0



OldaleTown_PlayerHouse_EventScript_EnterHouseMovingIn::
	lockall
	msgbox PlayerHouse_Text_IsntItNiceInHere, MSGBOX_DEFAULT
	applymovement LOCALID_MOM, Common_Movement_FacePlayer
	waitmovement 0
	msgbox PlayerHouse_Text_GoUpstairs, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OLDALE_TOWN_STATE, 2
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	releaseall
	end

OldaleTown_PlayerHouse_Movement_DadWalkIn:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_PlayerHouse_Movement_DadWalkOut:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldaleTown_PlayerHouse_EventScript_Mom::
	lock
	faceplayer
	msgbox PlayerHouse_Text_IsntItNiceInHere, MSGBOX_DEFAULT
	release
	end

OldaleTown_PlayerHouse_EventScript_GetStarter::
	playse SE_EXIT
	delay 10
	addobject LOCALID_DAD
	delay 30
	playse SE_PIN
	applymovement LOCALID_DAD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_DAD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_DAD, OldaleTown_PlayerHouse_Movement_DadWalkIn
	waitmovement 0
	msgbox PlayerHouse_Text_HeyKid, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_HIDE_PLAYERHOUSE_BOX
	fadescreen FADE_TO_BLACK
	setvar VAR_OLDALE_TOWN_STATE, 4
	callnative StartNewPokeballCaseUI
	waitstate
	fadedefaultbgm
	MSGBOX PlayerHouse_Text_MeetBirch, MSGBOX_DEFAULT
	waitmessage
	closemessage
	applymovement LOCALID_DAD, OldaleTown_PlayerHouse_Movement_DadWalkOut
	waitmovement 0
	playse SE_EXIT
	delay 10
	removeobject LOCALID_DAD
	end



OldaleTown_PlayerHouse_EventScript_GoOpenBox::
	lockall
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox PlayerHouse_Text_OpenBox, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	closemessage
	waitmovement 0
	releaseall
	end

PlayerHouse_Text_OpenBox:
	.string "MOM: Oh! Did you find the box?\n"
	.string "Go open it up and see what's inside!$"

PlayerHouse_Text_HeyKid:
	.string "DAD: Hey, kid! Settled in?\n"
	.string "Now that you're ready for your adventure,\l"
	.string "let's get you a POKéMON partner!$"

PlayerHouse_Text_MeetBirch:
	.string "DAD: Oh, by the way, I have a friend\n"
	.string "who's a POKéMON PROFESSOR.\p"
	.string "PROF. BIRCH is his name.\n"
	.string "He lives right next door, so you should\l"
	.string "go over and introduce yourself.\p"
	.string "He will give you a Pokedex\n"
	.string "and some pokeballs!\p"
	.string "I have to get back to the League,\n"
	.string "but I'll see you around, kid!$"

PlayerHouse_Text_IsntItNiceInHere:
	.string "MOM: See, {PLAYER}?\n"
	.string "Isn't it nice in here, too?$"

PlayerHouse_Text_GoUpstairs:
	.string "The mover's POKéMON do all the work\n"
	.string "of moving us in and cleaning up after.\l"
	.string "This is so convenient!\p"
	.string "{PLAYER}, your room is upstairs.\n"
	.string "Go check it out, dear!\p"
	.string "You can find some fresh clothes in\n"
	.string "the wardrobe.\p"
	.string "Also there is a surprise in the box,\n"
	.string "then you can go explore the region$"

PlayerHouse_Text_ArentYouInterestedInRoom:
	.string "MOM: Well, {PLAYER}?\p"
	.string "Aren't you interested in seeing your\n"
	.string "very own room?$"

PlayerHouse_Text_GoSetTheClock:
	.string "MOM: {PLAYER}.\p"
	.string "Go set the clock in your room, honey.$"

PlayerHouse_Text_OhComeQuickly:
	.string "MOM: Oh! {PLAYER}, {PLAYER}!\n"
	.string "Quick! Come quickly!$"

PlayerHouse_Text_MaybeDadWillBeOn:
	.string "MOM: Look! It's PETALBURG GYM!\n"
	.string "Maybe DAD will be on!$"

PlayerHouse_Text_ItsOverWeMissedHim:
	.string "MOM: Oh… It's over.\p"
	.string "I think DAD was on, but we missed him.\n"
	.string "Too bad.$"

PlayerHouse_Text_GoIntroduceYourselfNextDoor:
	.string "Oh, yes.\n"
	.string "One of DAD's friends lives in town.\p"
	.string "PROF. BIRCH is his name.\p"
	.string "He lives right next door, so you should\n"
	.string "go over and introduce yourself.$"

PlayerHouse_Text_SeeYouHoney:
	.string "MOM: See you, honey!$"

PlayerHouse_Text_DidYouMeetProfBirch:
	.string "MOM: Did you introduce yourself to\n"
	.string "PROF. BIRCH?$"

PlayerHouse_Text_YouShouldRestABit:
	.string "MOM: How are you doing, {PLAYER}?\n"
	.string "You look a little tired.\p"
	.string "I think you should rest a bit.$"

PlayerHouse_Text_TakeCareHoney:
	.string "MOM: Take care, honey!$"

PlayerHouse_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "MOM: Oh? Did DAD give you that BADGE?\p"
	.string "Then here's something from your MOM!$"

PlayerHouse_Text_DontPushYourselfTooHard:
	.string "Don't push yourself too hard, dear.\n"
	.string "You can always come home.\p"
	.string "Go for it, honey!$"

PlayerHouse_Text_IsThatAPokenav:
	.string "MOM: What is that, honey? A POKéNAV?\n"
	.string "Someone from DEVON gave it to you?\p"
	.string "Well, honey, how about registering\n"
	.string "your mom?\p"
	.string "… … …$"

PlayerHouse_Text_RegisteredMom:
	.string "Registered MOM\n"
	.string "in the POKéNAV.$"

PlayerHouse_Text_Vigoroth1:
	.string "Fugiiiiih!$"

PlayerHouse_Text_Vigoroth2:
	.string "Huggoh, uggo uggo…$"

PlayerHouse_Text_ReportFromPetalburgGym:
	.string "INTERVIEWER: …We brought you this\n"
	.string "report from in front of PETALBURG GYM.$"

PlayerHouse_Text_TheresAMovieOnTV:
	.string "There is a movie on TV.\p"
	.string "Two men are dancing on a big piano\n"
	.string "keyboard.\p"
	.string "Better get going!$"

PlayerHouse_Text_RunningShoesManual:
	.string "It's the instruction booklet for the\n"
	.string "RUNNING SHOES.\p"
	.string "“Press the B Button to run while\n"
	.string "wearing your RUNNING SHOES.\p"
	.string "“Lace up your RUNNING SHOES and hit\n"
	.string "the road running!”$"

PlayerHouse_Text_TicketFromBrineyCameForYou:
	.string "DAD: Hm?\p"
	.string "Hey, it's {PLAYER}!\p"
	.string "It's been a while since I saw you,\n"
	.string "but you look…stronger, somehow.\p"
	.string "That's the impression I get.\n"
	.string "But your old man hasn't given up yet!\p"
	.string "Oh, yes, I have something for you.\n"
	.string "This came to you from someone named\l"
	.string "MR. BRINEY.$"

PlayerHouse_Text_PortsInSlateportLilycove:
	.string "DAD: Hm, a TICKET for a ferry?\p"
	.string "If I recall, there are ferry ports in\n"
	.string "SLATEPORT and LILYCOVE.$"

PlayerHouse_Text_BetterGetBackToGym:
	.string "I'd better get back to PETALBURG GYM.\p"
	.string "MOM, thanks for looking after the house\n"
	.string "while I'm away.$"

PlayerHouse_Text_DadShouldStayLonger:
	.string "MOM: That DAD of yours…\p"
	.string "He comes home for the first time in a\n"
	.string "while, but all he talks about is POKéMON.\p"
	.string "He should relax and stay a little longer.$"

PlayerHouse_Text_IsThatABreakingStory:
	.string "MOM: Is that a breaking news story?$"

PlayerHouse_Text_LatiEmergencyNewsFlash:
	.string "We bring you this emergency\n"
	.string "news flash!\p"
	.string "In various HOENN locales, there have\n"
	.string "been reports of a BZZT…colored\l"
	.string "POKéMON in flight.\p"
	.string "The identity of this POKéMON is\n"
	.string "currently unknown.\p"
	.string "We now return you to the regular\n"
	.string "movie program.$"

PlayerHouse_Text_WhatColorDidTheySay:
	.string "MOM: {PLAYER}, did you catch that?\p"
	.string "What color did the announcer say\n"
	.string "that POKéMON was?$"

PlayerHouse_Text_StillUnknownPokemon:
	.string "MOM: Well, isn't that something!\n"
	.string "There are still unknown POKéMON.$"
