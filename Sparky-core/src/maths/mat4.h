#pragma once

#include "maths.h"
#include "vec4.h"
#include <iostream>
#include <iomanip>

namespace sparky{

	namespace maths{

		struct Mat4{

			union{
				float elements[4 * 4];
				struct {Vec4 columns[4];}; 
			};

			Mat4();
			Mat4(float diagonal);

			static Mat4 identity();
			static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static Mat4 perspective(float fov, float aspectRatio, float near, float far);

			static Mat4 translation(const Vec3& vector);
			static Mat4 rotation(float angle, const Vec3& axisVector);
			static Mat4 scale(const Vec3& vector);

			Mat4& multiply(const Mat4& other, const char* major);
			Vec3 multiply(const Vec3& other) const;
			Vec4 multiply(const Vec4& other) const;

			friend Mat4 operator*(Mat4 left, const Mat4& right);
			friend Vec3 operator*(const Mat4& left, const Vec3& right);
			friend Vec4 operator*(const Mat4& left, const Vec4& right);

			Mat4& operator*=(const Mat4& other);
			friend std::ostream& operator<<(std::ostream& stream, const Mat4& matrix); 
			
		};

		float toRadians(float degrees);

	}

}