#include "NavAreas/AwEmotionNavAreas.h"

#include "NavAreas/NavArea_Default.h"

FEmotionNavAreaGroup UAwEmotionNavArea_Base::GetNavAreaByEmotionType(const EAwEmotionType PermissionLevel)
{
	switch (PermissionLevel)
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

// EAwEmotionType UAwEmotionNavArea_Base::GetEmotionTypeByNavArea(const UClass* NavAreaClass)
// {
// 	if (NavAreaClass == UAwEmotionNavArea_FearLow::StaticClass())
// 	{
// 		return EAwEmotionType::Fear_Low;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_FearDefault::StaticClass())
// 	{
// 		return EAwEmotionType::Fear_Default;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_FearHigh::StaticClass())
// 	{
// 		return EAwEmotionType::Fear_High;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_SafetyLow::StaticClass())
// 	{
// 		return EAwEmotionType::Safety_Low;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_SafetyDefault::StaticClass())
// 	{
// 		return EAwEmotionType::Safety_Default;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_SafetyHigh::StaticClass())
// 	{
// 		return EAwEmotionType::Safety_High;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_NostalgiaLow::StaticClass())
// 	{
// 		return EAwEmotionType::Nostalgia_Low;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_NostalgiaDefault::StaticClass())
// 	{
// 		return EAwEmotionType::Nostalgia_Default;
// 	}
// 	else if (NavAreaClass == UAwEmotionNavArea_NostalgiaHigh::StaticClass())
// 	{
// 		return EAwEmotionType::Nostalgia_High;
// 	}
// 	else
// 	{
// 		return EAwEmotionType::None;
// 	}
// }
