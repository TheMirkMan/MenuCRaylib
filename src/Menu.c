#include <stdlib.h>
#include <raylib.h>




struct Object 
{
 int idObject;
 char *desc;
 Rectangle shape;
};



void Muovi(Rectangle *player,float delta)
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



int main()
{
 int widthW = 700, heightW = 500;
 float delta;

 _Bool MenuOpen = false, spawnedObject = false;
 struct Object object;
 Rectangle player = {0, 0, 50, 50};
 
 InitWindow(widthW, heightW, "test menu");
 while(!WindowShouldClose())
 {
	delta = GetFrameTime();
	ClearBackground(BLACK);
 	BeginDrawing();
		Muovi(&player, delta);

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