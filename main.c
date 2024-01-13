#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

int PlayField[10][10] = {
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0}};

int Snake[100][2];			
int SnakeSize = 0;	
int SnakeDirection = 1;
int apple[2];		
int appleExist = 0;
int main()
{
	Snake[0][0] = 2;
	Snake[0][1] = 2;
	/*Snake[1][0] = 2;
	Snake[1][1] = 1;
	Snake[2][0] = 2;
	Snake[2][1] = 0;*/
	

	while(1)
	{
		if(appleExist == 0)
		{
			int rx = rand() % 10; 
			int ry = rand() % 10; 
			
			apple[0] = rx;
			apple[1] = ry;
			appleExist = 1;
		}
		
		for(int i = 0; i <= SnakeSize; i++)
		{
			PlayField[Snake[i][0]][Snake[i][1]] = 1;	
		}
		
		if(Snake[0][0] == apple[0] && Snake[0][1] == apple[1])
			{
				appleExist = 0;
				SnakeSize++;
				Snake[SnakeSize][0] = Snake[SnakeSize-1][0];
				Snake[SnakeSize][1] = Snake[SnakeSize-1][1];


				
			}
		
		if( appleExist == 1)
		{
			PlayField[apple[0]][apple[1]] = 7;
		}
		
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10;j++)
			{
				printf("%d ",PlayField[j][i]);
			}
			printf("\n");
		}	
		printf("==============================\n");
		
		
		
		sleep(1.0f);
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10;j++)
			{
				PlayField[j][i] = 0;
			}
		}
		
		if(kbhit())
		{
			char c = getchar();
			if( c == '8')
			{
				SnakeDirection = 3;
			}
			
			if( c == '2')
			{
				SnakeDirection = 1;
			}
			
			if( c == '4')
			{
				SnakeDirection = 2;
			}
			
			if( c == '6')
			{
				SnakeDirection = 0;
			}
		}
			int score = SnakeSize * 10;
		printf("SCORE:%d\n",score);
		printf("\n==============================\n");
	
		
		if(SnakeSize != 0)
		{
			for(int i = SnakeSize; i > 0; i--)
			{	
					Snake[i][0] = Snake[i-1][0];
					Snake[i][1] = Snake[i-1][1];
			}
		}
		
		switch(SnakeDirection)
		{
			case 0:
					Snake[0][0] +=1;
					Snake[0][1] +=0;
					break;
				case 1:
					Snake[0][0] +=0;
					Snake[0][1] +=1;
					break;
				case 2:
					Snake[0][0] -=1;
					Snake[0][1] +=0;
					break;
				case 3:
					Snake[0][0] +=0;
					Snake[0][1] -=1;
					break;
		}
		
		
	}

}
