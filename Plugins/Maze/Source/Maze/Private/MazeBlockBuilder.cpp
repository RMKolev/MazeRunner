// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBlockBuilder.h"

void AMazeBlockBuilder::BuildCave() const
{
	const int rows = 72;
	const int cols = 129;

	char maze[rows][cols] = { "################################################################################################################################",
								"#####__#####_____##############################___#######################__####################################___##############",
								"####______________#############__#######___###_______#####_____####__###____###____###########################_____####__#######",
								"####_______________##_########____#####______________#####______##_________________#########____##############_____###____######",
								"####___________________######______###_______________#####________________________##########_____##__#########______#______#####",
								"####__##___####________######_______________________#########____________________############_________###__####____________#####",
								"################_______######______________________##########_____________________############______________###_____________####",
								"################______########____________________###########_______________________##########______________________________####",
								"###############______###########__________________###########_____________________________###________________________________###",
								"############__________##___######_________________#####___##____________##___________________________________________________###",
								"########____________________#####__________________###_________________####__________________________________________________###",
								"#######______________________###_______________________________________####___##______________________________________________##",
								"######________________________#______________##_________________________##___####_____________________________________________##",
								"######___________________________________######______________________________#######________________##_______________###_____###",
								"######__________________________________######_______________________________########______________####__________########____###",
								"###____________________________________######_________________________________########___##_______######________#########___####",
								"##_________________________________########____________________________________#######__####______######_________########___####",
								"##____________________##__________#######_____________###_______________________#####___#####______####__________#######____####",
								"##____________________#####______######______________######______________________####___#######_________________#######____#####",
								"##____________________#####_____####________________########______________________##############___________###########_____#####",
								"##_____________________####____#####________________#########_______________###___#########__##____________###########_____#####",
								"###____________________________#####_________________#___#####_____________###############____________________########_____#####",
								"###____________________________######____________________######___________#############________________________######_________##",
								"###____________________________######__________________########__________#############___________##____________####____________#",
								"###______________#_____________######______###________##########_________###########____________###_____________##_____________#",
								"#####___________###_____________####______#####_______##############_____##########_____##_____####_____________##_____________#",
								"######__________####______________________#####____________###########___##########____####____####_____###_____##____________##",
								"######__________####_______________________####______________##############_____####___####_____##______###_____###___________##",
								"#####____________####________________________##_______________############_______####___###____________________####__________###",
								"####_____________#####________________________________________###_______##_______####____###__________________######_______#####",
								"###_____________######_______________________________________###________###_____####______###_________________########____######",
								"###_______##____######____________________________________#####_________###########________###______##_________########____#####",
								"##_______####__#######________##__##_____________________#####__________###########_________###____####_________########_____###",
								"##________############_______########_____________##_____####__________############_________###____#######_______########____###",
								"##__________#########________########____________###_____###___________#############________###____########________######____###",
								"##___________#######_________########____________###____###___________##############________####__#########_________####____####",
								"###___________#####___________######_____________###___###____________####___########_______##############_________________#####",
								"#######_______#####____________________####___________####_____________##______########_____############______######_______#####",
								"########_____#######__________________#####___________####______________________########_____##########______#######_______#####",
								"########____#######__________________#####____________###____###________________########____________##______########________####",
								"########___#######___________________####____________####___####_______________########_____________##_____########__________###",
								"#######____#####_____________________###_____________####___###_______________####__________________##____######_______##____###",
								"###_________###______________________####____________###_____#__________#______##_________________________#####_______####____##",
								"###_________###_______________________####___________###______________________________________#____________####______#####____##",
								"####________###_______________________#####__________###__________________________________######___________####_____#####_____##",
								"#####_______###________________________####_____#_______________________________###_______#####_______#____#####____#####____###",
								"######_____#####________________________##_____####_______________________##########_________________###___#####_____###_____###",
								"#################___________________##__________####_____##___##__###_____##########________________####___#####____________####",
								"#################__________________####__________####___##############_______##_#####________________##____####_____________####",
								"#################___________##_____#####__________###___#######__#####___________######_____________________##__________##___###",
								"#########______##__________####____#####___________#_____####____####____________#######____________________________#######___##",
								"#######________######_____######__#####_______##__________________##_____________#######_______________________###########____##",
								"#####__________#######____##########_________####_________________________________######______________________########________##",
								"####___________#######____##########________#####__________________________________####_____________________#########_________##",
								"####___________########____##########_______#####_____________________________##____##___##_______________#####__##__________###",
								"####____________#######______#########______#####____________________________####_______####_____________####____________#######",
								"#####__##________#####________####__##______#####___________________________######______####______________##____________########",
								"##########_____________________##___________####___________________________#######______####_______________________#######____##",
								"###########_________________________________####_________________________#########_____#####______________________#######______#",
								"############________________________________####________________________#######________######_____________________#######______#",
								"###__########_______________________________#####____________##________########_________#####______________________#######____##",
								"##____#############__________________________#######________####____#############__________#___________####_________######____##",
								"##_____###__########______#__________________########_______####___###############__________________#######__________####_____##",
								"##___________######______###__________________#######________##___#################_________________#######___________##_____###",
								"##___________####________#######______________#######_____________######______#####_________________######__________________####",
								"##___________###_________########______________#####_____________######________#####__________________####__________________####",
								"##_______________________#########_____________####_____________#######_________####___________________###__________________####",
								"##_______________________#########____________####_____####____########_________#####__________________###_________________#####",
								"###__##__________________#########________########____######__#############_____######_____#####______####______#####____#######",
								"########__________###___###########______#########____######################___########___#######____######___##################",
								"###################################################__#############################################__############################",
								"################################################################################################################################" };


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; maze[i][j] != '\0'; j++)
		{
			FVector SpawnLocation = /*GetActorLocation() +*/ FVector(i * SideOfCubeAtScaleOne * ScaleForAllMeshes.X,
				j * SideOfCubeAtScaleOne * ScaleForAllMeshes.Y, 0);
			if (maze[i][j] == '#')
			{
				//SpawnLocation.Z = SideOfCubeAtScaleOne * ScaleForAllMeshes.Z;
				FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
				//AActor* Wall = World->SpawnActor<AActor>(WallActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				//Wall->SetActorScale3D(ScaleForAllMeshes);
				//WallInstancedMesh->AddInstance(SpawnTransform);

			}
			else if (maze[i][j] == '_') {
				FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation, ScaleForAllMeshes);
				/*AActor * Floor = World->SpawnActor<AActor>(FloorActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				Floor->SetActorScale3D(ScaleForAllMeshes);*/
				//FloorInstancedMesh->AddInstance(SpawnTransform);
			}
		}
	}
}
