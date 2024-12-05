#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileReader.generated.h"

USTRUCT(BlueprintType)
struct FObjectData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    FString ObjectName;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    FString ObjectType;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    FVector Position;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    FRotator Rotation;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    FVector Scale;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    bool bPhysics;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    float Mass;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    bool bGravity;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    int32 BodyType;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    float LinearDrag;

    UPROPERTY(BlueprintReadWrite, Category = "File Parsing")
    float AngularDrag;
};

UCLASS()
class UNREALENGINE_API UFileReader : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

private:
    static void ParseFile(const FString& FilePath, TArray<FObjectData>& OutObjects, FString& OutFileContents);

public:
    UFUNCTION(BlueprintCallable, Category = "File Parsing")
    static int32 GetTotalObjectCount(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "File Parsing")
    static FObjectData GetObjectDataByIndex(const FString& FilePath, int32 Index);

    UFUNCTION(BlueprintCallable, Category = "File Parsing")
    static FString GetFileContents(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "File Parsing")
    static void SpawnObjectsFromFile(const FString& FilePath, UWorld* World);
    
};
