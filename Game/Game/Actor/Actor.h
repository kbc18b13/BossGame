#pragma once
#include "Util/CharaConEx.h"
#include "graphics/SkinModelRender.h"
#include "Act/Act.h"

class PlayerCamera;
class IStage;

class Actor : public IGameObject{
public:
	Actor(UINT maxHP, IStage* stage);
	virtual ~Actor();

    void ActStateUpdate() {
		m_nowAct->Update(this);
		if( m_nowAct->isActEnd() ){
			ChangeAct( m_nowAct->GetNextAct() );
		}
    }

	void SetPos( const CVector3& pos ){
		m_chara.SetPosition( pos );
		m_model.SetPos( pos );
	}
	CVector3 GetPos() const{
		return m_chara.GetPosition();
	}
	void AddVelocity( const CVector3& v ){
		m_chara.AddVelocity( v );
	}

	virtual bool Damage(UINT damage, Actor* source);

	UINT GetNowHP() {
		return m_nowHP;
	}

	UINT GetMaxHP() {
		return m_maxHP;
	}

	float GetHPPer() {
		return float(m_nowHP) / m_maxHP;
	}

	float GetHeight(){
		return m_chara.GetHeight();
	}

	bool IsDeath(){
		return m_isDeath;
	}

	//�X�e�[�W���Z�b�g
	void SetStage( IStage* stage ){
		m_stage = stage;
	}

	//�X�e�[�W���Q�b�g
	IStage* GetStage(){
		return m_stage;
	}

	//�J�����Ń��b�N�I��
	void LockOn( PlayerCamera* camera ){
		lockCamera = camera;
	}

	//���b�N�I������
	void UnLockOn(){
		lockCamera = nullptr;
	}

protected:
	void ChangeAct( int index ){
		m_nowAct->End( this );
		m_nowAct = GetAct( index );
		m_nowAct->Start( this );
	}

	virtual Act* GetAct( int index ) = 0;

	Act* m_nowAct = nullptr; //���݂̃X�e�[�g

	UINT m_nowHP; //�q�b�g�|�C���g
	UINT m_maxHP; //�ő�q�b�g�|�C���g
	PlayerCamera* lockCamera = nullptr;

	bool m_isDeath = false; //���S���Ă�����true

	IStage* m_stage = nullptr; //��������X�e�[�W

	SkinModelRender m_model;
	CharaConEx m_chara;
};