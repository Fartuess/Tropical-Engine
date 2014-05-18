//#pragma once
//
//#include"Shaders_header.h"
//#include<map>
//#include<typeinfo>
//
//using namespace std;
//
//class Material
//{
//	enum paramtype
//	{
//		vec,
//		vec2,
//		vec3,
//		vec4,
//		mat3,
//		mat4,
//		unknownType
//	};
//
//	struct ShaderParameter
//	{
//		//string type;
//		paramtype type;
//		void* parameter;
//	};
//
//private:
//	map<string, ShaderParameter> VSparams;
//	map<string, ShaderParameter> PSparams;
//
//	paramtype stringToType(string type);
//public:
//	Shader* shader;
//
//	Material(Shader* shader);//, void* VSparams, void* PSparams)
//	void addVSparam(string name ,void* parameter);
//	void addPSparam(string name ,void* parameter);
//};