///@ PopupSetting.cpp
#include "PopupSetting.h"

bool PopupSetting::init() {
	
	if (!Popup::init()) {
		return false;
	}
	
	setTitlePopup("SETTING");


#if 1
	const char   *SRT_SETTING[] = { "Music", "Sound" };
	
	for (int index = 0; index < 2; index++) {
		// label
		auto  _label = Label::createWithTTF(SRT_SETTING[index], "fonts/arial.ttf", 30);
		_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * (7 - index * 2) / 10));
		m_popupLayer->addChild(_label);

		// slider bar
		m_sliderOptionMusic[index] = Slider::create();
		m_sliderOptionMusic[index]->setTag(index); 
		m_sliderOptionMusic[index]->setScale(0.5);
		m_sliderOptionMusic[index]->loadBarTexture("popup/spr_slidebar_off.png");
		m_sliderOptionMusic[index]->loadSlidBallTextures(
														"popup/spr_slidebar_button_normal.png",		
														"popup/spr_slidebar_button_selected.png",
														"popup/spr_slidebar_button_selected.png");
		m_sliderOptionMusic[index]->loadProgressBarTexture("popup/spr_slidebar_on.png");

		m_sliderOptionMusic[index]->setPosition(Vec2(visibleSize.width / 2 + origin.x,
			visibleSize.height * (6 - index * 2) / 10 + origin.y));
			
		m_sliderOptionMusic[index]->addEventListener(CC_CALLBACK_2(PopupSetting::sliderEvent, this));
		m_popupLayer->addChild(m_sliderOptionMusic[index]);
	}

	
	/// init checkbox
	// label
	auto  _labelMuteAllSound = Label::createWithTTF("Mute On Sound", "fonts/arial.ttf", 30);
	_labelMuteAllSound->setPosition(Vec2(visibleSize.width * 4 / 10, visibleSize.height * 3 / 10 + origin.y));
	m_popupLayer->addChild(_labelMuteAllSound);

	// checkbox
	m_checkboxMuteAllSound = CheckBox::create("popup/spr_checkbox_normal.png",
		"popup/spr_checkbox_normal_press.png",
		"popup/spr_checkbox_active.png",
		"popup/spr_checkbox_normal_press.png",
		"popup/spr_checkbox_active.png");
	m_checkboxMuteAllSound->setScale(0.5);
	m_checkboxMuteAllSound->setPosition(Vec2(visibleSize.width * 6 / 10, visibleSize.height * 3 / 10 + origin.y));
	m_checkboxMuteAllSound->addEventListener(CC_CALLBACK_2(PopupSetting::checkBoxSelectedEvent, this));
	m_popupLayer->addChild(m_checkboxMuteAllSound);
#endif

	return true;
}

void PopupSetting::onExit() {
	Popup::onExit();
}

void PopupSetting::sliderEvent(Ref *pSender, Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* _slider = dynamic_cast<Slider*>(pSender);
		float _valueVolume = float(_slider->getPercent()) / 100;
		changeVolumeOfAudio(_slider->getTag(), _valueVolume);
	}
}

void PopupSetting::checkBoxSelectedEvent(Ref* pSender, CheckBox::EventType type) {
	
	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		m_sliderOptionMusic[eSldMusic]->setPercent(0);
		m_sliderOptionMusic[eSldSound]->setPercent(0);
		
		//m_audio->setEffectsVolume(0.0f);
		//m_audio->setBackgroundMusicVolume(0.0f);
		break;

	case CheckBox::EventType::UNSELECTED:
		m_sliderOptionMusic[eSldSound]->setPercent(50);
		m_sliderOptionMusic[eSldMusic]->setPercent(50);
			
		//m_audio->setEffectsVolume(0.5f);
		//m_audio->setBackgroundMusicVolume(0.5f);
		break;

	default:
		break;
	}
}

void PopupSetting::changeVolumeOfAudio(int _typeAudio, float _valueVolume) {

	/*if (_typeAudio == eSldSound)
		m_audio->setEffectsVolume(_valueVolume);
	else
		m_audio->setBackgroundMusicVolume(_valueVolume);*/
}

