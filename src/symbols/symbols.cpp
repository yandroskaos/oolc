#include "symbols.h"
#include <cassert>

using namespace Symbols;

Symbol::Symbol(string _name, Types::Type* _type)
    : name(_name)
	, type(_type)
{
}

string Symbol::Name() const
{
	return name;
}

Types::Type* Symbol::Type() const
{
	return type;
}

Variable::Variable(string _name, Types::Type* _type, bool _isArgument)
    : Symbol(_name, _type)
	, address(0)
	, isArgument(_isArgument) 
{
}

bool Variable::IsArgument() const
{
	return isArgument;
}

int Variable::GetAddress() const
{
	return address;
}

void Variable::SetAddress(int _address)
{
	address = _address;
}

Member::Member(string _name, Types::Type* _type, Types::Class* _parent, bool _isStatic, Access _access)
    : Symbol(_name, _type)
	, isStatic(_isStatic)
	, access(_access)
	, parent(_parent)
{
}

bool Member::IsStatic() const
{
	return isStatic;
}

Access Member::GetAccess() const
{
	return access;
}

Types::Class* Member::GetParent() const
{
	return parent;
}

Attribute::Attribute(string _name, Types::Type* _type, Types::Class* _parent, bool _isStatic, Access _access)
    : Member(_name, _type, _parent, _isStatic, _access)
{
}

Method::Method(string _name, vector<string> _arguments, Types::Method* _type, Types::Class* _parent, bool _isStatic, Access _access)
    : Member(_name, _type, _parent, _isStatic, _access)
{
	int address = _isStatic ? 0 : 1;
	
	vector<Types::Type*> argTypes = _type->GetArguments();

	for(size_t i = 0; i < argTypes.size(); i++)
	{
		string n = i < _arguments.size() ? _arguments[i] : "a" + to_string(i);
		Variable* argument = new Variable(n, argTypes[i], true);
		argument->SetAddress(address++);
		arguments.push_back(argument);
	}
}

vector<Variable*> Method::GetArguments() const
{
	return arguments;
}

Table::Table()
{
}

Table::~Table()
{
    //
	// Cleaning
    //
}

void Table::Add(Symbol* _symbol)
{
	assert(!table.empty());

	table.at(table.size() - 1).insert(pair<string, Symbol*>(_symbol->Name(), _symbol));
}

Symbol* Table::operator[](const string& _name)
{
	for(auto i = table.rbegin(); i != table.rend(); i++)
	{
		auto j = i->find(_name);
		if(j != i->end())
			return j->second;
	}

	return nullptr;
}

Symbol* Table::SearchLastContextOnly(const string& _name)
{
	auto i = table.rbegin();
	if(i == table.rend())
		return nullptr;

	auto j = i->find(_name);
	
    if(j != i->end())
			return j->second;

	return nullptr;
}

void Table::Set()
{
	table.push_back(map<string, Symbol*>());
}

void Table::Reset()
{
	table.pop_back();
}

Symbols::Table Symbols::table;
