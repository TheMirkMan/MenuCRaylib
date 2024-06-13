#include <stdlib.h>
#include <raylib.h>




struct Oggetto 
{
 int IDOggetto;
 char *descrizione;
 Rectangle forma;
};



void Muovi(Rectangle *personaggio,float delta)
{
	if(IsKeyDown(KEY_W))
		personaggio->y -= 100 * delta;
	else if (IsKeyDown(KEY_S))
		personaggio->y += 100 * delta;

	if(IsKeyDown(KEY_A))
		personaggio->x -= 100 * delta;
	else if(IsKeyDown(KEY_D))
		personaggio->x += 100 * delta;	
}

void SpawnaOggetto(int larghezzaF, int altezzaF, _Bool *oggettoSpawnato, struct Oggetto *oggetto)
{
	oggetto->IDOggetto = 
}



int main()
{
 int larghezzaF = 700, altezzaF = 500;
 float delta;
 float* deltaPtr = &delta;
 _Bool menuAperto = false, oggettoSpawnato = false;
 struct Oggetto oggetto;
 Rectangle personaggio = {0, 0, 50, 50};
 
 InitWindow(larghezzaF, altezzaF, "prova Menù");
 while(!WindowShouldClose())
 {
	delta = GetFrameTime();
	ClearBackground(BLACK);
 	BeginDrawing();
		Muovi(&personaggio, delta);

		if(IsKeyPressed(KEY_E))
		{
			if(!menuAperto)
			{
				
			}
		}

		DrawRectangle(personaggio.x, personaggio.y, personaggio.width, personaggio.height, RED);
	EndDrawing();
 }

 CloseWindow();
}