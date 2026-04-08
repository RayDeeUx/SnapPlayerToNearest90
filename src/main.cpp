#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

bool enabled = true;
bool snapOnJumpPad = false;
bool snapOnJumpOrb = false;

bool ignoreYellowOrb = false;
bool ignorePinkOrb = false;
bool ignoreBlueOrb = false;
bool ignoreGreenOrb = false;
bool ignoreBlackOrb = false;
bool ignoreRedOrb = false;
bool ignoreGreenDashOrb = false;
bool ignorePinkDashOrb = false;
bool ignoreSpiderOrb = false;
bool ignoreCustomOrb = false;
bool ignoreTeleportOrb = false;

bool ignoreYellowPad = false;
bool ignorePinkPad = false;
bool ignoreBluePad = false;
bool ignoreRedPad = false;
bool ignoreSpiderPad = false;

$on_mod(Loaded) {
	enabled = Mod::get()->getSettingValue<bool>("enabled");
	listenForSettingChanges<bool>("enabled", [](const bool newEnabled) { enabled = newEnabled; });

	snapOnJumpPad = Mod::get()->getSettingValue<bool>("snapOnJumpPad");
	listenForSettingChanges<bool>("snapOnJumpPad", [](const bool newSnapOnJumpPad) { snapOnJumpPad = newSnapOnJumpPad; });

	snapOnJumpOrb = Mod::get()->getSettingValue<bool>("snapOnJumpOrb");
	listenForSettingChanges<bool>("snapOnJumpOrb", [](const bool newSnapOnJumpOrb) { snapOnJumpOrb = newSnapOnJumpOrb; });

	ignoreYellowOrb = Mod::get()->getSettingValue<bool>("ignoreYellowOrb");
	listenForSettingChanges<bool>("ignoreYellowOrb", [](const bool ignoreYellowOrbNew) { ignoreYellowOrb = ignoreYellowOrbNew; });

	ignorePinkOrb = Mod::get()->getSettingValue<bool>("ignorePinkOrb");
	listenForSettingChanges<bool>("ignorePinkOrb", [](const bool ignorePinkOrbNew) { ignorePinkOrb = ignorePinkOrbNew; });

	ignoreBlueOrb = Mod::get()->getSettingValue<bool>("ignoreBlueOrb");
	listenForSettingChanges<bool>("ignoreBlueOrb", [](const bool ignoreBlueOrbNew) { ignoreBlueOrb = ignoreBlueOrbNew; });

	ignoreGreenOrb = Mod::get()->getSettingValue<bool>("ignoreGreenOrb");
	listenForSettingChanges<bool>("ignoreGreenOrb", [](const bool ignoreGreenOrbNew) { ignoreGreenOrb = ignoreGreenOrbNew; });

	ignoreBlackOrb = Mod::get()->getSettingValue<bool>("ignoreBlackOrb");
	listenForSettingChanges<bool>("ignoreBlackOrb", [](const bool ignoreBlackOrbNew) { ignoreBlackOrb = ignoreBlackOrbNew; });

	ignoreRedOrb = Mod::get()->getSettingValue<bool>("ignoreRedOrb");
	listenForSettingChanges<bool>("ignoreRedOrb", [](const bool ignoreRedOrbNew) { ignoreRedOrb = ignoreRedOrbNew; });

	ignoreGreenDashOrb = Mod::get()->getSettingValue<bool>("ignoreGreenDashOrb");
	listenForSettingChanges<bool>("ignoreGreenDashOrb", [](const bool ignoreGreenDashOrbNew) { ignoreGreenDashOrb = ignoreGreenDashOrbNew; });

	ignorePinkDashOrb = Mod::get()->getSettingValue<bool>("ignorePinkDashOrb");
	listenForSettingChanges<bool>("ignorePinkDashOrb", [](const bool ignorePinkDashOrbNew) { ignorePinkDashOrb = ignorePinkDashOrbNew; });

	ignoreSpiderOrb = Mod::get()->getSettingValue<bool>("ignoreSpiderOrb");
	listenForSettingChanges<bool>("ignoreSpiderOrb", [](const bool ignoreSpiderOrbNew) { ignoreSpiderOrb = ignoreSpiderOrbNew; });

	ignoreCustomOrb = Mod::get()->getSettingValue<bool>("ignoreCustomOrb");
	listenForSettingChanges<bool>("ignoreCustomOrb", [](const bool ignoreCustomOrbNew) { ignoreCustomOrb = ignoreCustomOrbNew; });

	ignoreTeleportOrb = Mod::get()->getSettingValue<bool>("ignoreTeleportOrb");
	listenForSettingChanges<bool>("ignoreTeleportOrb", [](const bool ignoreTeleportOrbNew) { ignoreTeleportOrb = ignoreTeleportOrbNew; });

	ignoreYellowPad = Mod::get()->getSettingValue<bool>("ignoreYellowPad");
	listenForSettingChanges<bool>("ignoreYellowPad", [](const bool ignoreYellowPadNew) { ignoreYellowPad = ignoreYellowPadNew; });

	ignorePinkPad = Mod::get()->getSettingValue<bool>("ignorePinkPad");
	listenForSettingChanges<bool>("ignorePinkPad", [](const bool ignorePinkPadNew) { ignorePinkPad = ignorePinkPadNew; });

	ignoreBluePad = Mod::get()->getSettingValue<bool>("ignoreBluePad");
	listenForSettingChanges<bool>("ignoreBluePad", [](const bool ignoreBluePadNew) { ignoreBluePad = ignoreBluePadNew; });

	ignoreRedPad = Mod::get()->getSettingValue<bool>("ignoreRedPad");
	listenForSettingChanges<bool>("ignoreRedPad", [](const bool ignoreRedPadNew) { ignoreRedPad = ignoreRedPadNew; });

	ignoreSpiderPad = Mod::get()->getSettingValue<bool>("ignoreSpiderPad");
	listenForSettingChanges<bool>("ignoreSpiderPad", [](const bool ignoreSpiderPadNew) { ignoreSpiderPad = ignoreSpiderPadNew; });

}

class $modify(MyPlayerObject, PlayerObject) {
	void snapToNearest90(const bool enforceGroundCheck) {
		if (enabled && this->m_gameLayer && (this == m_gameLayer->m_player1 || this == m_gameLayer->m_player2) && this->isInNormalMode() && !this->m_isDashing && ((this->m_isOnGround && !this->m_isOnSlope) || enforceGroundCheck)) {
			this->setRotation(std::round(this->getRotation() / 90.f) * 90.f);
		}
	}
	void hitGround(GameObject* object, bool notFlipped) {
		PlayerObject::hitGround(object, notFlipped);
		MyPlayerObject::snapToNearest90(false);
	}
	void propellPlayer(float yVelocity, bool noEffects, int objectType) {
		PlayerObject::propellPlayer(yVelocity, noEffects, objectType);
		if (this->isInNormalMode() && snapOnJumpPad) {
			if (objectType = static_cast<int>(GameObjectType::YellowJumpPad) && ignoreYellowPad) return;
			if (objectType = static_cast<int>(GameObjectType::PinkJumpPad) && ignorePinkPad) return;
			if (objectType = static_cast<int>(GameObjectType::GravityPad) && ignoreBluePad) return;
			if (objectType = static_cast<int>(GameObjectType::RedJumpPad) && ignoreRedPad) return;
			if (objectType = static_cast<int>(GameObjectType::SpiderPad) && ignoreSpiderPad) return;
			MyPlayerObject::snapToNearest90(true);
		}
	}
	void ringJump(RingObject* object, bool skipCheck) {
		PlayerObject::ringJump(object, skipCheck);
		if (this->isInNormalMode() && snapOnJumpOrb && !skipCheck && object && object->m_isActivated && object->m_activated) {
			if (object->m_objectType == GameObjectType::YellowJumpRing && ignoreYellowOrb) return;
			if (object->m_objectType == GameObjectType::PinkJumpRing && ignorePinkOrb) return;
			if (object->m_objectType == GameObjectType::GravityRing && ignoreBlueOrb) return;
			if (object->m_objectType == GameObjectType::GreenRing && ignoreGreenOrb) return;
			if (object->m_objectType == GameObjectType::DropRing && ignoreBlackOrb) return;
			if (object->m_objectType == GameObjectType::RedJumpRing && ignoreRedOrb) return;
			if (object->m_objectType == GameObjectType::DashRing && ignoreGreenDashOrb) return;
			if (object->m_objectType == GameObjectType::GravityDashRing && ignorePinkDashOrb) return;
			if (object->m_objectType == GameObjectType::SpiderOrb && ignoreSpiderOrb) return;
			if (object->m_objectType == GameObjectType::CustomRing && ignoreCustomOrb) return;
			if (object->m_objectType == GameObjectType::TeleportOrb && ignoreTeleportOrb) return;
			MyPlayerObject::snapToNearest90(true);
		}
	}
};