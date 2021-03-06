#include <nan.h>
#include "../CGALib/gameinterface.h"

using namespace v8;

CGA::CGAInterface *g_CGAInterface = NULL;

#include "connect.h"
#include "info.h"
#include "item.h"
#include "map.h"
#include "npc.h"
#include "work.h"
#include "chat.h"

void LogBack(const Nan::FunctionCallbackInfo<v8::Value>& info) 
{
	Isolate* isolate = info.GetIsolate();
	HandleScope handle_scope(isolate);
	
	if (!g_CGAInterface->LogBack())
	{
		Nan::ThrowError("RPC Invocation failed.");
		return;
	}
}

void LogOut(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	Isolate* isolate = info.GetIsolate();
	HandleScope handle_scope(isolate);

	if (!g_CGAInterface->LogOut())
	{
		Nan::ThrowError("RPC Invocation failed.");
		return;
	}
}

void SayWords(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	Isolate* isolate = info.GetIsolate();
	HandleScope handle_scope(isolate);

	if (info.Length() < 1 || !info[0]->IsString()) {
		Nan::ThrowTypeError("Arg[0] must be string.");
		return;
	}
	if (info.Length() < 2) {
		Nan::ThrowTypeError("Arg[1] must be color.");
		return;
	}
	if (info.Length() < 3) {
		Nan::ThrowTypeError("Arg[2] must be range.");
		return;
	}
	if (info.Length() < 4) {
		Nan::ThrowTypeError("Arg[3] must be size.");
		return;
	}

	v8::String::Utf8Value str(info[0]->ToString());
	int color = (int)info[1]->IntegerValue();
	int range = (int)info[2]->IntegerValue();
	int size = (int)info[3]->IntegerValue();

	std::string sstr(*str);
	if (!g_CGAInterface->SayWords(sstr, color, range, size))
	{
		Nan::ThrowError("RPC Invocation failed.");
		return;
	}

	info.GetReturnValue().Set(true);
}

void Init(v8::Local<v8::Object> exports) {
	g_CGAInterface = CGA::CreateInterface();

	exports->Set(Nan::New("Connect").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(Connect)->GetFunction());
	exports->Set(Nan::New("AsyncConnect").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncConnect)->GetFunction());
	exports->Set(Nan::New("IsInGame").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(IsInGame)->GetFunction());
	exports->Set(Nan::New("GetWorldStatus").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetWorldStatus)->GetFunction());
	exports->Set(Nan::New("GetGameStatus").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetGameStatus)->GetFunction());
	exports->Set(Nan::New("GetPlayerInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetPlayerInfo)->GetFunction());
	exports->Set(Nan::New("SetPlayerFlagEnabled").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(SetPlayerFlagEnabled)->GetFunction());
	exports->Set(Nan::New("IsPlayerFlagEnabled").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(IsPlayerFlagEnabled)->GetFunction());
	exports->Set(Nan::New("IsSkillValid").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(IsSkillValid)->GetFunction());
	exports->Set(Nan::New("GetSkillInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetSkillInfo)->GetFunction());
	exports->Set(Nan::New("GetSkillsInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetSkillsInfo)->GetFunction());
	exports->Set(Nan::New("GetSubSkillInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetSubSkillInfo)->GetFunction());
	exports->Set(Nan::New("GetSubSkillsInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetSubSkillsInfo)->GetFunction());
	exports->Set(Nan::New("IsItemValid").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(IsItemValid)->GetFunction());
	exports->Set(Nan::New("GetItemInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetItemInfo)->GetFunction());
	exports->Set(Nan::New("GetItemsInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetItemsInfo)->GetFunction());
	exports->Set(Nan::New("GetBankItemsInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetBankItemsInfo)->GetFunction());
	exports->Set(Nan::New("IsPetValid").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(IsPetValid)->GetFunction());
	exports->Set(Nan::New("GetPetInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetPetInfo)->GetFunction());
	exports->Set(Nan::New("GetPetsInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetPetsInfo)->GetFunction());
	exports->Set(Nan::New("IsPetSkillValid").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(IsPetSkillValid)->GetFunction());
	exports->Set(Nan::New("GetPetSkillInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetPetSkillInfo)->GetFunction());
	exports->Set(Nan::New("GetPetSkillsInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetPetSkillsInfo)->GetFunction());	
	exports->Set(Nan::New("GetMapXY").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetMapXY)->GetFunction());
	exports->Set(Nan::New("GetMapXYFloat").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetMapXYFloat)->GetFunction());
	exports->Set(Nan::New("GetMapName").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetMapName)->GetFunction());
	exports->Set(Nan::New("GetMapUnits").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetMapUnits)->GetFunction());
	exports->Set(Nan::New("WalkTo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(WalkTo)->GetFunction());
	exports->Set(Nan::New("TurnTo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(TurnTo)->GetFunction());
	exports->Set(Nan::New("ForceMove").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(ForceMove)->GetFunction());
	exports->Set(Nan::New("ForceMoveTo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(ForceMoveTo)->GetFunction());
	exports->Set(Nan::New("IsMapCellPassable").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(IsMapCellPassable)->GetFunction());
	exports->Set(Nan::New("AsyncWalkTo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncWalkTo)->GetFunction());
	exports->Set(Nan::New("AsyncWaitMovement").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncWaitMovement)->GetFunction());
	exports->Set(Nan::New("LogBack").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(LogBack)->GetFunction());
	exports->Set(Nan::New("LogOut").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(LogOut)->GetFunction());
	exports->Set(Nan::New("DropItem").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(DropItem)->GetFunction());
	exports->Set(Nan::New("UseItem").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(UseItem)->GetFunction());
	exports->Set(Nan::New("MoveItem").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(MoveItem)->GetFunction());
	exports->Set(Nan::New("AsyncWaitPlayerMenu").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncWaitPlayerMenu)->GetFunction());
	exports->Set(Nan::New("AsyncWaitUnitMenu").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncWaitUnitMenu)->GetFunction());
	exports->Set(Nan::New("PlayerMenuSelect").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(PlayerMenuSelect)->GetFunction());
	exports->Set(Nan::New("UnitMenuSelect").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(UnitMenuSelect)->GetFunction());
	exports->Set(Nan::New("AsyncWaitNPCDialog").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncWaitNPCDialog)->GetFunction());	
	exports->Set(Nan::New("ClickNPCDialog").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(ClickNPCDialog)->GetFunction());
	exports->Set(Nan::New("SellNPCStore").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(SellNPCStore)->GetFunction());
	exports->Set(Nan::New("BuyNPCStore").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(BuyNPCStore)->GetFunction());
	exports->Set(Nan::New("SayWords").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(SayWords)->GetFunction());
	exports->Set(Nan::New("AsyncWaitWorkingResult").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncWaitWorkingResult)->GetFunction());
	exports->Set(Nan::New("StartWork").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(StartWork)->GetFunction());
	exports->Set(Nan::New("CraftItem").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(CraftItem)->GetFunction());
	exports->Set(Nan::New("AssessItem").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AssessItem)->GetFunction());
	exports->Set(Nan::New("GetCraftInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetCraftInfo)->GetFunction());
	exports->Set(Nan::New("GetCraftsInfo").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(GetCraftsInfo)->GetFunction());
	exports->Set(Nan::New("AsyncWaitChatMsg").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(AsyncWaitChatMsg)->GetFunction());	
}

NODE_MODULE(node_cga, Init)
