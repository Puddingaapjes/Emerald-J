OldaleTown_PlayerHouse_2F_MapScripts::
	.byte 0

OldaleTown_PlayerHouse_2F_RunningShoes::
	lockall
	setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_1
	setflag FLAG_HIDE_LITTLEROOT_TOWN_PLAYERS_HOUSE_VIGOROTH_2
	msgbox PlayerHouse_Text_Box, MSGBOX_DEFAULT
	closemessage
    call_if_unset FLAG_RECEIVED_RUNNING_SHOES, PlayerHouse_EventScript_GiveRunningShoes
	msgbox PlayerHouse_Text_Box_Empty, MSGBOX_DEFAULT
	closemessage
	release
	end	
	
PlayerHouse_EventScript_GiveRunningShoes::
	msgbox PlayerHouse_Text_ObtainedRunningShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitmessage
	message PlayerHouse_Text_SwitchShoesWithRunningShoes
	waitfanfare
	setflag FLAG_RECEIVED_RUNNING_SHOES
	waitmessage
	delay 30
	msgbox PlayerHouse_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	closemessage
	delay 30
	goto PlayerHouse_EventScript_SetReceivedRunningShoes

PlayerHouse_EventScript_SetReceivedRunningShoes::
	setflag FLAG_SYS_B_DASH
	setvar VAR_OLDALE_TOWN_STATE, 3
	release
	end


PlayerHouse_Text_Box:
	.string "Let's see what is in the box!$"

PlayerHouse_Text_Box_Empty::
	.string "The box is empty.$"	

PlayerHouse_Text_ObtainedRunningShoes:
	.string "Obtained running shoes!$"

PlayerHouse_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

PlayerHouse_Text_ExplainRunningShoes:
	.string "“Press the B Button while wearing these\n"
	.string "RUNNING SHOES to run extra-fast!\p"
	.string "“Slip on these RUNNING SHOES and race\n"
	.string "in the great outdoors!”$"
