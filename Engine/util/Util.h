/*!
 * @brief	���[�e�B���e�B�֐��B
 */
#pragma once


class Util{
public:
	/*!
	 * @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
	 */
	static int MakeHash( const char* string )
	{
		int hash = 0;
		int l = (int)strlen(string);
		for( int i = 0; i < l; i++ ){
			hash = hash * 37 + string[i];
		}
		return hash;
	}

	/*!
	* @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
	*/
	static int MakeHash(const wchar_t* string)
	{
		int hash = 0;
		int l = (int)wcslen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}

	//�����_����Int�l��Ԃ��B�͈͂�end�͊܂߂Ȃ��B
	static int RandomInt(int begine, int end);
	//�����_����float�l��Ԃ��B�͈͂�end�͊܂߂Ȃ��B
	static int RandomFloat(float begine, float end);
};

