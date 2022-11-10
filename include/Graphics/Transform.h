#pragma once

#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace ce { namespace graphics {

	class Transform
	{
	protected:
		/**
		* \brief Our position vector
		*
		* Each axis represents the position on said axis
		*/
		glm::vec3 m_position;

		/**
		* \brief Our scale vector
		*
		* Each axis represents the scale on said axis
		*/
		glm::vec3 m_scale;

		/**
		* \breif Our rotation vector in eular angles
		*
		* Each axis represents the degrees of rotation on said axis
		*/
		glm::vec3 m_rotation;

	public:
		glm::mat4 getAsMatrix();

		void pitch(float degrees);
		void yaw(float degrees);
		void roll(float degrees);

		void rotate(float x, float y, float z);
		void rotate(glm::vec3 degrees);

		void setRotation(float x, float y, float z);
		void setRotation(glm::vec3 degrees);

		glm::vec3 getRotation() { return m_rotation; }
		glm::quat getOrientation();

		void translate(float x, float y, float z); /**< Translate relative to orientation */
		void translate(glm::vec3 xyz); /**< Translate relative to orientation */

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