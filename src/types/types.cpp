#include "types.h"
#include <symbols/symbols.h>
#include <utils/conversion.h>

using namespace Types;

bool Type::IsNull     (Type const& _type) {return _type == *Types::table["null"];  }
bool Type::IsVoid     (Type const& _type) {return _type == *Types::table["void"];  }
bool Type::IsBool     (Type const& _type) {return _type == *Types::table["bool"];  }
bool Type::IsChar     (Type const& _type) {return _type == *Types::table["char"];  }
bool Type::IsInt      (Type const& _type) {return _type == *Types::table["int"];   }
bool Type::IsReal     (Type const& _type) {return _type == *Types::table["real"];  }
bool Type::IsString   (Type const& _type) {return _type == *Types::table["string"];}

bool Type::IsArray    (Type const& _type) {return dynamic_cast<Array const*>(&_type)     != nullptr;}
bool Type::IsMethod   (Type const& _type) {return dynamic_cast<Method const*>(&_type)    != nullptr;}
bool Type::IsClass    (Type const& _type) {return dynamic_cast<Class const*>(&_type)     != nullptr;}
bool Type::IsInterface(Type const& _type) {return dynamic_cast<Interface const*>(&_type) != nullptr;}
		
bool Type::IsNumeric  (Type const& _type) {return IsChar(_type)  || IsInt(_type) || IsReal(_type);}
bool Type::IsPrimitive(Type const& _type) {return IsBool(_type)  || IsNumeric(_type);}
bool Type::IsAggregate(Type const& _type) {return IsClass(_type) || IsInterface(_type);}

//
// Type
//
bool Type::operator==(const Type& _type) const
{
	return _type.Name() == Name();
}

bool Type::operator!=(const Type& _type) const
{
	return _type.Name() != Name();
}

bool Type::ImplicitCastTo(const Type& _to) const
{
	return false;
}

bool Type::ExplicitCastTo(const Type& _to) const
{
	return false;
}

//
// Class
//
Class::Class(string _name)
    : name(_name)
	, parent(nullptr)
{
}

string Class::Name() const
{
	return name;
}

bool Class::ImplicitCastTo(const Type& _to) const
{
	if(Type::IsInterface(_to))
	{
		Class const* p = this;
		while(p)
		{
			if(p->GetInterface(_to.Name()))
            	return true;
		
        	p = p->GetParent();
		}
	}

	if(Type::IsClass(_to))
	{
		Class const* p = this;
		while(p)
		{
			if(*p == _to)
            	return true;
		
        	p = p->GetParent();
		}
	}

	return false;
}

bool Class::ExplicitCastTo(const Type& _to) const
{
	return _to.ImplicitCastTo(*this);
}

Class* Class::GetParent() const
{
	return parent;
}

void Class::SetParent(Class* _parent)
{
	parent = _parent;
}

bool Class::InheritsFrom(string _name) const
{
	Class* p = GetParent();
	while(p)
	{
		if(p->Name() == _name)
            return true;
		
        p = p->GetParent();
	}

	return false;
}

void Class::AddInterface(Interface* _interface)
{
    interfaces.insert(Interfaces::value_type(_interface->Name(), _interface));
}

Interface* Class::GetInterface(string _name) const
{
	Interfaces::const_iterator i = interfaces.find(_name);
	
    if(i != interfaces.end()) 
		return i->second;
	
    return nullptr;
}

void Class::AddAttribute(Symbols::Attribute* _attribute)
{
	attributes.insert(Attributes::value_type(_attribute->Name(), _attribute));
}

Symbols::Attribute* Class::GetAttribute(string _attribute) const
{
	Attributes::const_iterator i = attributes.find(_attribute);
	
    if(i != attributes.end())
        return i->second;
	
    return nullptr;
}

void Class::AddMethod(Symbols::Method* _method)
{
	Methods::iterator i = methods.find(_method->Name());
	
    if(i != methods.end())
	{
		i->second.push_back(_method);
	}
	else
	{
		methods.insert(Methods::value_type(_method->Name(), vector<Symbols::Method*>()));
		methods[_method->Name()].push_back(_method);
	}
}

vector<Symbols::Method*> Class::GetMethod(string _method) const
{
	Methods::const_iterator i = methods.find(_method);
	
    if(i != methods.end())
        return i->second;
	
    return vector<Symbols::Method*>();
}

Class::Methods Class::GetAllMethods() const
{
	return methods;
}

//
// Interface
//
Interface::Interface(string _name)
	: Class(_name)
{
}

bool Interface::ImplicitCastTo(const Type& _to) const
{
	return false;
}

bool Interface::ExplicitCastTo(const Type& _to) const
{
	return _to.ImplicitCastTo(*this);
}


//
// Null
//
string Null::Name() const
{
	return "null";
}

bool Null::ImplicitCastTo(const Type& _to) const
{
    return Type::IsAggregate(_to) || Type::IsString(_to);
}

bool Null::ExplicitCastTo(const Type& _to) const
{
    return ImplicitCastTo(_to);
}

//
// Void
//
string Void::Name() const
{
    return "void";
}

//
// Bool
//
string Bool::Name() const
{
	return "bool";
}

bool Bool::ImplicitCastTo(const Type& _to) const
{
    return false;
}

bool Bool::ExplicitCastTo(const Type& _to) const 
{
    return false;
}

//
// Char
//
string Char::Name() const
{
	return "char";
}

bool Char::ImplicitCastTo(const Type& _to) const
{
	return Type::IsInt(_to) || Type::IsReal(_to);
}

bool Char::ExplicitCastTo(const Type& _to) const
{
	return ImplicitCastTo(_to);
}

//
// Int
//
string Int::Name() const
{
	return "int";
}

bool Int::ImplicitCastTo(const Type& _to) const
{
	return Type::IsReal(_to);
}

bool Int::ExplicitCastTo(const Type& _to) const
{
	return ImplicitCastTo(_to) || Type::IsChar(_to);
}

//
// Real
//
string Real::Name() const
{
	return "real";
}

bool Real::ImplicitCastTo(const Type& _to) const
{
	return false;
}

bool Real::ExplicitCastTo(const Type& _to) const
{
	return Type::IsInt(_to) || Type::IsChar(_to);
}

//
// String
//
string String::Name() const
{
	return "string";
}

//
// Array
//
Array::Array(const string& _name) 
    : baseType(Array::GetBaseType(_name))
	, dimensions(Array::GetDimensions(_name))
{
}

string Array::Name() const
{
	return to_string(dimensions) + baseType->Name();
}

Type* Array::GetBaseType() const
{
	return baseType;
}

int Array::GetDimensions() const
{
	return dimensions;
}

Type* Array::GetBaseType(const string& _name)
{
	return Types::table[_name.substr(_name.find_first_not_of("0123456789"))];
}

int Array::GetDimensions(const string& _name)
{
    return to_int(_name.substr(0, _name.find_first_not_of("0123456789")));
}

bool Array::IsArrayType(const string& _name)
{
    return _name.find_first_of("0123456789") == 0;
}

string Array::Brackets(int _dimensions)
{
	string result = "";
	for(auto i = 0; i < _dimensions; ++i)
	{
		result += "[]";
	}
	return result;
}

//
// Method
//
Method::Method(string _returnType, vector<string> const& _arguments)
{
	returnType = Types::table[_returnType];
	for(auto argument : _arguments)
		arguments.push_back(Types::table[argument]);
}

string Method::Name() const
{
	string name = "";

	name += returnType->Name();
	name += "(";
	if(arguments.size())
	{
		for(int i = 0; i < arguments.size() - 1; i++)
			name += arguments[i]->Name() + ",";
		name += arguments[arguments.size() - 1]->Name();
	}
	name += ")";

	return name;
}

bool Method::ImplicitCastTo(const Type& _to) const
{
	if(!Type::IsMethod(_to))
		return false;

	Method const& m = dynamic_cast<Method const&>(_to);
	
    if(arguments.size() != m.arguments.size())
		return false;

	for(int i = 0; i < arguments.size(); i++)
	{
		if(*arguments[i] != *m.arguments[i] && !arguments[i]->ImplicitCastTo(*m.arguments[i]))
			return false;
	}

	return true;
}

bool Method::ExplicitCastTo(const Type& _to) const
{
	return ImplicitCastTo(_to);
}

Type* Method::GetReturnType() const
{
	return returnType;
}

vector<Type*> Method::GetArguments() const
{
	return arguments;
}

bool Method::CompareSignature(Method* _method)
{
	string thisName = this->Name();
	string thisSignature = thisName.substr(thisName.find_first_of('('));

	string otherName = _method->Name();
	string otherSignature = otherName.substr(otherName.find_first_of('('));

	return thisSignature == otherSignature;
}

//
// Table
//
Table::Table()
{
    //
	// Add known types
    //
	Add(new Null());
	Add(new Void());
	Add(new Bool());
	Add(new Char());
	Add(new Int());
	Add(new Real());
	Add(new String());
}

Table::~Table() = default;

void Table::Add(Type* _type)
{
	if((*this)[_type->Name()] == nullptr)
		table.insert(pair<string, Type*>(_type->Name(), _type));
}

Type* Table::operator[](const string& _name)
{
    //
	// Find type
    //
	auto i = table.find(_name);
	if(i != table.end())
		return i->second;

    //
    // If it is an array type, insert and return
    //
	if(Array::IsArrayType(_name))
	{
		Array* arrayType = new Array(_name);
		table.insert(pair<string, Type*>(_name, arrayType));
		return arrayType;
	}

    //
    // Otherwise
    //
	return nullptr;
}

Types::Table Types::table;
