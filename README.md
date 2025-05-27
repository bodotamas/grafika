# Chalet - Faház szimuláció

---

Ez a projekt **most készült el**, célom, hogy a tantárgyból **megszerezzem az aláírást**.

---

## 📁 Projekt Felépítés

📁 c_sdk_220203

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
                📄 cube.obj
                📄 fireplace.obj
                📄 hare.obj
                📄 house3.obj
                📄 raptor.obj
                📄 terrain.obj
            📁 textures
                📄 brick.jpg
                📄 cube.png
                📄 grass2.jpg
                📄 guide.png
                📄 guide2.png
                📄 hare.jpg
                📄 raptor.png
                📄 wood.jpg
                📁 skybox
                    📄back.jpg
                    📄bottom.jpg
                    📄front.jpg
                    📄left.jpg
                    📄right.jpg
                    📄skybox.png
                    📄top.jpg
        📁 include
            📄 app.h
            📄 camera.h
            📄 scene.h
            📄 texture.h
            📄 utils.h
        📁 src
            📄 app.c
            📄 camera.c
            📄 main.c
            📄 scene.c
            📄 texture.c
            📄 utils.c
        📄 fahaz.exe
        📄 Makefile


---

## 📌 Projektleírás

A feladatra egy egyedi szimulációs környezetet választottam:  
egy **faházat egy elhagyatott mezőn**, amelyet a felhasználó **kívülről körbejárhat**.

A szimuláció tartalmaz:
- Egy **tavat** a ház mellett
- Egy **Velociraptort** és egy **nyulat**, amelyek folyamatosan mozognak
- Egy **kandallót** a ház belsejében, amely **fahiány miatt nem működik**

A jelenet célja egy nyugodt, mégis izgalmas, mozgó világ megjelenítése különféle elemekkel.

---

## 🎮 Irányítás

A játékvezérlés egyszerű és intuitív. A **TAB** billentyű lenyomásával megjelenik egy **GUIDE menü**, amely részletesen ismerteti az alapvető irányítási lehetőségeket.

---

<img src="./beadando2/assets/textures/guide.png" alt="Controls" width="700"/>

---

## 💡 További fejlesztési lehetőségek

- Interaktívabb környezet (pl. tüzet lehet rakni a kandallóban, ha fát találunk)
- Dinamikus időjárás
- Faház továbbfejlesztése

---
