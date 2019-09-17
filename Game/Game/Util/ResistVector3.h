/// <summary>
/// 空気抵抗のように減衰する移動速度ベクトル。
/// </summary>
class ResistVector3{
public:
	ResistVector3();

	/// <summary>
	/// 空気抵抗の計算を行う
	/// </summary>
	/// <param name="resist">係数(0～1)/秒</param>
	void Update(float resist);

	CVector3 v;//ベクトル本体
	float& x;//X成分への参照
	float& y;//Y成分への参照
	float& z;//Z成分への参照
};