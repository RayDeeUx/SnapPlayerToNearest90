#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

bool enabled = true;
bool snapOnJumpPad = false;
bool snapOnJumpOrb = false;

$on_mod(Loaded) {
	enabled = Mod::get()->getSettingValue<bool>("enabled");
	listenForSettingChanges<bool>("enabled", [](const bool newEnabled) { enabled = newEnabled; });

	snapOnJumpPad = Mod::get()->getSettingValue<bool>("snapOnJumpPad");
	listenForSettingChanges<bool>("snapOnJumpPad", [](const bool newSnapOnJumpPad) { snapOnJumpPad = newSnapOnJumpPad; });

	snapOnJumpOrb = Mod::get()->getSettingValue<bool>("snapOnJumpOrb");
	listenForSettingChanges<bool>("snapOnJumpOrb", [](const bool newSnapOnJumpOrb) { snapOnJumpOrb = newSnapOnJumpOrb; });
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
		if (this->isInNormalMode() && snapOnJumpPad) MyPlayerObject::snapToNearest90(true);
	}
	void ringJump(RingObject* object, bool skipCheck) {
		PlayerObject::ringJump(object, skipCheck);
		if (this->isInNormalMode() && snapOnJumpOrb && !skipCheck && object && object->m_isActivated && object->m_activated) MyPlayerObject::snapToNearest90(true);
	}
};