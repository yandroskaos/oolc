#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <symbols/symbols.h>
#include <ast/node.h>

namespace AST
{
	class Builder
	{
		static Node* ms_program;

		static Symbols::Access ms_currentAccess;
		static bool ms_currentStaticness;

		static void CopyCollection  (Collection& _member, Collection* _list);
		static void CopyStringList  (vector<string>& _member, Collection* _list);
		static void CopyArgumentList(vector<string>& _types, vector<string>& _names, Collection* _arguments);

	public:
		static Node* GetProgram();

		static void SetAccess(Symbols::Access _access);
		static void SetStatic(bool _isStatic);

		static Collection* BuildCollection(Node* _node);
		static Collection* AddCollection  (Collection* _container, Node* _node);
		static Collection* MergeCollection(Collection* _c1, Collection* _c2);

		static Node* Program(Collection* _classes);
		
		static Node* Interface  (string* _name, Collection* _members);
		static Node* Prototype  (Node* _declaration, Collection* _arguments);
		
		static Node*       Class      (string* _name, string* _parent, Collection* _interfaces, Collection* _members);
		static Collection* Attributes (string* _type, Collection* _attributes);
		static Node*       Constructor(string* _name, Collection* _arguments, Node* _body);
		static Node*       Method     (Node* _declaration, Collection* _arguments, Node* _body);

		static Node* MakeBlock      (Collection* _statements);
		static Node* ForceBlock     (Node* _statement);
		static Node* Variables      (string* _type, Collection* _variables);

		static Node* CreateSlot         (Collection* _slotMembers);
		static Node* NewExpression      (string* _type, Collection* _callList);
		static Node* NewArrayExpression (string* _type, Collection* _bracketList);
		static Node* IdentifierSlot     (string* _identifier, bool _methodInvocation, Collection* _arguments, Collection* _indexes);
	};
};

#endif
