# 🌌 Outer Space - Naprendszer szimuláció

Ez a projekt egy egyszerű **Naprendszer szimuláció**, amelyben bolygók mozognak a Nap körül, a kamera szabadon irányítható, és különböző látványos effektek is aktiválhatók.

---

## 📁 Projekt Felépítés

📁 csdk

    📁 examples
        └── ...
    📁 MinGW
        └── ...
    📁 Notepad++
        └── ...
    📄 shell.bat
    📁 beadando
        📁 assets
            📁 models
                📄 deathstar.obj
                📄 falcon.obj
                📄 geoid.obj
                📄 jupiter.obj
                📄 mars.obj
                📄 mercury.obj
                📄 saturn.obj
            📁 textures
                📄 deathstar.png
                📄 earth.png
                📄 falcon.png
                📄 help.png
                📄 jupiter.png
                📄 mercury.png
                📄 saturnbody.png
                📄 sky.png
                📄 sun.png
        📁 include
            📄 camera.h
            📄 draw.h
            📄 model.h
        📁 src
            📄 camera.c
            📄 draw.c
            📄 model.c
            📄 main.c
        📄 beadando.exe
        📄 glut32.dll
        📄 libfreeglut.dll
        📄 SOIL.dll
        📄 Makefile

---


## 🕹️ Irányítások

<img src="./beadando/assets/textures/help.png" alt="Controls" width="700"/>

- **W-A-S-D**: Mozgás előre, balra, hátra, jobbra.
- **Space / C**: Fel és le mozgás.
- **Egér**: Kamera forgatása (egérgomb nyomva tartásával).
- **E**: Bolygók mozgásának elindítása/leállítása.
- **F**: Millennium Falcon megjelenítése.
- **- / +**: Környezeti fényerő csökkentése/növelése.
- **Q**: Föld forgásának elindítása/leállítása.
- **X**: Napkitörés (solar flare) létrehozása.
- **H**: Űrköd (space nebula) létrehozása.

---


## ✨ Főbb funkciók

- Bolygók Kepler-törvények szerinti mozgása.
- Kamera szabad mozgása billentyűzettel és egérrel.
- Millennium Falcon különleges eseményként megjeleníthető.
- Dinamikus fényerő szabályozás.
- Napkitörés effekt (részecskerendszer).
- Űrköd (space nebula) generálás.
- Textúrázott modellek (pl. Szaturnusz gyűrűje, Föld, Jupiter stb.).

---


