#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include<stdbool.h>

typedef struct  
{
 int idObject;
 char *desc;
 Rectangle shape;
 Color color;
}Object;

typedef struct
{
	Rectangle shape;
	Rectangle collisionShape;
}Player;

typedef struct
{
	Rectangle shape;
	Rectangle Border;
	Vector2 Center;
	bool selected;
}InventorySpace;

void Move(Player *player,float delta)
{
	if(IsKeyDown(KEY_W))
	{
		player->shape.y -= 100 * delta;
		player->collisionShape.y = player->shape.y - player->collisionShape.height/2;
		player->collisionShape.x = player->shape.x;
	}
	else if (IsKeyDown(KEY_S))
	{
		player->shape.y += 100 * delta;
		player->collisionShape.y = player->shape.y + player->collisionShape.height/2;
		player->collisionShape.x = player->shape.x;
	}
	if(IsKeyDown(KEY_A))
	{
		player->shape.x -= 100 * delta;
		player->collisionShape.y = player->shape.y;
		player->collisionShape.x = player->shape.x - player->collisionShape.width/2;
	}
	else if(IsKeyDown(KEY_D))
	{
		player->shape.x += 100 * delta;			
		player->collisionShape.y = player->shape.y;
		player->collisionShape.x = player->shape.x + player->collisionShape.width/2;
	}
}

void initObject(Object *object)
{
	object[0].idObject = 0;
	object[0].desc = "apple";
	object[0].shape.height=15;
	object[0].shape.width=15;
	object[0].color= RED;

	object[1].idObject = 1;
	object[1].desc ="banana";
	object[1].shape.height=10;
	object[1].shape.width=20;
	object[1].color = YELLOW;

	object[2].idObject = 2;
	object[2].desc ="kiwi";
	object[2].shape.height=8;
	object[2].shape.width= 8;
	object[2].color=BROWN;

	object[3].idObject = 3;
	object[3].desc ="ficus";
	object[3].shape.height= 6;
	object[3].shape.width= 6;
	object[3].color= GREEN;

	object[4].idObject = 4;
	object[4].desc ="merinque";
	object[4].shape.height=6;
	object[4].shape.width=6;
	object[4].color= RAYWHITE;
}

void initInventorySpaces(InventorySpace *inventoryS, Rectangle inventoryUI)
{
	for(int i = 0; i<3; i++)
	{
		inventoryS[i].shape.width = 70;
		inventoryS[i].shape.height = 70;
		inventoryS[i].shape.x = inventoryUI.x + 10;
		inventoryS[i].shape.y = (inventoryUI.y + 10) + (inventoryS[i].shape.height * (i*1.3)-(10*(i-1)));
		inventoryS[i].Border = inventoryS[i].shape;
		inventoryS[i].selected = false;
		inventoryS[i].Center.x = inventoryS[i].shape.x + inventoryS[i].shape.width/2;
		inventoryS[i].Center.y = inventoryS[i].shape.y + inventoryS[i].shape.height/2;
	}
	inventoryS[0].selected = true;
}

void spawnObject(bool *spawnedObject, Object object[], Object *objectSelected, int widthW, int heightW)
{

	if(*spawnedObject == false)
	{
		*spawnedObject = true;
		*objectSelected = object[rand()%5];
		objectSelected->shape.x = rand()%widthW+1; 
		objectSelected->shape.y = rand()%heightW+1; 
		printf("spawned %s at %.2f X and %.2f Y\n",objectSelected->desc, objectSelected->shape.x, objectSelected->shape.y);
	}
	else
		DrawRectangle(objectSelected->shape.x, objectSelected->shape.y, objectSelected->shape.width, objectSelected->shape.height, objectSelected->color);

}

int main()
{
 srand(time(NULL));
 int widthW = 700, heightW = 500;
 int inventory[3][2] = {0,0,0,0,0,0};
 int selectedInventoryN = 0;
 float delta;

 bool  MenuOpen = false, spawnedObject = false, objTaken = false, full = false;
 Object object[5], selectedObject;
 Player player = {{0, 0, 50, 50}, player.shape};
 Rectangle inventoryUI = {widthW-(widthW/8), 0, 88, heightW};
 InventorySpace inventorySpace[3];


 
 

 initObject(object);
 initInventorySpaces(inventorySpace, inventoryUI);

 InitWindow(widthW, heightW, "test Inventory");
 while(!WindowShouldClose())
 {
	delta = GetFrameTime();
	ClearBackground(BLACK);
 	BeginDrawing();
		spawnObject(&spawnedObject, object,&selectedObject,widthW,heightW);
		if(IsKeyPressed(KEY_ENTER))
		{
			if(selectedObject.shape.x >= player.collisionShape.x && selectedObject.shape.x <= player.collisionShape.x + player.collisionShape.width)
			{
				if(selectedObject.shape.y >= player.collisionShape.y && selectedObject.shape.y <= player.collisionShape.y + player.collisionShape.height)
				{
					for(int i = 0; i<=2; i++)
					{
						if(inventory[i][0] == 0)
						{
							inventory[i][0] = selectedObject.idObject;
							inventory[i][1] +=1;
							objTaken = true;
							break;
						} 
						else if (inventory[i][0] == selectedObject.idObject && inventory[i][1] < 5)
						{
							inventory[i][1] += 1;
							objTaken = true;
							break;
						}

						printf("%s %d\n", object[(inventory[i][0]-1)].desc, inventory[i][1]);
					}
					if(objTaken)
					{
						spawnedObject = false;
						objTaken = false;
					}
					else
					{
						spawnedObject = false;
						printf ("Inventory full :( \n");
					}
				}
			}

		}


		if(IsKeyPressed(KEY_E))
		{
			if(!MenuOpen)
			{
				MenuOpen = true;
			}
			else {
				MenuOpen = false;
			}
		}
		
		if(MenuOpen)
		{
			DrawRectangle(inventoryUI.x, inventoryUI.y, inventoryUI.width, inventoryUI.height, WHITE);
			for (int i = 0; i < sizeof(inventorySpace); i++) 
			{
				DrawRectangle(inventorySpace[i].shape.x, inventorySpace[i].shape.y, inventorySpace[i].shape.width, inventorySpace[i].shape.height, GRAY);
				if(inventorySpace[i].selected == true)
				 {
					DrawRectangleLinesEx(inventorySpace[i].shape,5, GREEN);
				 }
			}
			
			if(IsKeyPressed(KEY_DOWN))
			{
				inventorySpace[selectedInventoryN].selected = false;
				if(selectedInventoryN == 2)
					selectedInventoryN = 0;
				else
				 	selectedInventoryN ++;
				inventorySpace[selectedInventoryN].selected =true;
			}
			if(IsKeyPressed(KEY_UP))
			{
				inventorySpace[selectedInventoryN].selected = false;
				if(selectedInventoryN == 0)
					selectedInventoryN = 2;
				else
				 	selectedInventoryN--;
				inventorySpace[selectedInventoryN].selected =true;
			}
			for (int i = 0; i<=2; i++)
			{
				if(inventory[i][0] != 0)
				{                    
					DrawRectangle(inventorySpace[i].Center.x-object[inventory[i][0]].shape.width/2, inventorySpace[i].Center.y - object[inventory[i][0]].shape.height/2, object[inventory[i][0]].shape.width, object[inventory[i][0]].shape.height, object[inventory[i][0]].color);
					DrawText(TextFormat("%d", inventory[i][1]), inventorySpace[i].Center.x+object[inventory[i][0]].shape.width/2, inventorySpace[i].Center.y + object[inventory[i][0]].shape.height/2, 10, BLACK);
				}
			}
		}
		else {
			Move(&player, delta);
		}

		DrawRectangle(player.shape.x, player.shape.y, player.shape.width, player.shape.height, RED);
		DrawRectangleLines(player.collisionShape.x, player.collisionShape.y, player.collisionShape.width, player.collisionShape.height, GREEN);
	EndDrawing();
 }

 CloseWindow();
}