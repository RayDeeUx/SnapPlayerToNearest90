#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

bool enabled = true;

$on_mod(Loaded) {
	enabled = Mod::get()->getSettingValue<bool>("enabled");
	listenForSettingChanges<bool>("enabled", [](const bool newEnabled){ enabled = newEnabled; });
}

class $modify(MyPlayerObject, PlayerObject) {
	void hitGround(GameObject* object, bool notFlipped) {
		PlayerObject::hitGround(object, notFlipped);
		if (enabled && this->m_gameLayer && (this == m_gameLayer->m_player1 || this == m_gameLayer->m_player2) && this->isInNormalMode() && !this->m_isDashing && this->m_isOnGround && !this->m_isOnSlope) this->setRotation(std::round(this->getRotation() / 90.f) * 90.f);
	}
};