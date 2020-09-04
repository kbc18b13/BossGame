#pragma once
class LongPressButton{
public:
	void SetButton( EnButton button ){
		m_button = button;
	}

	void Update();

	bool isLongPress(){
		return m_isPress && m_timer <= 0;
	}

	bool isTrigger(){
		return m_isTrigger;
	}

private:
	static constexpr float c_timer = 0.2f;
	float m_timer = 0;
	bool m_isPress = false;
	bool m_isTrigger = false;
	EnButton m_button;
};

