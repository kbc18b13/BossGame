/// <summary>
/// ��C��R�̂悤�Ɍ�������ړ����x�x�N�g���B
/// </summary>
class ResistVector3{
public:
	ResistVector3();

	/// <summary>
	/// ��C��R�̌v�Z���s��
	/// </summary>
	/// <param name="resist">�W��(0�`1)/�b</param>
	void Update(float resist);

	CVector3 v;//�x�N�g���{��
	float& x;//X�����ւ̎Q��
	float& y;//Y�����ւ̎Q��
	float& z;//Z�����ւ̎Q��
};