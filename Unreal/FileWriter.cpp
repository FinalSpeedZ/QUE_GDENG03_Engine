#include "FileWriter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"

void UFileWriter::WriteStaticMeshesToFile(const FString& FilePath, UWorld* World)
{
    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid World provided."));
        return;
    }

    TArray<FString> Lines;

    for (TActorIterator<AStaticMeshActor> ActorItr(World); ActorItr; ++ActorItr)
    {
        AStaticMeshActor* StaticMeshActor = *ActorItr;
        if (!StaticMeshActor)
            continue;

        UStaticMeshComponent* MeshComponent = StaticMeshActor->GetStaticMeshComponent();
        if (!MeshComponent)
            continue;

        FString ObjectName = StaticMeshActor->GetActorLabel();

        UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
        UStaticMesh* PlaneMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane.Plane"));
        UStaticMesh* SphereMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));
        UStaticMesh* CylinderMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
        UStaticMesh* CapsuleMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

        FString ObjectType;
        if (MeshComponent)
        {
            UStaticMesh* StaticMesh = MeshComponent->GetStaticMesh();
            if (StaticMesh == CubeMesh)
            {
                ObjectType = "Cube";
            }
            else if (StaticMesh == PlaneMesh)
            {
                ObjectType = "Plane";
            }
            else if (StaticMesh == SphereMesh)
            {
                ObjectType = "Sphere";
            }
            else if (StaticMesh == CylinderMesh)
            {
                ObjectType = "Cylinder";
            }
            else if (StaticMesh == CapsuleMesh)
            {
                ObjectType = "Capsule";
            }
            else
            {
                ObjectType = "Unknown";
            }
        }
        else
        {
            ObjectType = "Unknown";
        }

        FVector Position = StaticMeshActor->GetActorLocation() / 100.0f;
        FRotator Rotation = StaticMeshActor->GetActorRotation();
        FVector Scale = StaticMeshActor->GetActorScale3D();

        FString Line = FString::Printf(TEXT("Object Name: %s\n"), *ObjectName);
        Line += FString::Printf(TEXT("Object Type: %s\n"), *ObjectType);
        Line += FString::Printf(TEXT("Position: (%f, %f, %f)\n"), -Position.X, Position.Z, Position.Y);
        Line += FString::Printf(TEXT("Rotation: (%f, %f, %f)\n"), -Rotation.Roll, Rotation.Yaw, Rotation.Pitch);


        if (ObjectType == "Plane") 
        {
            Scale /= 2;
        }

        Line += FString::Printf(TEXT("Scale: (%f, %f, %f)\n"), Scale.X, Scale.Z, Scale.Y);

        bool bPhysics = MeshComponent->IsSimulatingPhysics();
        FString Physics = bPhysics ? "Yes" : "No";
        Line += FString::Printf(TEXT("Physics: %s\n"), *Physics);

        if (bPhysics)
        {
            Line += FString::Printf(TEXT("Mass: %f\n"), MeshComponent->GetMass());
            Line += FString::Printf(TEXT("Gravity: %s\n"), MeshComponent->IsGravityEnabled() ? TEXT("Yes") : TEXT("No"));

            int32 BodyType = 0;

            if (MeshComponent->Mobility == EComponentMobility::Movable)
            {
                BodyType = 2; 
            }
            else if (MeshComponent->Mobility == EComponentMobility::Stationary)
            {
                BodyType = 1; 
            }

            Line += FString::Printf(TEXT("BodyType: %d\n"), BodyType);

            Line += FString::Printf(TEXT("LinearDrag: %f\n"), MeshComponent->GetLinearDamping());
            Line += FString::Printf(TEXT("AngularDrag: %f\n"), MeshComponent->GetAngularDamping());
            Line += TEXT("Position Constraints: \n"); 
            Line += TEXT("Angular Constraints: \n");  
        }

        Line += TEXT("---\n");
        Lines.Add(Line);
    }

    FString FileContents = FString::Join(Lines, TEXT(""));
    if (FFileHelper::SaveStringToFile(FileContents, *FilePath))
    {
        UE_LOG(LogTemp, Log, TEXT("File saved successfully: %s"), *FilePath);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to save file: %s"), *FilePath);
    }
}
