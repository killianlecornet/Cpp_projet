
 #include <SFML/Graphics.hpp>

 using namespace sf;

 int main()
 {

     RenderWindow app(VideoMode(520, 450), "BRICK SHOOTER!");  //taille de l'image et titre
     app.setFramerateLimit(60); //fps du jeu

     Texture t1,t2,t3,t4;
     t1.loadFromFile("images/block02.png");  // image du block
     t2.loadFromFile("images/background.jpg"); //image du fond d'écran
     t3.loadFromFile("images/ball.png"); //image de la balle
     t4.loadFromFile("images/paddle.png");

     Sprite sBackground(t2), sBall(t3), sPaddle(t4);
     sPaddle.setPosition(300,440);  // position du paddle au départ

     Sprite block[1000];

     int n=0;
     for (int i=1;i<=10;i++) //nombre de block en horizontale
     for (int j=1;j<=10;j++) //nombre de block en verticale
       {
          block[n].setTexture(t1);
          block[n].setPosition(i*43,j*20); //position des rectangles
          n++;
       }

     float dx=4, dy=3; // mouvement de la balle en hauteur et en largeur
     float x=150, y=300; //position de la balle au départ

     while (app.isOpen())
     {
        Event e;
        while (app.pollEvent(e))
        {
          if (e.type == Event::Closed)
              app.close();
        }

     x+=dx;
     for (int i=0;i<n;i++)
         if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) //permet de deplacer les block
              {block[i].setPosition(-100,0); dx=-dx;}


     y+=dy;
     for (int i=0;i<n;i++)
         if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) //permet de deplacer les block
              {block[i].setPosition(-100,0); dy=-dy;}

     if (x<0 || x>520)  dx=-dx;
     if (y<0 || y>450)  dy=-dy;

     if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(8,0); // vitesse du paddle vers la droite
     if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-8,0); // vitesse du paddle vers la gauche

     if ( FloatRect(x,y,12,12).intersects(sPaddle.getGlobalBounds()) ) dy=-(rand()%5+2); // permet a la balle de rebonsir sur le paddle

     sBall.setPosition(x,y);

     app.clear();
     app.draw(sBackground);
     app.draw(sBall);
     app.draw(sPaddle);

     for (int i=0;i<n;i++)
      app.draw(block[i]);

     app.display();
     }

   return 0;
 }
