
//! \file tuto7.cpp reprise de tuto6.cpp mais en derivant App::init(), App::quit() et bien sur App::render().

#include "wavefront.h"
#include "texture.h"

#include "orbiter.h"
#include "draw.h"
#include "app.h"
#include "CharacterController.h"
#include "audio.h"
#include "glcore.h"
#include "shader.h"
#include "Objet.h"
#include "libs/imgui-master/imgui.h"
#include "libs/imgui-master/examples/imgui_impl_sdl.h"
#include "libs/imgui-master/examples/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>

class TP : public App
{
public:
    // constructeur : donner les dimensions de l'image, et eventuellement la version d'openGL.
    TP() : App(1024, 640) {}

    // creation des objets de l'application
    int init()
    {
        //initialise l'interface
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(this->m_window, this->m_context);
        ImGui_ImplOpenGL3_Init("#version 330");

        //initialise les meshs
        Objets.push_back(&m_caracter);
        m_caracter.mesh = read_mesh("data/projet/mesh/main.obj");
        Objets.push_back(&m_terrain);
        m_terrain.mesh = read_mesh("data/projet/mesh/sale2.obj");
        Objets.push_back(&m_terrain2);
        m_terrain2.mesh = read_mesh("data/projet/mesh/terrain2.obj");
        Objets.push_back(&lit);
        lit.mesh = read_mesh("data/projet/mesh/litdéformé.obj");
        Objets.push_back(&cheval);
        cheval.mesh = read_mesh("data/projet/mesh/chevalabasculedéformé.obj");
        Objets.push_back(&coussin1);
        coussin1.mesh = read_mesh("data/projet/mesh/coussindéformé.obj");
        Objets.push_back(&coussin2);
        coussin2.mesh = read_mesh("data/projet/mesh/coussin.obj");
        Objets.push_back(&canape);
        canape.mesh = read_mesh("data/projet/mesh/canapédéformé.obj");
        Objets.push_back(&vase);
        vase.mesh = read_mesh("data/projet/mesh/vase.obj");
        Objets.push_back(&vaseC);
        vaseC.mesh = read_mesh("data/projet/mesh/vasecassé.obj");
        Objets.push_back(&CouteauSang);
        CouteauSang.mesh = read_mesh("data/projet/mesh/couteausang.obj");
        Objets.push_back(&Shelf);
        Shelf.mesh = read_mesh("data/projet/mesh/shelf_pleine.obj");
        Objets.push_back(&Piano);
        Piano.mesh = read_mesh("data/projet/mesh/piano.obj");
        Objets.push_back(&Cape);
        Cape.mesh = read_mesh("data/projet/mesh/cape.obj");
        plane = read_mesh("data/projet/mesh/chien.obj");
        Guitare.mesh = read_mesh("data/projet/mesh/guitare.obj");
        back = read_mesh("data/projet/mesh/background.obj");

        //initialise les textures
        m_texture = read_texture(0, "data/projet/img/main.png");
        m_text_terrain = read_texture(0, "data/projet/img/sale2text.png");
        text_lit = read_texture(0, "data/projet/img/lit.png");
        m_text_terrain2 = read_texture(0, "data/projet/img/textureTerrain2.png");
        textChev = read_texture(0, "data/projet/img/textCheval.png");
        textCoussin = read_texture(0, "data/projet/img/textCoussin1.png");
        tCanape = read_texture(0, "data/projet/img/textCanapé.png");
        tVase = read_texture(0, "data/projet/img/testVase1.png");
        tCouteau = read_texture(0, "data/projet/img/couteau.png");
        textFull = read_texture(0, "data/projet/img/shelf_pleine.png");
        texPiano = read_texture(0, "data/projet/img/textpiano.png");
        texCape = read_texture(0, "data/projet/img/robe.png");
        texPlane = read_texture(0, "data/projet/img/chien.png");
        texGuitare = read_texture(0, "data/projet/img/textureTerrain2.png");
        Font = read_texture(0, "data/projet/img/background.png");

        //initialises les boudings box
        Point pmin, pmax;
        Cape.mesh.bounds(pmin, pmax);
        m_caracter.AddBox(pmin, pmax, Identity());
        lit.mesh.bounds(pmin, pmax);
        lit.AddBox(pmin, pmax, Translation(0, 0, -6) * Scale(0.3, 0.3, 0.3));
        cheval.mesh.bounds(pmin, pmax);
        cheval.AddBox(pmin, pmax, Translation(2, 0, 3) * Scale(0.2, 0.2, 0.2));
        coussin1.mesh.bounds(pmin, pmax);
        coussin1.AddBox(pmin, pmax, Translation(4, 0, 2) * Scale(0.3, 0.3, 0.3));
        coussin2.mesh.bounds(pmin, pmax);
        coussin2.AddBox(pmin, pmax, Translation(4, 0, 3.5) * Scale(0.3, 0.3, 0.3));
        canape.mesh.bounds(pmin, pmax);
        canape.AddBox(pmin, pmax, Translation(5.5, 0, 3.5) * Scale(0.4, 0.4, 0.4));
        vase.mesh.bounds(pmin, pmax);
        vase.AddBox(pmin, pmax, Translation(4, 0, -6) * Scale(0.2, 0.2, 0.2));
        vaseC.mesh.bounds(pmin, pmax);
        vaseC.AddBox(pmin, pmax, Translation(4.5, 0.1, -5) * RotationX(-75) * Scale(0.2, 0.2, 0.2));
        Shelf.mesh.bounds(pmin, pmax);
        Shelf.AddBox(pmin, pmax, Translation(-5, 0, -1) * RotationY(90) * Scale(0.3, 0.3, 0.3));
        Piano.mesh.bounds(pmin, pmax);
        Piano.AddBox(pmin, pmax, Translation(0, 0, -1) * Scale(0.5, 0.5, 0.5));

        getBoxes("data/projet/boites/sale2.txt", m_terrain);
        shad.init();
        aud.audio_Init();
        // etat openGL par defaut
        glClearColor(0.2f, 0.2f, 0.2f, 1.f); // couleur par defaut de la fenetre

        glClearDepth(1.f);       // profondeur par defaut
        glDepthFunc(GL_LESS);    // ztest, conserver l'intersection la plus proche de la camera
        glEnable(GL_DEPTH_TEST); // activer le ztest
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        CC.getCam().lookAt((Point)CC.position(), 5);
        m_view = CC.getCam();

        return 0; // ras, pas d'erreur
    }

    // destruction des objets de l'application
    int quit()
    {
        m_caracter.mesh.release();
        lit.mesh.release();
        m_terrain.mesh.release();
        m_terrain2.mesh.release();
        cheval.mesh.release();
        coussin1.mesh.release();
        coussin2.mesh.release();
        canape.mesh.release();
        vase.mesh.release();
        vaseC.mesh.release();
        CouteauSang.mesh.release();
        Shelf.mesh.release();
        Piano.mesh.release();
        Cape.mesh.release();
        Guitare.mesh.release();
        plane.release();
        back.release();
        glDeleteTextures(1, &m_texture);
        glDeleteTextures(1, &m_text_terrain2);
        glDeleteTextures(1, &m_text_terrain);
        glDeleteTextures(1, &textChev);
        glDeleteTextures(1, &textCoussin);
        glDeleteTextures(1, &tCanape);
        glDeleteTextures(1, &tVase);
        glDeleteTextures(1, &text_lit);
        glDeleteTextures(1, &tCouteau);
        glDeleteTextures(1, &textFull);
        glDeleteTextures(1, &texPiano);
        glDeleteTextures(1, &texCape);
        glDeleteTextures(1, &texPlane);
        glDeleteTextures(1, &texGuitare);
        glDeleteTextures(1, &Font);
        shad.quit();
        aud.audio_Quit();

        return 0;
    }

    // lis et crée les boxes de collisions autour des murs à partir d'un fichier
    void getBoxes(const char *filepath, Objet &obj)
    {
        std::string s;
        std::ifstream file(filepath);
        if (file.is_open())
        {

            getline(file, s);
            int nbPoint = atoi(s.c_str());
            Point p[nbPoint * 2];
            Transform t[nbPoint];
            for (int i = 0; i < nbPoint; ++i)
            {
                getline(file, s);
                std::istringstream ss(s);
                float x, y, z;
                ss >> x;
                ss >> y;
                ss >> z;
                p[i * 2] = Point(x, y, z);
                getline(file, s);
                std::istringstream ss2(s);
                ss2 >> x;
                ss2 >> y;
                ss2 >> z;
                p[i * 2 + 1] = Point(x, y, z);
                getline(file, s);
                float angle = atoi(s.c_str());
                if (angle == 0)
                    t[i] = Identity();
                else
                    t[i] = RotationY(angle);
            }
            file.close();
            for (int i = 0; i < nbPoint; i++)
                obj.AddBox(p[i*2], p[i*2 + 1], t[i]);
        }
        else
        {
            std::cout << "Unable to open file";
        }
    }

    // crée et affiche la touche à presser à proximité d'un indice
    void afficheE()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(480, 250));
        ImGui::SetNextWindowSize({100.0f, 30.0f});
        ImGui::Begin("Press E");
        ImGui::Text("............");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    // crée et affiche le message de victoire
    void afficheWin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(480, 250));
        ImGui::SetNextWindowSize({100.0f, 30.0f});
        ImGui::Begin("YOU WIN");
        ImGui::Text(".............");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // crée et affiche le message de perte
    void afficheLoose()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(480, 250));
        ImGui::SetNextWindowSize({100.0f, 30.0f});
        ImGui::Begin("YOU LOOSE");
        ImGui::Text("..............");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // crée et affiche le menu principal
    void afficheMenu()
    {
        Orbiter o=Orbiter();
        draw(back,Translation(0,1,0)*RotationX(90),o,Font);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(480, 350));
        ImGui::Begin("Menu");
        if (ImGui::Button("Play"))
        {
            controlefin = 5;
            aud.play_audio(aud.getPluie());
        }
        if (ImGui::Button("how to play?"))
            controlefin = 4;
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // crée et affiche le menu de presentation des touches
    void afficheInfo()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(450, 250));
        ImGui::Begin("how to play?");
        ImGui::Text("Z to moving forward");
        ImGui::Text("S to back off");
        ImGui::Text("D to turn right");
        ImGui::Text("Q to turn left");
        ImGui::Text("E to interact");
        if (ImGui::Button("Back"))
            controlefin = 3;
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // crée et affiche la boite de dialogue
    void affichetext(const char *s, const char *people, int line_number = 1, bool skippable = false)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(350, 100));
        ImGui::SetNextWindowSize({400.0f, 50.f + 18.f * line_number});
        ImGui::Begin(people);
        ImGui::Text("%s", s);
        if (skippable && ImGui::Button("skip"))
        {
            delay = 200.f;
            dialogue += 2000 - dialogue % 2000;
        }
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    //applique une transformation à une boite de collision
    void box_transform(Transform &T, Objet m)
    {
        for (unsigned int i = 0; i < m.boxes.size(); i++)
        {
            Objets[0]->boxes[i].T = T;
        }
    }

    // dessine une nouvelle image
    int render()
    {
        //affiche les boxs de collisions
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (controlefin == 0)
        {
            if (debug == 1 || debug == 2)
            {
                for (unsigned int i = 0; i < Objets.size(); ++i)
                {
                    for (unsigned int j = 0; j < Objets[i]->boxes.size(); ++j)
                    {
                        Mesh &m = Objets[i]->boxes[j].meshcollider;
                        draw(m,
                             Objets[i]->boxes[j].T,
                             m_view.view(),
                             m_view.projection(window_width(),
                                               window_height(), 45));
                    }
                }
            }
            //affiche la scène principale
            if (debug == 0 || debug == 2)
            {
                Point luxPosition;
                if (shad.foudreControle > 3000)
                {
                    luxPosition = (Point)((Point)CC.Position + Point(0, 0.2, 0) - 0.3 * (Point)CC.direction());

                }
                else
                {
                    luxPosition = Point(10, 0, 10);
                }
                Point Direction = (Point)CC.direction();

                shad.edraw(m_caracter.mesh, CC.getCh2w() * Translation(-0.1, 0.3, 0) * RotationY(-90) * Scale(0.08, 0.1, 0.05), m_view, m_texture, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(Cape.mesh, CC.getCh2w() * Translation(0, 0.3, 0) * RotationX(90) * Scale(0.3, 0.3, 0.2), m_view, texCape, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(lit.mesh, Translation(0, 0, -6) * Scale(0.3, 0.3, 0.3), m_view, text_lit, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(m_terrain.mesh, Identity(), m_view, m_text_terrain, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(m_terrain2.mesh, Translation(0, -2, 0) * Scale(20, 10, 20), m_view, m_text_terrain2, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(cheval.mesh, Translation(2, 0, 3) * Scale(0.2, 0.2, 0.2), m_view, textChev, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(coussin1.mesh, Translation(4, 0, 2) * Scale(0.3, 0.3, 0.3), m_view, textCoussin, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(coussin2.mesh, Translation(4, 0, 3.5) * Scale(0.3, 0.3, 0.3), m_view, textCoussin, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(canape.mesh, Translation(5.5, 0, 3.5) * Scale(0.4, 0.4, 0.4), m_view, tCanape, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(vase.mesh, Translation(4, 0, -6) * Scale(0.2, 0.2, 0.2), m_view, tVase, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(vaseC.mesh, Translation(4.5, 0.15, -5) * RotationX(-75) * Scale(0.2, 0.2, 0.2), m_view, tVase, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(CouteauSang.mesh, Translation(-1, 0.7, -7) * RotationX(-90) * Scale(0.05, 0.05, 0.05), m_view, tCouteau, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(CouteauSang.mesh, Translation(1, 0.7, -7) * RotationX(90) * RotationY(180) * Scale(0.05, 0.05, 0.05), m_view, tCouteau, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(Shelf.mesh, Translation(-5, 0, -1) * RotationY(90) * Scale(0.3, 0.3, 0.3), m_view, textFull, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(Piano.mesh, Translation(0, 0, -1) * Scale(0.5, 0.5, 0.5), m_view, texPiano, luxPosition, Direction, shad.getProgram(0));
                shad.edraw(Guitare.mesh, Translation(0, 0.4, -6.5) * RotationY(180) * RotationX(90) * Scale(0.1, 0.1, 0.1), m_view, texGuitare, luxPosition, Direction, shad.getProgram(0));
                if (shad.foudreControle <= 3000)
                {
                    shad.edraw(plane, Translation(CC.Position) * Translation(-1, 0.8, 0) * RotationY(90) * Scale(0.8, 0.8, 0.8), m_view, texPlane, luxPosition, Direction, shad.getProgram(1));
                    if (actionEc == 1)
                    {
                        affichetext("I see you.", "voice", 1, true);
                    }
                    if (actionEc == 2)
                    {
                        affichetext("tic tac tic tac.", "voice", 1, true);
                    }
                    if (actionEc == 3)
                    {
                        affichetext("oof.", "voice", 1, true);
                    }
                }
            }
        }
        //affiche la touche à presser si on est à proximité d'un indice
        if (controleindice == 1 && controlefin == 0)
        {
            afficheE();
        }
        //affiche si l'on gagne
        if (controlefin == 1)
        {
            afficheWin();
        }
        //affiche si l'on perd
        if (controlefin == 2)
        {
            afficheLoose();
        }
        //affiche le menu principal
        if (controlefin == 3)
        {
            afficheMenu();
        }
        //affiche le menu d'expliquation des touches
        if (controlefin == 4)
        {
            afficheInfo();
        }
        //affiche les dialogues
        if (controlefin == 5)
        {
            if (dialogue < 2000)
                affichetext("Hum...? Where am I?", "child", 1, true);
            if (dialogue < 4000 && dialogue > 2000)
                affichetext("What am I doing here?", "child", 1, true);
            if (dialogue < 6000 && dialogue > 4000)
                affichetext("Hello young man.", "voice", 1, true);
            if (dialogue < 8000 && dialogue > 6000)
                affichetext("We are delighted to welcome you.", "voice", 1, true);
            if (dialogue < 10000 && dialogue > 8000)
                affichetext("Who are you?", "child", 1, true);
            if (dialogue < 12000 && dialogue > 10000)
                affichetext("Lets play a game.", "voice", 1, true);
            if (dialogue < 14000 && dialogue > 12000)
                affichetext("You have two hundred and forty seconds to find\na way to exit.", "voice", 2, true);
            if (dialogue < 16000 && dialogue > 14000)
                affichetext("After this time...", "voice", 1, true);
            if (dialogue < 18000 && dialogue > 16000)
                affichetext("Good Bye.", "voice", 1, true);
            if (dialogue < 20000 && dialogue > 18000)
                affichetext("But we are magnanimous.", "voice", 1, true);
            if (dialogue < 22000 && dialogue > 20000)
                affichetext("We left you a lamp and some advice to help you.", "voice", 1, true);
            if (dialogue < 24000 && dialogue > 22000)
                affichetext("Listen carrefully.", "voice", 1, true);
            if (dialogue < 32000 && dialogue > 24000)
                affichetext("My first is a place to sleep.\nMy second is  a game from our childhood.\nMy third is a way to grow up.\nMy fourth is where you are not allowed to jump.\nMy fifth is in front of where the white and the black\nsing in harmony.\nMy last is next to what you seek", "voice", 6, true);
            if (dialogue < 34000 && dialogue > 32000) 
                affichetext("We will let you guess the last one", "voice", 1, true);

            if (dialogue < 34000 && dialogue > 32000)
                affichetext("Good luck.", "voice", 1, true);
            if (dialogue > 34000)
                controlefin = 0;
        }

        return 1;
    }

    // vérifie la posisition du personnage par rapport à un indice
    void verifPos(Vector v, int &controlePos, int value)
    {
        if (length(CC.Position - v) < 1 && controleindice == 0 && controlePoss[value] == 0)
        {
            controleindice = 1;
            controlePos = value;
        }
    }

    // vérifie si l'on touche un objet ou non
    bool verifCollide(Vector &x, int &s)
    {
        bool n = false;
        for (unsigned int i = 1; i < Objets.size(); i++)
        {
            for (unsigned int j = 0; j < Objets[i]->boxes.size(); j++)
            {
                n = Objets[0]->boxes[0].collides3d(Objets[i]->boxes[j], x);
                if (n == true)
                {
                    s = i;
                    return true;
                }
            }
        }
        return false;
    }
    int update(const float time, const float delta)
    {
        //boucle de dialogue
        if (controlefin == 5)
        {
            dialogue += delta;
            delay -= delta;
            if (controlefin == 5 && key_state(' ') && delay <= 0)
            {
                delay = 200.f;
                dialogue += 2000 - dialogue % 2000;
            }
        }
        //boucle principal
        if (controlefin == 0)
        {
            //affiche les boxs de collisions
            delay -= delta;
            if (key_state('g') && delay <= 0)
            {
                debug = (debug + 1) % 3;
                delay = 200.f;
                std::cout << "DEBUG Toggled !" << std::endl;
            }

            //controle les déplacements en fonction des boxs de collisions
            shad.time = time * 0.001;
            Transform T1 = CC.getCh2w();
            Vector x;
            int s;
            if (shad.foudreControle > 3000)
            {
                CC.update(delta);
                if (verifCollide(x, s))
                {
                    CC.setCh2w(T1 * Translation(Vector(0,0,0.02)));
                    Transform T = CC.getCh2w() * Translation(0, 0.3, 0) * RotationX(90) * Scale(0.3, 0.3, 0.2);
                    box_transform(T, m_caracter);
                    if (verifCollide(x, s))
                    {
                        CC.setCh2w(T1 * Translation(Vector(0,0,-0.02)));
                        Transform T = CC.getCh2w() * Translation(0, 0.3, 0) * RotationX(90) * Scale(0.3, 0.3, 0.2);
                        box_transform(T, m_caracter);
                        if (verifCollide(x, s))
                        {
                            CC.setCh2w(T1 * Translation(Vector(0.02,0,0)));
                            Transform T = CC.getCh2w() * Translation(0, 0.3, 0) * RotationX(90) * Scale(0.3, 0.3, 0.2);
                            box_transform(T, m_caracter);
                            if (verifCollide(x, s))
                            {
                                CC.setCh2w(T1 * Translation(Vector(-0.02,0,0)));
                            }
                        }
                    }
                }
                Transform T = CC.getCh2w() * Translation(0, 0.3, 0) * RotationX(90) * Scale(0.3, 0.3, 0.2);
                box_transform(T, m_caracter);
            } else if (controleThundersound == 0 && shad.foudreControle > 100) {
                aud.play_audio(aud.getThunder());
                controleThundersound = 1;
            }
            m_view = CC.getCam();

            // vérifie si on est à une certaine distance d'un indice et gère les interactions avec
            static int controlePos = -1;

            verifPos(Vector(4.5, 0, 3.5), controlePos, 0);
            verifPos(Vector(0, 0, -5.0), controlePos, 1);
            verifPos(Vector(-5, 0, -1), controlePos, 2);
            verifPos(Vector(-3, 0, -7), controlePos, 3);
            verifPos(Vector(4.5, 0, -1), controlePos, 4);
            verifPos(Vector(0, 0, 5), controlePos, 5);
            if (length(CC.Position - Vector(4.5, 0, 3.5)) >= 1 &&
                length(CC.Position - Vector(0, 0, -5)) >= 1 &&
                length(CC.Position - Vector(-5, 0, -1)) >= 1 &&
                length(CC.Position - Vector(-3, 0, -7)) >= 1 &&
                length(CC.Position - Vector(4.5, 0, -1)) >= 1 &&
                length(CC.Position - Vector(0, 0, 5)) >= 1)

            {
                controleindice = 0;
            }

            if (controleindice == 1 && controlePoss[controlePos] == 1)
            {
                controleindice = 0;
            }
            if (controleindice == 1 && key_state('e'))
            {
                shad.nbindice++;
                clear_key_state('e');
                controlePoss[controlePos] = 1;
            }

            // vérifie si l'on à gagné ou perdu
            if (shad.nbindice == 6)
            {
                controlefin = 1;
                aud.pause_audio(aud.getPluie());
            }
            if (countFoudre == 4)
            {
                controlefin = 2;
                aud.pause_audio(aud.getPluie());
                aud.play_audio(aud.getCri());
            }

            //lance ou éteint les bruits de pas
            static int controleMusic = 0;

            if ((key_state('s') || key_state('z') || key_state('q') || key_state('d')) && controleMusic == 0)
            {
                controleMusic = 1;
                aud.play_audio(aud.getWav());
            }
            if (!(key_state('s') || key_state('z') || key_state('q') || key_state('d')) && controleMusic == 1)
            {
                controleMusic = 0;
                aud.pause_audio(aud.getWav());
            }

            //lance le bruit de brisure du vase
            static int controleVase = 0;
            if (length(CC.Position - Vector(5, 0, -6)) < 6 && controleVase == 0)
            {
                aud.play_audio(aud.getVase());
                controleVase = 1;
            }

            //lance ou éteint les bruits à proximité du canapé
            static int controleSaut = 0;

            if (length(CC.Position - Vector(5.5, 0, 3.5)) < 4 && controleSaut == 0)
            {
                controleSaut = 1;
                aud.play_audio(aud.getSaut());
            }
            if (!(length(CC.Position - Vector(5.5, 0, 3.5)) < 4) && controleSaut == 1)
            {
                controleSaut = 0;
                aud.pause_audio(aud.getSaut());
            }

            //lance un éclair
            static int timed = 0;
            static int controle = 0;
            if (controle == 0)
            {
                shad.foudreControle = 60000;
                controle = 1;
            }

            if (timed < 60000)
            {
                shad.foudreControle = 60000 - timed;
            }
            else
            {
                shad.foudreControle = 60000;
                controleThundersound = 0;
                timed = 0;
                countFoudre++;
                actionEc++;
            }
            timed += delta;

            //lance le son d'un violon après le premier éclair
            static int violon = 0;
            if (violon == 0 && actionEc == 1)
            {
                aud.play_audio(aud.getViolon());
                violon = 1;
            }
            timed += delta;
        }
        return 1;
    }

protected:
    //déclaration des objets à afficher
    Objet m_caracter;
    Objet m_terrain;
    Objet m_terrain2;
    Objet lit;
    Objet cheval;
    Objet coussin1;
    Objet coussin2;
    Objet canape;
    Objet vase;
    Objet vaseC;
    Objet CouteauSang;
    Objet Shelf;
    Objet Piano;
    Objet Cape;
    Objet Guitare;
    Mesh plane;
    Mesh back;

    // déclaration des textures des objets
    GLuint m_texture;
    GLuint m_text_terrain;
    GLuint m_text_terrain2;
    GLuint text_lit;
    GLuint textChev;
    GLuint textCoussin;
    GLuint tCanape;
    GLuint tVase;
    GLuint tCouteau;
    GLuint textFull;
    GLuint texPlane;
    GLuint texPiano;
    GLuint texCape;
    GLuint texGuitare;
    GLuint Font;
    //controlleur de déplacement
    CharacterController CC;

    //caméra
    Orbiter m_view;
    //shader
    shader shad;
    //audio
    audio aud;
    //accès rapide aux objets
    std::vector<Objet *> Objets;

    //controle les évènements
    int controleindice = 0;
    int controlefin = 3;
    int controlePoss[6] = {0};
    int controleThundersound = 0;
    int dialogue = 0;
    int countFoudre = 0;
    int delay = 0;
    int debug = 0;
    int actionEc = 0;
};

int main(int argc, char **argv)
{
    // il ne reste plus qu'a creer un objet application et la lancer
    TP tp;
    tp.run();

    return 0;
}
