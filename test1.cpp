#include <iostream>
#include <string>


#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Rewrite/Frontend/Rewriters.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "LLVM/Support/raw_ostream.h"
#include "clang/AST/Stmt.h"
#include "clang/AST/Expr.h"
#include "clang/AST/RecursiveASTVisitor.h"

using namespace std;
using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;

static llvm::cl::OptionCategory MatcherSampleCategory("Matcher Sample");

int number = 0;

/*typedef struct node_t
{
	char* className;  
	char* value;
	int num = 0;
	int nown = 0;
	struct node_t* parent;
	struct node_t* next = NULL; 
} Node;*/
typedef struct node_t {
	char* className;
	char* value;
	char* type;
	int childnum;
	int tempnum;
	struct node_t* parent;
	struct node_t** child;
	struct node_t* next;
}Node;
Node *root;
Node *now;
Node *nowroot;
Node root1[100];
int num = 0;
int num1 = 0;
typedef struct node_f {
	int i;
	int j;
	int flag;
}Sign;
int sign = 0;
int num2 = 0;
int tempnum = 0;
int signnum = 0;
int flag = 0;


//Node* root1;
//Node* now1;
/*int min(int a, int b, int c) {
	if (a <= b && a <= c) {
		return 0;
	}
	if (b <= a && b <= c) {
		return 1;
	}
	if (c <= a && c <= b) {
		return 2;
	}
}*/

bool charIsSame(char* stra, char* strb) {
	int a = strlen(stra);
	int b = strlen(strb);
	int i;
	if (a != b) {
		return false;
	}
	for (i = 0; i < a; i++) {
		if (stra[i] != strb[i]) {
			return false;
		}
	}
	return true;
}
bool isSame(Node a, Node b) {
	//cout << "a:" << a.className << " b:" << b.className << endl;
	//cout << "isSame:" << (a.className[0] == b.className[0]) << endl;
	
	if (charIsSame(a.className,b.className) && charIsSame(a.value,b.value)){
		return true;
	}
	return false;
}

/*void compute_distance() {

	int **temp = (int**)malloc(sizeof(int*) * (num + 1));
	int **flag = (int**)malloc(sizeof(int*) * (num + 1));
	for (int i = 0; i < num + 1; i++) {
		temp[i] = (int*)malloc(sizeof(int) * (num1 + 1));
		memset(temp[i], 0, sizeof(int) * (num1 + 1));
		flag[i] = (int*)malloc(sizeof(int) * (num1 + 1));
		memset(flag[i], 0, sizeof(int) * (num1 + 1));
	}
	
	int i, j;

	for (i = 1; i <= num; i++) {
		temp[i][0] = i;
		flag[i][0] = 3;
	}

	for (j = 1; j <= num1; j++) {
		temp[0][j] = j;
		flag[0][j] = 2;
	}

	temp[0][0] = 0;

	for (i = 1; i <= num; i++) {
		for (j = 1; j <= num1; j++) {
			if (isSame(root[i-1],root1[j-1])){
				temp[i][j] = temp[i - 1][j - 1];
				flag[i][j] = 0;
				
			}
			else {
				
				if (temp[i - 1][j - 1] <= temp[i - 1][j] && temp[i - 1][j - 1] <= temp[i][j - 1]) {	
					temp[i][j] = temp[i - 1][j - 1] + 1;
					flag[i][j] = 1;  //修改
				}
				else if (temp[i][j - 1] <= temp[i - 1][j - 1] && temp[i][j - 1] <= temp[i - 1][j]) {	
					temp[i][j] = temp[i][j - 1] + 1;
					flag[i][j] = 2; //删除
				}
				else {
					
					temp[i][j] = temp[i - 1][j] + 1;
					flag[i][j] = 3; //增加
				}
				//temp[i][j] = min(temp[i - 1][j], temp[i][j - 1], temp[i - 1][j - 1]) + 1;
			}
			//cout << root[i-1].className << " " << root1[j-1].className <<" " << flag[i][j] << endl;
		}
	}
	cout << "long instance1:" << temp[num][num1] << endl;
	i = num;
	j = num1;
	while (temp[i][j] != 0) {
		if (flag[i][j] == 0) {
			i--;
			j--;
		}
		else {
			int resulti=i-1, resultj=j-1;
			if (i == 0) {
				resulti = 0;
			}
			if (j == 0) {
				resultj = 0;
			}
			sign[num2].i = resulti;
			sign[num2].j = resultj;
			cout << root[resulti].className << " " << root1[resultj].className << " " << endl;
			cout << root[resulti].value << " " << root1[resultj].value << " " << endl;
			if (flag[i][j] == 1) {
				sign[num2].flag = 1;
				num2++;
				i--;
				j--;
			}
			else if (flag[i][j] == 2) {
				sign[num2].flag = 2;
				num2++;
				j--;
			}
			else if (flag[i][j] == 3) {
				sign[num2].flag = 3;
				num2++;
				i--;
			}
			
		}
	}
	for (i = 0; i < num2; i++) {
		cout << sign[i].i << " " << sign[i].j << " " << sign[i].flag << endl;
 	}
	signnum = num2-1;
}*/

void printNode(Node* node) {
	cout << "输出节点" << endl;
	if (node) {

		int i;
		
		for (i = 0; i < node->childnum; i++) {
			cout << "childnum:"<<node->childnum << endl;
			printNode(node->child[i]);
		}
	}
}
void printTree(Node* root) {
		//int i;
		/*cout << num << num1 << endl;
		if (num == 0 && num1 == 0) {
			cout << "trees are null" << endl;
		}
		else if (num != 0 && num1 == 0) {
			for (i = 0; i < num; i++) {
				cout << "className:" << root[i].className << endl;
				cout << "value:" << root[i].value << endl;
			}
		}
		else if (num1 != 0) {
			for (i = 0; i < num1; i++) {
				cout << "className:" << root1[i].className << endl;
				cout << "value:" << root1[i].value << endl;
			}
		}*/
		Node* temp = (Node*)malloc(sizeof(Node));
		if (!root) {
			//cout << root->className << endl;
			cout << "tree is null" << endl;
			return;
		}
		temp = root->next;
		cout << "我要输出啦！！" << endl;
		//int i = 0;
		while (temp) {
			
			cout << "value:" << temp->value << endl;
			
			
			cout << "className:" << temp->className << endl;
			printNode(temp);
			temp = temp->next;
			//cout << "temp:" << (temp==NULL) << endl;
		}
		/*cout << root->value << endl;
		for (i = 0; i < root->num; i++) {
			printTree(root->children[i]);
		}*/

	}


class Visitor : public RecursiveASTVisitor < Visitor > {
public:
	Visitor(Rewriter &Rewrite):Rewrite(Rewrite) {};

	/*virtual bool VisitStmt(Stmt *stmt) {
		if (stmt){
			//cout << "Visit Stmt !" << endl;
		    //cout << "Visit :" << stmt->getStmtClassName() <<  endl;		
			
		}
			
		return true;
	}*/
	
	virtual bool VisitCompoundStmt(CompoundStmt *copStmt) {
		if (copStmt) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, copStmt->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "null");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = copStmt->child_begin(); it != copStmt->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << "cop:" <<now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}
	virtual bool VisitImplicitCastExpr(ImplicitCastExpr *implicitExpr) {
		if (implicitExpr) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, implicitExpr->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "null");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = implicitExpr->child_begin(); it != implicitExpr->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}
	
	virtual bool VisitArraySubscriptExpr(ArraySubscriptExpr *arrayExpr) {
		if (arrayExpr) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, arrayExpr->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "null");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = arrayExpr->child_begin(); it != arrayExpr->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}
	
	virtual bool VisitInitListExpr(InitListExpr *initExpr) {
		if (initExpr) {
			sign = 0;
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, initExpr->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "null");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = initExpr->child_begin(); it != initExpr->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << "initlist:" <<now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}
	virtual bool VisitForStmt(ForStmt *forStmt) {
		if (forStmt) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, forStmt->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "for");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = forStmt->child_begin(); it != forStmt->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}
	
	virtual bool VisitUnaryOperator(UnaryOperator *uOpStmt) {
		if (uOpStmt) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, uOpStmt->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, uOpStmt->getOpcodeStr(uOpStmt->getOpcode()).data());
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = uOpStmt->child_begin(); it != uOpStmt->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}
	virtual bool VisitCallExpr(CallExpr *callExpr) {
		if (callExpr) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, callExpr->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "null");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = callExpr->child_begin(); it != callExpr->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}

	virtual bool VisitIntegerLiteral(IntegerLiteral *intStmt) {
		if (intStmt) {
			if (sign == 1) {
				sign = 0;
				return true;
			}
			//cout << "Visit IntegerLiteral !" << endl;
			//llvm::errs() << intStmt->getValue() << "\n";
			/*llvm::APInt value = intStmt->getValue();
			value.print(llvm::outs(), false);
			cout << "\n";*/
			
			Node *temp = (Node*)malloc(sizeof(Node));
			if (temp == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}
			temp->className = (char*)malloc(20 * sizeof(char));
			strcpy(temp->className, intStmt->getStmtClassName());
			
			temp->value = (char*)malloc(10 * sizeof(char));
			strcpy(temp->value, intStmt->getValue().toString(10,true).data());
			//now->next = temp;
			temp->next = NULL;
			//now = now->next;*/
			if (number == 1) {
				temp->parent = now;
				//llvm::errs() << now->tempnum << "\n";
				now->child[now->tempnum] = temp;
				//now->next = temp;
				//llvm::errs() << "000" << "\n";
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
					//llvm::errs() << varDecl->value << "unchild" << "\n";
				while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
					//llvm::errs() << now->value << "childmiao" << "\n";
					now = now->parent;
				}
				llvm::errs() << "int:" << now->className << " " << temp->className <<" " << temp->value << "\n";
				llvm::errs() << now->tempnum << " " << now->childnum<< "\n";
				llvm::errs() << "\n";
			}
			else if (number == 2){
				root1[num1].className = (char*)malloc(20 * sizeof(char));
				strcpy(root1[num1].className, intStmt->getStmtClassName());
				root1[num1].value = (char*)malloc(10 * sizeof(char));
				strcpy(root1[num1].value, intStmt->getValue().toString(10, true).data());
				num1++;
				/*temp->parent = now1;
				now1->next = temp;
				now1 = now1->next;*/
			}
			else if (number == 3 && signnum >= 0) {
				/*cout << "tempnum:" << tempnum << endl;
				if (tempnum == sign[signnum].j) {
					
					if (sign[signnum].flag == 1) {
						Rewrite.ReplaceText(intStmt->getExprLoc(), root[sign[signnum].i].value);
					}
					signnum--;
				}
				tempnum++;*/
			}

		}

		return true;
	}

	virtual bool VisitDeclRefExpr(DeclRefExpr *declExpr) {
		if (declExpr) {
			
			Node *temp = (Node*)malloc(sizeof(Node));
			if (temp == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}
			temp->className = (char*)malloc(20 * sizeof(char));
			strcpy(temp->className, declExpr->getStmtClassName());
			//cout << temp->className << endl;
			//temp->parent = now;
			temp->value = (char*)malloc(10 * sizeof(char));
			strcpy(temp->value, declExpr->getFoundDecl()->getNameAsString().data());

			//now->next = temp;
			temp->next = NULL;
			//now = now->next;
			if (number == 1) {
				temp->parent = now;

				now->child[now->tempnum] = temp;

				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
					//llvm::errs() << now->value << "childmiao" << "\n";
					now = now->parent;
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
			else if (number == 2){
				root1[num1].className = (char*)malloc(20 * sizeof(char));
				strcpy(root1[num1].className, declExpr ->getStmtClassName());
				root1[num1].value = (char*)malloc(10 * sizeof(char));
				strcpy(root1[num1].value, declExpr->getFoundDecl()->getNameAsString().data());
				num1++;
				
			}
			else if (number == 3 && signnum >= 0) {
				
				/*while (tempnum == sign[signnum].j) {
					cout << "tempnum:" << tempnum << endl;
					if (sign[signnum].flag == 1) {
						Rewrite.ReplaceText(declExpr->getExprLoc(), root[sign[signnum].i].value);
					}
					if (sign[signnum].flag == 3) {
						Rewrite.InsertTextAfterToken(declExpr->getExprLoc(), root[sign[signnum].i].value);
					}
					if (sign[signnum].flag == 2) {
						operator delete(declExpr);
						//Rewrite.RemoveText(declExpr->getExprLoc(), declExpr->getFoundDecl()->getNameAsString().size());
					}
					signnum--;
				}*/
				tempnum++;
			}
		}
		return true;
	}

	virtual bool VisitReturnStmt(ReturnStmt *reStmt) {
		if (reStmt) {
			//cout << "Visit ReturnStmt!" << endl;
			//cout << reStmt->getRetValue() << endl;
			//Rewrite.ReplaceText(reStmt->getReturnLoc(),"true");
			//一定有
			Node *temp = (Node*)malloc(sizeof(Node));
			if (temp == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}
			temp->className = (char*)malloc(20 * sizeof(char));
			strcpy(temp->className, reStmt->getStmtClassName());
			//cout << temp->className << endl;
			//temp->parent = now;
			temp->value = (char*)malloc(10 * sizeof(char));
			//reStmt->getRetValue();
			strcpy(temp->value,"return");

			//now->next = temp;
			temp->next = NULL;
			//now = now->next;
			if (number == 1) {
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = reStmt->child_begin(); it != reStmt->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
				
			}
			else if (number == 2){
				root1[num1].className = (char*)malloc(20 * sizeof(char));
				strcpy(root1[num1].className, reStmt->getStmtClassName());
				root1[num1].value = (char*)malloc(10 * sizeof(char));
				strcpy(root1[num1].value, " ");
				num1++;
				/*temp->parent = now1;
				now1->next = temp;
				now1 = now1->next;*/
			}
			else if (number == 3 && signnum >= 0) {
				/*cout << "tempnum:" << tempnum << endl;
				if (tempnum == sign[signnum].j) {
					
					if (sign[signnum].flag == 1) {
						Rewrite.ReplaceText(reStmt->getReturnLoc(), root[sign[signnum].i].value);
					}
					if (sign[signnum].flag == 3) {
						Rewrite.InsertTextAfterToken(reStmt->getReturnLoc(), " ");
						Rewrite.InsertTextAfterToken(reStmt->getReturnLoc(), root[sign[signnum].i].value);
					}
					signnum--;
				}*/
				tempnum++;
			}
		}
		return true;
	}
	virtual bool VisitIfStmt(IfStmt *ifStmt) {
		if (ifStmt) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, ifStmt->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "if");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 0;
				for (Stmt::child_iterator it = ifStmt->child_begin(); it != ifStmt->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					temp->tempnum = 0;
					now = now->child[now->tempnum - 1];
				}
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
		}
		return true;
	}
	virtual bool VisitDeclStmt(DeclStmt *declStmt) {
		if (declStmt) {
			if (number == 1) {
				Node *temp = (Node*)malloc(sizeof(Node));
				if (temp == NULL) {
					llvm::errs() << "Error" << "\n";
					exit(EXIT_FAILURE);
				}
				temp->className = (char*)malloc(20 * sizeof(char));
				strcpy(temp->className, declStmt->getStmtClassName());
				temp->value = (char*)malloc(10 * sizeof(char));
				strcpy(temp->value, "null");
				temp->next = NULL;
				temp->parent = now;
				now->child[now->tempnum] = temp;
				now->tempnum++;
				temp->tempnum = 0;
				temp->childnum = 1;
				/*for (Stmt::child_iterator it = declStmt->child_begin(); it != declStmt->child_end(); ++it) {
					temp->childnum++;
				}
				if (temp->childnum == 0) {
					temp->child = NULL;
					while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
						now = now->parent;
					}
				}
				else {*/
					temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
					//temp->childnum = 1;
					now = now->child[now->tempnum - 1];
				//}
				llvm::errs() << "decl:" <<now->className << " " << temp->className << "\n";
				llvm::errs() << now->tempnum << "\n";
				llvm::errs() << "\n";
			}
			else if (number == 2) {
				root1[num1].className = (char*)malloc(20 * sizeof(char));
				strcpy(root1[num1].className, declStmt->getStmtClassName());
				root1[num1].value = (char*)malloc(10 * sizeof(char));
				strcpy(root1[num1].value, "int");
				num1++;
				/*temp->parent = now1;
				now1->next = temp;
				now1 = now1->next;*/
			}
			else if (number == 3 && signnum >= 0) {

				/*if (tempnum == sign[signnum].j) {
					cout << "tempnum:" << tempnum << endl;
					if (sign[signnum].flag == 1) {
						Rewrite.ReplaceText(declStmt->getStartLoc(), root[sign[signnum].i].value);
					}
					signnum--;
				}*/
				tempnum++;
			}
		}
		return true;
	}
	virtual bool VisitBinaryOperator(BinaryOperator *opStmt) {
		if (opStmt) {
			//cout << "Visit BinaryOperator!" << endl;
			//llvm::errs() << opStmt->getOpcodeStr() << "\n";
			//Rewrite.ReplaceText(opStmt->getOperatorLoc(), opStmt->getOpcodeStr().size(), "=");
			//Rewrite.RemoveText(opStmt->getOperatorLoc(), opStmt->getOpcodeStr().size());
			//Rewrite.InsertTextBefore(opStmt->getOperatorLoc(), "/*");
			//Rewrite.InsertTextAfterToken(opStmt->getOperatorLoc(), "*///=");
			Node *temp = (Node*)malloc(sizeof(Node));
			if (temp == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}
			temp->className = (char*)malloc(20 * sizeof(char));
			strcpy(temp->className, opStmt->getStmtClassName());
			temp->value = (char*)malloc(10 * sizeof(char));
			strcpy(temp->value, opStmt->getOpcodeStr().data());

			//now->next = temp;
			temp->next = NULL;
			//now = now->next;*/
			//一定有
		    if (number == 1) {
				
					temp->parent = now;
					now->child[now->tempnum] = temp;
					now->tempnum++;
					temp->tempnum = 0;
					temp->childnum = 0;
					for (Stmt::child_iterator it = opStmt->child_begin(); it != opStmt->child_end(); ++it) {
						temp->childnum++;
					}
					if (temp->childnum == 0) {
						temp->child = NULL;
						while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
							now = now->parent;
						}
					}
					else {
						temp->child = (Node**)malloc(temp->childnum * sizeof(Node*));
						//temp->childnum = 1;
						temp->tempnum = 0;
						now = now->child[now->tempnum - 1];
					}
					llvm::errs() << now->className << " " << temp->className << "\n";
					llvm::errs() << now->tempnum << "\n";
					llvm::errs() << "\n";
				
			}
			else if(number == 2){
				root1[num1].className = (char*)malloc(20 * sizeof(char));
				strcpy(root1[num1].className, opStmt->getStmtClassName());
				root1[num1].value = (char*)malloc(10 * sizeof(char));
				strcpy(root1[num1].value, opStmt->getOpcodeStr().data());
				num1++;
				/*temp->parent = now1;
				now1->next = temp;
				now1 = now1->next;*/
			}
			else if (number == 3 && signnum >= 0) {
				
				/*if (tempnum == sign[signnum].j) {
					//
					cout << "tempnum:" << tempnum << endl;
					if (sign[signnum].flag == 1) {
						Rewrite.ReplaceText(opStmt->getOperatorLoc(), root[sign[signnum].i].value);
					}
					if (sign[signnum].flag == 2) {
						
						Rewrite.RemoveText(opStmt->getOperatorLoc(), opStmt->getOpcodeStr().size());
					}
					signnum--;
				}*/
				tempnum++;
			}
		}
		return true;
	}
	virtual bool VisitExpr(Expr *expr) {
		//if (expr)
			//cout << "Visit Expr !" << endl;
			//cout << "Visit :" <<  endl;
			
			
		return true;
	}

	virtual bool VisitDecl(Decl *decl) {
		if (decl) {
			//cout << "Visit Decl !" << endl;
			//cout << decl->getDeclKindName() << endl;
			//cout << "Here is tree" << now->className << endl;
			/*Node *temp = (Node*)malloc(sizeof(Node));
			if (temp == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}

			temp->className = decl->getDeclKindName();
			temp->parent = now;
			now->next = temp;
			temp->next = NULL;
			now = now->next;*/
			//root->next = temp;
			//llvm::errs() << "end" << temp->className << "\n";
			//llvm::errs() << root->num << "\n";
			

			//root->num++;
			//now->next = temp;
		
			//decl->getBody()
			if (decl->getBody()) {
				
				//cout << "true" << endl;
			}
			//operator delete(decl, decl->getASTContext(), 1);
		}
			
		
		return true;
	}
	virtual bool VisitFunctionDecl(FunctionDecl *funDecl) {
		if (funDecl) {
			llvm::errs() << "参数个数："<<funDecl->param_size() << "\n";
			now->type = (char*)malloc(20 * sizeof(char));
			strcpy(now->type, funDecl->getType().getAsString().data());
			if (funDecl->hasBody()) {
				now->childnum = funDecl->param_size() + 1;
				now->child = (Node**)malloc(now->childnum * sizeof(Node*));
				llvm::errs() << "fun:" << now->tempnum << "\n";
			}

		}
		return true;
	}
	virtual bool VisitVarDecl(VarDecl *varDecl) {
		if (varDecl) {
			//llvm::errs() << "miao";
			Node* temp =  now->child[now->tempnum - 1];
			//llvm::errs() << "wang";
			//llvm::errs() << "miao" <<temp->className;
			temp->type = (char*)malloc(20 * sizeof(char));
			
			//llvm::errs() << "miao";
			strcpy(temp->type, varDecl->getType().getAsString().data());
			int i;
			for (i = 0; i < 19; i++) {
				llvm::errs() << temp->type[i];
				if (temp->type[i] == '[' && temp->value[i + 1] != ']') {
					sign = 1;
					break;
				}
			}
			//llvm::errs() << temp->value << "\n";
				//llvm::errs() << varDecl->getStorageClassSpecifierString(varDecl->getStorageClass())<<"\n";
				/*varDecl->getDefinition()->dump();
				varDecl->getCanonicalDecl()->dump();
				llvm::errs() << varDecl->getDeclName() << "\n";
				llvm::errs() << varDecl->getKind() << "\n";
				//llvm::errs() << varDecl->hasDefinitionAttr() << "\n";
				llvm::errs() << varDecl->hasDefiningAttr() << "\n";
				llvm::errs() << varDecl->evaluateValue() << "\n";
				varDecl->getType()->dump();
				QualType type = varDecl->getType();
				llvm::errs() << type.getAsString() << "\n";*/
				//varDecl->getDescribedTemplate()->dump();
			
			
			if (varDecl->hasInit()){
				//llvm::errs() << now->value << "child" << "\n";			
				temp->child = (Node**)malloc(sizeof(Node*));
				temp->childnum = 1;
				temp->tempnum = 0;
				now = now->child[now->tempnum - 1];
				//llvm::errs() << "var:" <<temp->value << "\n";

			}
			else {
				//llvm::errs() << varDecl->value << "unchild" << "\n";
				while (!(now->childnum == -1 || now->childnum > now->tempnum)) {
					//llvm::errs() << now->value << "childmiao" << "\n";
					now = now->parent;
				}
			}
			llvm::errs() << "var:" <<now->className << "\n";
			llvm::errs() << now->tempnum << "\n";
			llvm::errs() << "\n";
		}
		return true;
	}
	virtual bool VisitNamedDecl(NamedDecl *decl) {
		if (decl)
		{
		
			//llvm::errs() << decl->getDeclName() << "\n";
			//Rewrite.ReplaceText(decl->getLocation(),"miao");
			//cout << "Visit NamedDecl :" << decl->getQualifiedNameAsString() << endl;
			/*Node *temp = (Node*)malloc(sizeof(Node));
			if (temp == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}
			temp->className = (char*)malloc(10*sizeof(char));
			strcpy(temp->className,decl->getDeclKindName());
			//temp->parent = now;
			
			temp->value = (char*)malloc(10 * sizeof(char));
			strcpy(temp->value, decl->getQualifiedNameAsString().data());
			//now->next = temp;
			temp->next = NULL;
			//now = now->next;*/
			if (number == 1) {
					Node *temp = (Node*)malloc(sizeof(Node));
					
					temp->className = (char*)malloc(20 * sizeof(char));
					strcpy(temp->className, decl->getDeclKindName());
					temp->value = (char*)malloc(10 * sizeof(char));
					strcpy(temp->value, decl->getQualifiedNameAsString().data());
					temp->next = NULL;
				if (flag == 0) {
					temp->parent = now;
					//llvm::errs() << now->tempnum << "\n";
					now->child[now->tempnum] = temp;
					//now->next = temp;
					//llvm::errs() << "000" << "\n";
					now->tempnum++;
					temp->tempnum = 0;
					temp->childnum = 0;
					//decl->getBody()->dump();
					
					llvm::errs() << "decl1:" << now->tempnum << "\n";
					
				}
				else if (flag == 1) {
					flag = 0;
					temp->parent = nowroot;
					temp->childnum = -1;
					temp->tempnum = 0;
					//temp->next = NULL;
					nowroot->next = temp;
					nowroot = nowroot->next;
					now = nowroot;
					llvm::errs() << "decl2:" << now->tempnum << "\n";
					llvm::errs() << "change" << "\n";
				}
				//free(temp);
				llvm::errs() << now->className << " " << temp->className << "\n";
				llvm::errs() << now->childnum << "\n";
				llvm::errs() << "\n";
			}
			else if (number == 2){
				root1[num1].className = (char*)malloc(20 * sizeof(char));
				strcpy(root1[num1].className, decl->getDeclKindName());
				root1[num1].value = (char*)malloc(10 * sizeof(char));
				strcpy(root1[num1].value, decl->getQualifiedNameAsString().data());
				num1++;
				/*temp->parent = now1;
				now1->next = temp;
				now1 = now1->next;*/
			}
			else if (number == 3 && signnum >= 0) {
				
				/*if (tempnum == sign[signnum].j) {
					cout << "tempnum:" <<tempnum << endl;
					if (sign[signnum].flag == 1) {
						Rewrite.ReplaceText(decl->getLocation(), root[sign[signnum].i].value);
					}
					if (sign[signnum].flag == 2) {
						operator delete(decl, decl->getASTContext(), 0);
						
						Rewrite.RemoveText(decl->getLocation(), decl->getNameAsString().size());
						
					}
					signnum--;
				}*/
				tempnum++;
			}

		}
		return true;
	}
	virtual bool VisitNamespaceDecl(NamespaceDecl *decl) {
		if (decl) {
			//cout << "Visit NamespaceDecl:" << decl->getQualifiedNameAsString() << endl;
		}
		return true;
	}
private:
		Rewriter &Rewrite;
};

class MyASTConsumer : public ASTConsumer {
public:
	MyASTConsumer(Rewriter &R):visitor(R){}
	/*virtual void HandleTranslationUnit(clang::ASTContext &Context) {
		// Traversing the translation unit decl via a RecursiveASTVisitor
		// will visit all nodes in the AST.
		visitor.TraverseDecl(Context.getTranslationUnitDecl());
		Context.getTranslationUnitDecl()->dump();
	}*/
	/*TranslationUnitDecl *dc = Unit->getASTContext().getTranslationUnitDecl();
	if (dc) {
		for (DeclContext::decl_iterator dit = dc->decls_begin(); \
			dit != dc->decls_end(); dit++) {
			std::cout << dit->getDeclKindName() << std::endl;
		}*/
	bool HandleTopLevelDecl(DeclGroupRef DR) override {
		flag = 1;
		(*DR.begin())->dump();

		//for (DeclGroupRef::iterator it = DR.begin(); it != DR.end(); it++) {
			//DeclGroupRef::iterator newit = it;
			//(*newit)->getASTContext();
			/*if ((*it)==*(it)){
				cout << "false" << endl;
			}*/
			//llvm::errs() << "begin" << "\n";
			/*Node *temp = (Node*)malloc(sizeof(Node));
			if (temp == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}*/
			
			//temp->className = (*it)->getDeclKindName();
		    //llvm::errs() << "end" << temp->className << "\n";
			//llvm::errs() << root->num << "\n";
			//root->children[root->num] = temp;
			/*root->value = "root";
			root->className = "className";
			root->next = NULL;*/
			//cout << root->next << (root->next == NULL) << endl;
			//temp->parent = root;
			
			//root->num++;
			//now = root;

			
			visitor.TraverseDecl(*(DR.begin()));
			if (number == 2) {
				printTree(root1);
				//compute_distance();
				number++;
				visitor.TraverseDecl(*(DR.begin()));
			}
			//(*(DR.begin()))->dump(); //打印AST nodes*/
			//cout << "end:" << (((DR.begin())) == DR.begin()) << endl;
			/*if (((DR.begin())) == DR.end() && number == 2) {
				compute_distance();
			}*/
			
		
		
		cout << "Here!!" << number << endl;
		return true;
	}
	
private:
	Visitor visitor;
};

class MyFrontendAction : public ASTFrontendAction {
public:
	MyFrontendAction() {}
	void EndSourceFileAction() override {
		TheRewriter.getEditBuffer(TheRewriter.getSourceMgr().getMainFileID())
			.write(llvm::outs());
		
		//printTree(root);
		//if (number == 2) {
			//printTree(root1);
			//compute_distance();
			//number++;
			/*llvm::make_unique<MyASTConsumer>(TheRewriter);
			TheRewriter.getEditBuffer(TheRewriter.getSourceMgr().getMainFileID())
				.write(llvm::outs());*/
			//
		//}
		
	}
	unique_ptr<ASTConsumer>CreateASTConsumer(CompilerInstance &CI, StringRef file)override {
		number ++;
		cout << number << endl;
		if (number == 1) {
			root = (Node*)malloc(sizeof(Node));
			if (root == NULL) {
				llvm::errs() << "Error" << "\n";
			}
			root->tempnum = 0;
			root->childnum = -1;
			root->next = NULL;
			root->className = (char*)malloc(20 * sizeof(char));
			strcpy(root->className, "null");
			now = (Node*)malloc(sizeof(Node));
			nowroot = (Node*)malloc(sizeof(Node));
			nowroot = root;
			now = root;
		}
		/*if (number == 1) {
			root = (Node*)malloc(20*sizeof(Node));
			if (root == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}
			root->next = NULL;
			now = (Node*)malloc(sizeof(Node));
			now = root;
		}
		else {
			root1 = (Node*)malloc(sizeof(Node));
			if (root1 == NULL) {
				llvm::errs() << "Error" << "\n";
				exit(EXIT_FAILURE);
			}
			root1->next = NULL;
			now1 = (Node*)malloc(sizeof(Node));
			now1 = root;
		}*/
		TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
		llvm::errs() << "Create ASTConsumer for " << file << "\n";
		return llvm::make_unique<MyASTConsumer>(TheRewriter);
	}
private:
	Rewriter TheRewriter;
};

int main(int argc , const char **argv) {
	CommonOptionsParser op(argc, argv ,MatcherSampleCategory);

	ClangTool Tool(op.getCompilations(),op.getSourcePathList());

	return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());


	return 0;

}
