#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileWriter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALENGINE_API UFileWriter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "File Operations")
	static void WriteStaticMeshesToFile(const FString& FilePath, UWorld* World);
};
