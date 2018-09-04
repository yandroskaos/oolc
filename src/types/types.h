#ifndef __TYPES_H__
#define __TYPES_H__

#include <map>
#include <vector>
#include <string>
using namespace std;

namespace Symbols
{
	class Attribute;
	class Method;
}

namespace Types
{
	class Type
	{
	public:
		virtual string Name() const = 0;

		bool operator==(const Type& _type) const;
		bool operator!=(const Type& _type) const;
	
		virtual bool ImplicitCastTo  (const Type& _to)   const;
		virtual bool ExplicitCastTo  (const Type& _to)   const;

		//
		// Predicates
		//
		static bool IsNull     (Type const& _type);
		static bool IsVoid     (Type const& _type);
		static bool IsBool     (Type const& _type);
		static bool IsChar     (Type const& _type);
		static bool IsInt      (Type const& _type);
		static bool IsReal     (Type const& _type);
		static bool IsString   (Type const& _type);
		static bool IsArray    (Type const& _type);
		static bool IsMethod   (Type const& _type);
		static bool IsClass    (Type const& _type);
		static bool IsInterface(Type const& _type);
				
		static bool IsNumeric  (Type const& _type);
		static bool IsPrimitive(Type const& _type);
		static bool IsAggregate(Type const& _type);
	};

	class Interface;

	class Class : public Type
	{
	public:
		template <typename T>
		using Members    = map<string, T>;
		template <typename T>
		using Overloads  = vector<T>;
		using Methods    = Members<Overloads<Symbols::Method*>>;
		using Interfaces = map<string, Interface*>;
		using Attributes = Members<Symbols::Attribute*>;

	private:
		string     name;
		Class*     parent;
		Interfaces interfaces;
		Attributes attributes;
		Methods    methods;

	public:
		Class(string _name);

		string Name()     const override;

		bool ImplicitCastTo  (const Type& _to)   const override;
		bool ExplicitCastTo  (const Type& _to)   const override;

		Class* GetParent() const;
		void   SetParent(Class* _parent);
		bool   InheritsFrom(string _name) const;

		void       AddInterface(Interface* _interface);
		Interface* GetInterface(string _name) const;

		void                AddAttribute(Symbols::Attribute* _attribute);
		Symbols::Attribute* GetAttribute(string _attribute) const;

		void                     AddMethod(Symbols::Method* _method);
		vector<Symbols::Method*> GetMethod(string _method) const;

		Methods GetAllMethods() const;
	};

	class Interface : public Class
	{
	public:
		Interface(string _name);

		bool ImplicitCastTo  (const Type& _to) const override;
		bool ExplicitCastTo  (const Type& _to) const override;
	};

	class Null : public Type
	{
	public:
		string Name() const override;

		bool ImplicitCastTo  (const Type& _to) const override;
		bool ExplicitCastTo  (const Type& _to) const override;
	};

	class Void : public Type
	{
	public:
		string Name() const override;
	};

	class Bool : public Type
	{
	public:
		string Name() const override;

		bool ImplicitCastTo  (const Type& _to) const override;
		bool ExplicitCastTo  (const Type& _to) const override;
    };

	class Char : public Type
	{
	public:
		string Name() const override;

		bool ImplicitCastTo  (const Type& _to) const override;
		bool ExplicitCastTo  (const Type& _to) const override;
	};

	class Int : public Type
	{
	public:
		string Name() const override;

		bool ImplicitCastTo  (const Type& _to) const override;
		bool ExplicitCastTo  (const Type& _to) const override;
    };

	class Real : public Type
	{
	public:
		string Name() const override;

		bool ImplicitCastTo  (const Type& _to) const override;
		bool ExplicitCastTo  (const Type& _to) const override;
    };

	class String : public Type
	{
	public:
		string Name() const override;
	};

	class Array : public Type
	{
		Type*  baseType;
		int    dimensions;
	public:
		Array(const string& _name);

		string Name() const override;
		
		Type* GetBaseType()   const;
		int   GetDimensions() const;

		static int    GetDimensions(const string& _name);
		static Type*  GetBaseType  (const string& _name);
		static bool   IsArrayType  (const string& _name);
		static string Brackets     (int _dimensions);
	};

	class Method : public Type
	{
		Type*         returnType;
		vector<Type*> arguments;

	public:
		Method(string _returnType, vector<string> const& _arguments);

		string Name() const override;

		bool ImplicitCastTo  (const Type& _to) const override;
		bool ExplicitCastTo  (const Type& _to) const override;

		Type*         GetReturnType() const;
		vector<Type*> GetArguments()  const;

		bool CompareSignature(Method* _method);
	};


	class Table
	{
		map<string, Type*> table;
	public:
		Table();
		~Table();

		void Add(Type* _type);
		Type* operator[](const string& _name);
	};

	extern Table table;
}

#endif
