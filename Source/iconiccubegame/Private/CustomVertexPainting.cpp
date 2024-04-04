// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVertexPainting.h"
#include "Components.h"
#include "StaticMeshResources.h"
#include "Engine/StaticMesh.h"
#include "MeshVertexPainter/MeshVertexPainter.h"
#include "UObject/ObjectMacros.h"
#include "Math/Vector.h"
#include "Rendering/ColorVertexBuffer.h"

// ...other includes and code for other things...]


/*-----------------------------------------------------------------------------
FColorVertexBuffer
-----------------------------------------------------------------------------*/

/** The implementation of the static mesh color-only vertex data storage type. */
class FColorVertexData :
	public TStaticMeshVertexData<FColor>
{
public:
	FColorVertexData(bool InNeedsCPUAccess = false)
		: TStaticMeshVertexData<FColor>(InNeedsCPUAccess)
	{
	}
};

void FColorVertexBuffer::AllocateData(bool bNeedsCPUAccess /*= true*/)
{
	// Clear any old VertexData before allocating.
	CleanUp();

	VertexData = new FColorVertexData(bNeedsCPUAccess);
	// Calculate the vertex stride.
	Stride = VertexData->GetStride();
}


void UCustomVertexPainting::PaintVerticesRadius(UStaticMeshComponent* StaticMeshComponent, const FLinearColor& StartColor, const FLinearColor& EndColor, float Radius, bool bConvertToSRGB)
{


	if (!StaticMeshComponent || !StaticMeshComponent->GetStaticMesh())
	{
		return;
	}

	FTransform ComponentTrans = StaticMeshComponent->GetComponentTransform();

	/*
	const FBoxSphereBounds Bounds = StaticMeshComponent->GetStaticMesh()->GetBounds();
	const FBox Box = Bounds.GetBox();
	*/

	const int32 NumMeshLODs = StaticMeshComponent->GetStaticMesh()->GetNumLODs();
	StaticMeshComponent->SetLODDataCount(NumMeshLODs, NumMeshLODs);

	uint32 LODIndex = 0;
	for (FStaticMeshComponentLODInfo& LODInfo : StaticMeshComponent->LODData)
	{
		StaticMeshComponent->RemoveInstanceVertexColorsFromLOD(LODIndex);
		check(LODInfo.OverrideVertexColors == nullptr);

		const FStaticMeshLODResources& LODModel = StaticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources[LODIndex];
		const FPositionVertexBuffer& PositionVertexBuffer = LODModel.VertexBuffers.PositionVertexBuffer;
		const uint32 NumVertices = PositionVertexBuffer.GetNumVertices();

		TArray<FColor> VertexColors;
		VertexColors.AddZeroed(NumVertices);

		for (uint32 VertexIndex = 0; VertexIndex < NumVertices; ++VertexIndex)
		{

			const FVector& VertexPosition = PositionVertexBuffer.VertexPosition(VertexIndex);

			FVector TransPosition = StaticMeshComponent->GetAttachmentRootActor()->GetActorLocation() + StaticMeshComponent->GetAttachmentRootActor()->GetTransform().TransformVector(PositionVertexBuffer.VertexPosition(VertexIndex));

			float VertexDistance = FVector::Distance(TransPosition, FVector::ZeroVector);

			float LerpValue = (VertexDistance / Radius);

			UE_LOG(LogTemp, Log, TEXT("Vertex Position: %f, %f, %f, %f"), TransPosition.X, TransPosition.Y, TransPosition.Z, LerpValue);
			const FLinearColor Color = FMath::Lerp(StartColor, EndColor, LerpValue);
			VertexColors[VertexIndex] = Color.ToFColor(bConvertToSRGB);
		}

		LODInfo.OverrideVertexColors = new FColorVertexBuffer;
		LODInfo.OverrideVertexColors->InitFromColorArray(VertexColors);

		BeginInitResource(LODInfo.OverrideVertexColors);

		LODIndex++;
	}

#if WITH_EDITORONLY_DATA
	StaticMeshComponent->CachePaintedDataIfNecessary();
#endif
	StaticMeshComponent->MarkRenderStateDirty();
	StaticMeshComponent->bDisallowMeshPaintPerInstance = true;
}


void UCustomVertexPainting::PaintVerticesRadiusOverlay(UStaticMeshComponent* StaticMeshComponent, const FLinearColor& StartColor, const FLinearColor& EndColor, float Radius, bool bConvertToSRGB)
{


	if (!StaticMeshComponent || !StaticMeshComponent->GetStaticMesh())
	{
		return;
	}

	FTransform ComponentTrans = StaticMeshComponent->GetComponentTransform();

	/*
	const FBoxSphereBounds Bounds = StaticMeshComponent->GetStaticMesh()->GetBounds();
	const FBox Box = Bounds.GetBox();
	*/

	const int32 NumMeshLODs = StaticMeshComponent->GetStaticMesh()->GetNumLODs();
	StaticMeshComponent->SetLODDataCount(NumMeshLODs, NumMeshLODs);

	uint32 LODIndex = 0;
	for (FStaticMeshComponentLODInfo& LODInfo : StaticMeshComponent->LODData)
	{
		StaticMeshComponent->RemoveInstanceVertexColorsFromLOD(LODIndex);
		check(LODInfo.OverrideVertexColors == nullptr);

		const FStaticMeshLODResources& LODModel = StaticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources[LODIndex];
		const FPositionVertexBuffer& PositionVertexBuffer = LODModel.VertexBuffers.PositionVertexBuffer;
		const FColorVertexBuffer& ColorVertexBuffer = LODModel.VertexBuffers.ColorVertexBuffer;
		const uint32 NumVertices = PositionVertexBuffer.GetNumVertices();

		if (&ColorVertexBuffer == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ColorVertexBuffer is Null"));
			return;
			//ColorVertexBuffer.InitFromSingleColor(FColor::FromHex("FFFFFFFF"), NumVertices);
		}

		if (!(ColorVertexBuffer.GetNumVertices() == NumVertices))
		{
			UE_LOG(LogTemp, Warning, TEXT("ColorVertexBuffer Vertex Count (%i) is Not the Same As PositionVertexBuffer Vertex Count (%i)"), ColorVertexBuffer.GetNumVertices(), NumVertices);
			PaintVerticesRadius(StaticMeshComponent, StartColor, EndColor, Radius, bConvertToSRGB);
			UE_LOG(LogTemp, Warning, TEXT("Performed Basic Version of Function Instead"));
			return;
		}

		TArray<FColor> VertexColors;
		VertexColors.AddZeroed(NumVertices);

		for (uint32 VertexIndex = 0; VertexIndex < NumVertices; ++VertexIndex)
		{
			const FVector& VertexPosition = PositionVertexBuffer.VertexPosition(VertexIndex);

			if (VertexIndex > ColorVertexBuffer.GetNumVertices())
			{
				UE_LOG(LogTemp, Warning, TEXT("Vertex Index Outside of Range"));
				return;
			}

			FVector TransPosition = StaticMeshComponent->GetAttachmentRootActor()->GetActorLocation() + StaticMeshComponent->GetAttachmentRootActor()->GetTransform().TransformVector(PositionVertexBuffer.VertexPosition(VertexIndex));

			float VertexDistance = FVector::Distance(TransPosition, FVector::ZeroVector);

			float LerpValue = (VertexDistance / Radius);

			const FLinearColor Color = FMath::Lerp(StartColor, EndColor, LerpValue);

				if (ColorVertexBuffer.VertexColor(VertexIndex).A >= 128)
				{
					VertexColors[VertexIndex] = Color.ToFColor(bConvertToSRGB);
				}
				else
				{
					VertexColors[VertexIndex] = ColorVertexBuffer.VertexColor(VertexIndex);
				}

				UE_LOG(LogTemp, Log, TEXT("Vertex Color: %i, %i, %i, %i"), ColorVertexBuffer.VertexColor(VertexIndex).R, ColorVertexBuffer.VertexColor(VertexIndex).G, ColorVertexBuffer.VertexColor(VertexIndex).B, ColorVertexBuffer.VertexColor(VertexIndex).A);
		}

		LODInfo.OverrideVertexColors = new FColorVertexBuffer;
		LODInfo.OverrideVertexColors->InitFromColorArray(VertexColors);

		BeginInitResource(LODInfo.OverrideVertexColors);

		LODIndex++;
	}

#if WITH_EDITORONLY_DATA
	StaticMeshComponent->CachePaintedDataIfNecessary();
#endif
	StaticMeshComponent->MarkRenderStateDirty();
	StaticMeshComponent->bDisallowMeshPaintPerInstance = true;
}


void UCustomVertexPainting::GetVertexColorForExport(UStaticMeshComponent* StaticMeshComponent, bool& Success, TArray<FString>& OutputArray)
{
	Success = false;

	if (!StaticMeshComponent || !StaticMeshComponent->GetStaticMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("Static Mesh Component Not Found"));
		return;
	}



	const int32 NumMeshLODs = StaticMeshComponent->GetStaticMesh()->GetNumLODs();
	StaticMeshComponent->SetLODDataCount(NumMeshLODs, NumMeshLODs);

	TArray<FString> MeshOverrideColors;

	uint32 LODIndex = 0;
	for (FStaticMeshComponentLODInfo& LODInfo : StaticMeshComponent->LODData)
	{
		if (LODInfo.OverrideVertexColors == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Override Colors Found"));
			return;
		}

		FString CurrentLODOverrideColors;

		LODInfo.OverrideVertexColors->ExportText(CurrentLODOverrideColors);

		MeshOverrideColors.Add(CurrentLODOverrideColors);

		UE_LOG(LogTemp, Log, TEXT("Export String:%s"), *CurrentLODOverrideColors);

		LODIndex++;
	}

	OutputArray = MeshOverrideColors;

	Success = true;
	return;

}

void UCustomVertexPainting::SetVertexColorFromExport(UStaticMeshComponent* StaticMeshComponent, TArray<FString> InputArray, bool& Success)
{
	Success = false;

	if (!StaticMeshComponent || !StaticMeshComponent->GetStaticMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("Static Mesh Component Not Found"));
		return;
	}

	if (InputArray.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Export Array has No Items"));
		return;
	}

	const int32 NumMeshLODs = StaticMeshComponent->GetStaticMesh()->GetNumLODs();
	StaticMeshComponent->SetLODDataCount(NumMeshLODs, NumMeshLODs);

	TArray<FString> MeshOverrideColors;

	uint32 LODIndex = 0;
	for (FStaticMeshComponentLODInfo& LODInfo : StaticMeshComponent->LODData)
	{
		if (InputArray.IsValidIndex(LODIndex))
		{
			StaticMeshComponent->RemoveInstanceVertexColorsFromLOD(LODIndex);
			check(LODInfo.OverrideVertexColors == nullptr);

			FColorVertexBuffer OverrideImported;

			FString InputArrayLine = InputArray[LODIndex];

			TArray<FColor> VertexColors;
			ReadTextSafe(*InputArrayLine, VertexColors);

			UE_LOG(LogTemp, Log, TEXT("Import of String Successful:%s"), *InputArrayLine);

			LODInfo.OverrideVertexColors = new FColorVertexBuffer;
			LODInfo.OverrideVertexColors->InitFromColorArray(VertexColors);

			BeginInitResource(LODInfo.OverrideVertexColors);

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Outside Array Bounds"));
		}

		LODIndex++;
	}

	Success = true;

#if WITH_EDITORONLY_DATA
	StaticMeshComponent->CachePaintedDataIfNecessary();
#endif
	StaticMeshComponent->MarkRenderStateDirty();
	StaticMeshComponent->bDisallowMeshPaintPerInstance = true;
}

/** Export the data to a string, used for editor Copy&Paste. */
void FColorVertexBuffer::ExportText(FString& ValueStr) const
{
	// the following code only works if there is data and this method should only be called if there is data
	check(NumVertices);

	ValueStr += FString::Printf(TEXT("ColorVertexData(%i)=("), NumVertices);

	// 9 characters per color (ARGB in hex plus comma)
	ValueStr.Reserve(ValueStr.Len() + NumVertices * 9);

	for (uint32 i = 0; i < NumVertices; ++i)
	{
		uint32 Raw = VertexColor(i).DWColor();
		// does not handle endianess	
		// order: ARGB
		TCHAR ColorString[10];

		// does not use FString::Printf for performance reasons
		FCString::Sprintf(ColorString, TEXT("%.8x,"), Raw);
		ValueStr += ColorString;
	}

	// replace , by )
	ValueStr[ValueStr.Len() - 1] = ')';
}

/** Export the data from a string, used for editor Copy&Paste. */
void FColorVertexBuffer::ImportText(const TCHAR* SourceText)
{


	check(SourceText);

	uint32 VertexCount;

	if (FParse::Value(SourceText, TEXT("ColorVertexData("), VertexCount))
	{
		while (*SourceText && *SourceText != TEXT(')'))
		{
			++SourceText;
		}

		while (*SourceText && *SourceText != TEXT('('))
		{
			++SourceText;
		}

		check(*SourceText == TEXT('('));
		++SourceText;

		NumVertices = VertexCount;
		AllocateData(NeedsCPUAccess);
		VertexData->ResizeBuffer(NumVertices);
		uint8* Dst = (uint8*)VertexData->GetDataPointer();

		// 9 characters per color (ARGB in hex plus comma)
		for (uint32 i = 0; i < NumVertices; ++i)
		{
			// does not handle endianess or malformed input
			*Dst++ = FParse::HexDigit(SourceText[6]) * 16 + FParse::HexDigit(SourceText[7]);
			*Dst++ = FParse::HexDigit(SourceText[4]) * 16 + FParse::HexDigit(SourceText[5]);
			*Dst++ = FParse::HexDigit(SourceText[2]) * 16 + FParse::HexDigit(SourceText[3]);
			*Dst++ = FParse::HexDigit(SourceText[0]) * 16 + FParse::HexDigit(SourceText[1]);
			SourceText += 9;
		}
		check(*(SourceText - 1) == TCHAR(')'));

		// Make a copy of the vertex data pointer.
		Data = VertexData->GetDataPointer();

		BeginInitResource(this);
	}
}

/** Export the data from a string, used for editor Copy&Paste. */
void UCustomVertexPainting::ReadTextSafe(const TCHAR* SourceText, TArray<FColor>& OutputColorArray)
{
	check(SourceText);

	uint32 VertexCount;

	if (FParse::Value(SourceText, TEXT("ColorVertexData("), VertexCount))
	{
		while (*SourceText && *SourceText != TEXT(')'))
		{
			++SourceText;
		}

		while (*SourceText && *SourceText != TEXT('('))
		{
			++SourceText;
		}

		check(*SourceText == TEXT('('));
		++SourceText;

		OutputColorArray.AddZeroed(VertexCount);

		// 9 characters per color (ARGB in hex plus comma)
		for (uint32 i = 0; i < VertexCount; ++i)
		{
			FColor VertexColor;

			// does not handle endianess or malformed input
			VertexColor.B = FParse::HexDigit(SourceText[6]) * 16 + FParse::HexDigit(SourceText[7]);
			VertexColor.G = FParse::HexDigit(SourceText[4]) * 16 + FParse::HexDigit(SourceText[5]);
			VertexColor.R = FParse::HexDigit(SourceText[2]) * 16 + FParse::HexDigit(SourceText[3]);
			VertexColor.A = FParse::HexDigit(SourceText[0]) * 16 + FParse::HexDigit(SourceText[1]);

			OutputColorArray[i] = VertexColor;

			SourceText += 9;
		}
		check(*(SourceText - 1) == TCHAR(')'));
	}
}

void FColorVertexBuffer::Init(const FColorVertexBuffer& InVertexBuffer, bool bNeedsCPUAccess)
{
	NeedsCPUAccess = bNeedsCPUAccess;
	if (NumVertices)
	{
		Init(InVertexBuffer.GetNumVertices(), bNeedsCPUAccess);
		const uint8* InData = InVertexBuffer.Data;
		FMemory::Memcpy(Data, InData, Stride * NumVertices);
	}
}