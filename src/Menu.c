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
	Vector2 Center;
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
	object[0].idObject = 1;
	object[0].desc = "apple";
	object[0].shape.height=15;
	object[0].shape.width=15;
	object[0].color= RED;

	object[1].idObject = 2;
	object[1].desc ="banana";
	object[1].shape.height=10;
	object[1].shape.width=20;
	object[1].color = YELLOW;

	object[2].idObject = 3;
	object[2].desc ="kiwi";
	object[2].shape.height=8;
	object[2].shape.width= 8;
	object[2].color=BROWN;

	object[3].idObject = 4;
	object[3].desc ="ficus";
	object[3].shape.height= 6;
	object[3].shape.width= 6;
	object[3].color= GREEN;

	object[4].idObject = 5;
	object[4].desc ="merinque";
	object[4].shape.height=6;
	object[4].shape.width=6;
	object[4].color= RAYWHITE;
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
 float delta;

 bool  MenuOpen = false, spawnedObject = false, objTaken = false, full = false;
 Object object[5], selectedObject;
 Player player = {{0, 0, 50, 50}, player.shape};
 Rectangle inventoryUI = {widthW-(widthW/8), 0, 88, heightW};
 InventorySpace inventorySpace = {{inventoryUI.x + 10,inventoryUI.y+ 10,70,70}, {inventorySpace.shape.x + inventorySpace.shape.width/2,inventorySpace.shape.y + inventorySpace.shape.height/2}};
 
 

 initObject(object);

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
			DrawRectangle(inventorySpace.shape.x, inventorySpace.shape.y, inventorySpace.shape.width, inventorySpace.shape.height, GRAY);
			DrawRectangle(inventorySpace.shape.x, ((inventorySpace.shape.y * 2 + inventorySpace.shape.height)) , inventorySpace.shape.width, inventorySpace.shape.height, GRAY);
			DrawRectangle(inventorySpace.shape.x, ((inventorySpace.shape.height * 2 + 30))  , inventorySpace.shape.width, inventorySpace.shape.height, GRAY);

			for (int i = 0; i<=2; i++)
			{
				if(inventory[i][0] != 0)
				{                      //porcata																				//seconda porcata																								//terza porcata							//quarta porcata							//quinta porcata					
					DrawRectangle(inventorySpace.Center.x-object[inventory[i][0]-1].shape.width/2, (inventorySpace.Center.y - object[inventory[i][0]-1].shape.height/2) + (inventorySpace.shape.height * (i*1.3)-(10*(i-1))), object[inventory[i][0]-1].shape.width, object[inventory[i][0]-1].shape.height, object[inventory[i][0]-1].color);
					DrawText(TextFormat("%d", inventory[i][1]), inventorySpace.Center.x+object[inventory[i][0]-1].shape.width/2, inventorySpace.Center.y + object[inventory[i][0]-1].shape.height/2, 10, BLACK);
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