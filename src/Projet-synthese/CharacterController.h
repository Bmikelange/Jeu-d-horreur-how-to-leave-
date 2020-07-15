#ifndef _CHARCONTROL_H
#define _CHARCONTROL_H

#include "vec.h"
#include "mat.h"
#include "window.h"
#include "camera.h"

class CharacterController
	{
	public:
		CharacterController();

		//effectue les déplacements des personnages
		void update(const float dt);

		
		void turnXZ(const float& rot_angle_v);
		void accelerate(const float& speed_inc);
		void setVelocityMax(const float vmax);

		//définie la position du personnage
		void setPosition(const Vector& p);
		void setVelocityNorm(const float v);
		// récupère la position du personnage
		const Vector position() const;
		// récupère la direction du personnage
		const Vector direction() const;
		Camera&  getCam();

		float velocity() const;

		// récupère la transformation de déplacement du personnage
		Transform getCh2w();
		// définie la transformation de déplacement du personnage
		void setCh2w(Transform t);


		Vector Position;
	protected:
                Transform m_ch2w;   // matrice du character vers le monde
                                    // le personnage se déplace vers X
                                    // il tourne autour de Y
                                    // Z est sa direction droite
                                    
		float m_v;          // le vecteur vitesse est m_v * m_ch2w * Vector(1,0,0)
		float m_vMax;       // ne peut pas accélérer plus que m_vMax
		Camera camera;	//caméra de l'application
	};

#endif