//#include <conio.hpp>
#include <iostream>
#include <aro/cui/Console.hpp>
#include <aro/aws/Dimension.hpp>

namespace aro {

namespace cui {

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // from <windows.hpp>

void Console::clear()
{
  //clrscr();     // from <conio.hpp>

  COORD coordConsole = { 0, 0 }; // here's where we'll home the cursor
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer info
  DWORD dwConSize; // number of character cells in the current buffer

  // get the number of character cells in the current buffer
  GetConsoleScreenBufferInfo(hConsole, &csbi);

  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  // fill the entire screen with blanks
  FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
      dwConSize, coordConsole, &cCharsWritten);

  // get the current text attribute
  GetConsoleScreenBufferInfo(hConsole, &csbi);

  // now set the buffer's attributes accordingly
  FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
      dwConSize, coordConsole, &cCharsWritten);

  // put the cursor at (0, 0)
  SetConsoleCursorPosition(hConsole, coordConsole);
}

aws::RDimension Console::getSize()
{
   //return new aws::Dimension(80,24);
   
   static aws::RDimension size;

   if(size == nullref)
   {
	   CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer info

	   // get the number of character cells in the current buffer
	   GetConsoleScreenBufferInfo(hConsole, &csbi);

	   size = new aws::Dimension(csbi.dwSize.X, csbi.dwSize.Y);
   }

   return size;
}

void Console::putChar(vchar ch)
{
   std::wcout << ch;
}

void Console::putString(RString str)
{
   std::wcout << static_cast<const vchar*>(str);
}

void Console::moveCursor(vint x, vint y)
{
   //gotoxy(x,y);    // from <conio.hpp>

   COORD coord = { (vshort)x, (vshort)y };
   
   SetConsoleCursorPosition( hConsole, coord );
}

} /* namespace cui */

} /* namespace aro */
