/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include "projectile.h"
#include "howitzer.h"
#include "physics.h"
#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight)
      , ground(ptUpperRight)
      , hangTime(0.0)
      //,angle(0.0)
   {
      // Set the horizontal position of the howitzer. This should be random.
       srand((int)time(0));
       int randX = (rand() % (28000 - 1000)) + 1000;
       cout << randX << endl;
       this->howitzer.setPositionX(randX);


      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(this->howitzer.position);


      // This is to make the bullet travel across the screen. Notice how there are 
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      double x = 10000;
      double y = 2500;
      projectile.initPosition(10000, 2500, 0);
      

   }

   Ground ground;                 // the ground

   

   Howitzer howitzer;
   Howitzer  * ptHowitzer = &howitzer;          // location of the howitzer
   Position  ptUpperRight;        // size of the screen
   //double angle;                  // angle of the howitzer 

   Projectile projectile;

   double hangTime;                   // amount of time since the last firing
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //
   
   Physics::Angle* howitzerAngle = pDemo->howitzer.getAngle();
   double currentAngle = howitzerAngle->getRadians();

   // move a large amount
   if (pUI->isRight())
      *howitzerAngle += 0.05;
   if (pUI->isLeft())
      *howitzerAngle -= 0.05;

   // move by a little

   //if (pUI->isUp())
   //   howitzerAngle += (howitzerAngle >= 0 ? -0.003 : 0.003);
   //if (pUI->isDown())
   //   howitzerAngle += (howitzerAngle >= 0 ? 0.003 : -0.003);

   if (pUI->isUp())
      *howitzerAngle += (currentAngle >= 0 ? 0.003 : -0.003);
   if (pUI->isDown())
      *howitzerAngle += (currentAngle >= 0 ? -0.003 : 0.003);

   // fire that gun
   if (pUI->isSpace())
      pDemo->hangTime = 0.0;
   //
   // perform all the game logic
   //



   // advance time by half a second.
   pDemo->hangTime += 0.5;

   // move the projectile across the screen

    pDemo->projectile.computeNewPosition();
   

   //
   // draw everything
   //

   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY()- 20));

   // draw the ground first
   pDemo->ground.draw(gout);
   gout.setPosition(Position(4000, 8000));
   gout << "The angle of the barell is:" << howitzerAngle->getDegrees();

   // draw the howitzer
   Position howitzerPosition = pDemo->howitzer.getPosition();

   gout.drawHowitzer(howitzerPosition, howitzerAngle->getRadians(), pDemo->hangTime);
   
   // draw the projectile

   double Mountain_height = pDemo->ground.getElevationMeters(pDemo->projectile.getPosition());
   int i = 0;
   if (pDemo->projectile.getPosition().getMetersY() >= Mountain_height)
   {
       for (vector<Position>::reverse_iterator it = pDemo->projectile.paths.rbegin(); it != pDemo->projectile.paths.rend(); it++)
       {
           gout.drawProjectile((*it), 0.5 * (double)i++);
       }
       // draw some text on the screen
       gout.setf(ios::fixed | ios::showpoint);
       gout.precision(1);
       Position label;
       label.setPixelsX(560);
       label.setPixelsY(460);
       gout.setPosition(label);
       gout << "hang time: " << pDemo->hangTime << "s\n"
           << "distance:  " << pDemo->projectile.getPosition().getMetersX() << "m\n"
           << "altitude:  " << pDemo->projectile.getAltitude() << " m\n"
           << "speed:     " << pDemo->projectile.getSpeed() << " m/s\n";
   }
   
       

}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
