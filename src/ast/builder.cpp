#include <ast/builder.h>
#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>
#include <ast/parser_nodes.h>
#include <compiler.h>

#include <iostream>

using namespace Parsing;
using namespace AST;

Node*           Builder::ms_program           = 0;
Symbols::Access Builder::ms_currentAccess     = Symbols::Access::Public;
bool            Builder::ms_currentStaticness = false;

void Builder::CopyCollection(Collection& _member, Collection* _list)
{
	_member.clear();

	if(_list)
	{
        for(auto i : *_list)
		{
			_member.push_back(i);
		}

		delete _list;
	}
}

void Builder::CopyStringList(vector<string>& _member, Collection* _list)
{
	_member.clear();
	
    if(_list)
	{
        for(auto i : *_list)
		{
			Parsing::StringNode* n = dynamic_cast<Parsing::StringNode*>(i);
			_member.push_back(*n->info);

			delete n->info;
			delete n;
		}

		delete _list;
	}
}


void Builder::CopyArgumentList(vector<string>& _types, vector<string>& _names, Collection* _arguments)
{
	_types.clear();
	_names.clear();

	if(_arguments)
	{
		for(auto i : *_arguments)
		{
			Parsing::DeclarationNode* argument = dynamic_cast<Parsing::DeclarationNode*>(i);

			_types.push_back(*argument->type);
			_names.push_back(*argument->name);

			delete argument->type;
			delete argument->name;
			delete argument;
		}

		delete _arguments;
	}
}

Node* Builder::GetProgram()
{
	return ms_program;
}

void Builder::SetAccess(Symbols::Access _access)
{
	ms_currentAccess = _access;
}

void Builder::SetStatic(bool _isStatic)
{
	ms_currentStaticness = _isStatic;
}

Collection* Builder::BuildCollection(Node* _node)
{
	Collection* container = new Collection();
	return AddCollection(container, _node);
}

Collection* Builder::AddCollection(Collection* _container, Node* _node)
{
	_container->push_back(_node);
	return _container;
}

Collection* Builder::MergeCollection(Collection* _c1, Collection* _c2)
{
	for (auto i : *_c2)
	{
		_c1->push_back(i);
	}
	delete _c2;
	return _c1;
}


Node* Builder::Program(Collection* _classes)
{
	ProgramNode* n = new ProgramNode;

	n->name = Compiler::Module();

	CopyCollection(n->classes, _classes);
	COLLECTION_LINK(n, n->classes);

	ms_program = n;

	return n;
}

Node* Builder::Interface(string* _name, Collection* _members)
{
	InterfaceNode* n = new InterfaceNode;
	
    n->name = std::move(*_name);
	n->members = std::move(*_members);

	COLLECTION_LINK(n, n->members);

	delete _name;
	delete _members;

	return n;
}

Node* Builder::Prototype(Node* _declaration, Collection* _arguments)
{
	Parsing::DeclarationNode* decl = dynamic_cast<Parsing::DeclarationNode*>(_declaration);

	PrototypeNode* n = new PrototypeNode();

	n->returnType = std::move(*decl->type);
	n->name       = std::move(*decl->name);

	delete decl->type;
	delete decl->name;
	delete decl;

	CopyStringList(n->argumentTypes, _arguments);

	return n;
}

Node* Builder::Class(string* _name, string* _parent, Collection* _interfaces, Collection* _members)
{
	ClassNode* n = new ClassNode();

	n->name   = std::move(*_name);
	if(_parent)
	{
		n->parent = std::move(*_parent);
		delete _parent;
	}
	else
	{
		n->parent = "";
	}

	CopyStringList(n->interfaces, _interfaces);

	if(_members)
	{
		n->members = std::move(*_members);
		delete _members;
	}
	
	COLLECTION_LINK(n, n->members);

	delete _name;

	return n;
}

Collection* Builder::Attributes(string* _type, Collection* _attributes)
{
	Collection* c = new Collection;

	for(auto i : *_attributes)
	{
		Parsing::InitNode* n = dynamic_cast<Parsing::InitNode*>(i);

		AttributeNode* m = new AttributeNode;

		m->isStatic = ms_currentStaticness;
        m->access   = ms_currentAccess;
        m->type     = *_type;
		m->name     = std::move(*n->name);
		m->init     = n->expr;
		m->SetLine(n->GetLine());

		LINK(m, m->init);

		c->push_back(m);  

		delete n->name;
		delete n;
	}

	delete _type;

	return c;
}

Node* Builder::Constructor(string* _name, Collection* _arguments, Node* _body)
{
	MethodNode* n = new MethodNode();

	n->isStatic   = ms_currentStaticness;
    n->access     = ms_currentAccess;
	n->returnType = "void";
	n->name       = std::move(*_name);
	CopyArgumentList(n->argumentTypes, n->argumentNames, _arguments);
	n->body       = _body;

	LINK(n, n->body);

	delete _name;

	return n;
}

Node* Builder::Method(Node* _declaration, Collection* _arguments, Node* _body)
{
	Parsing::DeclarationNode* decl = dynamic_cast<Parsing::DeclarationNode*>(_declaration);

	MethodNode* n = new MethodNode();

	n->isStatic   = ms_currentStaticness;
    n->access     = ms_currentAccess;
	n->returnType = std::move(*decl->type);
	n->name       = std::move(*decl->name);
	n->body       = _body;

	LINK(n, n->body);

	delete decl->type;
	delete decl->name;
	delete decl;

	CopyArgumentList(n->argumentTypes, n->argumentNames, _arguments);

	return n;
}

Node* Builder::MakeBlock(Collection* _statements)
{
	BlockStatementNode* n = new BlockStatementNode;
	CopyCollection(n->statements, _statements);
	COLLECTION_LINK(n, n->statements);
	return n;
}

Node* Builder::ForceBlock(Node* _statement)
{
	if(dynamic_cast<BlockStatementNode*>(_statement))
		return _statement;

	BlockStatementNode* n = new BlockStatementNode();
	n->statements.push_back(_statement);
	COLLECTION_LINK(n, n->statements);
	return n;
}

Node* Builder::Variables(string* _type, Collection* _variables)
{
	VariableBlockNode* n = new VariableBlockNode();

	for(auto i : *_variables)
	{
		Parsing::InitNode* j = dynamic_cast<Parsing::InitNode*>(i);

		VariableNode* v = new VariableNode;
		v->type = *_type;
		v->name = *j->name;
		v->init = j->expr;
		v->SetLine(n->GetLine());
		LINK(v, v->init);

		n->variables.push_back(v);

		delete j->name;
		delete j;
	}
	delete _variables;
	delete _type;

	COLLECTION_LINK(n, n->variables);

	return n;
}

Node* AST::Builder::CreateSlot(Collection* _slotMembers)
{
	AST::SlotNode* slot = new AST::SlotNode();
	slot->isLeftValue = false;
	CopyCollection(slot->exprs, _slotMembers);
	COLLECTION_LINK(slot, slot->exprs);
	return slot;
}

Node* AST::Builder::NewExpression(string* _type, Collection* _callList)
{
	AST::NewExprNode* n = new AST::NewExprNode();

	n->type = std::move(*_type);
	CopyCollection(n->exprs, _callList);
	COLLECTION_LINK(n, n->exprs);
	delete _type;
	
	return n;
}

Node* AST::Builder::NewArrayExpression(string* _type, Collection* _bracketList)
{
	AST::NewArrayExprNode* n = new AST::NewArrayExprNode;

	n->type = std::move(*_type);
	CopyCollection(n->exprs, _bracketList);
	COLLECTION_LINK(n, n->exprs);
	delete _type;
	
	return n;
}

Node* AST::Builder::IdentifierSlot(string* _identifier, bool _methodInvocation, Collection* _arguments, Collection* _indexes)
{
	AST::IdentifierSlotNode* n = new AST::IdentifierSlotNode();

	n->identifier = std::move(*_identifier);
	n->methodInvocation = _methodInvocation;
	CopyCollection(n->arguments, _arguments);
	CopyCollection(n->indexes, _indexes);
	COLLECTION_LINK(n, n->arguments);
	COLLECTION_LINK(n, n->indexes);
	delete _identifier;
	
	return n;
}
