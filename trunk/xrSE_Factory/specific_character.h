//////////////////////////////////////////////////////////////////////////
// specific_character.h:	������� ���������� ��� � ���������� 
//							���������� � ����
//////////////////////////////////////////////////////////////////////////

#pragma		once


#include "character_info_defs.h"
#include "shared_data.h"
#include "xml_str_id_loader.h"


#ifdef XRGAME_EXPORTS

#include "PhraseDialogDefs.h"
#include "character_community.h"

#endif


//////////////////////////////////////////////////////////////////////////
// SSpecificCharacterData: ������ � ���������� ���������
//////////////////////////////////////////////////////////////////////////
struct SSpecificCharacterData : CSharedResource
{

#ifdef  XRGAME_EXPORTS

	SSpecificCharacterData ();
	virtual ~SSpecificCharacterData ();

	//������� ��� ���������
	xr_string	m_sGameName;
	//����� � ���������� ��������� (���� �� string table)
	shared_str	m_sBioText;
	//������ ���������� ��������, ������� ����� ����������� 
	xr_string	m_sSupplySpawn;
	//��� ������ ������������ �������� NPC ��� ���������
	xr_string	m_sNpcConfigSect;
	//��� ������ ������������ ����� ��� NPC ���������
	xr_string	m_sound_voice_prefix;

	float		m_fPanic_threshold;
	float		m_fHitProbabilityFactor;
	int			m_crouch_type;

	xr_string	m_critical_wound_weights;
#endif
	shared_str	m_terrain_sect;

	//��� ������
	xr_string m_sVisual;

#ifdef  XRGAME_EXPORTS
	
	//��������� ������
	shared_str				m_StartDialog;
	//������� ������, ������� ����� �������� ������ ��� ������� � ������ ����������
	DIALOG_ID_VECTOR		m_ActorDialogs;

	//��������� ������� ������ (��� �������� � �������) � ����� � �������� 
	int	m_iIconX, m_iIconY;

	//������� 
	CHARACTER_COMMUNITY			m_Community;

#endif
	
	//����
	CHARACTER_RANK_VALUE		m_Rank;
	//���������
	CHARACTER_REPUTATION_VALUE	m_Reputation;

	//������ ��������� (�������-��������, ������ � �.�.)
	//� ������� �� �����������
	xr_vector<CHARACTER_CLASS>	m_Classes;


	//�������� �� �� ��� �������� �� ������������ ��� ���������� ������
	//� �������� ������ ����� ����� �������� ID
	bool m_bNoRandom;
	//���� �������� �������� ������� �� ��������� ��� ����� �������
	bool m_bDefaultForCommunity;
#ifdef  XRGAME_EXPORTS
	struct SMoneyDef{
		u32				min_money;
		u32				max_money;
		bool			inf_money;
	};
	SMoneyDef			money_def;
#endif
};

class CInventoryOwner;
class CCharacterInfo;
class CSE_ALifeTraderAbstract;


class CSpecificCharacter: public CSharedClass<SSpecificCharacterData, SPECIFIC_CHARACTER_ID, false>,
						  public CXML_IdToIndex<SPECIFIC_CHARACTER_ID, int, CSpecificCharacter>
{
private:
	typedef CSharedClass	<SSpecificCharacterData, SPECIFIC_CHARACTER_ID, false>				inherited_shared;
	typedef CXML_IdToIndex	<SPECIFIC_CHARACTER_ID, int, CSpecificCharacter>					id_to_index;

	friend id_to_index;
	friend CInventoryOwner;
	friend CCharacterInfo;
	friend CSE_ALifeTraderAbstract;
public:

								CSpecificCharacter		();
								~CSpecificCharacter		();

	virtual void				Load					(SPECIFIC_CHARACTER_ID		id);

protected:
	const SSpecificCharacterData* data					() const { VERIFY(inherited_shared::get_sd()); return inherited_shared::get_sd();}
	SSpecificCharacterData*		  data					()	   { VERIFY(inherited_shared::get_sd()); return inherited_shared::get_sd();}

	//�������� �� XML �����
	virtual void				load_shared				(LPCSTR);
	static void					InitXmlIdToIndex		();

	SPECIFIC_CHARACTER_ID		m_OwnId;
public:

#ifdef  XRGAME_EXPORTS
	LPCSTR						Name					() const ;
	shared_str					Bio						() const ;
	const CHARACTER_COMMUNITY&	Community				() const ;
	SSpecificCharacterData::SMoneyDef& MoneyDef			() 	{return data()->money_def;}
#endif

	CHARACTER_RANK_VALUE		Rank					() const ;
	CHARACTER_REPUTATION_VALUE	Reputation				() const ;
	LPCSTR						Visual					() const ;

#ifdef  XRGAME_EXPORTS
	LPCSTR						SupplySpawn				() const ;
	LPCSTR						NpcConfigSect			() const ;
	LPCSTR						sound_voice_prefix		() const ;
	float						panic_threshold			() const ;
	float						hit_probability_factor	() const ;
	int							crouch_type				() const ;
	LPCSTR						critical_wound_weights	() const ;

	int							TradeIconX				() const	 {return data()->m_iIconX;}
	int							TradeIconY				() const	 {return data()->m_iIconY;}
#endif
	shared_str					terrain_sect			() const;
};


//////////////////////////////////////////////////////////////////////////