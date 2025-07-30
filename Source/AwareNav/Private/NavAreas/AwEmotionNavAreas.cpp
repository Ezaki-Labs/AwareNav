#include "NavAreas/AwEmotionNavAreas.h"

#include "NavAreas/NavArea_Default.h"

EAwEmotionType UAwEmotionNavArea_Base::GetEmotionTypeByNavArea(const UClass* EmotionType)
{
	if (EmotionType == UAwEmotionNavArea_Fear::StaticClass())
	{
		return EAwEmotionType::Fear;
	}
	if (EmotionType == UAwEmotionNavArea_Haunting::StaticClass())
	{
		return EAwEmotionType::Haunting;
	}
	if (EmotionType == UAwEmotionNavArea_Safety::StaticClass())
	{
		return EAwEmotionType::Safety;
	}
	if (EmotionType == UAwEmotionNavArea_Nostalgia::StaticClass())
	{
		return EAwEmotionType::Nostalgia;
	}

	return EAwEmotionType::None;
}

UClass* UAwEmotionNavArea_Base::GetNavAreaByEmotionType(const EAwEmotionType EmotionType)
{
	switch (EmotionType)
	{
	case EAwEmotionType::Fear:
		return UAwEmotionNavArea_Fear::StaticClass();
	case EAwEmotionType::Haunting:
		return UAwEmotionNavArea_Haunting::StaticClass();
	case EAwEmotionType::Safety:
		return UAwEmotionNavArea_Safety::StaticClass();
	case EAwEmotionType::Nostalgia:
		return UAwEmotionNavArea_Nostalgia::StaticClass();
	default:
		return UNavArea_Default::StaticClass();
	}
}
