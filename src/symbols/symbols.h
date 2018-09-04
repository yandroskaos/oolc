#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

#include <vector>
#include <map>
#include <string>
using namespace std;

#include <types/types.h>

namespace Symbols
{
	class Symbol
	{
	private:
		string       name;
		Types::Type* type;
	
	protected:
		Symbol(string _name, Types::Type* _type);

	public:

		virtual string       Name()   const;
		virtual Types::Type* Type()   const;
	};

	class Variable : public Symbol
	{
		int  address;
		bool isArgument;

	public:
		Variable(string _name, Types::Type* _type, bool _isArgument);

		bool IsArgument() const;

		int  GetAddress() const;
		void SetAddress(int _address);
	};

    enum class Access
    {
        Private,
        Protected,
        Public
    };

	class Member : public Symbol
	{
		bool          isStatic;
		Access        access;
		Types::Class* parent;

	protected:
		Member(string _name, Types::Type* _type, Types::Class* _parent, bool _isStatic, Access _access);
	
	public:
		bool          IsStatic()  const;
		Access        GetAccess() const;
		Types::Class* GetParent() const;
	};

	class Attribute : public Member
	{
	public:
		Attribute(string _name, Types::Type* _type, Types::Class* _parent, bool _isStatic, Access _access);
	};

	class Method : public Member
	{
		vector<Variable*> arguments;

	public:
		Method(string _name, vector<string> _arguments, Types::Method* _type, Types::Class* _parent, bool _isStatic, Access _access);

		vector<Variable*> GetArguments() const;
	};

	class Table
	{
		vector<map<string, Symbol*> > table;

	public:
		Table();
		~Table();

		void Add(Symbol* _symbol);
		Symbol* operator[](const string& _name);
		Symbol* SearchLastContextOnly(const string& _name);

		void Set();
		void Reset();
	};

	extern Table table;

};

#endif
