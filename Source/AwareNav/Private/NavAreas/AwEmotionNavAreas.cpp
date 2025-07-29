#include "NavAreas/AwEmotionNavAreas.h"

#include "NavAreas/NavArea_Default.h"

FEmotionNavAreaGroup UAwEmotionNavArea_Base::GetNavAreaGroupByEmotionType(const EAwEmotionType EmotionType)
{
	switch (EmotionType)
	{
	case EAwEmotionType::Fear:
		return FEmotionNavAreaGroup {UAwEmotionNavArea_FearDefault::StaticClass(), UAwEmotionNavArea_FearLow::StaticClass(), UAwEmotionNavArea_FearHigh::StaticClass()};
	case EAwEmotionType::Safety:
		return FEmotionNavAreaGroup {UAwEmotionNavArea_SafetyDefault::StaticClass(), UAwEmotionNavArea_SafetyLow::StaticClass(), UAwEmotionNavArea_SafetyHigh::StaticClass()};
	case EAwEmotionType::Nostalgia:
		return FEmotionNavAreaGroup {UAwEmotionNavArea_NostalgiaDefault::StaticClass(), UAwEmotionNavArea_NostalgiaLow::StaticClass(), UAwEmotionNavArea_NostalgiaHigh::StaticClass()};
	default:
		return FEmotionNavAreaGroup {UNavArea_Default::StaticClass(), UNavArea_Default::StaticClass(), UNavArea_Default::StaticClass()};
	}
}
