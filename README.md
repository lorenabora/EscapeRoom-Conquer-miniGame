# EscapeRoom-Conquer-miniGame
## Game Overview
- The game is a 2D, pixel art, kind of escape room where you need to conquer it to be declared the winner. The player is inside the throne room, locked inside with 2 knights and a king. Inside the chest you get the weapon and once you stepped a little too close to the enemies, the knights start coming after you and attack you ruthless. If you manage to eliminate the knights, the king will make sure to protect his crown and try to eliminate you, but be carefull, he is not king in name only.
- The goal is to become the new king of the room in order to escape (so basically kill all the enemies).
- The ending? Well, it depends on you! You win? A message in green will announce it. You lose( either killed or mutual destruction), your soul will be trapped in the game forever.
- Hints! The game is structured in 3 stages:
  1. When you "wake up" in the game and you need to search for the weapon.
  2. When the knights attack: in this stage you have a safe zone where the knights can't attack the player and not only that, but once the player steps into that zone, the knights freeze.
  3. When the king arises, the safe zone is no longer available and the king can dodge your attacks getting teleported randomly in the room.

## Class Arhitecture & OOP Design
The game is sectioned into more classes: Entity, Hero, Knight, King, Game, ExceptionsG.

Class Entity is the base, abstracted class of the game. Because even if you are the hero(player) or one of the enemies, most of the functions have the same scope, so I decided to override them in order for the player to move based on the WASD keys and atttack with the space bar, meanwhile the enemies have automated triggers that makes them move, they follow the player in the room and attacks them only inside a range. I enforced the custom behavior using pure virtual functions.

Also, in this class I created specific protected data like the forms of the entities, the HP bar, the textures, value of the HP and maximum of HP per entity and, of course, the gameStage.

In the public zone of this function I initialised the constructor and virtual destructor, followed closely by functions:
- clone() : copy a smart pointer for creation of a new entity which will have the specific features from the class where it gets called( Hero, Knight, King); constant pure virtual function;
- getLevelMessage() : pure virtual function for determination of the stage of the game;
- getEntity() : return the type of variable of the entity (e.g.: sf::RectangleShape);
- getHPBar() : helping function for modification of the HP bar during a fight;
- getHP() : helping function for numerical modification of the HP bar( gets the value in real time);
- moveEntity() : pure virtual function that is overridden for each type of entity;
- attack() : pure virtual function for controlled( player)/ automatic (knights, king) attacks;
- updateHPBar() : where use the other two functions to midify the length and tha value of HP;
- moveHPBar(): follow the entity in the room( above each head there is an HP bar);
- isAlive();
- isPointInsideConvexShape() : verify the center of entity to be inside the walls of the room;
- isPlayerWithinWalls() : with the help of the previous function, rezolving the collisions with the walls;
- draw() : called untill an entity reaches 0 HP.

For the Hero, the movement is based on the keys WASD, the attack ( in a close range) with the space bar, meanwhile for the knights/king, based on each stage, they start moving following actually the coordonates of the player in the room, they "attack" them only if they are reachable.

The King has a special function, dodgeAttack(), that teleports the king randomly on the map so that the player needs to strugle a bit for a clean victory.

The Game class is the engie of all the game, here I render the movements, update the locations, HP of the entities, the fights are worn. All the frames are updated while the window with the game is not closed. 

In the public zone I included the destructor, constructor, the function getGameMesssage(), override of the << operator( for messages line inside the terminal) and the run() function that plays the 3 private functions( handleEvents(), update(), render()).

## Game Mechanics
- Controls: WASD for movement, Space for attack (player);
- Safe Zone: only active during stage 1 and 2;
- Enemy AI: chase, attack in the proxy, the king can dodge.
- Victory condition: the player needs to be the only survivor. If, by chance, you kill the king and the king kills you simultaneously, it is called defeat because you can't escape a room where you where eliminated.

## Exception Handling
In the ExceptionsG class there are 3 functions that I want to present: 
- FileLoadingException() : used in testing the error on loading the background image;
- InvalidMovementException() and InvalidAttackException() : used for the hero in case that there are collisions or errors during a fight( not respecting the minimum distance or a missed attack).

## Design patterns
### Singleton
Am modificat clasa Game in asa fel incat: am sters constructorul de copiere pentru a permite crearea unei singure instante, am mutat constructorul din zona publica in cea privata, am creat instanta drept pointer static( static Game* instance;), am creat in zona publica un getter pentru aceasta instanta si la final am grija sa o sterg/distrug ( functia destroyInstance()).

### Observer pattern
Este putin mai necunoscut decat Singleton, Factory sau Builder, dar are rolul de a crea notificari in timp real pentru observatori/jucatori. Pentru aceasta am mai creat 3 clasa: Observer, Subjects si HealthUI care vor crea, respectiv afisa notificarile in legatura cu damage-ul pe care il ia playerul.

Clasa Observer contine un dsestructor virtual default si o functie virtual pura notify( const std::string& event) care va fi suprascrisa in asa fel incat sa notifice observatorii.

Clasa Subjects va mosteni clasa Observer, va avea in zona rivate un vector de pointeri de tip observer( lista observatorilor), iar in zona publica avem addObserver(), removeObserver() si notifyObservers(), functie care va trimite o notificare catre observatori.

Clasa HealthUI mosteneste clasa Observer si suprascrie functia notify() in asa fel incat sa anunte observatorii de noul scor al barii de HP/cata viata mai are jucatorul.

Clasa Game va mosteni clasa Subjects si vom crea functia updateGameHealth() care are ca unic scop apelarea functie notifyObservers().

## Language used/ Tech Stack
- C++
- SFML library

## How to play
- make sure that you have installed the SFML library on your computer, the dependencies can be a real headache
- after everything is installed and you cloned the git, just press run as if it is a simple code writen for school
- on the game window, click on the "Play" message written in green in the middle of the screen
Enjoy!

## Bibliografie 

1.	YouTube, FuniTinker, “How I structure Entities In My Own C++ Game Engine”
2.	YouTube, Dan Zaidan, “How to program a game in C++”(toate videoclipurile)
3.	 YouTube, EOD-Ethan, “How to setup SFML in Visual Studio in 5 minutes. Fully Explained.”
4.	YouTube, Mustafa Sibai, “Creating an RPG C++/SFML -Part 10- Moving the player with WASD”
5.	YouTube, Hilze Vonck, “SFML 2.4 For Beginners-1:Opening a Window”
6.	YouTube, Gamefromscratch, “SFML Tutorial – Spritesheets and Animations”
7.	SFML( official site), sectiunile “Tutorials” si “Documentation”
8.	SFML community forums>>help>>general, articolele “Health Bars..”, “Array of shapes”, “Sprites Collision- how to stop them from moving?”, “Different between sf::Event::KeyPressed and sf::Keyboard::isKeyPressed(…)”, “My first SFML game”, “Artificial Intelligence”, “NPC/AI, how?”, “Smoothest possible movement”, “Correct way to do a player movement”, “Player Movement with Classes”, “Smooth character movement with Arrow keys”, “How to resize my sprite and not have it so stretched out?”, “How to resize my sprite?...what am I missing?”.
