# EscapeRoom-Conquer-miniGame
## Idee de bază

Povestea din spatele temei pe care am ales-o este următoarea: dumneavoastră( jucătorul) vă treziți în camera tronului fără niciun indiciu, ușa din spatele dumneavoastră este încuiată, singura șansă de scapare este să rămâneți ultimul din încăpere. Scopul jocului este să evadați din încăpere prin devenirea noului rege( rege va fi entitatea care rămâne în viață până la finalul jocului).

În partea din stânga-sus aveți mesaje sau indicii care să vă ajute să câștigați joculețul. În cufărul din stânga jucătorului se află sabia pe care o va utiliza jucătorul. 

În prima etapă a jocului cavalerii regelui vor ataca jucătorul după acesta va păși în afara zonei sigure. Această zona se va reactiva odată cu reintrarea jucătorului în ea, dar numai în această etapă. După ce cavalerii au fost ambii învinși, regele va încerca să își apere titlul, atacând jucătorul și încercând să se apere de atacurile acestuia dacă o anumită distanță este atinsă între rege și jucător. În această ultimă etapă a jocului, zona sigură nu se va mai reactiva, jucătorul devenind vulnerabil.
Există trei cazuri ale acestui joc: câștigă jucătorul, iar un mesaj îi va reflecta gândurile; regele va câștiga, ceea ce înseamnă că nu ați reușit să evadați din încăpere, sau ambii adversari vor dispărea din cameră, ceea ce înseamnă că jucătorul și regele s-au atacat simultan și au pierit în bătăție, moment în care se declară pierderea jocului( din punct de vedere al scopului inițial).

## Funcționalitatea codului detaliata
Codul este împărțit în șase clase: Entity, Hero, Knight, King, Game și ExceptionsG.

Clasa Entity este clasa părinte pentru cele trei tipuri de entități ale jocului: Hero, Knight, King. În această clasă am creat  ca date protected formele entității și bării de HP, textura entității, valoare HP-ului și maximul de HP inițial( variabile tip float), gameStage( de tip int pentru a contoriza stagiile jocului).

În zona publică a clasei am inițializat constructorul parametrizat și destructorul virtual, urmate de următoarele funcții: clone()- funție care se ocupă de copierea unui smart pointer pentru generarea unei noi entități care va avea caracteristicile specifice unei categorii de entități, funcție constantă pur virtuală; getLevelMessage()- funcție pur virtuală care va fi suprascrisă pentru a determina stagiul jocului; getEntity()- funcție care va returna tipul de variabilă pe care îl are entitatea( va returna un sf::RectangleShape); getHPBar()- funcție ajutătoare pentru a modifica bara de HP pentru momentele în care o entitate a fost atacată și pierde din viață; getHP()- funcție creată din același motiv precum precedenta, doar că va ajuta la modificarea numerică a HP-ului; moveEntity()- funcție virtual pură pe care o voi suprascrie pentru a personaliza mișcarea fiecărui tip de entitate; attack()- funcție virtual pură pe care o voi personaliza pentru fiecare tip de entitate; updateHPBar()- funcție care va actualiza valoarea de HP și îi va modifica lungimea barei; moveHPBar()- funcție care va face posibilă mișcarea în sincron a barei de HP odată cu entitatea; isAlive()- verific dacă entittaea mai este vie sau a ajuns la HP 0, o voi folosi drept condiție în funcția draw; isPointInsideConvexShape()-funcție care verifică dacă un punct( centrul entității) este în interiorul pereților; isPlayerWithinWalls()-funcție proiectată pentru a rezolva coliziunile cu pereții încăperii care nu este un poligon regulat pentru a nu ieși entitățile din cadrul încăperii, se folosește de funcția isPointInsideConvexShape(); draw()- funcție care desenează entitatea în cazul în care nu a murit.

Clasa Hero moștenește clasa Entity și îi suprascrie funcțiile pure astfel încât: în funcția moveEntity() folosesc evenimentele tastelor W,A,S,D pentru a muta jucătorul în direcțiile aferente și a crea mișcări cât mai line, rotația entității în funcție de direcția de mișcare, iar funcția attack() se folosește de bara space pentru a ataca inamicii de la o anumită distanță. Funcția de clonare a fost suprascrisă pentru a returna un smart pointer de tip Hero, iar getLevelMessage va fi setat la starea 0, începerea jocului.
Suplimentar, avem constructorul special entității nerou care folosește constructorul clasei Entity, adăugând numai posiția specifică jucătorului.

Clasa Knight este similară cu cea a eroului, doar că în funcția de moveEntity() cavalerii vor urmări eroul drept țintă, modificându-și direcția în funcție de mișcarea jucătorului, iar funcția attack() se va activa doar dacă jucătorul intră într-o anumită distanță. Funcția de clonare va fi folosită într-un vector de cavaleri de tip smart pointers în clasa Game.

Clasa King operează la fel precum clasa Knight, diferența vine de la funcția specială a acestei clase: dodgeAttack care se ocupă de teleportarea regelui într-o direcție și o distanță randomizată pentru a fi mai dificil de învins de către erou.

Clasa Game are grijă ca toate buclele jocului să funcționeze bine, sa se actualizeze corect toate frame-urile jocului cât timp fereastra este deschisă. Am două zone: în cea publică am inclus constructorul, destructorul clasei, funcția getGameMessage care va afișa mesajele stagiilor jocului, suprascrierea operatorului <<( pentru mesajele care vor fi scrise în terminal) și funcția run care manevrează cele trei funcții private care pun în funcțiune jocul cât timp fereastra este deschisă( handleEvents, update, render). 
În partea privată a aceste clase am atât inițializările smart pointerilor, rendarea ferestrei, texturile, fontul, pereții, temporizatoarele și variabilele pentru gameStage și knightAlive( cavalerul care a rămas în viață). Drept funcții private le am pe următoarele: addKnights- care adaugă cavalerii în vector pe pozițiile corecte; initializeWalls – initializez zidurile incaperii pentru coliziuni; initilalizeChest – initializeaza cufarul de unde isi ia sabia( unde schimb textura cu una care are sabie in mana); initializeSafeZone – initializeze zona sigură din prima etapă; initilaizeBackground – initializez fundalul; initializeUI – setez cele două ferestre de start și Game Over cu mesaje și efect de blurare a fundalului; renderMenu – afisez mesajul de Play și fundalul aferent; renderGameOver – afisez mesajul de Game Over și fundalul aferent;  updateGameMessage – afișează mesajul din etapa jocului în care se află jucătorul; handleEvents – se ocupă de evenimente( deschiderea ferestrei, schimbarea interfetei de joc); isInSafeZone – verific dacă jucătorul se află în aria zonei sigure; changeTexture – schimb textura eroului atunci când ajunge la cufăr o dată; betweenKnights – setează o anumită distanță între cavaleri pentru a nu se suprapune entitățile lor; update – se ocupă de tot jocul, aici apelăm funcțiile anterior precizate, mișcăm entitățile, lansăm atacurile, actualizăm fiecare frame și mesaj; render – afișăm toate entitățile, fundaluri, pereți și ce alte lucruri mai sunt necesare pentru interfața grafică a jocului.

# Pe scurt:
## Mostenire
In partea principala a codului, clasa de baza este Entity, de la care vor mosteni atribute clasele derivate: Hero, Knight si King.
In partea a doua, la tratarea exceptiilor, am mostenit din std::exception exceptii pentru cele 3 pe care am ales sa le rezolv( incarcarea esuata a fisierului, miscarea in afara peretilor; coliziuni, atacuri invalide).

## Functii virtuale pure si utilizare clone
In clasa Entity( devenita clasa abstracta) veti observa functiile

virtual std:unique_ptr<Entity> clone() const =0; care va ajuta la clonarea/copierea unei entitati din aceeasi subcategorie si va fi suprascrisa in asa fel in toate cele 3 clase derivate;

virtual std::string getLevelMessage(int gameStage) const=0; pentru actualizarea mesajului din fiecare stadiu al jocului;

virtual void moveEntity(const sf::ConvexShape& walls, float delta_t, Entity& entity, Entity* enemy = nullptr) = 0; pentru ca hero(jucatorul) se va misca pe baza tastelor WASD, pe cand inamicii vor avea functii scrise in asa fel inca sa urmareasca tinta;

virtual void attack(sf::RectangleShape& player, sf::RectangleShape& enemy, float attackRange, float& enemyHP, sf::Clock& attackTimer) = 0; atacul jucatorului este pe baza apasarea tastei Space, pe cand inamicii ataca automat cand le intrii in raza de atac.

## Smart pointers
Toate entitatile sunt construite drept smart pointers, urmarind sintaxa concreta. De asemenea, am un vector de entitati pentru cei doi cavaleri care vor fi identici, singura exceptie fiind pozitia lor initiala in incapere si barile HP diferite( doar nu doream sa moara ambii in acelasi timp, nu?).

Folosesc dynamic_cast pentru crearea de pointeri a entitatilor atunci cand trebuie sa apelez anumite functii cum are fi moveEntity() si attack().

De asemenea, suprascriu operatorul de afisare pentru mesajele din consola.

## Tratarea exceptiilor
Mai exista clasa ExceptionsG care se ocupă cu prinderea și tratarea a trei exceptii diferite: FileLoadingException, InvalidMovementException, InvalidAttackException. Pe prima o folosesc la testarea excepție de neîncărcare a imaginii de fundal în clasa Game. Pe următoarele două le flosesc cu try/catch în clasa Hero pentru nerespectarea mișcărilor impuse de la tastatură și atacuri invalide( ceva nu ar funcționa bine sau distanța e mult prea mare).

## Templates
Singura modificare a codului pentru a implementa un template esrte in functia changeTexture() pentru a crea oportunitatea de a schimba textura oricarui obiect desenabil care permie incarcarea unei texturi.

## Design patterns
### Singleton
Am modificat clasa Game in asa fel incat: am sters constructorul de copiere pentru a permite crearea unei singure instante, am mutat constructorul din zona publica in cea privata, am creat instanta drept pointer static( static Game* instance;), am creat in zona publica un getter pentru aceasta instanta si la final am grija sa o sterg/distrug ( functia destroyInstance()).

### Observer pattern
Este putin mai necunoscut decat Singleton, Factory sau Builder, dar are rolul de a crea notificari in timp real pentru observatori/jucatori. Pentru aceasta am mai creat 3 clasa: Observer, Subjects si HealthUI care vor crea, respectiv afisa notificarile in legatura cu damage-ul pe care il ia playerul.

Clasa Observer contine un dsestructor virtual default si o functie virtual pura notify( const std::string& event) care va fi suprascrisa in asa fel incat sa notifice observatorii.

Clasa Subjects va mosteni clasa Observer, va avea in zona rivate un vector de pointeri de tip observer( lista observatorilor), iar in zona publica avem addObserver(), removeObserver() si notifyObservers(), functie care va trimite o notificare catre observatori.

Clasa HealthUI mosteneste clasa Observer si suprascrie functia notify() in asa fel incat sa anunte observatorii de noul scor al barii de HP/cata viata mai are jucatorul.

Clasa Game va mosteni clasa Subjects si vom crea functia updateGameHealth() care are ca unic scop apelarea functie notifyObservers().

## Bibliografie 

1.	YouTube, FuniTinker, “How I structure Entities In My Own C++ Game Engine”
2.	YouTube, Dan Zaidan, “How to program a game in C++”(toate videoclipurile)
3.	 YouTube, EOD-Ethan, “How to setup SFML in Visual Studio in 5 minutes. Fully Explained.”
4.	YouTube, Mustafa Sibai, “Creating an RPG C++/SFML -Part 10- Moving the player with WASD”
5.	YouTube, Hilze Vonck, “SFML 2.4 For Beginners-1:Opening a Window”
6.	YouTube, Gamefromscratch, “SFML Tutorial – Spritesheets and Animations”
7.	SFML( official site), sectiunile “Tutorials” si “Documentation”
8.	SFML community forums>>help>>general, articolele “Health Bars..”, “Array of shapes”, “Sprites Collision- how to stop them from moving?”, “Different between sf::Event::KeyPressed and sf::Keyboard::isKeyPressed(…)”, “My first SFML game”, “Artificial Intelligence”, “NPC/AI, how?”, “Smoothest possible movement”, “Correct way to do a player movement”, “Player Movement with Classes”, “Smooth character movement with Arrow keys”, “How to resize my sprite and not have it so stretched out?”, “How to resize my sprite?...what am I missing?”.
