#include "mat4.h"

namespace sparky{

	namespace maths{

		Mat4::Mat4(){

			for(int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;

		}

		Mat4::Mat4(float diagonal){

			for(int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;

			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;

		}

		Mat4 Mat4::identity(){

			return Mat4(1.0f);

		}

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far){

			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);
			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;

		}

		Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far){

			Mat4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;

		}

		Mat4 Mat4::translation(const Vec3& vector){

			Mat4 result(1.0f);

			result.elements[0 + 3 * 4] = vector.x;
			result.elements[1 + 3 * 4] = vector.y;
			result.elements[2 + 3 * 4] = vector.z;

			return result;

		}

		Mat4 Mat4::scale(const Vec3& vector){

			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = vector.x;
			result.elements[1 + 1 * 4] = vector.y;
			result.elements[2 + 2 * 4] = vector.z;

			return result;

		}

		Mat4 Mat4::rotation(float angle, const Vec3& axisVector){

			Mat4 result(1.0f);

			float r = toRadians(angle);
			float s = sin(r);
			float c = cos(r);
			float omc = 1.0f - c;

			float x = axisVector.x;
			float y = axisVector.y;
			float z = axisVector.z;

			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = x * y * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;

			return result;

		}

		Mat4& Mat4::multiply(const Mat4& other, const char* major){

			/*Mat4 auxMat;

			for(int yO = 0; yO < 4; yO++){

				for(int y = 0; y < 4; y++){

					int sum = 0;

					for(int x = 0; x < 4; x++)
						sum += elements[x + yO * 4] * other.elements[y + x * 4];

					if(major == "row")
						auxMat.elements[y + yO * 4] = sum;
					else if(major == "column")
						auxMat.elements[yO + y * 4] = sum;
					else{
						std::cerr << "warning: error on matrix multiplication!" << std::endl;
						return *this;
					}

				}
			}

			*this = auxMat;
			return *this;*/

			float data[16];
			for (int row = 0; row < 4; row++){
				for (int col = 0; col < 4; col++){
					float sum = 0.0f;
					for (int e = 0; e < 4; e++){
						sum += elements[col + e * 4] * other.elements[e + row * 4];
					}
					data[col + row * 4] = sum;
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix){

			stream << std::endl <<"|" << std::setprecision(3) << matrix.elements[0] << "\t" << std::setprecision(3) << matrix.elements[1] << "\t" << std::setprecision(3) << matrix.elements[2] << "\t" << std::setprecision(3) << matrix.elements[3] << "|" << std::endl 
				<< "|" << std::setprecision(3) << matrix.elements[4] << "\t" << std::setprecision(3) << matrix.elements[5] << "\t" << std::setprecision(3) << matrix.elements[6] << "\t" << std::setprecision(3) << matrix.elements[7] << "|" << std::endl 
				<< "|" << std::setprecision(3) << matrix.elements[8] << "\t" << std::setprecision(3) << matrix.elements[9] << "\t" << std::setprecision(3) << matrix.elements[10] << "\t" << std::setprecision(3) << matrix.elements[11] << "|" << std::endl 
				<< "|" << std::setprecision(3) << matrix.elements[12] << "\t" << std::setprecision(3) << matrix.elements[13] << "\t" << std::setprecision(3) << matrix.elements[14] << "\t" << std::setprecision(3) << matrix.elements[15] << "|" << std::endl;

			return stream;

		}

		Mat4 operator*(Mat4 left, const Mat4& right){

			return left.multiply(right, "row");
		
		}

		Mat4& Mat4::operator*=(const Mat4& other){

			return multiply(other, "row");

		}

		Vec3 operator*(const Mat4& left, const Vec3& right){

			return left.multiply(right);

		}

		Vec4 operator*(const Mat4& left, const Vec4& right){

			return left.multiply(right);

		}

		float toRadians(float degrees){
			return (float)(degrees * (M_PI/180.0f));
		}

		Vec3 Mat4::multiply(const Vec3& other) const{

			return Vec3(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
				);

		}

		Vec4 Mat4::multiply(const Vec4& other) const{

			return Vec4(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
				);

		}

	}

}