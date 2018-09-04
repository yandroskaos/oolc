#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>
using namespace std;

#include <ast/visitor.h>
#include <types/types.h>

#define CAN_BE_VISITED \
    void Accept(Visitor* _visitor) override

#define ACCEPT_VISITOR(X)             \
    void X::Accept(Visitor* _visitor) \
    {                                 \
        _visitor->Visit(this);        \
    }

#define COLLECTION_ACCEPT(C) \
    for(auto n : C)          \
    {                        \
        n->Accept(this);     \
    }

#define LINK(P, S) \
	if(S) { (S)->SetParent(P); }

#define COLLECTION_LINK(P, C) \
    for(auto S : C)           \
    {                         \
        S->SetParent(P);      \
    }

namespace AST
{
	class Node
	{
		Node*        parent;
		int          line;
	    Types::Type* type;
	public:
        void  SetParent(Node* _newParent);
		Node* GetParent();
		
        void SetLine(int _line);
		int  GetLine();

       	void         SetType(Types::Type* _type);
		Types::Type* GetType();

		Node();
		virtual ~Node();
		
        virtual void Accept(Visitor* _visitor);
	};

	using Collection = vector<Node*>;
}

#endif
