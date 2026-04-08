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
	void snapToNearest90() {
		if (enabled && this->m_gameLayer && (this == m_gameLayer->m_player1 || this == m_gameLayer->m_player2) && this->isInNormalMode() && !this->m_isDashing && this->m_isOnGround && !this->m_isOnSlope) {
			this->setRotation(std::round(this->getRotation() / 90.f) * 90.f);
		}
	}
	void hitGround(GameObject* object, bool notFlipped) {
		PlayerObject::hitGround(object, notFlipped);
		MyPlayerObject::snapToNearest90();
	}
	void bumpPlayer(float bumpMod, int objectType, bool noEffects, GameObject* object) {
		PlayerObject::bumpPlayer(bumpMod, objectType, noEffects, object);
		if (snapOnJumpPad) MyPlayerObject::snapToNearest90();
	}
	void boostPlayer(float yVelocity) {
		PlayerObject::boostPlayer(yVelocity);
		if (snapOnJumpOrb) MyPlayerObject::snapToNearest90();
	}
};