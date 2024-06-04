# 🎮 my_rpg 🗡️ Drysfa Xaar

![Drysfa Xaar](https://toro-nicolas.github.io/my_rpg/preview.png)

## Table of contents 📑
- [Description](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#description-)
- [Usage](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#usage-%EF%B8%8F)
- [Result](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#result-)
- [Compilation](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#compilation-%EF%B8%8F)
- [Documentation](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#documentation-)
- [Code mandatory](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#code-mandatory-)
- [What's next ?](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#whats-next--)
- [Contributors](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#contributors-)


## Description 📝
The **my_rpg** is a project carried out by **groups of 4** (see [Contributors](https://github.com/toro-nicolas/my_rpg/blob/main/README.md#contributors-), during our **1st year** in [**EPITECH**](https://www.epitech.eu/) Grand Ecole program.  
Its purpose is to create in [**C**](https://en.wikipedia.org/wiki/C_(programming_language)) a [**Role Playing Game**](https://en.wikipedia.org/wiki/Role-playing_game).  
An RPG, or role-playing game, is a type of **video game** where you **embody a character** and progress through a **story** by **completing quests**, **fighting enemies** and developing your **character's skills**.  
In our rpg, you play the role of a **little spirit trapped in a labyrinth**, and your aim is to **escape from the maze**.  


## Usage ⚔️
You can run my_rpg like this :
```sh
./my_rpg
```

For more information, please see the help section or the tutorial.
```sh
> ./my_rpg -h
USAGE
        ./my_rpg

DESCRIPTION
        A role-playing game made by Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Raphaël LAUNAY.
```


## Result 🚩
The result of this project is an **almost perfect my_rpg**.  
If you discover a **problem** or an **error**, don't hesitate to **create an issue** and **report it** to us as soon as possible.


### my.epitech.eu result

| Category          | Percentage | Numbers of tests |  Crash   |
|-------------------|:----------:|:----------------:|:--------:|
| Minimal functions |     0%     |       0/1        |    No    |
| repository size   |    100%    |       1/1        |    No    |
| **Results**       |  **50%**   |     **1/2**      |  **No**  |


### Keynote result
We got the **best my_rpg** of **our class**.

Project Mark :
```
Mark : 68
Preliminary (2 / 2) :

Error management (2 / 2) :

Window management (3 / 3) :
Tri state
Events (1 / 1) :

Animations (2 / 2) :
Tout suer la meme sprite sheet
sfClock and framerate (3 / 3) :
OK
Basic button (2 / 2) :
OK
Welcome menu (1 / 1) :
OK
Settings option (2 / 2) :
Volume slider
Setting option : volume (2 / 2) :
Separation des deux
Setting option : window (3 / 3) :
OK
Saving system (part I) (2 / 2) :
Save
Ingame menu access (1 / 1) :
OK
Character's option : characteristics (3 / 3) :
Carac
Character's option : inventory (2 / 3) :
Que des armes
Character's option : equipement (3 / 3) :
OK
Saving system (part II) (1 / 3) :
Save le character
Setting's option : volume & window (1 / 1) :
OK
Setting's option : commands (2 / 2) :
OK
General informations (2 / 2) :
NPC visible
Character informations (3 / 3) :
OK
NPC and ennemies informations (3 / 3) :
OK
Visuals rendering (1 / 2) :
Render 2D
Colliding system (2 / 2) :
Collisions avec meshing
Fightings effects (1 / 3) :
Animation d'attaque
Environnement effects (0 / 3) :

The universe (1 / 4) :

Quest and NPC (2 / 4) :

Fighting system (4 / 4) :
ARPG
Gains (4 / 4) :
OK
Global architecture (2 / 3) :

Game engine (0 / 10) :

Rigor code (-1 / 0) :

Skills/abilities tree (0 / 4) :

Configuration files (1 / 3) :
Simple texte 
Map editor (0 / 5) :

Procedural generation (5 / 5) :
Génération procédurale
Scripting language (0 / 2) :

Bonus (0 / 20) :

```

Oral Mark :
```
Mark : 4142
Testing Policy (2 / 4) :

Methodology and Organisation (40 / 40) :
Organisation
Involvment (100 / 400) :

Oral Presentation (4000 / 4000) :
Du coup, et voilà
Des caractères non joueurs
Ne faites pas référence aux groupes précédents, la keynote est la votre.
Librairie != bibliothèque
Video des 3 hunters très bon
video du  hunter très bon
CSFML a expliciter
Démonstration en video.
Difficultés techniques intéressantes mais montrez !
```


### Features
| Feature                                                                                                                                                                                                          | Mandatory | Must | Should | Could |
|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------|------|--------|-------|
| The player needs to have characteristics                                                                                                                                                                         | ✅         |      |        |       |
| The player can fight enemies AND the characteristics impact the fights results                                                                                                                                   | ✅         |      |        |       |
| The player have an inventory which can contain a limited set of items                                                                                                                                            | ✅         |      |        |       |
| The player can earn experience by winning fights and/or accomplishing specific actions                                                                                                                           | ✅         |      |        |       |
| The player can level up thanks to experience AND upgrading its characteristics                                                                                                                                   | ✅         |      |        |       |
| The game contains NPC                                                                                                                                                                                            | ✅         |      |        |       |
| The game contains at least one quest                                                                                                                                                                             | ✅         |      |        |       |
| The game contains a how to play system at the very beginning                                                                                                                                                     | ✅         |      |        |       |
| Collision system including moving and static elements with different shapes                                                                                                                                      |           | ✅    |        |       |
| Camera movements (zoom, translation, rotation)                                                                                                                                                                   |           | ✅    |        |       |
| 3D effects (depth scaling, isometric projection...)                                                                                                                                                              |           | ✅    |        |       |
| Buttons must have at least 3 different states                                                                                                                                                                    |           | ✅    |        |       |
| Saving system (You can try to use sfView elements)                                                                                                                                                               |           | ✅🤷  |        |       |
| The window may be closed using events                                                                                                                                                                            |           | ✅    |        |       |
| The windows may have different modes: Window mode, Full-screen mode                                                                                                                                              |           | ✅    |        |       |
| The windows may have different resolutions, at least two (1920x1080, and an other)                                                                                                                               |           | ✅    |        |       |
| The game manages inputs from the mouse click and keyboard                                                                                                                                                        |           | ✅    |        |       |
| The game contains animated sprites rendered thanks to sprite sheets                                                                                                                                              |           | ✅    |        |       |
| Animations in your program are frame rate independent                                                                                                                                                            |           | ✅🤷  |        |       |
| Animations and movements in your program are timed by clocks                                                                                                                                                     |           | ✅🤷  |        |       |
| Main menu                                                                                                                                                                                                        |           | ✅    |        |       |
| Must contain at least these options: Start the game, Resume game (grayed out if not possible), Settings, Quit the game                                                                                           |           | ✅    |        |       |
| The settings option must contain: Sound and music volume options, A window size and resolution options                                                                                                           |           | ✅    |        |       |
| In-game menu                                                                                                                                                                                                     |           |      |        |       |
| Must be accessible by pressing the Escape key                                                                                                                                                                    |           |      | ✅      |       |          
| Must contain at least these options: Character options (equipment and inventory management, characteristics management), Saving, Loading, Settings (the same as main menu), Commands list                        |           |      | ✅🤷    |       |          
| Splash screen at the beginning                                                                                                                                                                                   |           |      | ✅      |       |          
| Command edit into the in-game menu                                                                                                                                                                               |           |      | ✅      |       |          
| As much information as possible about the game should be stored in a configuration file                                                                                                                          |           |      | ❌      |       |          
| The game should have an advanced collision system to manage complex fighting                                                                                                                                     |           |      |        | ✅     |
| The game should contain a simple particle system: with at least 2 types of particle, particle effects (changing colors, scaling, bouncing, fading) to simulate realistic environment (wind, fire, rain, snow...) |           |      |        | ✅     |
| Could have a skill tree, unlocking different abilities (active and passive)                                                                                                                                      |           |      |        | ❌     |
| Could have a complete particle engine                                                                                                                                                                            |           |      |        | ❌     |
| Could use scripting to describe entities                                                                                                                                                                         |           |      |        | ❌     |
| Could have a map editor                                                                                                                                                                                          |           |      |        | ✅🤷   |


### Tests and code coverage
**Unit tests** were performed using [criterion](https://criterion.readthedocs.io/en/master/intro.html).  
In this project, **only** the **library code is covered**.  
Unit tests are still to be performed, but a large part of the code is already covered:
- Lines: 90.0%
- Functions: 100%
- Branches:	41.5%

You can compile the project and run the unit tests with this command :
```sh
make tests_run
```

For more details, please click [here](https://toro-nicolas.github.io/my_rpg/tests/test.html).


## Compilation 🛠️
You can compile the project with this command :
```sh
make
```

If you want clean the project, you can run this command :
```sh
make fclean
```

You can clean and compile the project with ```make re```.    

You can compile the unit tests with this command :
```sh
make unit_tests
```


## Documentation 📚
The documentation is accessible [here](https://toro-nicolas.github.io/my_rpg/html/).

You can generate the documentation with this command :
```sh
make doc
```
You need multiple package for generate them :
- doxygen
- doxygen-latex
- doxygen-doxywizard
- graphviz


## Code mandatory 📦
- You'll need to create a branch where you'll push your code. Once you've completed your tasks on this branch, we'll work together to merge it and check that everything works.
- Every function you add must be code-style.
- Before merging, you'll need to check that all unit tests pass by running ```make tests_run```.
- If the github actions don't succeed, then ask yourself some questions
- Each commit will contain ```[+]``` or ```[-]``` or ```[~]``` followed by a message
    - ```[+]``` : Add feature
    - ```[-]``` : Delete feature
    - ```[~]``` : Edit feature

**Of course, in exceptional cases, we may depart from these rules.**


## What's next ? 🚀
- Finish the saving system
- Add new items like consomables or equipment
- Add new decorations
- Add a final boss
- Rework the scenario
- Add unit tests on each piece of code


## Contributors 👥
For this project, we were a group of **4 people**. Here are the people in the group:
- [Gianni TUERO](https://github.com/xJundo)
- [Lou PELLEGRINO](https://github.com/DimitriLaPoudre)
- [Nicolas TORO](https://github.com/toro-nicolas)
- [Raphaël LAUNAY](https://github.com/frenchkiwi)
