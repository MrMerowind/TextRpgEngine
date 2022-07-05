#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED

bool reload_game;
bool exit_;
HANDLE hConsole;

  void gotoxy(int x, int y)
{
  COORD c;

  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void SetWindowSize( int Width, int Height)
{
   COORD bufsize;
   bufsize = GetLargestConsoleWindowSize( hConsole );
   SMALL_RECT small_rect;
   small_rect.Left = 0;
   small_rect.Top = 0;
   small_rect.Right = Width;
   small_rect.Bottom = Height;
   bufsize.X = small_rect.Right+1;
   bufsize.Y = small_rect.Bottom+1;
   SetConsoleScreenBufferSize( hConsole, bufsize );
   SetConsoleWindowInfo( hConsole, TRUE, &small_rect );
   bufsize.X = small_rect.Right+1;
   bufsize.Y = small_rect.Bottom+1;
   SetConsoleScreenBufferSize( hConsole, bufsize );
   SetConsoleWindowInfo(hConsole, TRUE, &small_rect );
   HWND prevhWnd;
   if( prevhWnd == GetActiveWindow() )
      {
         BringWindowToTop( prevhWnd );
         ShowWindow( prevhWnd, SW_MAXIMIZE  );
      }
}


#endif // DECLARATIONS_H_INCLUDED
