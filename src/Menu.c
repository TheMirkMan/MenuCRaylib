#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>


typedef struct  
{
 int idObject;
 char *desc;
 Rectangle shape;
 Color color;
}Object;


void Move(Rectangle *player,float delta)
{
	if(IsKeyDown(KEY_W))
		player->y -= 100 * delta;
	else if (IsKeyDown(KEY_S))
		player->y += 100 * delta;

	if(IsKeyDown(KEY_A))
		player->x -= 100 * delta;
	else if(IsKeyDown(KEY_D))
		player->x += 100 * delta;	
}

void initObject(Object *object)
{
	object[0].idObject = 1;
	object[0].desc = "apple";
	object[0].shape.height=10;
	object[0].shape.width=10;
	object[0].color= RED;

	object[1].idObject = 2;
	object[1].desc ="banana";
	object[1].shape.height=10;
	object[1].shape.width=20;
	object[1].color = YELLOW;

	object[2].idObject = 3;
	object[2].desc ="kiwi";
	object[2].shape.height=5;
	object[2].shape.width= 5;
	object[2].color=BROWN;

	object[3].idObject = 4;
	object[3].desc ="ficus";
	object[3].shape.height= 2;
	object[3].shape.width= 2;
	object[3].color= GREEN;

	object[4].idObject = 5;
	object[4].desc ="merinque";
	object[4].shape.height=5;
	object[4].shape.width=5;
	object[4].color= RAYWHITE;
}

void spawnObject(_Bool* spawnedObject, Object *object, Object *objectSelected, int widthW, int heightW)
{
	if(!spawnedObject)
	{
		*spawnedObject = true;
		*objectSelected = object[rand()%(4-0+1)+1];
		objectSelected->shape.x = rand()%(widthW-0+1)+1; 
		objectSelected->shape.y = rand()%(heightW-0+1)+1; 

		printf("spawned %s at %.2f X and %.2f Y",objectSelected->desc, objectSelected->shape.x, objectSelected->shape.y);
	}

	DrawRectangle(objectSelected->shape.x, objectSelected->shape.y, objectSelected->shape.width, objectSelected->shape.height, objectSelected->color);
}

int main()
{
 srand(time(NULL));
 int widthW = 700, heightW = 500;
 float delta;

 _Bool MenuOpen = false, spawnedObject = false;
 Object object[5], selectedObject;
 Rectangle player = {0, 0, 50, 50};
 
 initObject(object);

 InitWindow(widthW, heightW, "test Inventory");
 while(!WindowShouldClose())
 {
	delta = GetFrameTime();
	ClearBackground(BLACK);
 	BeginDrawing();
		Move(&player, delta);
		spawnObject(&spawnedObject, object,&selectedObject,widthW,heightW);
		if(IsKeyPressed(KEY_E))
		{
			if(!MenuOpen)
			{
				
			}
		}

		DrawRectangle(player.x, player.y, player.width, player.height, RED);
	EndDrawing();
 }

 CloseWindow();
}