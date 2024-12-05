#include "FileReader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/Engine.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"

#include "EngineUtils.h" 

void UFileReader::ParseFile(const FString& FilePath, TArray<FObjectData>& OutObjects, FString& OutFileContents)
{
    OutObjects.Empty();

    TArray<FString> FileLines;
    if (FFileHelper::LoadFileToStringArray(FileLines, *FilePath)) 
    {
        OutFileContents = FString::Join(FileLines, TEXT("\n"));

        FObjectData CurrentObjectData;
        bool bParsingObject = false;

        for (const FString& Line : FileLines)
        {
            FString TrimmedLine = Line.TrimStartAndEnd();

            if (TrimmedLine.StartsWith(TEXT("Object Name:")))
            {
                if (bParsingObject)
                {
                    OutObjects.Add(CurrentObjectData);
                }

                bParsingObject = true;
                CurrentObjectData = FObjectData(); 
                CurrentObjectData.ObjectName = TrimmedLine.RightChop(12).TrimStartAndEnd(); 
            }
            else if (bParsingObject)
            {
                if (TrimmedLine.StartsWith(TEXT("Object Type:")))
                {
                    CurrentObjectData.ObjectType = TrimmedLine.RightChop(13).TrimStartAndEnd(); 
                }
                else if (TrimmedLine.StartsWith(TEXT("Position:")))
                {
                    FString PositionString = TrimmedLine.RightChop(10).TrimStartAndEnd(); 

                    PositionString.RemoveFromStart(TEXT("("));
                    PositionString.RemoveFromEnd(TEXT(")"));

                    TArray<FString> PositionComponents;
                    PositionString.ParseIntoArray(PositionComponents, TEXT(","), true);

                    if (PositionComponents.Num() == 3)
                    {
                        CurrentObjectData.Position.X = FCString::Atof(*PositionComponents[0]);
                        CurrentObjectData.Position.Y = FCString::Atof(*PositionComponents[2]);
                        CurrentObjectData.Position.Z = FCString::Atof(*PositionComponents[1]);

                        CurrentObjectData.Position.X *= 100;
                        CurrentObjectData.Position.Y *= 100;
                        CurrentObjectData.Position.Z *= 100;
                    }
                }

                else if (TrimmedLine.StartsWith(TEXT("Rotation:")))
                {
                    FString RotationString = TrimmedLine.RightChop(10).TrimStartAndEnd(); 

                    RotationString.RemoveFromStart(TEXT("("));
                    RotationString.RemoveFromEnd(TEXT(")"));

                    TArray<FString> RotationComponents;
                    RotationString.ParseIntoArray(RotationComponents, TEXT(","), true);

                    if (RotationComponents.Num() == 3)
                    {
                        CurrentObjectData.Rotation.Pitch = FCString::Atof(*RotationComponents[2]);
                        CurrentObjectData.Rotation.Yaw = FCString::Atof(*RotationComponents[1]);
                        CurrentObjectData.Rotation.Roll = -FCString::Atof(*RotationComponents[0]);
                    }
                }
                else if (TrimmedLine.StartsWith(TEXT("Scale:")))
                {
                    FString ScaleString = TrimmedLine.RightChop(7).TrimStartAndEnd(); 

                    ScaleString.RemoveFromStart(TEXT("("));
                    ScaleString.RemoveFromEnd(TEXT(")"));

                    TArray<FString> ScaleComponents;
                    ScaleString.ParseIntoArray(ScaleComponents, TEXT(","), true);

                    if (ScaleComponents.Num() == 3)
                    {
                        CurrentObjectData.Scale.X = FCString::Atof(*ScaleComponents[0]);
                        CurrentObjectData.Scale.Y = FCString::Atof(*ScaleComponents[2]);
                        CurrentObjectData.Scale.Z = FCString::Atof(*ScaleComponents[1]);
                    }
                }
                else if (TrimmedLine.StartsWith(TEXT("Physics:")))
                {
                    CurrentObjectData.bPhysics = TrimmedLine.RightChop(9).TrimStartAndEnd().Equals(TEXT("Yes"));
                }
                else if (TrimmedLine.StartsWith(TEXT("Mass:")))
                {
                    FString MassString = TrimmedLine.RightChop(5).TrimStartAndEnd(); 
                    CurrentObjectData.Mass = FCString::Atoi(*MassString);
                }
                else if (TrimmedLine.StartsWith(TEXT("Gravity:")))
                {
                    CurrentObjectData.bGravity = TrimmedLine.RightChop(8).TrimStartAndEnd().Equals(TEXT("Yes"));
                }
                else if (TrimmedLine.StartsWith(TEXT("BodyType:")))
                {
                    FString BodyTypeString = TrimmedLine.RightChop(9).TrimStartAndEnd();
                    CurrentObjectData.BodyType = FCString::Atoi(*BodyTypeString);
                }
                else if (TrimmedLine.StartsWith(TEXT("LinearDrag:")))
                {
                    FString LinearDragString = TrimmedLine.RightChop(11).TrimStartAndEnd(); 
                    CurrentObjectData.LinearDrag = FCString::Atof(*LinearDragString);
                }
                else if (TrimmedLine.StartsWith(TEXT("AngularDrag:")))
                {
                    FString AngularDragString = TrimmedLine.RightChop(12).TrimStartAndEnd(); 
                    CurrentObjectData.AngularDrag = FCString::Atof(*AngularDragString);
                }
                else if (TrimmedLine.IsEmpty())
                {
                    OutObjects.Add(CurrentObjectData);
                    bParsingObject = false;
                }
            }
        }

        if (bParsingObject)
        {
            OutObjects.Add(CurrentObjectData);
        }
    }
}


int32 UFileReader::GetTotalObjectCount(const FString& FilePath)
{
    TArray<FObjectData> ParsedObjects;
    FString FileContents;
    ParseFile(FilePath, ParsedObjects, FileContents);
    return ParsedObjects.Num();
}

FObjectData UFileReader::GetObjectDataByIndex(const FString& FilePath, int32 Index)
{
    TArray<FObjectData> ParsedObjects;
    FString FileContents;
    ParseFile(FilePath, ParsedObjects, FileContents);

    if (ParsedObjects.IsValidIndex(Index))
    {
        return ParsedObjects[Index];
    }

    return FObjectData(); 
}

FString UFileReader::GetFileContents(const FString& FilePath)
{
    FString FileContents;
    FFileHelper::LoadFileToString(FileContents, *FilePath);
    return FileContents;
}


void UFileReader::SpawnObjectsFromFile(const FString& FilePath, UWorld* World)
{
    TArray<FObjectData> ParsedObjects;
    FString FileContents;
    ParseFile(FilePath, ParsedObjects, FileContents);


    for (TActorIterator<AStaticMeshActor> ActorItr(World); ActorItr; ++ActorItr)
    {
        AStaticMeshActor* Actor = *ActorItr;
        if (Actor)
        {
            Actor->Destroy();  
        }
    }

    for (const FObjectData& ObjectData : ParsedObjects)
    {

    	FVector SpawnLocation = ObjectData.Position;
    	FRotator SpawnRotation = ObjectData.Rotation;
    	FVector SpawnScale = ObjectData.Scale;

        SpawnLocation.X *= -1;

    	FActorSpawnParameters SpawnParams;

    	AStaticMeshActor* SpawnedActor = World->SpawnActor<AStaticMeshActor>(SpawnLocation, SpawnRotation, SpawnParams);

    	if (SpawnedActor)
    	{
    		UStaticMeshComponent* MeshComp = SpawnedActor->GetStaticMeshComponent();
    		if (MeshComp)
    		{
                if (ObjectData.ObjectType.Equals(TEXT("Cube")))
                {
                    UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));

                    if (CubeMesh)
                    {
                        MeshComp->SetStaticMesh(CubeMesh);
                    }
                }

                if (ObjectData.ObjectType.Equals(TEXT("Plane")))
                {
                    UStaticMesh* PlaneMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane.Plane"));

                    if (PlaneMesh)
                    {
                        MeshComp->SetStaticMesh(PlaneMesh);
                    }
                }

                if (ObjectData.ObjectType.Equals(TEXT("Sphere")))
                {
                    UStaticMesh* SphereMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));

                    if (SphereMesh)
                    {
                        MeshComp->SetStaticMesh(SphereMesh);
                    }
                }

                if (ObjectData.ObjectType.Equals(TEXT("Cylinder")))
                {
                    UStaticMesh* CylinderMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

                    if (CylinderMesh)
                    {
                        MeshComp->SetStaticMesh(CylinderMesh);
                    }
                }

                if (ObjectData.ObjectType.Equals(TEXT("Capsule")))
                {
                    UStaticMesh* CapsuleMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

                    if (CapsuleMesh)
                    {
                        MeshComp->SetStaticMesh(CapsuleMesh);
                    }
                }
    		}

            UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
            if (Material)
            {
                MeshComp->SetMaterial(0, Material); 
            }

            if (ObjectData.bPhysics)
            {
                if (ObjectData.BodyType == 2 ) // Dynamic
                { 
					MeshComp->SetSimulatePhysics(true);
                	MeshComp->SetMobility(EComponentMobility::Movable);

                    SpawnedActor->Tags.Add("Dynamic");
                }

                else if (ObjectData.BodyType == 1) // Kinemaatic
                {
                    MeshComp->SetSimulatePhysics(true);
                    MeshComp->SetMobility(EComponentMobility::Stationary);

                    MeshComp->SetEnableGravity(false);

                    SpawnedActor->Tags.Add("Kinematic");
                }

                else // Static
                {
                    MeshComp->SetSimulatePhysics(false);
                    MeshComp->SetMobility(EComponentMobility::Static);

                    SpawnedActor->Tags.Add("Static");
                }
	            MeshComp->SetMassOverrideInKg(NAME_None, ObjectData.Mass); 
	            MeshComp->SetLinearDamping(ObjectData.LinearDrag); 
	            MeshComp->SetAngularDamping(ObjectData.AngularDrag); 
            }

            else
            {
                SpawnedActor->Tags.Add("No Physics");
            }

            if (ObjectData.bGravity)
            {
                MeshComp->SetEnableGravity(true);
            }
            else
            {
                MeshComp->SetEnableGravity(false);
            }


            if (ObjectData.ObjectType.Equals(TEXT("Plane")))
            {
    			SpawnedActor->SetActorScale3D(SpawnScale * 2);
            }
            else
            {
                SpawnedActor->SetActorScale3D(SpawnScale);
            }

    		SpawnedActor->SetActorLabel(ObjectData.ObjectName);
    	}
    }
}