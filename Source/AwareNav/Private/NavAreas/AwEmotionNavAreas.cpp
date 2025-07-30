#include "NavAreas/AwEmotionNavAreas.h"

#include "NavAreas/NavArea_Default.h"

float UAwEmotionNavArea_Base::GetAreaDynamicCost(const float CostMultiplier) const
{
	const float DefaultEffectAreaModifiedCost = DefaultEffectAreaCost * CostMultiplier;

	if (bIsLowEffectArea)
	{
		if (DefaultEffectAreaModifiedCost > 1.0f)
		{
			return FMath::Max(DefaultEffectAreaModifiedCost - EmotionLowEffectDiff, 1.0f);
		}
		if (DefaultEffectAreaModifiedCost < 1.0f)
		{
			return FMath::Min(DefaultEffectAreaModifiedCost + EmotionLowEffectDiff, 1.0f);
		}
	}
	else
	{
		return DefaultEffectAreaModifiedCost;
	}
		
	return 1.0f;
}

FEmotionNavAreaGroup UAwEmotionNavArea_Base::GetNavAreaGroupByEmotionType(const EAwEmotionType EmotionType)
{
	switch (EmotionType)
	{
	case EAwEmotionType::Fear:
		return FEmotionNavAreaGroup {UAwEmotionNavArea_FearDefault::StaticClass(), UAwEmotionNavArea_FearLowEffect::StaticClass()};
	case EAwEmotionType::Haunting:
		return FEmotionNavAreaGroup {UAwEmotionNavArea_HauntingDefault::StaticClass(), UAwEmotionNavArea_HauntingLowEffect::StaticClass()};
	case EAwEmotionType::Safety:
		return FEmotionNavAreaGroup {UAwEmotionNavArea_SafetyDefault::StaticClass(), UAwEmotionNavArea_SafetyLowEffect::StaticClass()};
	case EAwEmotionType::Nostalgia:
		return FEmotionNavAreaGroup {UAwEmotionNavArea_NostalgiaDefault::StaticClass(), UAwEmotionNavArea_NostalgiaLowEffect::StaticClass()};
	default:
		return FEmotionNavAreaGroup {UNavArea_Default::StaticClass(), UNavArea_Default::StaticClass()};
	}
}
