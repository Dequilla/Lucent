#pragma once

#include "BaseComponent.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace ce { namespace game {

	class TransformComponent : public BaseComponent
	{
	protected:
		/**
		* \brief Our position vector
		*
		* Each axis represents the position on said axis
		*/
		glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		
		/**
		* \brief Our scale vector
		*
		* Each axis represents the scale on said axis
		*/
		glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

		/**
		* \breif Our rotation vector in eular angles
		*
		* Each axis represents the degrees of rotation on said axis
		*/
		glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	public:
		virtual void init() override;

		virtual void tick(float dt) override;
		virtual void draw(ce::graphics::Renderer3D* renderer) override;

		virtual std::string getType() override;

		/**
		* \brief Get the position, rotation and scale as a matrix for drawing etc.
		*/
		glm::mat4 getAsModelMatrix();

		void pitch(float degrees);
		void yaw(float degrees);
		void roll(float degrees);

		void rotate(float degX, float degY, float degZ);
		void rotate(glm::vec3 degrees);

		void setRotation(float degX, float degY, float degZ);
		void setRotation(glm::vec3 degrees);

		glm::vec3 getRotation() { return m_rotation; }

		void move(float x, float y, float z);
		void move(glm::vec3 xyz);

		void setPosition(float x, float y, float z);
		void setPosition(glm::vec3 xyz);

		glm::vec3 getPosition() { return m_position; }

		void scale(float x, float y, float z);
		void scale(glm::vec3 xyz);

		void setScale(float x, float y, float z);
		void setScale(glm::vec3 xyz);

		glm::vec3 getScale() { return m_scale; }

	};

}}