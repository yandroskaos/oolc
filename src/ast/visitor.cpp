#include <ast/visitor.h>

#include <ast/structure_nodes.h>
#include <ast/statement_nodes.h>
#include <ast/expression_nodes.h>

using namespace AST;

//
// Program Structure Nodes
//
void Visitor::Visit(ProgramNode*           _node)
{
    COLLECTION_ACCEPT(_node->classes);
}
void Visitor::Visit(InterfaceNode*         _node)
{
    COLLECTION_ACCEPT(_node->members);
}
void Visitor::Visit(PrototypeNode*         _node) {}
void Visitor::Visit(ClassNode*             _node)
{
    COLLECTION_ACCEPT(_node->members);
}
void Visitor::Visit(AttributeNode*         _node)
{
    if(_node->init)
        _node->init->Accept(this);
}
void Visitor::Visit(MethodNode*            _node)
{
    _node->body->Accept(this);
}

//
// Statement Nodes
//
void Visitor::Visit(BlockStatementNode*           _node)
{
    COLLECTION_ACCEPT(_node->statements);
}
void Visitor::Visit(EmptyStatementNode*           _node) {}
void Visitor::Visit(WriteStatementNode*           _node)
{
    _node->expr->Accept(this);
}
void Visitor::Visit(ReadStatementNode*            _node)
{
    _node->slot->Accept(this);
}
void Visitor::Visit(IfElseStatementNode*          _node)
{
    _node->condition->Accept(this);
    _node->ifBody->Accept(this);
    if(_node->elseBody)
        _node->elseBody->Accept(this);
}
void Visitor::Visit(WhileStatementNode*           _node)
{
    _node->body->Accept(this);
}
void Visitor::Visit(ForStatementNode*             _node)
{
    if(_node->init)
        _node->init->Accept(this);
    if(_node->condition)
        _node->condition->Accept(this);
    if(_node->update)    
        _node->update->Accept(this);
    _node->body->Accept(this);
}
void Visitor::Visit(ReturnStatementNode*          _node)
{
    if(_node->expr)
        _node->expr->Accept(this);
}
void Visitor::Visit(VariableNode*                 _node)
{
    if(_node->init)
        _node->init->Accept(this);
}
void Visitor::Visit(VariableBlockNode*            _node)
{
    COLLECTION_ACCEPT(_node->variables);
}
void Visitor::Visit(ExpressionStatementNode*      _node)
{
    _node->expr->Accept(this);
}

//
// Expresion Nodes
//
void Visitor::Visit(NullExprNode*            _node) {}
void Visitor::Visit(BoolCteExprNode*         _node) {}
void Visitor::Visit(CharCteExprNode*         _node) {}
void Visitor::Visit(IntCteExprNode*          _node) {}
void Visitor::Visit(RealCteExprNode*         _node) {}
void Visitor::Visit(StringCteExprNode*       _node) {}
void Visitor::Visit(GreaterExprNode*         _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(LesserExprNode*          _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(EqualExprNode*           _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(NotEqualExprNode*        _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(AndExprNode*             _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(OrExprNode*              _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(PlusExprNode*            _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(MinusExprNode*           _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(MulExprNode*             _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(DivExprNode*             _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(AssignmentExprNode*      _node)
{
    _node->leftExpr->Accept(this);
    _node->rightExpr->Accept(this);
}
void Visitor::Visit(NotExprNode*             _node)
{
    _node->expr->Accept(this);
}
void Visitor::Visit(MinusUnaryExprNode*      _node)
{
    _node->expr->Accept(this);
}
void Visitor::Visit(CastExprNode*            _node)
{
    _node->expr->Accept(this);
}
void Visitor::Visit(NewExprNode*             _node)
{
    COLLECTION_ACCEPT(_node->exprs);
}
void Visitor::Visit(NewArrayExprNode*        _node)
{
    COLLECTION_ACCEPT(_node->exprs);
}
void Visitor::Visit(SlotNode*                _node)
{
    COLLECTION_ACCEPT(_node->exprs);
}
void Visitor::Visit(ThisSlotNode*            _node) {}
void Visitor::Visit(IdentifierSlotNode*      _node)
{
    COLLECTION_ACCEPT(_node->arguments);
    COLLECTION_ACCEPT(_node->indexes);
}
