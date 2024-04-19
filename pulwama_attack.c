#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include<stdbool.h>
float busX =-500.0;
float busY = 0.0;
float busSpeed=0.6;
//float busSpeed2=1.0;
float carX = 500.0;
float carY = 0.0;
float carSpeed=-0.5;
int elapsedTime = 0;
float cloud1X = 90.0;
float cloud2X = 140.0;
float cloud3X = 190.0;
float cloud4X = 270.0;
float cloud5X = 320.0;
float cloud6X = 405.0;
float cloud7X = 430.0;
int storySceneDuration = 8000; // Set the duration in milliseconds (e.g., 10 seconds)
int currentScene = 0;
bool explosion = false; // Flag to indicate if a collision occurs
float explosionX; // X position of the explosion
float explosionY; // Y position of the explosion
float explosionRadius=5.0;
typedef struct stColor {
    double red, green, blue;
    double alpha;
} RgbColor;

RgbColor createColor(int red, int green, int blue, double alpha) {
    RgbColor color;
    color.red = (double) red / 256;
    color.green = (double) green / 256;
    color.blue = (double) blue / 256;
    color.alpha = (double) alpha;
    return color;
}

RgbColor color;
void drawText(char text[], int x, int y, int z)
{
    // The color
    glColor3f(1, 1, 1);
    // Position of the text to be printed
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void printLines(char **s, int offsetY, int n, int x, int y)
{
    int i = 0;
    for (; i < n; i++)
    {
        drawText(s[i], x, y + offsetY, 0);
        offsetY -= 25;
    }
}
void drawCandles()
{
    glBegin(GL_QUADS); //candle1
    color = createColor(227, 242, 249, 0);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(400.0, 0.0);
    glVertex2f(420.0, 0.0);
    glVertex2f(420.0, 210.0);
    glVertex2f(400.0, 210.0);
    glEnd();

    glBegin(GL_QUADS); //candle2
    color = createColor(227, 242, 249, 0);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(440.0, 0.0);
    glVertex2f(460.0, 0.0);
    glVertex2f(460.0, 180.0);
    glVertex2f(440.0, 180.0);
    glEnd();

    glBegin(GL_QUADS); //candle3
    color = createColor(227, 242, 249, 0);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(360.0, 0.0);
    glVertex2f(380.0, 0.0);
    glVertex2f(380.0, 180.0);
    glVertex2f(360.0, 180.0);
    glEnd();

    //drawWick
    glLineWidth(3.0);

    glColor3f(0.0, 0.0, 0.0); //wick1
    glBegin(GL_LINES);
    glVertex2f(450.0, 180.0);
    glVertex2f(450.0, 200.0);
    glEnd();

    glColor3f(0.0, 0.0, 0.0); //wick2
    glBegin(GL_LINES);
    glVertex2f(370.0, 180.0);
    glVertex2f(370.0, 200.0);
    glEnd();

    glColor3f(0.0, 0.0, 0.0); //wick3
    glBegin(GL_LINES);
    glVertex2f(410.0, 210.0);
    glVertex2f(410.0, 230.0);
    glEnd();
}
void drawFire(int xfire, int yfire){

    glBegin(GL_POLYGON);

        color = createColor(230, 78, 58, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(xfire,yfire+20);

        color = createColor(241, 119, 57, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f((xfire+15.0),(yfire-12.0));

        color = createColor(246, 166, 63, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f((xfire+18.5),(yfire-26.0));

        color = createColor(241, 196, 101, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f((xfire+18.0),(yfire-45.0));


        color = createColor(6, 206, 255, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f((xfire),(yfire-77));


        color = createColor(241, 196, 101, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f((xfire-18.0),(yfire-45.0));

        color = createColor(246, 166, 63, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f((xfire-18.5),(yfire-26.0));

        color = createColor(241, 119, 57, 0);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f((xfire-15.0),(yfire-12.0));

    glEnd();

}
void cloud(float x, float y, float radius)
{
    float theta = 0.0;

    glColor3f(1.0, 1.0, 1.0); // Set color to white
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for (int i = 0; i < 360; i++)
    {
        theta = i * 3.1416 / 180;
        glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
    }
    glEnd();
}
void wheel1(float x, float y)
{
   float th;
   glBegin(GL_POLYGON);
   glColor3f(0, 0, 0);
   for(int i = 0; i < 360; i++)
   {
       th = i * (3.1416 / 180);
       glVertex2f(x + 13 * cos(th), y + 13 * sin(th));
   }
   glEnd();
}

void wheel2(float x, float y)
{
    float th;
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    for (int i = 0; i < 360; i++)
    {
        th = i * (3.1416 / 180);
        glVertex2f(x + 8 * cos(th), y + 8 * sin(th));
    }
    glEnd();
}


/*
void wheel1(float x, float y)
{
    float theta = 0.0;

    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for (int i = 0; i < 360; i++)
    {
        theta = i * 3.1416 / 180;
        glVertex2f(x + 13* cos(theta), y + 13 * sin(theta));
    }
    glEnd();
}*/
void StoryScene()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0); // Purple color
    glVertex2f(0.0, 0.0);
    glVertex2f(800.0, 0.0);
    glColor3f(1.0,0.0,0.0); // Dark blue color
    glVertex2f(800.0, 500.0);
    glVertex2f(0.0, 800.0);
    glEnd();

    char *story[] = {
        "On 14th of February 2019, a convoy of vehicles carrying security personnel on the Jammu",
        "Srinagar National Highway was attacked by a vehicle-borne suicide bomber at Lethpora in the",
        " Pulwama district.The attack resulted in the deaths of 40 Central Reserve Police Force (CRPF) personnel and the",
        "attacker.The responsibility for the attack was claimed by  the Pakistan-based Islamist militant",
        "group.The attacker was Adil Ahmad Dar, a local from Pulwama district.India has blamed",
        "Pakistan for the attack. Pakistan condemned the attack and denied any connection to it."
    };

    printLines(story, 8, 7, 0, 350);
    drawCandles();
    int opt;
    if (opt == 1)
    {
        drawFire(425.0, -23);
        drawFire(485.0, -53);
        drawFire(365.0, -73);
    }
    glPopMatrix();
}

void drawMainScene()
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0); // Purple color
    glVertex2f(-800.0, 500.0);
    glVertex2f(800.0, 500.0);
    glColor3f(0.07, 0.05, 0.34); // Dark blue color
    glVertex2f(800.0, -500.0);
    glVertex2f(-800.0, -500.0);
    glEnd();

    glClearColor(1.0, 1.0, 1.0, 1.0);
    char h1[] = "Computer Graphics Project";
    char h2[] = "PULWAMA ATTACK";
    char h3[] = "by";
    char name1[] = "ALREYA EDEL PATRAO";
    char usn1[] = "4SO20CS008";
    char name2[] = "ANSILLA PAIS";
    char usn2[] = "4SO20CS015";
    char message[] = "Press 1 to start";

drawText(h1, 200, 300, 0);
drawText(h2, 200, 272, 0);
drawText(h3, 230, 240, 0);
drawText(name1, 370, 210, 0);
drawText(usn1, 370, 190, 0);
drawText(name2, 90, 210, 0);
drawText(usn2, 90, 190, 0);
drawText(message, 200, 20, 0);

}

void drawBus()
{
// Calculate the updated bus position based on busX and busY
    int busPosX = 250 + busX;
    int busPosY = 120 + busY;

    // Draw the bus body
    glColor3f(0.1, 0.3, 0.2); // bus
    glBegin(GL_POLYGON);
    glVertex2d(busPosX, busPosY);
    glVertex2d(busPosX, busPosY + 80);
    glVertex2d(busPosX + 150, busPosY + 80);
    glVertex2d(busPosX + 158, busPosY + 40);
    glVertex2d(busPosX + 158, busPosY);
    glEnd();

    // Draw the door
    glColor3f(0.7, 1, 1); // bus
    glBegin(GL_POLYGON);
    glVertex2d(busPosX + 74, busPosY + 10);
    glVertex2d(busPosX + 74, busPosY + 70);
    glVertex2d(busPosX + 97, busPosY + 70);
    glVertex2d(busPosX + 97, busPosY + 10);
    glEnd();

    // Draw the windows
    glColor3f(0.7, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2d(busPosX + 8, busPosY + 40);
    glVertex2d(busPosX + 8, busPosY + 70);
    glVertex2d(busPosX + 33, busPosY + 70);
    glVertex2d(busPosX + 33, busPosY + 40);
    glEnd();

    glColor3f(0.7, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2d(busPosX + 40, busPosY + 40);
    glVertex2d(busPosX + 40, busPosY + 70);
    glVertex2d(busPosX + 65, busPosY + 70);
    glVertex2d(busPosX + 65, busPosY + 40);
    glEnd();

    glColor3f(0.7, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2d(busPosX + 106, busPosY + 40);
    glVertex2d(busPosX + 106, busPosY + 70);
    glVertex2d(busPosX + 130, busPosY + 70);
    glVertex2d(busPosX + 130, busPosY + 40);
    glEnd();

       glColor3f(0.7, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2d(busPosX + 137, busPosY + 40);
    glVertex2d(busPosX + 137, busPosY + 70);
    glVertex2d(busPosX + 146, busPosY + 70);
    glVertex2d(busPosX + 152, busPosY + 40);
    glEnd();

    // Draw the wheels
    wheel1(busPosX + 46, busPosY);
    wheel1(busPosX + 114, busPosY);
    wheel2(busPosX + 46, busPosY);
    wheel2(busPosX + 114, busPosY);
}
/*
    int busPosX = 50 + busX;
    int busPosY = 120 + busY;

    glColor3f(0.1, 0.3, 0.2); // Set color to dark green
    glBegin(GL_POLYGON);
    glVertex2d(busPosX, busPosY);
    glVertex2d(busPosX, busPosY + 80);
    glVertex2d(busPosX + 150, busPosY + 80);
    glVertex2d(busPosX + 150, busPosY);
    glEnd();

    glColor3f(0.7, 1, 1); // Set color to light blue
    glBegin(GL_POLYGON);
    glVertex2d(busPosX + 20, busPosY + 10);
    glVertex2d(busPosX + 20, busPosY + 70);
    glVertex2d(busPosX + 60, busPosY + 70);
    glVertex2d(busPosX + 60, busPosY + 10);
    glEnd();

    glColor3f(0.7, 1, 1); // Set color to light blue
    glBegin(GL_POLYGON);
    glVertex2d(busPosX + 90, busPosY + 10);
    glVertex2d(busPosX + 90, busPosY + 70);
    glVertex2d(busPosX + 130, busPosY + 70);
    glVertex2d(busPosX + 130, busPosY + 10);
    glEnd();

    wheel(busPosX + 30, busPosY, 13);
    wheel(busPosX + 120, busPosY, 13);*/


void drawCar()
{
/*
    int carPosX = 50 + carX;
    int carPosY = 120 + carY;

    glColor3f(0.9, 0.5, 0.1); // Set color to orange
    glBegin(GL_POLYGON);
    glVertex2d(carPosX, carPosY);
    glVertex2d(carPosX, carPosY + 80);
    glVertex2d(carPosX + 150, carPosY + 80);
    glVertex2d(carPosX + 150, carPosY);
    glEnd();

    glColor3f(0.7, 1, 1); // Set color to light blue
    glBegin(GL_POLYGON);
    glVertex2d(carPosX + 20, carPosY + 10);
    glVertex2d(carPosX + 20, carPosY + 70);
    glVertex2d(carPosX + 60, carPosY + 70);
    glVertex2d(carPosX + 60, carPosY + 10);
    glEnd();

    glColor3f(0.7, 1, 1); // Set color to light blue
    glBegin(GL_POLYGON);
    glVertex2d(carPosX + 90, carPosY + 10);
    glVertex2d(carPosX + 90, carPosY + 70);
    glVertex2d(carPosX + 130, carPosY + 70);
    glVertex2d(carPosX + 130, carPosY + 10);
    glEnd();

    wheel(carPosX + 30, carPosY, 13);
    wheel(carPosX + 120, carPosY, 13);*/
// Calculate the updated car position based on carX and carY
    int carPosX = 400 + carX;
    int carPosY = 120 + carY;

    // Draw the car body
    glColor3f(0.9, 0.5, 0.1); // car
    glBegin(GL_POLYGON);
    glVertex2d(carPosX-128,carPosY);
    glVertex2d(carPosX-118,carPosY+48);
    glVertex2d(carPosX-80,carPosY+48);
 glVertex2d(carPosX-60,carPosY+80);
    //glVertex2d(carPosX, carPosY);
    glVertex2d(carPosX, carPosY + 80);
    glVertex2d(carPosX, carPosY);
    //glVertex2d(carPosX + 120, carPosY + 80);
    //glVertex2d(carPosX + 150, carPosY + 40);
    //glVertex2d(carPosX + 150, carPosY);
    glEnd();
 // Draw the windows
    glColor3f(0.7, 1, 1);
    glBegin(GL_POLYGON);
     glVertex2d(carPosX-84,carPosY+48);
    glVertex2d(carPosX-58,carPosY+78);
    glVertex2d(carPosX-35,carPosY+78);
    glVertex2d(carPosX-35,carPosY+48);
    glEnd();

    glColor3f(0.7, 1, 1);//window
    glBegin(GL_POLYGON);
     glVertex2d(carPosX-33,carPosY+48);
    glVertex2d(carPosX-33,carPosY+78);
    glVertex2d(carPosX-5,carPosY+78);
    glVertex2d(carPosX-5,carPosY+48);
    glEnd();

    //black
      glColor3f(0.2, 0, 0);
    glBegin(GL_POLYGON);
     glVertex2d(carPosX,carPosY+20);
    glVertex2d(carPosX,carPosY+50);
    glVertex2d(carPosX+5,carPosY+50);
    glVertex2d(carPosX+5,carPosY+20);
    glEnd();
 // Draw the wheels
    wheel1(carPosX -92, carPosY);
    wheel1(carPosX -30, carPosY);
    wheel2(carPosX -92, carPosY);
    wheel2(carPosX -30, carPosY);

}/*
void drawExplosion()
{
    glColor3f(1.0, 0.5, 0.0); // Set color to orange
    glBegin(GL_TRIANGLES);
    glVertex2f(explosionX, explosionY );
    glVertex2f(explosionX - 20, explosionY + 40);
    glVertex2f(explosionX + 20, explosionY + 40);
    glEnd();
}
*/
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the sky
    glColor3f(0.4, 0.6, 1.0); // Set color to light blue
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(0, 500);
    glVertex2d(800, 500);
    glVertex2d(800, 0);
    glEnd();

    // Draw the road
    glColor3f(0.2, 0.2, 0.2); // Set color to dark gray
    glBegin(GL_QUADS);
    glVertex2d(0, 50);
    glVertex2d(0, 150);
    glVertex2d(500, 150);
    glVertex2d(500, 50);
    glEnd();

    // Draw the clouds
    cloud(cloud1X, 440, 30);
    cloud(cloud2X, 440, 50);
    cloud(cloud3X, 440, 30);
    cloud(cloud4X, 420, 30);
    cloud(cloud5X, 420, 40);
    cloud(cloud6X, 430, 30);
    cloud(cloud7X, 430, 35);
  glColor3f(1.0, 1.0, 1.0);
glBegin(GL_QUADS);
    glVertex2d(210, 122);
    glVertex2d(213, 130);
    glVertex2d(331, 130);
    glVertex2d(328, 122);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2d(0, 122);
    glVertex2d(0, 130);
    glVertex2d(48, 130);
    glVertex2d(45, 122);
    glEnd();
 glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2d(63, 122);
    glVertex2d(66, 130);
    glVertex2d(185, 130);
    glVertex2d(182, 122);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
     glVertex2d(348, 122);
    glVertex2d(351, 130);
    glVertex2d(470, 130);
    glVertex2d(467, 122);
    glEnd();
 // Draw the grass
    glColor3f(0, 0.5, 0.1);
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(0, 50);
    glVertex2d(800, 50);
    glVertex2d(800, 0);
    glEnd();

    // Draw the vehicles based on the current scene
    if(currentScene==0)
    drawMainScene();
    if (currentScene == 1 || currentScene == 3)
        drawBus();
    if (currentScene == 2 || currentScene == 3)
        drawCar();
     // Draw explosion
    if (explosion)
    {
        glColor3f(1.0, 0.0, 0.0); // Set color to red
         glBegin(GL_TRIANGLE_FAN);
    glVertex2f(explosionX, explosionY);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = explosionX + explosionRadius * cos(angle);
        float y = explosionY + explosionRadius * sin(angle);
        glVertex2f(x, y);
    }
   
    glEnd();





    }
    if(currentScene==4)
    StoryScene();


    glFlush();
    return;
}

void update(int value)
{
      // Update the bus position if scene 1 or scene 3 is active
    if (currentScene == 1 || currentScene == 3)
        busX += busSpeed;

    // Update the car position if scene 2 or scene 3 is active
    if (currentScene == 2 || currentScene == 3)
        carX += carSpeed;


//busX+=busSpeed1;
  //carX+=busSpeed2;
   // Check for collision between the bus and car
    float distance = sqrt((busX - carX) * (busX - carX) + (busY - carY) * (busY - carY));
/*    float collisionThreshold = 100.0;
    if (distance < collisionThreshold)
    {
        isCollision = true;
        explosionX = (busX + carX) / 2;
        explosionY = (busY + carY) / 2;
    }
    else
    {
        isCollision = false;
    }*/
    float collisionThreshold=150.0;
     if (distance <= collisionThreshold && currentScene==3 && !explosion)
    {
        explosion = true;
        explosionX =carX+230;
        explosionY = busY+150;
        explosionRadius = 0.0;
    }

    // Update explosion radius
    if (explosion)
    {
        explosionRadius += 10.0;
    //    explosionRadius+=10.0;
        if (explosionRadius > 800.0)
        {
            explosion = false;
            // Reset positions
            busX = -500.0;
            busY = 0.0;
            carX = 500.0;
            carY = 0.0;
            currentScene = 4;
        }
    }

/*
if(isCollision)
{
drawExplosion();
}*/
    //elapsedTime++;

    // Update the positions of the bus, car, and clouds
    busX -= 0.1;
    carX -= 0.3;
    cloud1X += 0.05;
    cloud2X += 0.06;
    cloud3X += 0.07;
    cloud4X += 0.08;
    cloud5X += 0.09;
    cloud6X += 0.1;
    cloud7X += 0.11;

    // Reset the positions when they go off the screen
    if (busX >800)
        busX = -500;
    if (carX < -500)
        carX = 800;
    if (cloud1X > 500)
        cloud1X = -50;
    if (cloud2X > 500)
        cloud2X = -60;
    if (cloud3X > 500)
        cloud3X = -70;
    if (cloud4X > 500)
        cloud4X = -80;
    if (cloud5X > 500)
        cloud5X = -90;
    if (cloud6X > 500)
        cloud6X = -100;
    if (cloud7X > 500)
        cloud7X = -110;
    elapsedTime += value;
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
        currentScene = 1;
    else if (key == '2')
        currentScene = 2;
    else if (key == '3')
   {
        currentScene = 3;

        // Reset the positions of the bus and car when key 3 is pressed
        busX = -500.0;
        carX = 500.0;
    }
    else if(key == '4' ){
    currentScene=4;
    StoryScene();
    }

        //currentScene = 3;

    glutPostRedisplay();
}
void timer(int value)
{
    update(value);
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}


void myInit(void)
{
    glClearColor(0.3, 0.9, 1.0, 0);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bus and Car Animation");
    myInit();
    glutDisplayFunc(drawScene);
    glutTimerFunc(10, update, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


