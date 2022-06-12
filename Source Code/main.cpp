#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "customrectangleshape.h"

using namespace std;

class Animated : public sf::Sprite
{
public:
    int speedx = 0;
    int speedy = 0;
    Animated(int fps, const string &texture_path) : time_beetween_frames(1.0f / fps)
    {
        texture.loadFromFile(texture_path);
        setTexture(texture);
    }

    void animationframe(const sf::IntRect &frame)
    {
        frames.emplace_back(frame);
        if(frames.size() == 1)
        {
            setTextureRect(frames.at(0));
        }

    }

    float animate(const sf::Time &elapsed)
    {
        auto secounds = elapsed.asSeconds();
        move(speedx * secounds, speedy * secounds);
        float run;
        bool runup;
        bool runside;



        bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        if(up == false and down ==false)
        {
            speedy = 0;
             runup = false;
        }else {runup = true;}

        bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        if(right == false and left ==false)
        {
            speedx = 0;
             runside= false;
        }else {runside = true;}
        if (runup == false and runside ==false)
        {
            run = 0;
        }else {run = 1;}

        secounds_per_frame += elapsed.asSeconds();



        if(not frames.empty()and secounds_per_frame >= time_beetween_frames)
        {
            index = (index + 1) % frames.size();
            setTextureRect(frames[index]);
            secounds_per_frame = 0;
        }
        return run;


    }
    void animateNPC(const sf::Time &elapsed)
    {
        secounds_per_frame += elapsed.asSeconds();


        if(not frames.empty()and secounds_per_frame >= time_beetween_frames)
        {
            index = (index + 1) % frames.size();
            setTextureRect(frames[index]);
            secounds_per_frame = 0;
        }

    }

    void key_pressed(sf::Keyboard::Key key, bool runenable)
    {


        if (runenable == true){
            if(key == sf::Keyboard::Up)
            {
                speedy = -200;

            }else if(key == sf::Keyboard::Down)
            {
                speedy = 200;

            }else if(key == sf::Keyboard::Right)
            {
                speedx = 200;
                setOrigin(getLocalBounds().width / 2, 0);
                auto scale = getScale();
                setScale(abs(scale.x),scale.y);

            }else if(key == sf::Keyboard::Left)
            {
                speedx = -200;
                setOrigin(getLocalBounds().width / 2, 0);
                auto scale = getScale();
                setScale(-abs(scale.x),scale.y);

            }else{ speedx = 0; speedy = 0;}
        }



    };

    bool interact(const sf::RectangleShape &questgiver1, bool quest1)
    {
       bool quest_active;
       if (quest1 == false)
       {quest_active = false;} else {quest_active = true;}


       bool interaction = getGlobalBounds().intersects(questgiver1.getGlobalBounds());
       if(interaction)
       {quest_active = true;}


       return quest_active;
    };

    bool Contact(const sf::RectangleShape &space)
    {

       bool interaction = getGlobalBounds().intersects(space.getGlobalBounds());

       return interaction;
    };



private:
    sf::Texture texture;
    vector<sf::IntRect> frames;
    int index = 0;
    float secounds_per_frame = 0;
    float time_beetween_frames = 0;

};
bool Switch(bool check)
{
   bool aftercheck;
   if (check == false)
   {aftercheck = false;} else {aftercheck = true;}
   return aftercheck;
};

int main()
{
    std::srand(std::time(nullptr));

    sf::Time elapsed;
    int score = 0;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "MFRPG - 0.1.2 - Hubert Marciniak");
    sf::Texture tex;
    tex.loadFromFile("grass.png");
    sf::Sprite back(tex);
    sf::Texture bare;
    bare.loadFromFile("floor.png");
    sf::Sprite Bare(bare);
    sf::Texture top;
    top.loadFromFile("floortop.png");
    sf::Sprite Top(top);
    sf::Texture mid;
    mid.loadFromFile("floormid.png");
    sf::Sprite Mid(mid);
    sf::Texture st;
    st.loadFromFile("stairs.png");
    sf::Sprite Stairs(st);
    sf::Texture bot;
    bot.loadFromFile("floorbottom.png");
    sf::Sprite Bottom(bot);
    sf::Texture call;
    call.loadFromFile("Callback.png");
    sf::Sprite DialogCall(call);
    sf::Texture go;
    go.loadFromFile("Gameover.png");
    sf::Sprite over(go);
    sf::Texture t1;
    t1.loadFromFile("Tutorial1.png");
    sf::Sprite tutorial1(t1);
    sf::Texture t2;
    bool tut1 = true;
    t2.loadFromFile("Tutorial2.png");
    sf::Sprite tutorial2(t2);
    bool tut2 = true;
    sf::Texture t3;
    t3.loadFromFile("Tutorial3.png");
    sf::Sprite tutorial3(t3);
    bool tut3 = true;

    window.setVerticalSyncEnabled(true);

    Animated Titlecard(5,"TitleAnimation.png");
    Titlecard.setPosition(0,0);
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(1600, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(2400, 0, 800, 600));
    Titlecard.animationframe(sf::IntRect(2400, 0, 800, 600));

    Animated Finalanimation(6,"TitleAnimation.png");
    Finalanimation.setPosition(0,0);

    int iforfinal = 0;
    Animated Finalframe(6,"TitleAnimation.png");
    Finalframe.setPosition(0,0);
    Finalframe.animationframe(sf::IntRect(0, 0, 800, 600));

    Animated Hero(10,"character.png");
    Hero.setScale(2, 2);
    Hero.setPosition(50,400);
    Hero.animationframe(sf::IntRect(150, 0, 50, 37)); // hero running frame 1
    Hero.animationframe(sf::IntRect(200, 0, 50, 37)); // hero running frame 2
    Hero.animationframe(sf::IntRect(250, 0, 50, 37)); // hero running frame 3
    Hero.animationframe(sf::IntRect(300, 0, 50, 37)); // hero running frame 4
    Hero.animationframe(sf::IntRect(350, 0, 50, 37)); // hero running frame 5
    Hero.animationframe(sf::IntRect(400, 0, 50, 37)); // hero running frame 6

    Animated Herotop(10,"character.png");
    Herotop.setScale(2, 2);
    Herotop.setPosition(50,400);
    Herotop.animationframe(sf::IntRect(150, 0, 50, 25)); // hero running frame 1
    Herotop.animationframe(sf::IntRect(200, 0, 50, 25)); // hero running frame 2
    Herotop.animationframe(sf::IntRect(250, 0, 50, 25)); // hero running frame 3
    Herotop.animationframe(sf::IntRect(300, 0, 50, 25)); // hero running frame 4
    Herotop.animationframe(sf::IntRect(350, 0, 50, 25)); // hero running frame 5
    Herotop.animationframe(sf::IntRect(400, 0, 50, 25)); // hero running frame 6

    Animated Herowalk(5,"character.png");
    Herowalk.setScale(2, 2);
    Herowalk.setPosition(50,400);
    Herowalk.animationframe(sf::IntRect(0, 0, 50, 37)); // hero standing frame 1
    Herowalk.animationframe(sf::IntRect(50, 0, 50, 37)); // hero standing frame 2
    Herowalk.animationframe(sf::IntRect(100, 0, 50, 37)); // hero standing frame 3

    Animated Herowalktop(5,"character.png");
    Herowalktop.setScale(2, 2);
    Herowalktop.setPosition(50,400);
    Herowalktop.animationframe(sf::IntRect(0, 0, 50, 25)); // hero standing frame 1
    Herowalktop.animationframe(sf::IntRect(50, 0, 50, 25)); // hero standing frame 2
    Herowalktop.animationframe(sf::IntRect(100, 0, 50, 25)); // hero standing frame 3

    Animated NPC1(4,"NPC1.png");
    NPC1.setScale(-2, 2);
    NPC1.setPosition(600,210);
    NPC1.animationframe(sf::IntRect(0, 0, 50, 37)); //  standing frame 1
    NPC1.animationframe(sf::IntRect(50, 0, 50, 37)); //  standing frame 2
    NPC1.animationframe(sf::IntRect(100, 0, 50, 37)); //  standing frame 3
    sf::RectangleShape INPC1(sf::Vector2f(60, 60));
    INPC1.setPosition(520,230);

    Animated Ghost(4,"Ghost1.png");
    Ghost.setScale(-2, 2);
    Ghost.animationframe(sf::IntRect(0, 0, 50, 37)); //  standing frame 1
    Ghost.animationframe(sf::IntRect(50, 0, 50, 37)); //  standing frame 2
    Ghost.animationframe(sf::IntRect(100, 0, 50, 37)); //  standing frame 3
    Ghost.setOrigin(Ghost.getLocalBounds().width / 2, 0);
    sf::RectangleShape Hitbox(sf::Vector2f(10, 10));
    Animated north(4,"TextN.png");
    north.setScale(0.5, 0.5);
    north.setPosition(0,350);
    Animated Swordlost(4,"TextA.png");
    Swordlost.setScale(0.5, 0.5);
    Swordlost.setPosition(0,350);
    Animated Scoreboard(4,"SCboard.png");
    Scoreboard.setScale(0.5, 0.5);
    Scoreboard.setPosition(550,250);
    sf::Text Score_text;
    std::stringstream ss;  // #include <sstream>
    ss << score;
    Score_text.setFillColor(sf::Color::Red);
    Score_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    Score_text.setPosition(650, 330);
    Score_text.setCharacterSize(54);
    sf::Font font;
    Score_text.setFont(font);
    font.loadFromFile("arial.ttf");

    // Location
    bool Village = true;
    bool Mansion = false;

    // State

    bool Contact = false;
    bool sword = false;
    int selected = 0;
    int iforselected = 0;
    int iforchoice = 0;
    int iforsword = 0;
    bool confirmchoice = false;
    bool drawas = false;
    bool drawws = false;
    bool Victory = false;
    Animated overlay(4,"CombatOverlay.png");
    overlay.setScale(0.5, 0.5);
    overlay.setPosition(0,350);
    sf::Texture com;
    com.loadFromFile("Combatcall.png");
    sf::Sprite Combatcall(com);
    Animated HeroC(5,"character.png");
    HeroC.setScale(7, 7);
    HeroC.setPosition(0,100);
    HeroC.animationframe(sf::IntRect(0, 0, 50, 37)); // hero standing frame 1
    HeroC.animationframe(sf::IntRect(50, 0, 50, 37)); // hero standing frame 2
    HeroC.animationframe(sf::IntRect(100, 0, 50, 37)); // hero standing frame 3
    Animated EnemyC(5,"Ghost1.png");
    EnemyC.setScale(-7, 7);
    EnemyC.setPosition(801,100);
    EnemyC.animationframe(sf::IntRect(0, 0, 50, 37)); //  standing frame 1
    EnemyC.animationframe(sf::IntRect(50, 0, 50, 37)); //  standing frame 2
    EnemyC.animationframe(sf::IntRect(100, 0, 50, 37)); //  standing frame 3
    Animated a(4,"Attack.png");
    a.setScale(0.5, 0.5);
    a.setPosition(10,365);
    Animated w(4,"Weapon.png");
    w.setScale(0.5, 0.5);
    w.setPosition(10,440);
    Animated r(4,"Run.png");
    r.setScale(0.5, 0.5);
    r.setPosition(10,515);
    Animated as(4,"ASkill.png");
    as.setScale(0.7, 0.7);
    as.setPosition(270,400);
    Animated ws(4,"WSkill.png");
    ws.setScale(0.7, 0.7);
    ws.setPosition(270,400);
    Animated reg(4,"Regularslash.png");
    reg.setScale(0.5, 0.5);
    reg.setPosition(390,140);
    Animated skill(4,"Skillslash.png");
    skill.setScale(0.5, 0.5);
    skill.setPosition(390,140);
    Animated Escape(4,"Escape.png");
    Escape.setScale(1, 1);
    Escape.setPosition(300,200);




    bool runenable = true;
    bool Dialog = true;
    bool Dialog2 = true;
    bool Fin = false;
    bool End = false;
    bool Text1 = true;
    bool Text2 = true;
    bool Text3 = true;
    Animated NPCD(4,"NPC1.png");
    NPCD.setScale(-10, 10);
    NPCD.setPosition(801,100);
    NPCD.animationframe(sf::IntRect(0, 0, 50, 37)); //  standing frame 1
    NPCD.animationframe(sf::IntRect(50, 0, 50, 37)); //  standing frame 2
    NPCD.animationframe(sf::IntRect(100, 0, 50, 37)); //  standing frame 3
    Animated HeroD(5,"character.png");
    HeroD.setScale(10, 10);
    HeroD.setPosition(0,100);
    HeroD.animationframe(sf::IntRect(0, 0, 50, 37)); // hero standing frame 1
    HeroD.animationframe(sf::IntRect(50, 0, 50, 37)); // hero standing frame 2
    HeroD.animationframe(sf::IntRect(100, 0, 50, 37)); // hero standing frame 3
    Animated Call1(4,"Text1.png");
    Call1.setScale(0.5, 0.5);
    Call1.setPosition(0,350);
    Animated Call2(4,"Text2.png");
    Call2.setScale(0.5, 0.5);
    Call2.setPosition(0,350);
    Animated Call3(4,"Text3.png");
    Call3.setScale(0.5, 0.5);
    Call3.setPosition(0,350);
    Animated Spc(4,"Spc.png");
    Spc.setScale(0.7, 0.7);
    Spc.setPosition(450,550);
    Animated Esc(4,"Esc.png");
    Esc.setScale(0.7, 0.7);
    Esc.setPosition(470,570);

    // QUESTS
    bool quest1 = false;
    Animated QuestM1(1,"QM1.png");
    QuestM1.setScale(1, 1);
    QuestM1.setPosition(545,170);
    Animated Quest1(4,"Quest1.png");
    Quest1.setScale(1, 1);
    Quest1.setPosition(0,0);
    Animated QuestHidden(4,"QuestH.png");
    QuestHidden.setScale(1, 1);
    QuestHidden.setPosition(0,0);

    int i = 0;
    int a1;
    int a2;
    int a3;
    int a4;
    int b2;
    int b3;
    int c1;
    int c2;
    int c3;
    int c4;
    Animated tile1 (1,"Tile1.png");
    Animated tile2 (1,"Tile2.png");
    Animated tile3 (1,"Tile3.png");
    Animated tile4 (1,"Tile4.png");
    Animated tile5 (1,"Tile5.png");
    Animated tile6 (1,"Tile6.png");
    Animated tile7 (1,"Tile7.png");
    Animated tile8 (1,"Tile8.png");
    Animated tile9 (1,"Tile9.png");
    Animated tile10 (1,"Tile10.png");
    Animated tile11 (1,"Tile11.png");

    // run the program as long as the window is open
    sf::Clock clock;
    bool title = true;
    while (window.isOpen()) {
        quest1 = Hero.interact(INPC1,quest1);

      sf::Event event;
      while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
          window.close();
          return 0;
        } else if (event.type == sf::Event::KeyPressed) {
            if(End == true)
            {runenable = false;}
          Hero.key_pressed(event.key.code, runenable);
          Herowalk.key_pressed(event.key.code,runenable);
          Herotop.key_pressed(event.key.code,runenable);
          Herowalktop.key_pressed(event.key.code,runenable);
          title = false;
        }

      }

      sf::Time elapsed = clock.restart();


      // clear the window with black color
      window.clear(sf::Color(64,141,74)); 

      if (Village == true)
      {
          window.draw(back);
          window.draw(NPC1);
          //window.draw(INPC1);

          NPC1.animateNPC(elapsed);
      }else if (Mansion == true)
      {
          window.draw(Bare);
      }


      if(quest1)
      {
          if (Dialog==false)
          {
              runenable = true;
              if(Victory == false)
              {if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                  {
                     window.draw(Quest1);
                  }else{window.draw(QuestHidden);}
              }

          } else
          {
              runenable = false;
              if (Text1 == true)
              {
                  window.draw(DialogCall);
                  window.draw(HeroD);
                  window.draw(NPCD);
                  window.draw(Spc);
                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                  {Text1 = false;}
              }else
              {
                 if (Text2== true)
                 {
                     window.draw(DialogCall);
                     window.draw(HeroD);
                     window.draw(NPCD);
                     window.draw(Esc);
                     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                     {Text2 = false;}
                 }else{Dialog=false;runenable = true;}
              }
          }
      }else if(Village == true){
          window.draw(QuestM1);
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
          window.draw(Hero);

      }else
      {
          Herowalk.setPosition(Hero.getPosition().x , Hero.getPosition().y);
         window.draw(Herowalk);
      }



      HeroD.animateNPC(elapsed);
      NPCD.animateNPC(elapsed);
      EnemyC.animate(elapsed);
      HeroC.animate(elapsed);
      Hero.animate(elapsed);
      Herowalk.animate(elapsed);
      Herotop.animate(elapsed);
      Ghost.animate(elapsed);
      Herowalktop.animate(elapsed);
      Finalanimation.animate(elapsed);//                                    ANIMATE

      // Object Collision
        // Village
      if(Village == true)
      {
          // tutorial 1
          if (tut1 == true)
          {
              window.draw(tutorial1);
              window.draw(Esc);
              runenable = false;
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
              {
                  tut1 =false;
                  runenable = true;
              }
          }
          // ------------------Titlecard
          if (title == true)
          {
             window.draw(Titlecard);
             Titlecard.animateNPC(elapsed);
          }
          // Window Border

          if (Hero.getPosition().x < 60)
          {
              Hero.setPosition(60, Hero.getPosition().y);
          }
          if (Hero.getPosition().x > 740)
          {
              // Mansion Gate
              if(Hero.getPosition().y >200 and Hero.getPosition().y <300)
              { if(quest1)
                  {
                      if(Hero.getPosition().x > 770)
                      {

                          // MANSION RANDOMISER ---------------------------------------------------------------------------------------
                          c4 = rand() % 3;
                          if(c4 == 1)
                          {
                              c3 = rand() % 5;
                          }else { c3 = rand() % 6;}
                          if (c3 == 4)
                          {c2 = rand() % 7;}else
                          {c2 = 8;}
                          if (c2 == 3){c1 = rand() % 3;}else{c1 = rand() % 4;}
                          if (c1 == 3){b2 = rand() % 4;}else{b2 = rand() % 5;}
                          if(c2 == 8 and b2 == 3)
                          {
                            b3 = 0;
                          } else {b3= rand() % 5;}

                          a1= rand() % 4;
                          a2= rand() % 3;
                          a3= rand() % 3;
                          a4= rand() % 4;
                          //----------------------------------------------------------------------------------------------------------------
                          Mansion = true;
                          Village = false;
                          Hero.setPosition(50, Hero.getPosition().y);
                          Ghost.setPosition(700, 450);
                          EnemyC.setPosition(801,100);
                          if (sword == true)
                          {
                              sword = false;
                          }
                          iforsword = 0;
                      }

                  }else {Hero.setPosition(741, Hero.getPosition().y);}

              }else {Hero.setPosition(740, Hero.getPosition().y);}

          }
          if (Hero.getPosition().y < 30)
          {
              Hero.setPosition(Hero.getPosition().x, 30);
          }
          if (Hero.getPosition().y < 32 and Hero.getPosition().x < 450 and Hero.getPosition().x > 350)
          {
              if (Fin == false)
              {
                  window.draw(north);
              }else
              {// --------------------Ending Cutscene

                  End = true;
                  Finalanimation.animationframe(sf::IntRect(0, 100, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 95, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 90, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 85, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 80, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 75, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 70, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 65, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 60, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 55, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 50, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 40, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 30, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 20, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 10, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 0, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 0, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 0, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 0, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(0, 0, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(800, 0, 800, 600));
                  Finalanimation.animationframe(sf::IntRect(800, 0, 800, 600));
                  if (iforfinal < 505)
                  {
                      window.draw(Finalanimation);
                      iforfinal = iforfinal + 1;
                  }else{window.draw(Finalframe);}
              }

          }
          if (Hero.getPosition().y >  510)
          {
              Hero.setPosition(Hero.getPosition().x, 510);
          }

          // Blue Building
          if(Hero.getPosition().x >450 and Hero.getPosition().x < 455 and Hero.getPosition().y >20 and Hero.getPosition().y <190 )
          {
              Hero.setPosition(450, Hero.getPosition().y );
          }
          if(Hero.getPosition().x > 455 and Hero.getPosition().x < 715 and Hero.getPosition().y <190 )
          {
              Hero.setPosition(Hero.getPosition().x, 190);
          }
          if(Hero.getPosition().x <720 and Hero.getPosition().x > 715 and Hero.getPosition().y <190 )
          {
              Hero.setPosition(720, Hero.getPosition().y );
          }
          // Orange Building
          if(Hero.getPosition().x >530 and Hero.getPosition().x < 550 and Hero.getPosition().y >350)
          {
              Hero.setPosition(530, Hero.getPosition().y );
          }
          if(Hero.getPosition().x > 550 and Hero.getPosition().x < 750 and Hero.getPosition().y >350 )
          {
              Hero.setPosition(Hero.getPosition().x, 350);
          }
          // Red Building
          if(Hero.getPosition().x >5 and Hero.getPosition().x < 300 and Hero.getPosition().y <155)
          {
              Hero.setPosition(300, Hero.getPosition().y );
          }
          if(Hero.getPosition().x > 5 and Hero.getPosition().x < 295 and Hero.getPosition().y <160 )
          {
              Hero.setPosition(Hero.getPosition().x, 160);
          }
          // Ending Dialog
          if (Victory == true)
          {
              if (Fin == false)
              {
                  window.draw(QuestM1);
              }
              Fin = Hero.interact(INPC1,Fin);
          }
      }

      if (Mansion == true)
      {

          //Enemy
          window.draw(Ghost);
          if(iforsword > 97 or Victory == false)
          {
              if(tut2 == false)
              {
                  if(Hero.getPosition().x > Ghost.getPosition().x)
                  {
                     Ghost.move(0.7,0);
                     Ghost.setScale(2,2);
                  } else if(Hero.getPosition().x < Ghost.getPosition().x)
                  {
                      Ghost.move(-0.7,0);
                      Ghost.setScale(-2,2);
                  }
                  if(Hero.getPosition().y > Ghost.getPosition().y)
                  {
                     Ghost.move(0,0.7);

                  } else if(Hero.getPosition().y < Ghost.getPosition().y)
                  {
                      Ghost.move(0,-0.7);

                  }
              }

          }


          Hitbox.setPosition(Ghost.getPosition().x, Ghost.getPosition().y+40);
          Contact = Hero.Contact(Hitbox);

          // Window Border

          if (Hero.getPosition().x < 30)
          {
              Hero.setPosition(30, Hero.getPosition().y);
          }
          if (Hero.getPosition().x > 760)
          {
              Hero.setPosition(760, Hero.getPosition().y);
          }
          if (Hero.getPosition().y < 5)
          {
              Hero.setPosition(Hero.getPosition().x, 5);
          }
          if (Hero.getPosition().y >  520)
          {
              Hero.setPosition(Hero.getPosition().x, 520);
          }

          // Mansion Builder----------------------------------------------------------------------
          //Premament----Premament----Premament----Premament----Premament----Premament----Premament----Premament----Premament----
          window.draw(Top);
          if(Hero.getPosition().x >170 and Hero.getPosition().x < 180 and Hero.getPosition().y >230 and Hero.getPosition().y <340 )
          {
              Hero.setPosition(170, Hero.getPosition().y);// Left Wall Left Side
          }
          if(Hero.getPosition().x >210 and Hero.getPosition().x < 220 and Hero.getPosition().y >230 and Hero.getPosition().y <340 )
          {
              Hero.setPosition(220, Hero.getPosition().y);// Left Wall Right Side
          }
          if(Hero.getPosition().x >180 and Hero.getPosition().x < 210 and Hero.getPosition().y >230 and Hero.getPosition().y <240 )
          {
              Hero.setPosition(Hero.getPosition().x, 230);// Left Wall Top Side
          }
          if(Hero.getPosition().x >180 and Hero.getPosition().x < 210 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
          {
              Hero.setPosition(Hero.getPosition().x, 340);// Left Wall Bottom Side
          }

          if(Hero.getPosition().x >110 and Hero.getPosition().x < 119 and Hero.getPosition().y >160 and Hero.getPosition().y <190 )
          {
              Hero.setPosition(120, Hero.getPosition().y);//
          }
          if(Hero.getPosition().x >10 and Hero.getPosition().x < 120 and Hero.getPosition().y >150 and Hero.getPosition().y <160 )
          {
              Hero.setPosition(Hero.getPosition().x, 150);//
          }
          if(Hero.getPosition().x >10 and Hero.getPosition().x < 120 and Hero.getPosition().y >190 and Hero.getPosition().y <200 )
          {
              Hero.setPosition(Hero.getPosition().x, 200);//
          }

          if(Hero.getPosition().x >150 and Hero.getPosition().x < 205  and Hero.getPosition().y >150 and Hero.getPosition().y <160 )
          {
              Hero.setPosition(Hero.getPosition().x, 150);//
          }
          if(Hero.getPosition().x >150 and Hero.getPosition().x < 205 and Hero.getPosition().y >190 and Hero.getPosition().y <200 )
          {
              Hero.setPosition(Hero.getPosition().x, 200);//
          }
          if(Hero.getPosition().x >185 and Hero.getPosition().x < 220 and Hero.getPosition().y >160 and Hero.getPosition().y <190 )
          {
              Hero.setPosition(220, Hero.getPosition().y);//
          }
          if(Hero.getPosition().x >140 and Hero.getPosition().x < 160 and Hero.getPosition().y >160 and Hero.getPosition().y <190 )
          {
              Hero.setPosition(140, Hero.getPosition().y);//
          }

          if(Hero.getPosition().x >110 and Hero.getPosition().x < 138 and Hero.getPosition().y >310 and Hero.getPosition().y <340 )
          {
              Hero.setPosition(138, Hero.getPosition().y);//
          }
          if(Hero.getPosition().x >10 and Hero.getPosition().x < 130 and Hero.getPosition().y >300 and Hero.getPosition().y <310 )
          {
              Hero.setPosition(Hero.getPosition().x, 300);//
          }
          if(Hero.getPosition().x >10 and Hero.getPosition().x < 130 and Hero.getPosition().y >340 and Hero.getPosition().y <350 )
          {
              Hero.setPosition(Hero.getPosition().x, 350);//
          }

          if(Hero.getPosition().x >580 and Hero.getPosition().x < 590 and Hero.getPosition().y >160 and Hero.getPosition().y <340 )
          {
              Hero.setPosition(580, Hero.getPosition().y);// Right Wall Left Side
          }
          if(Hero.getPosition().x >630 and Hero.getPosition().x < 640 and Hero.getPosition().y >160 and Hero.getPosition().y <340 )
          {
              Hero.setPosition(640, Hero.getPosition().y);// Right Wall Right Side
          }
          if(Hero.getPosition().x >590 and Hero.getPosition().x < 630 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
          {
              Hero.setPosition(Hero.getPosition().x, 340);// Right Wall Bottom Side
          }

          if(Hero.getPosition().x >580 and Hero.getPosition().x <800 and Hero.getPosition().y >140 and Hero.getPosition().y <170 )
          {
              Hero.setPosition(Hero.getPosition().x, 140);//
          }
          if(Hero.getPosition().x >580 and Hero.getPosition().x <800 and Hero.getPosition().y >190 and Hero.getPosition().y <235 )
          {
              Hero.setPosition(Hero.getPosition().x, 235);
          }

          if(Hero.getPosition().x >580 and Hero.getPosition().x <800 and Hero.getPosition().y >290 and Hero.getPosition().y <335 )
          {
              //Chest entrance
              if( Hero.getPosition().x <670)
              {
                  Hero.setPosition(Hero.getPosition().x, 335);
              }else if (Hero.getPosition().x >705)
              {
                  Hero.setPosition(Hero.getPosition().x, 335);
              }

          }
          if(Hero.getPosition().x >580 and Hero.getPosition().x <800 and Hero.getPosition().y >200 and Hero.getPosition().y <335 )
          {
              //Chest interior
              if( Hero.getPosition().x <680)
              {
                  Hero.setPosition(680, Hero.getPosition().y);
              }else if (Hero.getPosition().x >700)
              {
                  Hero.setPosition(700, Hero.getPosition().y);
              }else if (Hero.getPosition().x <700 and Hero.getPosition().x > 680)
              {
                  if (Victory == false)
                  {
                    sword = true;
                  } else
                  {
                      // MANSION RANDOMISER ---------------------------------------------------------------------------------------
                      c4 = rand() % 3;
                      if(c4 == 1)
                      {
                          c3 = rand() % 5;
                      }else { c3 = rand() % 6;}
                      if (c3 == 4)
                      {c2 = rand() % 7;}else
                      {c2 = 8;}
                      if (c2 == 3){c1 = rand() % 3;}else{c1 = rand() % 4;}
                      if (c1 == 3){b2 = rand() % 4;}else{b2 = rand() % 5;}
                      if(c2 == 8 and b2 == 3)
                      {
                        b3 = 0;
                      } else {b3= rand() % 5;}

                      a1= rand() % 4;
                      a2= rand() % 3;
                      a3= rand() % 3;
                      a4= rand() % 4;
                      //----------------------------------------------------------------------------------------------------------------
                      Hero.setPosition(50, Hero.getPosition().y);
                      Ghost.setPosition(700, 450);
                      EnemyC.setPosition(801,100);
                      score = score + 1;

                  }
              }

          }

          //Premament----Premament----Premament----Premament----Premament----Premament----Premament----Premament----Premament----
          if (a1== 0)
          {
              Animated copya1tile1 (1,"Tile1.png");
              copya1tile1.setPosition(0,-20);
              window.draw(copya1tile1);

              if(Hero.getPosition().x >60 and Hero.getPosition().x < 65 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(65, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >00 and Hero.getPosition().x < 10 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(00, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >00 and Hero.getPosition().x < 70 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >00 and Hero.getPosition().x < 70 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >67 and Hero.getPosition().x < 80 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(67, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >90 and Hero.getPosition().x < 130 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(130, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >190 and Hero.getPosition().x < 220 and Hero.getPosition().y >35 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(220, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >67 and Hero.getPosition().x < 200 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >67 and Hero.getPosition().x < 200 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);
              }

          }else if (a1 == 1)
          {
              Animated copya1tile7 (1,"Tile7.png");
              copya1tile7.setPosition(0,-20);
              window.draw(copya1tile7);
              //Tile 7 -------------------------------Unique
              if(Hero.getPosition().x >110 and Hero.getPosition().x < 120 and Hero.getPosition().y >0 and Hero.getPosition().y <60 )
              {
                 Hero.setPosition(110, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >155 and Hero.getPosition().x < 165 and Hero.getPosition().y >0 and Hero.getPosition().y <60  )
              {
                  Hero.setPosition(165, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >120 and Hero.getPosition().x <165 and Hero.getPosition().y >50 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 60);//
              }
              if(Hero.getPosition().x >0 and Hero.getPosition().x < 0 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                 Hero.setPosition(0, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >95 and Hero.getPosition().x < 110 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(110 , Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >0 and Hero.getPosition().x < 110 and Hero.getPosition().y >80 and Hero.getPosition().y <90 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >0 and Hero.getPosition().x < 110 and Hero.getPosition().y >125 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 135);//
              }
          }else if (a1 == 2)
          {
              Animated copya1tile2 (1,"Tile2.png");
              copya1tile2.setPosition(0,-20);
              window.draw(copya1tile2);
              if(Hero.getPosition().x >220 and Hero.getPosition().x < 235 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(235, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >141 and Hero.getPosition().x < 150 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(141, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >141 and Hero.getPosition().x < 235 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >141 and Hero.getPosition().x < 235 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >67 and Hero.getPosition().x < 80 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(67, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >90 and Hero.getPosition().x < 140 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(140, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >0 and Hero.getPosition().x < 140 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);
              }
              if(Hero.getPosition().x >0 and Hero.getPosition().x < 140 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);
              }
          }
          else if (a1 == 3)
          {
             Animated copya1tile3 (1,"Tile3.png");
            copya1tile3.setPosition(0,-20);
            window.draw(copya1tile3);
            // ---------------------------------------Left Wall
            if(Hero.getPosition().x >025 and Hero.getPosition().x < 035 and Hero.getPosition().y >00 and Hero.getPosition().y <135  )
            {
                Hero.setPosition(035, Hero.getPosition().y);//
            }
            if(Hero.getPosition().x >00 and Hero.getPosition().x <033 and Hero.getPosition().y >125 and Hero.getPosition().y <135 )
            {
                Hero.setPosition(Hero.getPosition().x, 135);//
            }
          }
          if (a2== 0)
          {
              Animated copya2tile1 (1,"Tile1.png");
              copya2tile1.setPosition(200,-20);
              window.draw(copya2tile1);
              if(Hero.getPosition().x >260 and Hero.getPosition().x < 265 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(265, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >181 and Hero.getPosition().x < 210 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(181, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >200 and Hero.getPosition().x < 270 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >200 and Hero.getPosition().x < 270 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >267 and Hero.getPosition().x < 280 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(267, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >290 and Hero.getPosition().x < 330 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(330, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >390 and Hero.getPosition().x < 420 and Hero.getPosition().y >35 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(420, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >267 and Hero.getPosition().x < 400 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >267 and Hero.getPosition().x < 400 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);
              }
          }else if (a2 == 1)
          {
              Animated copya2tile7 (1,"Tile7.png");
              copya2tile7.setPosition(200,-20);
              window.draw(copya2tile7);
              //Tile 7 -------------------------------Unique
              if(Hero.getPosition().x >310 and Hero.getPosition().x < 320 and Hero.getPosition().y >0 and Hero.getPosition().y <60 )
              {
                 Hero.setPosition(310, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >355 and Hero.getPosition().x < 365 and Hero.getPosition().y >0 and Hero.getPosition().y <60  )
              {
                  Hero.setPosition(365, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >320 and Hero.getPosition().x <365 and Hero.getPosition().y >50 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 60);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >295 and Hero.getPosition().x < 310 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(310 , Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 310 and Hero.getPosition().y >80 and Hero.getPosition().y <90 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 310 and Hero.getPosition().y >125 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 135);//
              }

          }else if (a2 == 2)
          {
              Animated copya2tile2 (1,"Tile2.png");
              copya2tile2.setPosition(200,-20);
              window.draw(copya2tile2);
              // Tile2 --------------------------------------------Unique
              if(Hero.getPosition().x >420 and Hero.getPosition().x < 435 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(435, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >341 and Hero.getPosition().x < 350 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(341, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >341 and Hero.getPosition().x < 435 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >341 and Hero.getPosition().x < 435 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >267 and Hero.getPosition().x < 280 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(267, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >290 and Hero.getPosition().x < 340 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(340, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >185 and Hero.getPosition().x < 200 and Hero.getPosition().y >35 and Hero.getPosition().y <80 )
              {
                 Hero.setPosition(185, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >185 and Hero.getPosition().x < 340 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);
              }
              if(Hero.getPosition().x >185 and Hero.getPosition().x < 340 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);
              }

          }
          if (a3== 0)
          {
              Animated copya3tile1 (1,"Tile1.png");
              copya3tile1.setPosition(400,-20);
              window.draw(copya3tile1);
              if(Hero.getPosition().x >460 and Hero.getPosition().x < 465 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(465, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >381 and Hero.getPosition().x < 410 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(381, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >400 and Hero.getPosition().x < 470 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >400 and Hero.getPosition().x < 470 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >467 and Hero.getPosition().x < 480 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(467, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >490 and Hero.getPosition().x < 530 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(530, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >590 and Hero.getPosition().x < 620 and Hero.getPosition().y >35 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >467 and Hero.getPosition().x < 600 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >467 and Hero.getPosition().x < 600 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);
              }
          }else if (a3 == 1)
          {
              Animated copya3tile7 (1,"Tile7.png");
              copya3tile7.setPosition(400,-20);
              window.draw(copya3tile7);
              //Tile 7 -------------------------------Unique
              if(Hero.getPosition().x >510 and Hero.getPosition().x < 520 and Hero.getPosition().y >0 and Hero.getPosition().y <60 )
              {
                 Hero.setPosition(510, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >555 and Hero.getPosition().x < 565 and Hero.getPosition().y >0 and Hero.getPosition().y <60  )
              {
                  Hero.setPosition(565, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >520 and Hero.getPosition().x <565 and Hero.getPosition().y >50 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 60);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >495 and Hero.getPosition().x < 510 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(510 , Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 510 and Hero.getPosition().y >80 and Hero.getPosition().y <90 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 510 and Hero.getPosition().y >125 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 135);//
              }
          }else if (a3 == 2)
          {
              Animated copya3tile2 (1,"Tile2.png");
              copya3tile2.setPosition(400,-20);
              window.draw(copya3tile2);
              // Tile2 --------------------------------------------Unique
              if(Hero.getPosition().x >620 and Hero.getPosition().x < 635 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(635, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >541 and Hero.getPosition().x < 550 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(541, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >541 and Hero.getPosition().x < 635 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >541 and Hero.getPosition().x < 635 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >467 and Hero.getPosition().x < 480 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(467, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >490 and Hero.getPosition().x < 540 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(540, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >385 and Hero.getPosition().x < 400 and Hero.getPosition().y >35 and Hero.getPosition().y <80 )
              {
                 Hero.setPosition(385, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >385 and Hero.getPosition().x < 540 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);
              }
              if(Hero.getPosition().x >385 and Hero.getPosition().x < 540 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);
              }
          }
          if (a4== 0)
          {
              Animated copya4tile1 (1,"Tile1.png");
              copya4tile1.setPosition(600,-20);
              window.draw(copya4tile1);
              if(Hero.getPosition().x >660 and Hero.getPosition().x < 665 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(665, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >581 and Hero.getPosition().x < 610 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(581, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >600 and Hero.getPosition().x < 670 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >600 and Hero.getPosition().x < 670 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >667 and Hero.getPosition().x < 680 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(667, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >690 and Hero.getPosition().x < 730 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(730, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >790 and Hero.getPosition().x < 820 and Hero.getPosition().y >35 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(820, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >667 and Hero.getPosition().x < 800 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >667 and Hero.getPosition().x < 800 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);//
              }
          }else if (a4 == 1)
          {
              Animated copya4tile7 (1,"Tile7.png");
              copya4tile7.setPosition(600,-20);
              window.draw(copya4tile7);
              //Tile 7 -------------------------------Unique
              if(Hero.getPosition().x >710 and Hero.getPosition().x < 720 and Hero.getPosition().y >0 and Hero.getPosition().y <60 )
              {
                 Hero.setPosition(710, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >755 and Hero.getPosition().x < 765 and Hero.getPosition().y >0 and Hero.getPosition().y <60  )
              {
                  Hero.setPosition(765, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >720 and Hero.getPosition().x <765 and Hero.getPosition().y >50 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 60);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 590 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                 Hero.setPosition(580, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >695 and Hero.getPosition().x < 710 and Hero.getPosition().y >80 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(710 , Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 710 and Hero.getPosition().y >80 and Hero.getPosition().y <90 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 710 and Hero.getPosition().y >125 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 135);//
              }
          }else if (a4 == 2)
          {
              Animated copya4tile2 (1,"Tile2.png");
              copya4tile2.setPosition(600,-20);
              window.draw(copya4tile2);
              // Tile2 --------------------------------------------Unique
              if(Hero.getPosition().x >820 and Hero.getPosition().x < 835 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(835, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >741 and Hero.getPosition().x < 750 and Hero.getPosition().y >90 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(741, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >741 and Hero.getPosition().x < 835 and Hero.getPosition().y >80 and Hero.getPosition().y <100 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);//
              }
              if(Hero.getPosition().x >741 and Hero.getPosition().x < 835 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 140);//
              }

              if(Hero.getPosition().x >667 and Hero.getPosition().x < 680 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(667, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >690 and Hero.getPosition().x < 740 and Hero.getPosition().y >00 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(740, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >585 and Hero.getPosition().x < 600 and Hero.getPosition().y >35 and Hero.getPosition().y <80 )
              {
                 Hero.setPosition(585, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >585 and Hero.getPosition().x < 740 and Hero.getPosition().y >60 and Hero.getPosition().y <80 )
              {
                  Hero.setPosition(Hero.getPosition().x, 80);
              }
              if(Hero.getPosition().x >585 and Hero.getPosition().x < 740 and Hero.getPosition().y >25 and Hero.getPosition().y <60 )
              {
                  Hero.setPosition(Hero.getPosition().x, 25);
              }
          }
          else if (a4 == 3)
          {
             Animated copya1tile4 (1,"Tile4.png");
            copya1tile4.setPosition(600,-20);
            window.draw(copya1tile4);
          }
          if (b2== 0)
          {
              Animated copy3tile10 (1,"Tile10.png");
              copy3tile10.setPosition(200,180);
              window.draw(copy3tile10);
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 380 and Hero.getPosition().y >130 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(370, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >415 and Hero.getPosition().x <425 and Hero.getPosition().y >130 and Hero.getPosition().y <335  )
              {
                  Hero.setPosition(425, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 425 and Hero.getPosition().y >130 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x <425 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 335);//
              }
              // Tile10---------------------------------------Unique
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >130 and Hero.getPosition().y <225 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >225 and Hero.getPosition().x < 235 and Hero.getPosition().y >130 and Hero.getPosition().y <225  )
              {
                  Hero.setPosition(235, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 233 and Hero.getPosition().y >130 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x <233 and Hero.getPosition().y >215 and Hero.getPosition().y <225 )
              {
                  Hero.setPosition(Hero.getPosition().x, 225);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >340 and Hero.getPosition().x < 350 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(350, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >280 and Hero.getPosition().y <290 )
              {
                  Hero.setPosition(Hero.getPosition().x, 280);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 335);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >180 and Hero.getPosition().y <225 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >340 and Hero.getPosition().x < 350 and Hero.getPosition().y >180 and Hero.getPosition().y <225 )
              {
                  Hero.setPosition(350, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >180 and Hero.getPosition().y <190 )
              {
                  Hero.setPosition(Hero.getPosition().x, 180);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >215 and Hero.getPosition().y <225 )
              {
                  Hero.setPosition(Hero.getPosition().x, 225);//
              }

          }else if (b2 == 1)
          {
              Animated copy3tile7 (1,"Tile7.png");
              copy3tile7.setPosition(200,180);
              window.draw(copy3tile7);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(420, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >175 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(Hero.getPosition().x, 185);//
              }
              //Tile 7 -------------------------------Unique
              if(Hero.getPosition().x >310 and Hero.getPosition().x < 320 and Hero.getPosition().y >130 and Hero.getPosition().y <260 )
              {
                 Hero.setPosition(310, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >355 and Hero.getPosition().x < 365 and Hero.getPosition().y >130 and Hero.getPosition().y <260  )
              {
                  Hero.setPosition(365, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >320 and Hero.getPosition().x <365 and Hero.getPosition().y >250 and Hero.getPosition().y <260 )
              {
                  Hero.setPosition(Hero.getPosition().x, 260);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >295 and Hero.getPosition().x < 310 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(310 , Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 310 and Hero.getPosition().y >280 and Hero.getPosition().y <290 )
              {
                  Hero.setPosition(Hero.getPosition().x, 280);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 310 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 335);//
              }


          }else if (b2 == 2)
          {
              Animated copy3tile4 (1,"Tile4.png");
              copy3tile4.setPosition(200,180);
              window.draw(copy3tile4);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(420, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >175 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(Hero.getPosition().x, 185);//
              }
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 380 and Hero.getPosition().y >130 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(370, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >415 and Hero.getPosition().x <425 and Hero.getPosition().y >130 and Hero.getPosition().y <335  )
              {
                  Hero.setPosition(425, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 425 and Hero.getPosition().y >130 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x <425 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 335);//
              }
          }
          else if (b2 == 3)
          {
             Animated copy3tile2 (1,"Tile2.png");
             copy3tile2.setPosition(200,180);
            window.draw(copy3tile2);
            // ---------------------------------------Top Wall
            if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
            {
               Hero.setPosition(180, Hero.getPosition().y);//
            }
            if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
            {
                Hero.setPosition(420, Hero.getPosition().y);//
            }
            if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
            {
                Hero.setPosition(Hero.getPosition().x, 130);//
            }
            if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >175 and Hero.getPosition().y <185 )
            {
                Hero.setPosition(Hero.getPosition().x, 185);//
            }
            // Tile2 --------------------------------------------Unique
            if(Hero.getPosition().x >420 and Hero.getPosition().x < 435 and Hero.getPosition().y >290 and Hero.getPosition().y <340 )
            {
                Hero.setPosition(435, Hero.getPosition().y);//
            }
            if(Hero.getPosition().x >341 and Hero.getPosition().x < 350 and Hero.getPosition().y >290 and Hero.getPosition().y <340 )
            {
                Hero.setPosition(341, Hero.getPosition().y);//
            }
            if(Hero.getPosition().x >341 and Hero.getPosition().x < 435 and Hero.getPosition().y >280 and Hero.getPosition().y <300 )
            {
                Hero.setPosition(Hero.getPosition().x, 280);//
            }
            if(Hero.getPosition().x >341 and Hero.getPosition().x < 435 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
            {
                Hero.setPosition(Hero.getPosition().x, 340);//
            }

            if(Hero.getPosition().x >267 and Hero.getPosition().x < 280 and Hero.getPosition().y >180 and Hero.getPosition().y <280 )
            {
                Hero.setPosition(267, Hero.getPosition().y);//
            }
            if(Hero.getPosition().x >290 and Hero.getPosition().x < 340 and Hero.getPosition().y >180 and Hero.getPosition().y <280 )
            {
                Hero.setPosition(340, Hero.getPosition().y);//
            }
            if(Hero.getPosition().x >185 and Hero.getPosition().x < 200 and Hero.getPosition().y >235 and Hero.getPosition().y <280 )
            {
               Hero.setPosition(185, Hero.getPosition().y);
            }
            if(Hero.getPosition().x >185 and Hero.getPosition().x < 340 and Hero.getPosition().y >260 and Hero.getPosition().y <280 )
            {
                Hero.setPosition(Hero.getPosition().x, 280);
            }
            if(Hero.getPosition().x >185 and Hero.getPosition().x < 340 and Hero.getPosition().y >225 and Hero.getPosition().y <260 )
            {
                Hero.setPosition(Hero.getPosition().x, 225);
            }
          }
          else if (b2 == 4)
                    {
                        Animated copy3tile9 (1,"Tile9.png");
                        copy3tile9.setPosition(200,180);
                        window.draw(copy3tile9);
                        if(Hero.getPosition().x >230 and Hero.getPosition().x < 240 and Hero.getPosition().y >150 and Hero.getPosition().y <300 )
                        {
                            Hero.setPosition(230, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >355 and Hero.getPosition().x < 365 and Hero.getPosition().y >150 and Hero.getPosition().y <300 )
                        {
                            Hero.setPosition(365, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >230  and Hero.getPosition().x < 365 and Hero.getPosition().y >150 and Hero.getPosition().y <170 )
                        {
                          Hero.setPosition(Hero.getPosition().x, 150);//
                        }
                        if(Hero.getPosition().x >230  and Hero.getPosition().x < 365 and Hero.getPosition().y >290 and Hero.getPosition().y <300 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 300);//
                        }
                    }
          if (b3== 0)
          {
              Animated copy4tile10 (1,"Tile10.png");
              copy4tile10.setPosition(400,180);
              window.draw(copy4tile10);
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >570 and Hero.getPosition().x < 580 and Hero.getPosition().y >130 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(570, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >615 and Hero.getPosition().x < 625 and Hero.getPosition().y >130 and Hero.getPosition().y <335  )
              {
                  Hero.setPosition(625, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >570 and Hero.getPosition().x < 625 and Hero.getPosition().y >130 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >570 and Hero.getPosition().x <625 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 335);//
              }
              // Tile10---------------------------------------Unique
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >130 and Hero.getPosition().y <225 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >425 and Hero.getPosition().x < 435 and Hero.getPosition().y >130 and Hero.getPosition().y <225  )
              {
                  Hero.setPosition(435, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 433 and Hero.getPosition().y >130 and Hero.getPosition().y <135 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x <433 and Hero.getPosition().y >215 and Hero.getPosition().y <225 )
              {
                  Hero.setPosition(Hero.getPosition().x, 225);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x <490 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >540 and Hero.getPosition().x < 550 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(550, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 550 and Hero.getPosition().y >280 and Hero.getPosition().y <290 )
              {
                  Hero.setPosition(Hero.getPosition().x, 280);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 550 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 335);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >180 and Hero.getPosition().y <225 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >540 and Hero.getPosition().x < 550 and Hero.getPosition().y >180 and Hero.getPosition().y <225 )
              {
                  Hero.setPosition(550, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 550 and Hero.getPosition().y >180 and Hero.getPosition().y <190 )
              {
                  Hero.setPosition(Hero.getPosition().x, 180);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 550 and Hero.getPosition().y >215 and Hero.getPosition().y <225 )
              {
                  Hero.setPosition(Hero.getPosition().x, 225);//
              }

          }else if (b3 == 1)
          {
              Animated copy4tile7 (1,"Tile7.png");
              copy4tile7.setPosition(400,180);
              window.draw(copy4tile7);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >175 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(Hero.getPosition().x, 185);//
              }

              //Tile 7 -------------------------------Unique
              if(Hero.getPosition().x >510 and Hero.getPosition().x < 520 and Hero.getPosition().y >130 and Hero.getPosition().y <260 )
              {
                 Hero.setPosition(510, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >555 and Hero.getPosition().x < 565 and Hero.getPosition().y >130 and Hero.getPosition().y <260  )
              {
                  Hero.setPosition(565, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >520 and Hero.getPosition().x <565 and Hero.getPosition().y >250 and Hero.getPosition().y <260 )
              {
                  Hero.setPosition(Hero.getPosition().x, 260);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >495 and Hero.getPosition().x < 510 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(510 , Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 510 and Hero.getPosition().y >280 and Hero.getPosition().y <290 )
              {
                  Hero.setPosition(Hero.getPosition().x, 280);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 510 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 335);//
              }

          }else if (b3 == 2)
          {
              Animated copy3tile1 (1,"Tile1.png");
              copy3tile1.setPosition(400,180);
              window.draw(copy3tile1);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >130 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
              {
                  Hero.setPosition(Hero.getPosition().x, 130);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >175 and Hero.getPosition().y <185 )
              {
                  Hero.setPosition(Hero.getPosition().x, 185);//
              }

              if(Hero.getPosition().x >460 and Hero.getPosition().x < 465 and Hero.getPosition().y >290 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(465, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >381 and Hero.getPosition().x < 410 and Hero.getPosition().y >290 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(381, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >400 and Hero.getPosition().x < 470 and Hero.getPosition().y >280 and Hero.getPosition().y <300 )
              {
                  Hero.setPosition(Hero.getPosition().x, 280);//
              }
              if(Hero.getPosition().x >400 and Hero.getPosition().x < 467 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 340);//
              }

              if(Hero.getPosition().x >467 and Hero.getPosition().x < 480 and Hero.getPosition().y >200 and Hero.getPosition().y <280 )
              {
                  Hero.setPosition(467, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >490 and Hero.getPosition().x < 530 and Hero.getPosition().y >200 and Hero.getPosition().y <280 )
              {
                  Hero.setPosition(530, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >590 and Hero.getPosition().x < 620 and Hero.getPosition().y >235 and Hero.getPosition().y <280 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >467 and Hero.getPosition().x < 600 and Hero.getPosition().y >260 and Hero.getPosition().y <280 )
              {
                  Hero.setPosition(Hero.getPosition().x, 280);
              }
              if(Hero.getPosition().x >467 and Hero.getPosition().x < 600 and Hero.getPosition().y >225 and Hero.getPosition().y <260 )
              {
                  Hero.setPosition(Hero.getPosition().x, 225);
              }
          }
          else if (b3 == 3)
          {
              b3 = 0;
          }
          else if (b3 == 4)
                    {
                        Animated copy3tile8 (1,"Tile8.png");
                        copy3tile8.setPosition(400,180);
                        window.draw(copy3tile8);
                        // ---------------------------------------Left Wall
                        if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >130 and Hero.getPosition().y <335 )
                        {
                           Hero.setPosition(380, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >425 and Hero.getPosition().x < 435 and Hero.getPosition().y >130 and Hero.getPosition().y <335  )
                        {
                            Hero.setPosition(435, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >380 and Hero.getPosition().x < 433 and Hero.getPosition().y >130 and Hero.getPosition().y <135 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 130);//
                        }
                        if(Hero.getPosition().x >380 and Hero.getPosition().x <433 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 335);//
                        }
                        // ---------------------------------------Right Wall
                        if(Hero.getPosition().x >570 and Hero.getPosition().x < 580 and Hero.getPosition().y >130 and Hero.getPosition().y <335 )
                        {
                           Hero.setPosition(570, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >615 and Hero.getPosition().x < 625 and Hero.getPosition().y >130 and Hero.getPosition().y <335  )
                        {
                            Hero.setPosition(625, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >570 and Hero.getPosition().x < 625 and Hero.getPosition().y >130 and Hero.getPosition().y <135 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 130);//
                        }
                        if(Hero.getPosition().x >570 and Hero.getPosition().x <625 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 335);//
                        }
                        // Tile 8 -------------------------------------Unique
                        if(Hero.getPosition().x >450 and Hero.getPosition().x < 460 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
                        {
                           Hero.setPosition(450, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >280 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(620, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >450 and Hero.getPosition().x < 620 and Hero.getPosition().y >280 and Hero.getPosition().y <290 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 280);//
                        }
                        if(Hero.getPosition().x >450 and Hero.getPosition().x < 620 and Hero.getPosition().y >325 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 335);//
                        }
                        if(Hero.getPosition().x >540 and Hero.getPosition().x < 550 and Hero.getPosition().y >210 and Hero.getPosition().y <260 )
                        {
                            Hero.setPosition(550, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >410 and Hero.getPosition().x < 550 and Hero.getPosition().y >210 and Hero.getPosition().y <220 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 210);//
                        }
                        if(Hero.getPosition().x >410 and Hero.getPosition().x < 550 and Hero.getPosition().y >250 and Hero.getPosition().y <260 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 260);//
                        }

                        if(Hero.getPosition().x >440 and Hero.getPosition().x < 465 and Hero.getPosition().y >130 and Hero.getPosition().y <180 )
                        {
                            Hero.setPosition(465, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >410 and Hero.getPosition().x < 465 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 130);//
                        }
                        if(Hero.getPosition().x >410 and Hero.getPosition().x < 465 and Hero.getPosition().y >170 and Hero.getPosition().y <180 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 180);//
                        }
                        if(Hero.getPosition().x >530 and Hero.getPosition().x < 540 and Hero.getPosition().y >130 and Hero.getPosition().y <180 )
                        {
                            Hero.setPosition(530, Hero.getPosition().y);
                        }
                        if(Hero.getPosition().x >530 and Hero.getPosition().x < 585 and Hero.getPosition().y >130 and Hero.getPosition().y <140 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 130);
                        }
                        if(Hero.getPosition().x >530 and Hero.getPosition().x < 585 and Hero.getPosition().y >170 and Hero.getPosition().y <180 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 180);
                        }
                    }
          if (Victory == true)
          {
             window.draw(Stairs);
          }else {window.draw(Mid);}


          if (c4 == 0)
          {
              tile6.setPosition(600,380);
              window.draw(tile6);
              // ---------------------------------------Bottom Wall
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 590 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(580, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >810 and Hero.getPosition().x < 820 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(820, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 820 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 820 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >770 and Hero.getPosition().x < 780 and Hero.getPosition().y >130 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(770, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >770 and Hero.getPosition().x < 825 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >770 and Hero.getPosition().x <825 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }

              if(Hero.getPosition().x >685 and Hero.getPosition().x < 695 and Hero.getPosition().y >330 and Hero.getPosition().y <480 )
              {
                 Hero.setPosition(685, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >685 and Hero.getPosition().x <780 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >685 and Hero.getPosition().x <780 and Hero.getPosition().y >470 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }

          }else if (c4 == 1)
          {
              tile9.setPosition(600,380);
              window.draw(tile9);
              if(Hero.getPosition().x >630 and Hero.getPosition().x < 640 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(630, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >755 and Hero.getPosition().x < 765 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(765, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >630  and Hero.getPosition().x < 765 and Hero.getPosition().y >350 and Hero.getPosition().y <370 )
              {
                Hero.setPosition(Hero.getPosition().x, 350);//
              }
              if(Hero.getPosition().x >630  and Hero.getPosition().x < 765 and Hero.getPosition().y >490 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(Hero.getPosition().x, 500);//
              }
          }else if (c4 == 2)
          {
              tile10.setPosition(600,380);
              window.draw(tile10);
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >770 and Hero.getPosition().x < 780 and Hero.getPosition().y >130 and Hero.getPosition().y <335 )
              {
                 Hero.setPosition(770, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >770 and Hero.getPosition().x < 825 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >770 and Hero.getPosition().x <825 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              // Tile10---------------------------------------Unique
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 590 and Hero.getPosition().y >330 and Hero.getPosition().y <425 )
              {
                 Hero.setPosition(580, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >625 and Hero.getPosition().x < 635 and Hero.getPosition().y >330 and Hero.getPosition().y <425  )
              {
                  Hero.setPosition(635, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 633 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x <633 and Hero.getPosition().y >415 and Hero.getPosition().y <425 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 590 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(580, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >740 and Hero.getPosition().x < 750 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(750, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 750 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 750 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 590 and Hero.getPosition().y >380 and Hero.getPosition().y <425 )
              {
                 Hero.setPosition(580, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >740 and Hero.getPosition().x < 750 and Hero.getPosition().y >380 and Hero.getPosition().y <425 )
              {
                  Hero.setPosition(750, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 750 and Hero.getPosition().y >380 and Hero.getPosition().y <390 )
              {
                  Hero.setPosition(Hero.getPosition().x, 380);//
              }
              if(Hero.getPosition().x >580 and Hero.getPosition().x < 750 and Hero.getPosition().y >415 and Hero.getPosition().y <425 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);//
              }

          }
          if (c3 == 0)
          {
              tile1.setPosition(400,380);
              window.draw(tile1);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >375 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(Hero.getPosition().x, 385);//
              }

              if(Hero.getPosition().x >460 and Hero.getPosition().x < 465 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(465, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >381 and Hero.getPosition().x < 410 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(381, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >400 and Hero.getPosition().x < 470 and Hero.getPosition().y >480 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >400 and Hero.getPosition().x < 470 and Hero.getPosition().y >530 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(Hero.getPosition().x, 540);//
              }

              if(Hero.getPosition().x >467 and Hero.getPosition().x < 480 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(467, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >490 and Hero.getPosition().x < 530 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(530, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >590 and Hero.getPosition().x < 620 and Hero.getPosition().y >435 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >467 and Hero.getPosition().x < 600 and Hero.getPosition().y >460 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >467 and Hero.getPosition().x < 600 and Hero.getPosition().y >425 and Hero.getPosition().y <460 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);
              }
          }else if (c3 == 1)
          {
              tile5.setPosition(400,380);
              window.draw(tile5);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >375 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(Hero.getPosition().x, 385);//
              }

              // ---------------------------------------Bottom Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }

          }else if (c3 == 2)
          {
              tile7.setPosition(400,380);
              window.draw(tile7);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >375 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(Hero.getPosition().x, 385);//
              }
              //Tile 7 -------------------------------Unique
              if(Hero.getPosition().x >510 and Hero.getPosition().x < 520 and Hero.getPosition().y >330 and Hero.getPosition().y <460 )
              {
                 Hero.setPosition(510, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >555 and Hero.getPosition().x < 565 and Hero.getPosition().y >330 and Hero.getPosition().y <460  )
              {
                  Hero.setPosition(565, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >520 and Hero.getPosition().x <565 and Hero.getPosition().y >450 and Hero.getPosition().y <460 )
              {
                  Hero.setPosition(Hero.getPosition().x, 460);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >495 and Hero.getPosition().x < 510 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(510 , Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 510 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 510 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }

          }else if (c3 == 3)
          {
              tile2.setPosition(400,380);
              window.draw(tile2);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >375 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(Hero.getPosition().x, 385);//
              }
              // Tile2 --------------------------------------------Unique
              if(Hero.getPosition().x >620 and Hero.getPosition().x < 635 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(635, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >541 and Hero.getPosition().x < 550 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(541, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >541 and Hero.getPosition().x < 635 and Hero.getPosition().y >480 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >541 and Hero.getPosition().x < 635 and Hero.getPosition().y >530 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(Hero.getPosition().x, 540);//
              }

              if(Hero.getPosition().x >467 and Hero.getPosition().x < 480 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(467, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >490 and Hero.getPosition().x < 540 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(540, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >385 and Hero.getPosition().x < 400 and Hero.getPosition().y >435 and Hero.getPosition().y <480 )
              {
                 Hero.setPosition(385, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >385 and Hero.getPosition().x < 540 and Hero.getPosition().y >460 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);
              }
              if(Hero.getPosition().x >385 and Hero.getPosition().x < 540 and Hero.getPosition().y >425 and Hero.getPosition().y <460 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);
              }

          }else if (c3 == 4)
          {
              tile11.setPosition(400,380);
              window.draw(tile11);
              // ---------------------------------------Bottom Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >610 and Hero.getPosition().x < 620 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 620 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              // ---------------------------------------Left Wall
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 390 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(380, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >425 and Hero.getPosition().x < 435 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
              {
                  Hero.setPosition(435, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x < 433 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >380 and Hero.getPosition().x <433 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
          }else if (c3 == 5)
          {
              tile9.setPosition(400,380);
              window.draw(tile9);
              if(Hero.getPosition().x >430 and Hero.getPosition().x < 440 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(430, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >555 and Hero.getPosition().x < 565 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(565, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >430  and Hero.getPosition().x < 565 and Hero.getPosition().y >350 and Hero.getPosition().y <370 )
              {
                Hero.setPosition(Hero.getPosition().x, 350);//
              }
              if(Hero.getPosition().x >430  and Hero.getPosition().x < 565 and Hero.getPosition().y >490 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(Hero.getPosition().x, 500);//
              }
          }
          if (c2 == 0)
          {
              Animated copytile1 (1,"Tile1.png");
              copytile1.setPosition(200,380);
              window.draw(copytile1);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >375 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(Hero.getPosition().x, 385);//
              }

              if(Hero.getPosition().x >260 and Hero.getPosition().x < 265 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(265, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >181 and Hero.getPosition().x < 210 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(181, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >200 and Hero.getPosition().x < 270 and Hero.getPosition().y >480 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >200 and Hero.getPosition().x < 270 and Hero.getPosition().y >530 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(Hero.getPosition().x, 540);//
              }

              if(Hero.getPosition().x >267 and Hero.getPosition().x < 280 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(267, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >290 and Hero.getPosition().x < 330 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(330, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >390 and Hero.getPosition().x < 420 and Hero.getPosition().y >435 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(420, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >267 and Hero.getPosition().x < 400 and Hero.getPosition().y >460 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >267 and Hero.getPosition().x < 400 and Hero.getPosition().y >425 and Hero.getPosition().y <460 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);//
              }
          }else if (c2 == 1)
          {
              Animated copytile2 (1,"Tile2.png");
              copytile2.setPosition(200,380);
              window.draw(copytile2);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >375 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(Hero.getPosition().x, 385);//
              }
              // Tile2 --------------------------------------------Unique
              if(Hero.getPosition().x >220 and Hero.getPosition().x < 235 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(235, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >341 and Hero.getPosition().x < 350 and Hero.getPosition().y >490 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(341, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >341 and Hero.getPosition().x < 435 and Hero.getPosition().y >480 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >341 and Hero.getPosition().x < 435 and Hero.getPosition().y >530 and Hero.getPosition().y <540 )
              {
                  Hero.setPosition(Hero.getPosition().x, 540);//
              }

              if(Hero.getPosition().x >267 and Hero.getPosition().x < 280 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(267, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >290 and Hero.getPosition().x < 340 and Hero.getPosition().y >400 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(340, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >185 and Hero.getPosition().x < 200 and Hero.getPosition().y >435 and Hero.getPosition().y <480 )
              {
                 Hero.setPosition(185, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >185 and Hero.getPosition().x < 340 and Hero.getPosition().y >460 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);
              }
              if(Hero.getPosition().x >185 and Hero.getPosition().x < 340 and Hero.getPosition().y >425 and Hero.getPosition().y <460 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);
              }
          }else if (c2 == 2)
          {
              Animated copytile4 (1,"Tile4.png");
              copytile4.setPosition(200,380);
              window.draw(copytile4);
              // ---------------------------------------Top Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >330 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(620, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >375 and Hero.getPosition().y <385 )
              {
                  Hero.setPosition(Hero.getPosition().x, 385);//
              }
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 380 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(370, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >415 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
              {
                  Hero.setPosition(425, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x <425 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
          }else if (c2 == 3)
          {
              Animated copytile9 (1,"Tile9.png");
              copytile9.setPosition(200,380);
              window.draw(copytile9);
              if(Hero.getPosition().x >230 and Hero.getPosition().x < 240 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(230, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >355 and Hero.getPosition().x < 365 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(365, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >230  and Hero.getPosition().x < 365 and Hero.getPosition().y >350 and Hero.getPosition().y <370 )
              {
                Hero.setPosition(Hero.getPosition().x, 350);//
              }
              if(Hero.getPosition().x >230  and Hero.getPosition().x < 365 and Hero.getPosition().y >490 and Hero.getPosition().y <500 )
              {
                  Hero.setPosition(Hero.getPosition().x, 500);//
              }
          }else if (c2 == 4)
          {
              Animated copytile8 (1,"Tile8.png");
              copytile8.setPosition(200,380);
              window.draw(copytile8);
              // ---------------------------------------Left Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >225 and Hero.getPosition().x < 235 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
              {
                  Hero.setPosition(235, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 233 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x <233 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 380 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(370, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >415 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
              {
                  Hero.setPosition(425, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x <425 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              // Tile 8 -------------------------------------Unique
              if(Hero.getPosition().x >250 and Hero.getPosition().x < 260 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(250, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(420, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >250 and Hero.getPosition().x < 420 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >250 and Hero.getPosition().x < 420 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              if(Hero.getPosition().x >340 and Hero.getPosition().x < 350 and Hero.getPosition().y >410 and Hero.getPosition().y <460 )
              {
                  Hero.setPosition(350, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >210 and Hero.getPosition().x < 250 and Hero.getPosition().y >410 and Hero.getPosition().y <420 )
              {
                  Hero.setPosition(Hero.getPosition().x, 410);//
              }
              if(Hero.getPosition().x >210 and Hero.getPosition().x < 350 and Hero.getPosition().y >450 and Hero.getPosition().y <460 )
              {
                  Hero.setPosition(Hero.getPosition().x, 460);//
              }

              if(Hero.getPosition().x >240 and Hero.getPosition().x < 265 and Hero.getPosition().y >330 and Hero.getPosition().y <380 )
              {
                  Hero.setPosition(265, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >210 and Hero.getPosition().x < 265 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >210 and Hero.getPosition().x < 265 and Hero.getPosition().y >370 and Hero.getPosition().y <380 )
              {
                  Hero.setPosition(Hero.getPosition().x, 380);//
              }
              if(Hero.getPosition().x >330 and Hero.getPosition().x < 340 and Hero.getPosition().y >330 and Hero.getPosition().y <380 )
              {
                  Hero.setPosition(330, Hero.getPosition().y);
              }
              if(Hero.getPosition().x >330 and Hero.getPosition().x < 385 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);
              }
              if(Hero.getPosition().x >330 and Hero.getPosition().x < 385 and Hero.getPosition().y >370 and Hero.getPosition().y <380 )
              {
                  Hero.setPosition(Hero.getPosition().x, 380);
              }
          }else if (c2 == 5)
          {
              Animated copytile6(1,"Tile6.png");
              copytile6.setPosition(200,380);
              window.draw(copytile6);
              // ---------------------------------------Bottom Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(420, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 380 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(370, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >415 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
              {
                  Hero.setPosition(425, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x <425 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }

              if(Hero.getPosition().x >285 and Hero.getPosition().x < 295 and Hero.getPosition().y >330 and Hero.getPosition().y <480 )
              {
                 Hero.setPosition(285, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >285 and Hero.getPosition().x <380 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >285 and Hero.getPosition().x <380 and Hero.getPosition().y >470 and Hero.getPosition().y <480 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
          }
          else if (c2 == 6)
            {
              Animated copytile10 (1,"Tile10.png");
              copytile10.setPosition(200,380);
              window.draw(copytile10);
              // ---------------------------------------Right Wall
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 380 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(370, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >415 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
              {
                  Hero.setPosition(425, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x < 425 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >370 and Hero.getPosition().x <425 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              // Tile10---------------------------------------Unique
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >330 and Hero.getPosition().y <425 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >225 and Hero.getPosition().x < 235 and Hero.getPosition().y >330 and Hero.getPosition().y <425  )
              {
                  Hero.setPosition(235, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 233 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x <233 and Hero.getPosition().y >415 and Hero.getPosition().y <425 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 290 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >340 and Hero.getPosition().x < 350 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(350, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >380 and Hero.getPosition().y <425 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >340 and Hero.getPosition().x < 350 and Hero.getPosition().y >380 and Hero.getPosition().y <425 )
              {
                  Hero.setPosition(350, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >380 and Hero.getPosition().y <390 )
              {
                  Hero.setPosition(Hero.getPosition().x, 380);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 350 and Hero.getPosition().y >415 and Hero.getPosition().y <425 )
              {
                  Hero.setPosition(Hero.getPosition().x, 425);//
              }
          }else if (c2 == 8)
          {
              tile11.setPosition(200,380);
              window.draw(tile11);
              // ---------------------------------------Bottom Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >410 and Hero.getPosition().x < 420 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(420, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
              {
                  Hero.setPosition(Hero.getPosition().x, 480);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 420 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }

              // ---------------------------------------Left Wall
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 190 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
              {
                 Hero.setPosition(180, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >225 and Hero.getPosition().x < 235 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
              {
                  Hero.setPosition(235, Hero.getPosition().y);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 233 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
              {
                  Hero.setPosition(Hero.getPosition().x, 330);//
              }
              if(Hero.getPosition().x >180 and Hero.getPosition().x < 233 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
              {
                  Hero.setPosition(Hero.getPosition().x, 535);//
              }
          }
          //c1 = 0;
          if (c1 == 0)
          {
                        Animated copy2tile8 (1,"Tile8.png");
                        copy2tile8.setPosition(0,380);
                        window.draw(copy2tile8);
                        // ---------------------------------------Left Wall
                        if(Hero.getPosition().x >025 and Hero.getPosition().x < 035 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
                        {
                            Hero.setPosition(035, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >00 and Hero.getPosition().x < 033 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);//
                        }
                        if(Hero.getPosition().x >00 and Hero.getPosition().x <033 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 535);//
                        }
                        // ---------------------------------------Right Wall
                        if(Hero.getPosition().x >170 and Hero.getPosition().x < 180 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
                        {
                           Hero.setPosition(170, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >215 and Hero.getPosition().x < 225 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
                        {
                            Hero.setPosition(225, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >170 and Hero.getPosition().x < 225 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);//
                        }
                        if(Hero.getPosition().x >170 and Hero.getPosition().x <225 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 535);//
                        }
                        // Tile 8 -------------------------------------Unique
                        if(Hero.getPosition().x >50 and Hero.getPosition().x < 60 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
                        {
                           Hero.setPosition(50, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >210 and Hero.getPosition().x < 220 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(220, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >50 and Hero.getPosition().x < 220 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 480);//
                        }
                        if(Hero.getPosition().x >50 and Hero.getPosition().x < 220 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 535);//
                        }
                        if(Hero.getPosition().x >140 and Hero.getPosition().x < 150 and Hero.getPosition().y >410 and Hero.getPosition().y <460 )
                        {
                            Hero.setPosition(150, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >10 and Hero.getPosition().x < 50 and Hero.getPosition().y >410 and Hero.getPosition().y <420 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 410);//
                        }
                        if(Hero.getPosition().x >10 and Hero.getPosition().x < 150 and Hero.getPosition().y >450 and Hero.getPosition().y <460 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 460);//
                        }

                        if(Hero.getPosition().x >40 and Hero.getPosition().x < 65 and Hero.getPosition().y >330 and Hero.getPosition().y <380 )
                        {
                            Hero.setPosition(65, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >10 and Hero.getPosition().x < 65 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);//
                        }
                        if(Hero.getPosition().x >10 and Hero.getPosition().x < 65 and Hero.getPosition().y >370 and Hero.getPosition().y <380 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 380);//
                        }
                        if(Hero.getPosition().x >130 and Hero.getPosition().x < 140 and Hero.getPosition().y >330 and Hero.getPosition().y <380 )
                        {
                            Hero.setPosition(130, Hero.getPosition().y);
                        }
                        if(Hero.getPosition().x >130 and Hero.getPosition().x < 185 and Hero.getPosition().y >330 and Hero.getPosition().y <340 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);
                        }
                        if(Hero.getPosition().x >130 and Hero.getPosition().x < 185 and Hero.getPosition().y >370 and Hero.getPosition().y <380 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 380);
                        }

          }else if (c1 == 1)
                    {
                        Animated copy2tile6(1,"Tile6.png");
                        copy2tile6.setPosition(0,380);
                        window.draw(copy2tile6);
                        // ---------------------------------------Bottom Wall
                        if(Hero.getPosition().x >210 and Hero.getPosition().x < 220 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(220, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 220 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 480);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 220 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 535);//
                        }
                        // ---------------------------------------Right Wall
                        if(Hero.getPosition().x >170 and Hero.getPosition().x < 180 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
                        {
                           Hero.setPosition(170, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >215 and Hero.getPosition().x < 225 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
                        {
                            Hero.setPosition(225, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >170 and Hero.getPosition().x < 225 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);//
                        }
                        if(Hero.getPosition().x >170 and Hero.getPosition().x <225 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 535);//
                        }

                        if(Hero.getPosition().x >85 and Hero.getPosition().x < 95 and Hero.getPosition().y >330 and Hero.getPosition().y <480 )
                        {
                           Hero.setPosition(85, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >85 and Hero.getPosition().x <180 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);//
                        }
                        if(Hero.getPosition().x >85 and Hero.getPosition().x <180 and Hero.getPosition().y >470 and Hero.getPosition().y <480 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 480);//
                        }
                    }
                    else if (c1 ==2)
                      {
                        Animated copy2tile10 (1,"Tile10.png");
                        copy2tile10.setPosition(0,380);
                        window.draw(copy2tile10);
                        // ---------------------------------------Right Wall
                        if(Hero.getPosition().x >170 and Hero.getPosition().x < 180 and Hero.getPosition().y >330 and Hero.getPosition().y <535 )
                        {
                           Hero.setPosition(170, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >215 and Hero.getPosition().x < 225 and Hero.getPosition().y >330 and Hero.getPosition().y <535  )
                        {
                            Hero.setPosition(225, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >170 and Hero.getPosition().x < 225 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);//
                        }
                        if(Hero.getPosition().x >170 and Hero.getPosition().x <225 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 535);//
                        }
                        // Tile10---------------------------------------Unique
                        if(Hero.getPosition().x >25 and Hero.getPosition().x < 35 and Hero.getPosition().y >330 and Hero.getPosition().y <425  )
                        {
                            Hero.setPosition(35, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 33 and Hero.getPosition().y >330 and Hero.getPosition().y <335 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 330);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x <33 and Hero.getPosition().y >415 and Hero.getPosition().y <425 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 425);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 90 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
                        {
                           Hero.setPosition(0, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >140 and Hero.getPosition().x < 150 and Hero.getPosition().y >480 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(150, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 150 and Hero.getPosition().y >480 and Hero.getPosition().y <490 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 480);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 150 and Hero.getPosition().y >525 and Hero.getPosition().y <535 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 535);//
                        }
                        if(Hero.getPosition().x >140 and Hero.getPosition().x < 150 and Hero.getPosition().y >380 and Hero.getPosition().y <425 )
                        {
                            Hero.setPosition(150, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 150 and Hero.getPosition().y >380 and Hero.getPosition().y <390 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 380);//
                        }
                        if(Hero.getPosition().x >0 and Hero.getPosition().x < 150 and Hero.getPosition().y >415 and Hero.getPosition().y <425 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 425);//
                        }
                    }else if (c1 == 3)
                    {
                        Animated copytile9 (1,"Tile9.png");
                        copytile9.setPosition(0,380);
                        window.draw(copytile9);
                        if(Hero.getPosition().x >030 and Hero.getPosition().x < 040 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
                        {
                            Hero.setPosition(030, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >155 and Hero.getPosition().x < 165 and Hero.getPosition().y >350 and Hero.getPosition().y <500 )
                        {
                            Hero.setPosition(165, Hero.getPosition().y);//
                        }
                        if(Hero.getPosition().x >030  and Hero.getPosition().x < 165 and Hero.getPosition().y >350 and Hero.getPosition().y <370 )
                        {
                          Hero.setPosition(Hero.getPosition().x, 350);//
                        }
                        if(Hero.getPosition().x >030  and Hero.getPosition().x < 165 and Hero.getPosition().y >490 and Hero.getPosition().y <500 )
                        {
                            Hero.setPosition(Hero.getPosition().x, 500);//
                        }
                    }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
              Herotop.setPosition(Hero.getPosition().x , Hero.getPosition().y);
              window.draw(Herotop);

          }else
          {
             Herowalktop.setPosition(Hero.getPosition().x , Hero.getPosition().y);
             window.draw(Herowalktop);
          }
          if(c2 == 3)
          {
              Animated oncopytile9 (1,"Tile9ON.png");
              oncopytile9.setPosition(200,380);
              window.draw(oncopytile9);
          }
          if (c1 == 3)
          {
              Animated oncopy1tile9 (1,"Tile9ON.png");
              oncopy1tile9.setPosition(0,380);
              window.draw(oncopy1tile9);
          }
          if (c3 == 5)
          {
             Animated ontile9 (1,"Tile9ON.png");
             ontile9.setPosition(400,380);
             window.draw(ontile9);
          }
          if (b2 == 4)
          {
                  Animated oncopy3tile9 (1,"Tile9ON.png");
                  oncopy3tile9.setPosition(200,180);
                  window.draw(oncopy3tile9);
          }
          if (c4 == 1)
          {
              Animated ontile9 (1,"Tile9ON.png");
              ontile9.setPosition(600,380);
              window.draw(ontile9);
          }
          window.draw(Ghost);

          if (sword == true)
          {
              bool swordUI;
              if(i < 100)
              {
                  swordUI = true;
                  i = i + 1;
              }else{swordUI = false;}

              if(swordUI == true)
              {
                  sf::Texture in1;
                  in1.loadFromFile("SwordIndicator.png");
                  sf::Sprite swordindicator(in1);
                  swordindicator.setPosition(260,160);
                  window.draw(swordindicator);
                  sf::Texture in2;
                  in2.loadFromFile("Indicator.png");
                  sf::Sprite indicator(in2);
                  indicator.setPosition(300,380);
                  window.draw(indicator);
              }
          }





          window.draw(Bottom);
          if (Victory == true)
          {
              if(iforsword < 100)
              {
                  window.draw(Swordlost);
                  iforsword = iforsword + 1;
              }
          }
          if(quest1 and Victory == false)
          {
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
              {
                 window.draw(Quest1);
              }else{window.draw(QuestHidden);}
          }else if(Village == true){
              window.draw(QuestM1);
          }
          // Tutorial 2
          if (tut2 == true)
          {
              window.draw(tutorial2);
              window.draw(Esc);
              runenable = false;
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
              {
                  tut2 =false;
                  runenable = true;
              }
          }
      }
      if(quest1)// ------------------------------------------Dialog Window
      {
          if (Dialog==true)
          {
              if (Text1 == true)
              {
                  window.draw(DialogCall);
                  window.draw(HeroD);
                  window.draw(NPCD);
                  window.draw(Call1);
                  window.draw(Spc);
                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                  {Text1 = false;}
              }else
              {
                 if (Text2== true)
                 {
                     window.draw(DialogCall);
                     window.draw(HeroD);
                     window.draw(NPCD);
                      window.draw(Call2);
                      window.draw(Esc);
                     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                     {Text2 = false;}
                 }else{Dialog=false;}
              }
          }
      }
      if(Fin)
      {
          if (Dialog2==false)
          {
              runenable = true;
              // Tutorial 2
              if (tut3 == true)
              {
                  window.draw(tutorial3);
                  window.draw(Spc);
                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                  {
                      tut3 =false;
                  }
              }

          } else
          {
              runenable = false;
                 if (Text3== true)
                 {
                     window.draw(DialogCall);
                     window.draw(HeroD);
                     window.draw(NPCD);
                     window.draw(Call3);
                     window.draw(Esc);
                     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                     {Text3 = false;}
                 }else{Dialog2=false;runenable = true;}
              }
          }

      // Combat

      if (Contact==true)
      {
          Mansion = false;
          Village = true;

          runenable = false;
          if(sword == true)
          {
              window.draw(Combatcall);
              window.draw(HeroC);
              window.draw(EnemyC);
              window.draw(overlay);
              if (confirmchoice == false)
              {
                  if(iforselected < 10)
                  {
                      iforselected = iforselected + 1;
                  }else{
                      if (selected == 0)
                      {
                          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                          {
                              selected = selected + 1;
                              iforselected = 0;
                          }
                      }else if(selected == 1)
                      {
                          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                          {
                              selected = selected - 1;
                              iforselected = 0;
                          }
                          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                          {
                              selected = selected + 1;
                              iforselected = 0;
                          }
                      }else if(selected == 2)
                      {
                          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                          {
                              selected = selected - 1;
                              iforselected = 0;
                          }
                      }
                  }
              }else if (confirmchoice == true)
              {
                  if (selected == 0)
                  {
                      drawas = true;
                      drawws = false;
                      if(iforchoice < 200)
                      {
                          iforchoice = iforchoice + 1;
                          window.draw(reg);
                      }else{
                          iforchoice = 0;
                          confirmchoice = false;
                      }

                  }else if(selected == 1)
                  {
                      drawas = false;
                      drawws = true;
                      if(iforchoice < 200)
                      {
                          iforchoice = iforchoice + 1;
                          window.draw(skill);
                      }else{
                          iforchoice = 0;

                          Victory = true;
                      }
                  }else if(selected == 2)
                  {
                      if(iforchoice < 400)
                      {
                          iforchoice = iforchoice + 1;
                          window.draw(Escape);
                      }else{
                          iforchoice = 0;
                          confirmchoice = false;
                      }
                  }
              }
              if (drawas == true)
              {window.draw(as);}
              if (drawws == true)
              {window.draw(ws);}


              if (selected == 0)
              {
                  window.draw(a);
                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                  {
                      confirmchoice = true;
                  }
              }else if(selected == 1)
              {
                  window.draw(w);
                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                  {
                      confirmchoice = true;
                  }
              }else if(selected == 2)
              {
                  window.draw(r);
                  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                  {
                      confirmchoice = true;
                  }
              }
              if(Victory == true)
              {
                  EnemyC.move(0,1);
                  if(EnemyC.getPosition().y > 300)
                  {
                      Contact = false;
                      runenable = true;
                      Hero.setPosition(350, 250);
                  }
              }


          }else {
               window.draw(over);
               if(score > 0)
               {
                   Score_text.setString(ss.str().c_str());
                   window.draw(Scoreboard);
                   window.draw(Score_text);
               }

          }
      }


      // end the current frame
      window.display();
    }
    return 0;
}
