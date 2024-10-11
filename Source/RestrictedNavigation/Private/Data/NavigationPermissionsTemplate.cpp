#include "Data/NavigationPermissionsTemplate.h"

void FNavigationPermissionsTemplate::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
    TArray<FNavigationPermissionsTemplate *> Rows;
    InDataTable->GetAllRows<FNavigationPermissionsTemplate>(TEXT("Setting nav query filters"), Rows);
    
    for (int i = 0; i < Rows.Num(); ++i)
    {
        if (i >= 20)
        {
            break;
        }
        FNavigationPermissionsTemplate * Row = Rows[i];
        Row->NavQueryFilter = GetRestrictedNavigationQueryFilterByIndex(i);
    }
}
