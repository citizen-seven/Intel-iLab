#include "Tree.h"

CNode::CNode()
{
    left = NULL;
    right = NULL;
    num = 0;
    sign = 0;
    var = 0;
    func = "";
}

CNode::~CNode()
{
    if (left != NULL)  delete left;
    if (right != NULL)  delete right;
    left = NULL;
    right = NULL;
}
/*
 CNode* CNode::TieLeft(CNode* MyLeft)
 {
 left = MyLeft;
 return this;
 }
 
 CNode* CNode::TieRight(CNode* MyRight)
 {
 right = MyRight;
 return this;
 }
 
 void CNode::PutNum(c_type tp, double nm)
 {
 type = tp;
 num = nm;
 }
 
 void CNode::PutSign(c_type tp, char sg)
 {
 type = tp;
 sign = sg;
 }
 
 void CNode::PutVar(c_type tp, char vr)
 {
 type = tp;
 var = vr;    
 }
 */
void CNode::GoDump(int tab)
{
    if(this != NULL)
    {
        int i = 0;
        left -> GoDump(tab + 1);
        for(i = 0; i < tab - 1; i++)
        { 
            cout <<"    ";
        }
        //cout << "---->";
        switch(type)
        {
            case (0):{ cout << num; break; } //выводит большие числа в виде X.XXXXXe+XX
            case (1):{ cout << sign; break; }
            case (2):{ cout << var; break; }
            case (3):{ cout << func; break; }
        }
        cout << endl;
        right -> GoDump(tab + 1);
    }
}

CNode::CNode(double val)
{
    left = NULL;
    right = NULL;
    type = Number;
    num = val;
    sign = 0;
    var = 0;
    func = "";
}

CNode::CNode(char t_var)
{
    left = NULL;
    right = NULL;
    type = Varible;
    num = 0;
    sign = 0;
    var = t_var;
    func = "";
}

CNode::CNode(char t_data, CNode* t_left, CNode* t_right)
{
    left = t_left;
    right = t_right;
    type = Sign;
    num = 0;
    sign = t_data;
    var = '\0';
    func = "";
}

CNode::CNode(string t_str, CNode* t_left)
{
    left = t_left;
    right = NULL;
    type = Function;
    num = 0;
    sign = 0;
    var = 0;
    func = t_str;
}

int print_node(ofstream& latex, CNode* tree) {
    if (tree->GetType() != Function) {
        if (tree->GoLeft() != NULL) { 
            if ((tree->GoLeft()->GetType() == Number)||(tree->GoLeft()->GetType() == Varible)) {
                print_node(latex, tree->GoLeft());
            } else {
                latex << "\\left(";
                print_node(latex, tree->GoLeft());
                latex << "\\right)";
            }
        }
    } else {
        print_data(latex, tree);
        latex << "\\left(";
        std::cout << tree->GetFun() << "(";
        print_node(latex, tree->GoLeft());
        latex << "\\right)";
        std::cout << ")";
    }
    if (tree->GetType() != Function) print_data(latex, tree);
    if (tree->GoRight() != NULL) {
        if ((tree->GoRight()->GetType() == Number)||(tree->GoRight()->GetType() == Varible)) {
            print_node(latex, tree->GoRight());
        } else {
            latex << "\\left(";
            print_node(latex, tree->GoRight());
            latex << "\\right)";
        }
    }
    return 0;
}

void print_data (ofstream& latex, CNode* tree) {
    if (tree->GetType() == Number) {
        latex << tree->GetNum();
        std::cout << tree->GetNum();
    } else if (tree->GetType() == Sign) {
        latex << tree->GetSign();
        std::cout << tree->GetSign();
    } else if (tree->GetType() == Varible) {
        std::cout << tree->GetVar();
        latex << tree->GetVar();
    } else if (tree->GetType() == Function) {
        latex << tree->GetFun();
    }
}

/*int print_equation(CNode* tree) {
    std::ofstream latex ("equation.tex");
    latex << "\\documentclass[a4paper, 12pt, twoside]{article}\n\
    \\usepackage[T2A,T1]{fontenc}\n\
    \\usepackage[utf8]{inputenc}\n\
    \\usepackage[russian,english]{babel}\n\
    \\usepackage{amsmath}\n\
    \\begin{document}\n\
    \\begin{otherlanguage*}{russian}\n\
    Вывод выражения, поехали!" << std::endl;
    latex << "\n" << "$$";
    print_node(latex, tree);
    latex << "$$" << std::endl;
    latex << "\\end{otherlanguage*}\n\
    \\end{document}" << std::endl;
    latex.close();
    return 0;
}*/

int print_tree(CNode* tree) {
    std::ofstream output ("tree.tex");
    output << "\\documentclass[a4paper, 12pt]{article}\n\
    \\usepackage[T2A,T1]{fontenc}\n\
    \\usepackage[utf8]{inputenc}\n\
    \\usepackage[russian,english]{babel}\n\
    \\usepackage{amsmath}\n\
    \\usepackage{qtree}\n\
    \\usepackage{graphicx}\n\
    \\usepackage{tikz-qtree}\n\
    \\begin{document}\n\
    \\begin{otherlanguage*}{russian}\n\
    Печать дерева, поехали!" << std::endl;
    output << "\n Your expression is:\n" << "$$";
    print_node(output, tree);
    output << "$$" << std::endl;
    output << std::endl;
    
    output << "\n Your tree is:\n\
    \\begin{center}\n\
    \\resizebox{\\linewidth}{!}{\\begin{tikzpicture}[sibling distance = \\baselineskip]\n\
    \\tikzset{every tree node/.style={align=center}}\n\
    \\tikzset{level 1+/.style={level distance=3\\baselineskip}}\n\
    \\Large \\Tree";
    print_graph(output, tree);
    output << std::endl;
    output << "\\end{tikzpicture}}\n\
    \\end{center}\n\
    \\end{otherlanguage*}\n\
    \\end{document}" << std::endl;
    output.close();
    return 0;
}

int print_graph(ofstream& output, CNode* tree) {
    if (tree->GoLeft() != NULL) { 
        output << " [. \\node[circle,draw=red] {";
        print_data(output, tree);
        output << "}; ";
        print_graph(output, tree->GoLeft());
    }
    if ((tree->GetType() == Number)||(tree->GetType() == Varible)) {
        output << " [. \\node[circle,draw=green]{";
        print_data(output, tree);
        output << "}; ]";
    }
    if (tree->GoRight() != NULL) print_graph(output, tree->GoRight());
    if (tree->GetType() == Sign || tree->GetType() == Function) output << " ]";
    return 0;
}